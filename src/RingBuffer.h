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
    // int maxSize;
} RB_t;

RB_t *RB_InitBuffer(size_t elementSize);
int RB_InsertElement(RB_t *const me, uint16_t element);
int RB_RemoveElement(RB_t *const me, uint16_t *element);
int RB_IsFull(RB_t *const me);
int RB_IsEmpty(RB_t *const me);
void DestroyBuffer(RB_t *const me);

#if defined(__cplusplus)
}
#endif
