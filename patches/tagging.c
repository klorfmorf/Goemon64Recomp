#include "patches.h"

static inline void* memcpy(void* s1, const void* s2, size_t n) {
    char* su1 = (char*)s1;
    const char* su2 = (const char*)s2;
    while (n > 0) {
        *su1 = *su2;
        su1++;
        su2++;
        n--;
    }
    return (void*)s1;
}

/* Not needed?
RECOMP_PATCH void func_801E99CC_5A58DC(ProjectileTask* task, Object *object, s32 type) {
    Object *current_object;

    current_object = (Object *)object->heap_element.next;

    while (current_object != NULL) {

        func_801E8858_5A4768(current_object, 10);

        current_object->scale.x -= D_8020B834_5C7744;
        current_object->scale.y -= D_8020B834_5C7744;
        current_object->scale.z -= D_8020B834_5C7744;
        current_object->position.x += current_object->unknown_88.x;
        current_object->position.x += current_object->unknown_88.y;
        current_object->position.x += current_object->unknown_88.z;

        if (current_object->scale.x <= 0.0f) {
            current_object = (Object *)func_80036158_36D58(&task->task, object->heap_element.next, 1);

            task->unknown_61 -= 1;

            if (type == 0) {
                task->unknown_AA = 2;
            }
        } else {
            current_object = (Object *)current_object->heap_element.next;
        }
    }
}
*/

/* Wrong?
RECOMP_PATCH HeapElement *func_80036158_36D58(Task* task, HeapElement *heap_element, s8 count) {
    HeapElement *task_element;
    HeapElement *current_element;
    HeapElement *next_element;

    task_element = task->heap_element;

    if (task_element == NULL) {
        heap_element = NULL; 
    } else {
        if (task_element == heap_element) {
            task_element = NULL;
        } else {
            if (task_element != NULL) {
                next_element = task_element->next;

                while (next_element != heap_element && next_element != NULL) {
                    next_element = next_element->next;
                }
            }

            if (task_element == NULL) {
                return NULL;
            }
        }

        current_element = heap_element;
        while (count != 0) {
            count--;

            heap_element = func_80035FDC_36BDC(current_element);
            func_80036308_36F08(current_element);

            if (task_element == NULL) {
                task->heap_element = heap_element;
            } else {
                task_element->next = heap_element;
            }

            if (heap_element == NULL) {
                task->heap_element_2 = task_element;

                if (count != 0) {
                    return NULL;

                }
            }

            current_element = heap_element;
        }
    }

    return heap_element;
}
*/

RECOMP_PATCH void func_8000A5C4_B1C4(Object *object) {
    HeapElement *previous_next_element;

    previous_next_element = object->heap_element.next;

    // Clear the object with a default object.
    memcpy(object, &D_8005B974_5C574, sizeof(D_8005B974_5C574));

    object->heap_element.next = previous_next_element;

    // @recomp Skip interpolation on this frame since the object was reset and thus probably transformed a lot.
    object->overlay_info[5].unknown_2[1] |= 0x01;
}

RECOMP_PATCH void func_08002414_715384(SnowGeneratorTask* task, Object *object, u32 type) {
    s32 random_number;
    u32 is_event_set;

    // @recomp Skip interpolation every time this function is called.
    if (object != NULL) {
        object->overlay_info[5].unknown_2[1] |= 0x01;
    }

    switch (type) {
    case 0:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x + 100.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + task->center_position.z;
        break;

    case 1:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x - 70.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + (task->center_position.z + 70.0);
        break;

    case 2:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x - 70.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + (task->center_position.z - 70.0);
        break;

    case 3:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x + 70.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + (task->center_position.z + 70.0);
        break;

    case 4:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x - 100.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + task->center_position.z;
        break;

    case 5:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x + 70.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + (task->center_position.z - 70.0);
        break;
    
    default:
        random_number = (*func_802192B4_5D4784)(30);
        object->position.x = random_number + (task->center_position.x - 70.0);

        random_number = (*func_802192B4_5D4784)(30);
        object->position.z = random_number + (task->center_position.z - 70.0);
        break;
    }

    // This checks if a room-specific event is set.
    is_event_set = func_80023E94_24A94(0);

    if (!is_event_set) {
        if (*(f32 *)(&task->actor_task.pad[0x70]) != 0.0) {
            object->position.y = *(f32 *)(&task->actor_task.pad[0x70]);
            return;
        }
    }

    object->position.y = task->center_position.y + 130.0;
}
