#ifndef INC_RING_BUFFER_IRING_BUFFER
#define INC_RING_BUFFER_IRING_BUFFER

#include <stdint.h>

namespace RingBuffer {

/**
 * @brief Interface for a generic ring buffer (circular buffer).
 * 
 * This interface defines the common operations for a ring buffer, including 
 * initialization, adding/removing elements, and checking the buffer's state 
 * (whether it's full or empty).
 * The ring buffer operates in a first-in, first-out (FIFO) manner, where data is 
 * added to the end of the buffer and removed from the front. If the buffer becomes
 * full, new elements overwrite the oldest elements in the  buffer. This is useful 
 * for scenarios where a fixed-size buffer is required, and losing old data when 
 * the buffer is full is acceptable.
 */
class IRingBuffer
{
  public:
    virtual ~IRingBuffer() = default;

    /**
     * @brief Adds an element to the ring buffer.
     * 
     * Inserts the provided value into the buffer at the head position. If the 
     * buffer is full, the oldest element in the buffer is overwritten by the 
     * new element.
     * 
     * @param value The element to add to the buffer
     * @return true     Success
     * @return false    Element could not be added
     */
    virtual bool Add(uint8_t value) = 0;
    virtual bool Add(uint16_t value) = 0;
    virtual bool Add(uint32_t value) = 0;
    virtual bool Add(uint64_t value) = 0;

    /**
     * @brief Removes an element from the ring buffer.
     * 
     * Removes the oldest element from the buffer (at the tail position) and stores 
     * it in the provided reference. If the buffer is empty, this method returns false.
     * 
     * @param value Reference to store the removed value
     * @return true     Success
     * @return false    Value could not be removed
     */
    virtual bool Remove(uint8_t &value) = 0;
    virtual bool Remove(uint16_t &value) = 0;
    virtual bool Remove(uint32_t &value) = 0;
    virtual bool Remove(uint64_t &value) = 0;

    /**
     * @brief Checks if the ring buffer is empty.
     * 
     * @return true     Buffer is empty
     * @return false    Buffer contains one or more elements
     */
    virtual bool IsEmpty() const = 0;

    /**
     * @brief Checks if the ring buffer is full.
     * 
     * @return true     Buffer is full
     * @return false    Buffer has space for more elements
     */
    virtual bool IsFull() const = 0;
};

} // namespace RingBuffer

#endif /* INC_RING_BUFFER_IRING_BUFFER */
