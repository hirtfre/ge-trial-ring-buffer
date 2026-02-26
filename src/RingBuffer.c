#include "RingBuffer.h"
#include <AbstractionLayer/IMemory.h>
#include <stdlib.h>
// #include <stdio.h>

RB_t *RB_InitBuffer(size_t elementSize)
{
    (void)elementSize;
    RB_t *me = MEM_Calloc(sizeof(RB_t), 1);

    me->array = (int *)MEM_Calloc(BUFFER_CAPACITY, elementSize);
    me->capacity = BUFFER_CAPACITY - 1;
    me->head = 0;
    me->tail = 0;
    me->count = 0;
    // me->maxSize = BUFFER_CAPACITY;

    return me;
}

int RB_InsertElement(RB_t *const me, uint16_t element)
{
    if (RB_IsFull(me))
    {
        // printf("Buffer Overflow\n");
        return -1; // Buffer is full
    }

    me->array[me->head] = element;
    me->head = (me->head + 1) % me->capacity;
    me->count++;

    if (me->head == me->capacity)
        me->head = 0;

    return 0;
}

int RB_RemoveElement(RB_t *const me, uint16_t *element)
{
    if (RB_IsEmpty(me))
    {
        // printf("Buffer Underflow\n");
        return -1; // Buffer is empty
    }

    *element = (uint16_t)me->array[me->tail];
    me->tail = (me->tail + 1) % me->capacity;
    me->count--;

    if (me->tail == me->capacity)
        me->tail = 0;

    return 0;
}

int RB_IsFull(RB_t *me)
{
    return ((me->head + 1) % me->capacity) == me->tail;
}

int RB_IsEmpty(RB_t *me)
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
    // me->capacity = 0;
    // me->head = me->tail = me->count = 0;

    MEM_Free(me);
}