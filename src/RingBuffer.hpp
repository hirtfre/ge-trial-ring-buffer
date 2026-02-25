#ifndef SRC_RING_BUFFER
#define SRC_RING_BUFFER

#include "RingBuffer.h"
#include <RingBuffer/IRingBuffer.h>
#include <stddef.h>
#include <stdint.h>

namespace RingBuffer {

class RingBuffer : public IRingBuffer
{
  public:
    explicit RingBuffer() = default;
    ~RingBuffer();

    /**
     * @brief Initializes the ring buffer.
     * 
     * This method must be called before any other method on the ring buffer.
     * 
     * @return true     Success
     * @return false    Failure
     */
    bool Init(size_t pElementSize);
    bool Add(uint8_t value) override;
    bool Add(uint16_t value) override;
    bool Add(uint32_t value) override;
    bool Add(uint64_t value) override;
    bool Remove(uint8_t &value) override;
    bool Remove(uint16_t &value) override;
    bool Remove(uint32_t &value) override;
    bool Remove(uint64_t &value) override;
    bool IsEmpty() const override;
    bool IsFull() const override;

  private:
    template <typename T> bool AddInteger(T value);
    template <typename T> bool RemoveInteger(T &value);
    RB_t *ringBuffer = nullptr;
    size_t elementSize = 0;
};

} // namespace RingBuffer

#endif /* SRC_RING_BUFFER */
