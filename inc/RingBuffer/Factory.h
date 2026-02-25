#ifndef INC_RING_BUFFER_FACTORY
#define INC_RING_BUFFER_FACTORY

#include "IRingBuffer.h"
#include <stddef.h>

namespace RingBuffer {

/**
 * @brief A factory class to create and destroy instances of RingBuffer.
 */
class Factory
{
  public:
    Factory() = delete;
    ~Factory() = delete;

    /**
     * @brief Creates an instance of a RingBuffer for the given type.
     * 
     * @tparam T The data type for the elements stored in the buffer (e.g., uint16_t, int32_t).
     * @return A pointer to the created IRingBuffer, or nullptr if initialization fails.
     */
    static IRingBuffer *Create(size_t elementSize);

    /**
     * @brief Destroys an instance of an IRingBuffer.
     * 
     * This method deallocates the memory and calls the destructor for the provided 
     * IRingBuffer instance.
     * 
     * @param ringBuffer A pointer to the IRingBuffer pointer. After destruction, the 
     * pointer is set to nullptr.
     */
    static void Destroy(IRingBuffer **ringBuffer);
};

} // namespace RingBuffer

#endif /* INC_RING_BUFFER_FACTORY */
