#include "RingBuffer.hpp"
#include <AbstractionLayer/IMemory.h>
#include <RingBuffer/Factory.h>
#include <new>

namespace RingBuffer {

IRingBuffer *Factory::Create(size_t elementSize)
{
    auto *memory = MEM_Calloc(1, sizeof(RingBuffer));
    RingBuffer *ringBuffer = nullptr;

    if (memory == nullptr)
    {
        goto unable_to_allocate_memory;
    }

    ringBuffer = new (memory) RingBuffer();

    if (!ringBuffer->Init(elementSize))
    {
        goto unable_to_init;
    }

    return ringBuffer;

unable_to_init:
    ringBuffer->~RingBuffer();

unable_to_allocate_memory:
    return nullptr;
}

void Factory::Destroy(IRingBuffer **ringBuffer)
{
    if (ringBuffer == nullptr || *ringBuffer == nullptr)
    {
        return;
    }

    (*ringBuffer)->~IRingBuffer();
    MEM_Free(*ringBuffer);
    *ringBuffer = nullptr;
}

} /* namespace RingBuffer */
