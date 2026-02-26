#include "RingBuffer.h"
#include <AbstractionLayer/IMemory.h>
#include <stdlib.h>

RB_t *RB_InitBuffer(size_t elementSize)
{
    RB_t *me = MEM_Calloc(1, sizeof(RB_t));

    me->array = (int *)MEM_Calloc(1, BUFFER_CAPACITY * elementSize);
    me->capacity = BUFFER_CAPACITY - 1;
    me->head = 0;
    me->tail = 0;
    me->count = 0;

    return me;
}

bool RB_InsertElement(RB_t *const me, uint16_t element)
{
    if (RB_IsFull(me))
    {
        return false; // Buffer is full
    }

    me->array[me->head] = element;
    me->head = (me->head + 1) % me->capacity;
    me->count++;

    if (me->head == me->capacity)
        me->head = 0;

    return true;
}

bool RB_RemoveElement(RB_t *const me, uint16_t *element)
{
    if (RB_IsEmpty(me))
    {
        return false; // Buffer is empty
    }

    *element = (uint16_t)me->array[me->tail];
    me->tail = (me->tail + 1) % me->capacity;
    me->count--;

    if (me->tail == me->capacity)
        me->tail = 0;

    return true;
}

bool RB_IsFull(RB_t *me)
{
    return ((me->head + 1) % me->capacity) == me->tail;
}

bool RB_IsEmpty(RB_t *me)
{
    return me->count == 0;
}

void DestroyBuffer(RB_t *me)
{
    if (me->array != NULL)
    {
        MEM_Free(me->array);
        me->array = NULL;
    }

    MEM_Free(me);
}