#include "RingBuffer.hpp"

namespace RingBuffer {

RingBuffer::~RingBuffer()
{
    DestroyBuffer(ringBuffer);
}

bool RingBuffer::Init(size_t pElementSize)
{
    ringBuffer = RB_InitBuffer(pElementSize);
    elementSize = pElementSize;

    if (ringBuffer == nullptr)
    {
        return false;
    }

    return true;
}

bool RingBuffer::Add(uint8_t value)
{
    if (elementSize < sizeof(uint8_t))
    {
        return false;
    }

    return AddInteger(value);
}

bool RingBuffer::Add(uint16_t value)
{
    if (elementSize < sizeof(uint16_t))
    {
        return false;
    }

    return AddInteger(value);
}

bool RingBuffer::Add(uint32_t value)
{
    if (elementSize < sizeof(uint32_t))
    {
        return false;
    }

    return AddInteger(value);
}

bool RingBuffer::Add(uint64_t value)
{
    if (elementSize < sizeof(uint64_t))
    {
        return false;
    }

    return AddInteger(value);
}

bool RingBuffer::Remove(uint8_t &value)
{
    if (elementSize < sizeof(uint8_t))
    {
        return false;
    }

    return RemoveInteger(value);
}

bool RingBuffer::Remove(uint16_t &value)
{
    if (elementSize < sizeof(uint16_t))
    {
        return false;
    }

    return RemoveInteger(value);
}

bool RingBuffer::Remove(uint32_t &value)
{
    if (elementSize < sizeof(uint32_t))
    {
        return false;
    }

    return RemoveInteger(value);
}

bool RingBuffer::Remove(uint64_t &value)
{
    if (elementSize < sizeof(uint64_t))
    {
        return false;
    }

    return RemoveInteger(value);
}

template <typename T> bool RingBuffer::AddInteger(T value)
{
    /** @todo Remove cast when c implementation supports other integer types*/
    return RB_InsertElement(ringBuffer, static_cast<uint16_t>(value));
}

template <typename T> bool RingBuffer::RemoveInteger(T &value)
{
    /** @todo Remove cast when c implementation supports other integer types*/
    return RB_RemoveElement(ringBuffer, reinterpret_cast<uint16_t *>(&value));
}

bool RingBuffer::IsFull() const
{
    return RB_IsFull(ringBuffer);
}

bool RingBuffer::IsEmpty() const
{
    return RB_IsEmpty(ringBuffer);
}

} // namespace RingBuffer
