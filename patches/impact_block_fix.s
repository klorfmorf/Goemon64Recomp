.include "macro.inc"

.set noat
.set noreorder

.section .recomp_patch, "ax"

glabel func_801DD218_6085F8
    /* 6085F8 801DD218 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 6085FC 801DD21C AFBF0014 */  sw         $ra, 0x14($sp)
    /* 608600 801DD220 AFA40020 */  sw         $a0, 0x20($sp)
    /* 608604 801DD224 AFA50024 */  sw         $a1, 0x24($sp)
    /* 608608 801DD228 3C014080 */  lui        $at, (0x40800000 >> 16)
    /* 60860C 801DD22C 44813000 */  mtc1       $at, $f6
    /* 608610 801DD230 C48400A0 */  lwc1       $f4, 0xA0($a0)
    /* 608614 801DD234 3C014120 */  lui        $at, (0x41200000 >> 16)
    /* 608618 801DD238 44818000 */  mtc1       $at, $f16
    /* 60861C 801DD23C 46062200 */  add.s      $f8, $f4, $f6
    /* 608620 801DD240 00802825 */  or         $a1, $a0, $zero
    /* 608624 801DD244 240F0028 */  addiu      $t7, $zero, 0x28
    /* 608628 801DD248 E48800A0 */  swc1       $f8, 0xA0($a0)
    /* 60862C 801DD24C C48A00A0 */  lwc1       $f10, 0xA0($a0)
    /* 608630 801DD250 8FAE001C */  lw         $t6, 0x1C($sp)
    /* 608634 801DD254 460A803E */  c.le.s     $f16, $f10
    /* 608638 801DD258 00000000 */  nop
    /* 60863C 801DD25C 45020009 */  bc1fl      .L801DD284_608664
    /* 608640 801DD260 3C0141F0 */   lui       $at, (0x41F00000 >> 16)
/* This crashes because it is trying to access an unitialized local variable. */
/* Seems to read an actual pointer off of the stack on real hardware and emulators by chance. */
/* It actually writes a zero byte into a really important function `func_80034734_35334` here. */
/* Based on patterns from the caller and callees the local variable would have been initialized to: */
/* local = 0x802F7000 + 0x140 */
/*     608644 801DD264 A1C0000D     sb         $zero, 0xD($t6) */
    /* 608648 801DD268 AC8F007C */  sw         $t7, 0x7C($a0)
    /* 60864C 801DD26C 3C04801E */  lui        $a0, %hi(func_801DCF18_6082F8)
    /* 608650 801DD270 2484CF18 */  addiu      $a0, $a0, %lo(func_801DCF18_6082F8)
    /* 608654 801DD274 0C00D487 */  jal        func_8003521C_35E1C
    /* 608658 801DD278 AFA50020 */   sw        $a1, 0x20($sp)
    /* 60865C 801DD27C 8FA50020 */  lw         $a1, 0x20($sp)
    /* 608660 801DD280 3C0141F0 */  lui        $at, (0x41F00000 >> 16)
  .L801DD284_608664:
    /* 608664 801DD284 44810000 */  mtc1       $at, $f0
    /* 608668 801DD288 3C0140A0 */  lui        $at, (0x40A00000 >> 16)
    /* 60866C 801DD28C 44812000 */  mtc1       $at, $f4
    /* 608670 801DD290 C4B2009C */  lwc1       $f18, 0x9C($a1)
    /* 608674 801DD294 3C01C20C */  lui        $at, (0xC20C0000 >> 16)
    /* 608678 801DD298 46049181 */  sub.s      $f6, $f18, $f4
    /* 60867C 801DD29C E4A6009C */  swc1       $f6, 0x9C($a1)
    /* 608680 801DD2A0 C4A8009C */  lwc1       $f8, 0x9C($a1)
    /* 608684 801DD2A4 4600403E */  c.le.s     $f8, $f0
    /* 608688 801DD2A8 00000000 */  nop
    /* 60868C 801DD2AC 45020003 */  bc1fl      .L801DD2BC_60869C
    /* 608690 801DD2B0 8CB80094 */   lw        $t8, 0x94($a1)
    /* 608694 801DD2B4 E4A0009C */  swc1       $f0, 0x9C($a1)
    /* 608698 801DD2B8 8CB80094 */  lw         $t8, 0x94($a1)
  .L801DD2BC_60869C:
    /* 60869C 801DD2BC 57000010 */  bnel       $t8, $zero, .L801DD300_6086E0
    /* 6086A0 801DD2C0 44810000 */   mtc1      $at, $f0
    /* 6086A4 801DD2C4 3C01420C */  lui        $at, (0x420C0000 >> 16)
    /* 6086A8 801DD2C8 44810000 */  mtc1       $at, $f0
    /* 6086AC 801DD2CC 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* 6086B0 801DD2D0 44818000 */  mtc1       $at, $f16
    /* 6086B4 801DD2D4 C4AA0098 */  lwc1       $f10, 0x98($a1)
    /* 6086B8 801DD2D8 46105481 */  sub.s      $f18, $f10, $f16
    /* 6086BC 801DD2DC E4B20098 */  swc1       $f18, 0x98($a1)
    /* 6086C0 801DD2E0 C4A40098 */  lwc1       $f4, 0x98($a1)
    /* 6086C4 801DD2E4 4600203E */  c.le.s     $f4, $f0
    /* 6086C8 801DD2E8 00000000 */  nop
    /* 6086CC 801DD2EC 4500000F */  bc1f       .L801DD32C_60870C
    /* 6086D0 801DD2F0 00000000 */   nop
    /* 6086D4 801DD2F4 1000000D */  b          .L801DD32C_60870C
    /* 6086D8 801DD2F8 E4A00098 */   swc1      $f0, 0x98($a1)
    /* 6086DC 801DD2FC 44810000 */  mtc1       $at, $f0
  .L801DD300_6086E0:
    /* 6086E0 801DD300 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* 6086E4 801DD304 44814000 */  mtc1       $at, $f8
    /* 6086E8 801DD308 C4A60098 */  lwc1       $f6, 0x98($a1)
    /* 6086EC 801DD30C 46083280 */  add.s      $f10, $f6, $f8
    /* 6086F0 801DD310 E4AA0098 */  swc1       $f10, 0x98($a1)
    /* 6086F4 801DD314 C4B00098 */  lwc1       $f16, 0x98($a1)
    /* 6086F8 801DD318 4610003E */  c.le.s     $f0, $f16
    /* 6086FC 801DD31C 00000000 */  nop
    /* 608700 801DD320 45000002 */  bc1f       .L801DD32C_60870C
    /* 608704 801DD324 00000000 */   nop
    /* 608708 801DD328 E4A00098 */  swc1       $f0, 0x98($a1)
  .L801DD32C_60870C:
    /* 60870C 801DD32C 0C0774F7 */  jal        func_801DD3DC_6087BC
    /* 608710 801DD330 00A02025 */   or        $a0, $a1, $zero
    /* 608714 801DD334 8FBF0014 */  lw         $ra, 0x14($sp)
    /* 608718 801DD338 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 60871C 801DD33C 03E00008 */  jr         $ra
    /* 608720 801DD340 00000000 */   nop
    /* 608724 801DD344 03E00008 */  jr         $ra
    /* 608728 801DD348 00000000 */   nop
endlabel func_801DD218_6085F8

glabel func_801DD134_608514
    /* 608514 801DD134 27BDFFE0 */  addiu      $sp, $sp, -0x20
    /* 608518 801DD138 AFBF0014 */  sw         $ra, 0x14($sp)
    /* 60851C 801DD13C AFA50024 */  sw         $a1, 0x24($sp)
    /* 608520 801DD140 8C8E007C */  lw         $t6, 0x7C($a0)
    /* 608524 801DD144 3C0140A0 */  lui        $at, (0x40A00000 >> 16)
    /* 608528 801DD148 51C00013 */  beql       $t6, $zero, .L801DD198_608578
    /* 60852C 801DD14C 44810000 */   mtc1      $at, $f0
    /* 608530 801DD150 3C014170 */  lui        $at, (0x41700000 >> 16)
    /* 608534 801DD154 44810000 */  mtc1       $at, $f0
    /* 608538 801DD158 C484009C */  lwc1       $f4, 0x9C($a0)
    /* 60853C 801DD15C 8C8F0094 */  lw         $t7, 0x94($a0)
    /* 608540 801DD160 46002181 */  sub.s      $f6, $f4, $f0
    /* 608544 801DD164 15E00005 */  bnez       $t7, .L801DD17C_60855C
    /* 608548 801DD168 E486009C */   swc1      $f6, 0x9C($a0)
    /* 60854C 801DD16C C4880098 */  lwc1       $f8, 0x98($a0)
    /* 608550 801DD170 46004281 */  sub.s      $f10, $f8, $f0
    /* 608554 801DD174 10000004 */  b          .L801DD188_608568
    /* 608558 801DD178 E48A0098 */   swc1      $f10, 0x98($a0)
  .L801DD17C_60855C:
    /* 60855C 801DD17C C4900098 */  lwc1       $f16, 0x98($a0)
    /* 608560 801DD180 46008480 */  add.s      $f18, $f16, $f0
    /* 608564 801DD184 E4920098 */  swc1       $f18, 0x98($a0)
  .L801DD188_608568:
    /* 608568 801DD188 8FA2001C */  lw         $v0, 0x1C($sp)
    /* 60856C 801DD18C 1000000E */  b          .L801DD1C8_6085A8
    /* 608570 801DD190 A0400003      sb        $zero, 0x3($v0) */
    /* 608574 801DD194 44810000 */  mtc1       $at, $f0
  .L801DD198_608578:
    /* 608578 801DD198 C484009C */  lwc1       $f4, 0x9C($a0)
    /* 60857C 801DD19C 8C980094 */  lw         $t8, 0x94($a0)
    /* 608580 801DD1A0 46002181 */  sub.s      $f6, $f4, $f0
    /* 608584 801DD1A4 17000005 */  bnez       $t8, .L801DD1BC_60859C
    /* 608588 801DD1A8 E486009C */   swc1      $f6, 0x9C($a0)
    /* 60858C 801DD1AC C4880098 */  lwc1       $f8, 0x98($a0)
    /* 608590 801DD1B0 46004281 */  sub.s      $f10, $f8, $f0
    /* 608594 801DD1B4 10000004 */  b          .L801DD1C8_6085A8
    /* 608598 801DD1B8 E48A0098 */   swc1      $f10, 0x98($a0)
  .L801DD1BC_60859C:
    /* 60859C 801DD1BC C4900098 */  lwc1       $f16, 0x98($a0)
    /* 6085A0 801DD1C0 46008480 */  add.s      $f18, $f16, $f0
    /* 6085A4 801DD1C4 E4920098 */  swc1       $f18, 0x98($a0)
  .L801DD1C8_6085A8:
    /* 6085A8 801DD1C8 44802000 */  mtc1       $zero, $f4
    /* 6085AC 801DD1CC C486009C */  lwc1       $f6, 0x9C($a0)
    /* 6085B0 801DD1D0 3C028021 */  lui        $v0, %hi(D_8020EED0_63A2B0)
    /* 6085B4 801DD1D4 4604303E */  c.le.s     $f6, $f4
    /* 6085B8 801DD1D8 00000000 */  nop
    /* 6085BC 801DD1DC 45000008 */  bc1f       .L801DD200_6085E0
    /* 6085C0 801DD1E0 00000000 */   nop
    /* 6085C4 801DD1E4 8C42EED0 */  lw         $v0, %lo(D_8020EED0_63A2B0)($v0)
    /* 6085C8 801DD1E8 24420140 */  addiu      $v0, $v0, 0x140
    /* 6085CC 801DD1EC A040000C */  sb         $zero, 0xC($v0)
    /* 6085D0 801DD1F0 0C00D3B5 */  jal        func_80034ED4_35AD4
    /* 6085D4 801DD1F4 A040000D */   sb        $zero, 0xD($v0)
    /* 6085D8 801DD1F8 10000004 */  b          .L801DD20C_6085EC
    /* 6085DC 801DD1FC 8FBF0014 */   lw        $ra, 0x14($sp)
  .L801DD200_6085E0:
    /* 6085E0 801DD200 0C0774F7 */  jal        func_801DD3DC_6087BC
    /* 6085E4 801DD204 00000000 */   nop
    /* 6085E8 801DD208 8FBF0014 */  lw         $ra, 0x14($sp)
  .L801DD20C_6085EC:
    /* 6085EC 801DD20C 27BD0020 */  addiu      $sp, $sp, 0x20
    /* 6085F0 801DD210 03E00008 */  jr         $ra
    /* 6085F4 801DD214 00000000 */   nop
endlabel func_801DD134_608514