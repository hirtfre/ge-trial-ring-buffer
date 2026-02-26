#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#define BUFFER_CAPACITY 16

#if defined(__cplusplus)
extern "C" {
#endif

typedef struct
{
    uint8_t capacity;
    short count;
    int *array;
    int head;
    int tail;
} RB_t;

RB_t *RB_InitBuffer(size_t elementSize);

/*
 * Return: true if insert element is successful 
 */
bool RB_InsertElement(RB_t *const me, uint16_t element);

/*
 * Return: true if remove element is successful 
 */
bool RB_RemoveElement(RB_t *const me, uint16_t *element);

/*
 * Return: true if buffer is full
 */
bool RB_IsFull(RB_t *const me);

/*
 * Return: true if buffer is empty 
 */
bool RB_IsEmpty(RB_t *const me);
void DestroyBuffer(RB_t *const me);

#if defined(__cplusplus)
}
#endif
