#include "patches.h"

/*====================================================================
 * 
 * Copyright 1995, Silicon Graphics, Inc.
 * All Rights Reserved.
 * This is UNPUBLISHED PROPRIETARY SOURCE CODE of Silicon Graphics,
 * Inc.; the contents of this file may not be disclosed to third
 * parties, copied or duplicated in any form, in whole or in part,
 * without the prior written permission of Silicon Graphics, Inc.
 *
 * RESTRICTED RIGHTS LEGEND:
 * Use, duplication or disclosure by the Government is subject to
 * restrictions as set forth in subdivision (c)(1)(ii) of the Rights
 * in Technical Data and Computer Software clause at DFARS
 * 252.227-7013, and/or in similar or successor clauses in the FAR,
 * DOD or NASA FAR Supplement. Unpublished - rights reserved under the
 * Copyright Laws of the United States.
 *====================================================================*/
#include <ultralog.h>
#include <assert.h>
#include "sched.h"

// @recomp
#define osCreateScheduler func_80006DF0_79F0
#define osScAddClient func_80006F3C_7B3C
#define osScRemoveClient func_80006F8C_7B8C
#define osScGetCmdQ func_80007014_7C14
#define osScGetUnknownQ func_8000701C_7C1C
#define osScGetInterruptQ func_80007024_7C24

extern OSViMode D_80079500_7A100[];

/*
 * private typedefs and defines
 */
#define VIDEO_MSG       666
#define RSP_DONE_MSG    667
#define RDP_DONE_MSG    668
#define PRE_NMI_MSG     669

/*
 * OSScTask state
 */
#define OS_SC_DP                0x0001  /* set if still needs dp        */
#define OS_SC_SP                0x0002  /* set if still needs sp        */
#define OS_SC_YIELD             0x0010  /* set if yield requested       */
#define OS_SC_YIELDED           0x0020  /* set if yield completed       */

/*
 * OSScTask->flags type identifier
 */
#define OS_SC_XBUS      (OS_SC_SP | OS_SC_DP)
#define OS_SC_DRAM      (OS_SC_SP | OS_SC_DP | OS_SC_DRAM_DLIST)
#define OS_SC_DP_XBUS   (OS_SC_SP)
#define OS_SC_DP_DRAM   (OS_SC_SP | OS_SC_DRAM_DLIST)
#define OS_SC_SP_XBUS   (OS_SC_DP)
#define OS_SC_SP_DRAM   (OS_SC_DP | OS_SC_DRAM_DLIST)

/*
 * private functions
 */
static void     __scMain(void *arg);
static void     __scHandleGraphicsTask(OSSched *s, OSScTask *task);
static void     __scHandleRetrace(OSSched *s);
static void     __scHandleRSP(OSSched *s);
static void     __scHandleRDP(OSSched *s);

static void     __scAppendList(OSSched *s, OSScTask *t);
OSScTask        *__scTaskReady(OSScTask *t);
static s32      __scTaskComplete(OSSched *s,OSScTask *t);
static void     __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp);
static void	__scYield(OSSched *s);
static s32      __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp,
                             s32 availRCP);


/*
#define SC_LOGGING 1
*/


#ifdef SC_LOGGING
#define SC_LOG_LEN      32*1024
static OSLog    scLog;
static OSLog    *l = &scLog;
static u32      logArray[SC_LOG_LEN/sizeof(u32)];
#endif

static OSScTask *currentGfxTask;
static u8       runningNonGfxTask;

/***********************************************************************
 * Scheduler API
 **********************************************************************/
RECOMP_PATCH void osCreateScheduler(OSSched *sc, void *stack, OSPri priority,
                       u8 mode, u8 numFields)
{
    sc->curRSPTask      = 0;
    sc->curRDPTask      = 0;
    sc->clientList      = 0;
    sc->frameCount      = 0;
    sc->audioListHead   = 0;
    sc->gfxListHead     = 0;
    sc->audioListTail   = 0;
    sc->gfxListTail     = 0;
    sc->retraceMsg.type = OS_SC_RETRACE_MSG;  /* sent to apps */
    sc->prenmiMsg.type  = OS_SC_PRE_NMI_MSG;

    currentGfxTask = NULL;
    runningNonGfxTask = FALSE;
    
    osCreateMesgQueue(&sc->interruptQ, sc->intBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->cmdQ, sc->cmdMsgBuf, OS_SC_MAX_MESGS);
    osCreateMesgQueue(&sc->unknownQ, sc->unknownBuf, OS_SC_MAX_MESGS);

    /*
     * Set up video manager, listen for Video, RSP, and RDP interrupts
     */
    osCreateViManager(OS_PRIORITY_VIMGR);    
    osViSetMode(&D_80079500_7A100[mode]);
    osViBlack(TRUE);
    osSetEventMesg(OS_EVENT_SP, &sc->interruptQ, (OSMesg)RSP_DONE_MSG);
    osSetEventMesg(OS_EVENT_DP, &sc->interruptQ, (OSMesg)RDP_DONE_MSG);    
    osSetEventMesg(OS_EVENT_PRENMI, &sc->interruptQ, (OSMesg)PRE_NMI_MSG);    

    osViSetEvent(&sc->interruptQ, (OSMesg)VIDEO_MSG, numFields);    

#ifdef SC_LOGGING    
    osCreateLog(l, logArray, sizeof(logArray));
#endif

    osCreateThread(&sc->thread, 4, __scMain, (void *)sc, stack, priority);
    osStartThread(&sc->thread);
}

/*
 * Add a client to the scheduler.  Clients receive messages at retrace time
 */
RECOMP_PATCH void osScAddClient(OSSched *sc, OSScClient *c, OSMesgQueue *msgQ)
{
    OSIntMask mask;

    mask = osSetIntMask(OS_IM_NONE);

    c->msgQ = msgQ;
    c->next = sc->clientList;
    sc->clientList = c;

    osSetIntMask(mask);
}

RECOMP_PATCH void osScRemoveClient(OSSched *sc, OSScClient *c)
{
    OSScClient *client = sc->clientList; 
    OSScClient *prev   = 0;
    OSIntMask  mask;

    mask = osSetIntMask(OS_IM_NONE);
    
    while (client != 0) {
        if (client == c) {
	    if(prev)
		prev->next = c->next;
	    else
		sc->clientList = c->next;
            break;
        }
        prev   = client;
        client = client->next;
    }

    osSetIntMask(mask);
}

RECOMP_PATCH OSMesgQueue *osScGetCmdQ(OSSched *sc)
{
    return &sc->cmdQ;
}

RECOMP_PATCH OSMesgQueue *osScGetUnknownQ(OSSched *sc)
{
    return &sc->unknownQ;
}

RECOMP_PATCH OSMesgQueue *osScGetInterruptQ(OSSched *sc)
{
    return &sc->interruptQ;
}

/***********************************************************************
 * Scheduler implementation
 **********************************************************************/
static void __scMain(void *arg)
{
    OSMesg msg;
    OSSched *sc = (OSSched *)arg;
    OSScClient *client;
    static int count = 0;
    
    while (1) {
        
        osRecvMesg(&sc->interruptQ, (OSMesg *)&msg, OS_MESG_BLOCK);

#ifdef SC_LOGGING 
        if (++count % 1024 == 0)
            osFlushLog(l);
#endif
        

        switch ((int) msg) {
            case (VIDEO_MSG):
                __scHandleRetrace(sc);
                break;

            case (RSP_DONE_MSG):
                __scHandleRSP(sc);
                break;

            case (RDP_DONE_MSG):
                __scHandleRDP(sc);
                break;

            case (PRE_NMI_MSG):
            /*
            * notify audio and graphics threads to fade out
            */
                for (client = sc->clientList;client != 0;client = client->next) {
                    osSendMesg(client->msgQ, (OSMesg) &sc->prenmiMsg,
                                OS_MESG_NOBLOCK);
                }
                break;

            default:
                __scHandleGraphicsTask(sc, (OSScTask *)msg);
                break;
        }
    }
}

void __scHandleGraphicsTask(OSSched *sc, OSScTask *task)
{
    s32 state;
    OSScTask *sp = 0;
    OSScTask *dp = 0;

    sc->frameCount++;

    if (task != currentGfxTask) {
        currentGfxTask = task;

        __scAppendList(sc, task);

        state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
        if ( __scSchedule (sc, &sp, &dp, state) != state && !runningNonGfxTask)
            __scExec(sc, sp, dp);
    }
}

/*
 * scHandleRetrace()
 */
static int dp_busy = 0;
static int dpCount = 0;

void __scHandleRetrace(OSSched *sc)
{
    OSScTask    *rspTask;
    OSScClient  *client;
    s32         i;
    s32         state;
    OSScTask    *sp = 0;
    OSScTask    *dp = 0;
    
    sc->frameCount++;
    
#ifdef SC_LOGGING
    osLogEvent(l, 500, 4, sc->frameCount, sc->curRSPTask, sc->curRDPTask);
#endif

    /*
     * Read the task command queue and schedule tasks
     */
    while (osRecvMesg(&sc->cmdQ, (OSMesg *)&rspTask, OS_MESG_NOBLOCK) != -1) {
        __scAppendList(sc, rspTask);
    }
    
    if (sc->doAudio && sc->curRSPTask) {
        /*
         * Preempt the running gfx task.  Note: if the RSP
         * component of the graphics task has finished, but the
         * RDP component is still running, we can start an audio
         * task which will freeze the RDP (and save the RDP cmd
         * FIFO) while the audio RSP code is running.
         */
        __scYield(sc);
    } else {
        state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
        if ( __scSchedule (sc, &sp, &dp, state) != state)
            __scExec(sc, sp, dp);
    }
    
    /*
     * notify audio and graphics threads to start building the command
     * lists for the next frame (client threads may choose not to
     * build the list in overrun case)
     */
    for (client = sc->clientList; client != 0; client = client->next) {
        osSendMesg(client->msgQ, (OSMesg) &sc->retraceMsg, OS_MESG_NOBLOCK);
    }
}

/*
 * __scHandleRSP is called when an RSP task signals that it has
 * finished or yielded (at the hosts request)
 */
void __scHandleRSP(OSSched *sc)
{
    OSScTask *t, *sp = 0, *dp = 0;
    s32 state;

    
    assert(sc->curRSPTask);

    t = sc->curRSPTask;
    sc->curRSPTask = 0;
    
#ifdef SC_LOGGING    
    osLogEvent(l, 510, 3, t, t->state, t->flags);
#endif
    
    if (t->list.t.type != M_GFXTASK) {
        runningNonGfxTask = FALSE;
    }

    if ((t->state & OS_SC_YIELD) && osSpTaskYielded_recomp(&t->list)) {
        t->state |= OS_SC_YIELDED;
#ifndef _FINALROM
	t->totalTime += osGetTime() - t->startTime;
#endif
        if ((t->flags & OS_SC_TYPE_MASK) == OS_SC_XBUS) {
            /* push the task back on the list */
            t->next = sc->gfxListHead;
            sc->gfxListHead = t;
            if (sc->gfxListTail == 0)
                sc->gfxListTail = t;
        }
        
#ifdef SC_LOGGING
        osLogEvent(l, 521, 1, t);
#endif
        
    } else {
        t->state &= ~OS_SC_NEEDS_RSP;
        __scTaskComplete(sc, t);
    }

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule (sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}

/*
 * __scHandleRDP is called when an RDP task signals that it has
 * finished
 */
void __scHandleRDP(OSSched *sc)
{
    OSScTask *t, *sp = 0, *dp = 0; 
    s32 state;
        
    assert(sc->curRDPTask);
    assert(sc->curRDPTask->list.t.type == M_GFXTASK);
    
    t = sc->curRDPTask;
    sc->curRDPTask = 0;
    
#ifdef SC_LOGGING    
    osLogEvent(l, 515, 3, t, t->state, t->flags);
#endif

    t->state &= ~OS_SC_NEEDS_RDP;

    __scTaskComplete(sc, t);

    state = ((sc->curRSPTask == 0) << 1) | (sc->curRDPTask == 0);
    if ( (__scSchedule (sc, &sp, &dp, state)) != state)
        __scExec(sc, sp, dp);
}

/*
 * __scTaskReady checks to see if the graphics task is able to run
 * based on the current state of the RCP.
 */
OSScTask *__scTaskReady(OSScTask *t) 
{
    int rv = 0;
    void *a;
    void *b;    

    if (t) {    
        /*
         * If there is a pending swap bail out til later (next
         * retrace).
         */
        if ((a=osViGetCurrentFramebuffer()) != (b=osViGetNextFramebuffer())) {
#ifdef SC_LOGGING
            osLogEvent(l, 513, 2, a, b);
#endif            
            return 0;
        }

        return t;
    }

    return 0;
}

/*
 * __scTaskComplete checks to see if the task is complete (all RCP
 * operations have been performed) and sends the done message to the
 * client if it is.
 */
s32 __scTaskComplete(OSSched *sc, OSScTask *t) 
{
    int rv;
    static int firsttime = 1;

    if ((t->state & OS_SC_RCP_MASK) == 0) { /* none of the needs bits set */

        assert (t->msgQ);

#ifndef _FINALROM
	t->totalTime += osGetTime() - t->startTime;
#endif
	
#ifdef SC_LOGGING
        osLogEvent(l, 504, 1, t);
#endif
        rv = osSendMesg(t->msgQ, t->msg, OS_MESG_BLOCK);

	if (t->list.t.type == M_GFXTASK) {
            if ((t->flags & OS_SC_SWAPBUFFER) && (t->flags & OS_SC_LAST_TASK)){
		if (firsttime) {
    		    osViBlack(FALSE);
		    firsttime = 0;
		}
                osViSwapBuffer(t->frame_buffer);
#ifdef SC_LOGGING
            osLogEvent(l, 525, 1, t->frame_buffer);
#endif
            }
	}
        return 1;
    }
    
    return 0;
}

/*
 * Place task on either the audio or graphics queue
 */
void __scAppendList(OSSched *sc, OSScTask *t) 
{
    long type = t->list.t.type;
    
    assert ( (type == M_AUDTASK) || (type == M_GFXTASK));
    
    if (type == M_AUDTASK) {
        if (sc->audioListTail)
            sc->audioListTail->next = t;
        else
            sc->audioListHead = t;
            
        sc->audioListTail = t;
        sc->doAudio = 1;
#ifdef SC_LOGGING
        osLogEvent(l, 506, 1, t);
#endif
    } else {
        if (sc->gfxListTail)
            sc->gfxListTail->next = t;
        else
            sc->gfxListHead = t;
        
	sc->gfxListTail = t;
#ifdef SC_LOGGING
        osLogEvent(l, 507, 1, t);
#endif
    }
    
    t->next = NULL;
    t->state = t->flags & OS_SC_RCP_MASK;    
}

/*
 * 
 */
void __scExec(OSSched *sc, OSScTask *sp, OSScTask *dp)
{
    int rv;
    
#ifdef SC_LOGGING
    osLogEvent(l, 511, 2, sp, dp);
#endif

    assert(sc->curRSPTask == 0);

    if (sp) {
        if (sp->list.t.type == M_AUDTASK) {
            osWritebackDCacheAll();  /* flush the cache */
        }
    
        sp->state &= ~(OS_SC_YIELD | OS_SC_YIELDED);
#ifndef _FINALROM
	sp->startTime = osGetTime();
#endif
        if (sp->list.t.type != M_GFXTASK) {
            runningNonGfxTask = TRUE;
        }

        osSpTaskLoad_recomp(&sp->list);
        osSpTaskStartGo_recomp(&sp->list);    
        sc->curRSPTask = sp;
        if (sp == dp)
            sc->curRDPTask = dp;
    }

    if (dp && (dp != sp)) {
        assert(dp->list.t.output_buff);
    
#ifdef SC_LOGGING
        osLogEvent(l, 523, 3, dp, dp->list.t.output_buff,
                   (u32)*dp->list.t.output_buff_size);
#endif
        rv = osDpSetNextBuffer(dp->list.t.output_buff,
                               *dp->list.t.output_buff_size);

        dp_busy = 1;
        dpCount = 0;
        
        assert(rv == 0);
        
        sc->curRDPTask = dp;
    }
}

static void __scYield(OSSched *sc) 
{

#ifdef SC_LOGGING
    osLogEvent(l, 503, 1, sc->curRSPTask );
#endif
    
    if (sc->curRSPTask->list.t.type == M_GFXTASK) {
    
/*	assert(sc->curRSPTask->state & OS_SC_YIELD);*/

        sc->curRSPTask->state |= OS_SC_YIELD;

        osSpTaskYield_recomp();
    } else {
#ifdef SC_LOGGING
        osLogEvent(l, 508, 1, sc->curRSPTask);
#endif        
    }    
}

/*
 * Schedules the tasks to be run on the RCP
 */
s32 __scSchedule(OSSched *sc, OSScTask **sp, OSScTask **dp, s32 availRCP) 
{
    s32 avail = availRCP;
    OSScTask *gfx = sc->gfxListHead;
    OSScTask *audio = sc->audioListHead;

#ifdef SC_LOGGING
    osLogEvent(l, 517, 3, *sp, *dp, availRCP);
#endif    

    if (sc->doAudio && (avail & OS_SC_SP)) {

        if (gfx && (gfx->flags & OS_SC_PARALLEL_TASK)) {
            *sp = gfx;
            avail &= ~OS_SC_SP;
        } else {
            *sp = audio;
            avail &= ~OS_SC_SP;
            sc->doAudio = 0;
            sc->audioListHead = sc->audioListHead->next;
            if (sc->audioListHead == NULL)
                sc->audioListTail = NULL; 
        }        
    } else {            
#ifdef SC_LOGGING
        osLogEvent(l, 520, 1, gfx);
#endif        
        if (__scTaskReady(gfx)) {            

#ifdef SC_LOGGING
            osLogEvent(l, 522, 3, gfx, gfx->state, gfx->flags);
#endif        
            switch (gfx->flags & OS_SC_TYPE_MASK) {
              case (OS_SC_XBUS):
                  if (gfx->state & OS_SC_YIELDED) {
#ifdef SC_LOGGING
                      osLogEvent(l, 518, 0);
#endif                      
		      /* can hit this if RDP finishes at yield req */
                      /* assert(gfx->state & OS_SC_DP); */

                      if (avail & OS_SC_SP) {   /* if SP is available */
#ifdef SC_LOGGING
                      osLogEvent(l, 519, 0);
#endif                      
                          *sp = gfx;
                          avail &= ~OS_SC_SP;
                      
                          if (gfx->state & OS_SC_DP) {  /* if it needs DP */
                              *dp = gfx;
                              avail &= ~OS_SC_DP;

                              if (avail & OS_SC_DP == 0)
                                  assert(sc->curRDPTask == gfx);
                              
                          }

                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                          
                      }                  
                  } else {
                      if (avail == (OS_SC_SP | OS_SC_DP)) {
                          *sp = *dp = gfx;
                          avail &= ~(OS_SC_SP | OS_SC_DP);
                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                      }
                  }
                      
                  break;
          
              case (OS_SC_DRAM):
              case (OS_SC_DP_DRAM):
              case (OS_SC_DP_XBUS):
                  if (gfx->state & OS_SC_SP) {  /* if needs SP */
                      if (avail & OS_SC_SP) {   /* if SP is available */
                          *sp = gfx;
                          avail &= ~OS_SC_SP;
                      }
                  } else if (gfx->state & OS_SC_DP) {   /* if needs DP */
                      if (avail & OS_SC_DP) {        /* if DP available */
                          *dp = gfx;
                          avail &= ~OS_SC_DP;
                          sc->gfxListHead = sc->gfxListHead->next;
                          if (sc->gfxListHead == NULL)
                              sc->gfxListTail = NULL;
                      }
                  }
                  break;

              case (OS_SC_SP_DRAM):
              case (OS_SC_SP_XBUS):
              default:
                  break;
            }
        }
    }

    if (avail != availRCP)
        avail = __scSchedule(sc, sp, dp, avail);

    return avail;
    
}
