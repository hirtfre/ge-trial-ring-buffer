#include "../../src/RingBuffer.hpp"
#include "../submodules/AbstractionLayer/mock/MemoryMock.h"
#include <RingBuffer/Factory.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace RingBuffer {
namespace Test {

class RingBufferTest : public ::testing::Test
{
  protected:
    IRingBuffer *uut = nullptr;
    testing::NiceMock<AbstractionLayer::MemoryMock> memoryMock;

    uint8_t uint8Value = 34;
    uint16_t uint16Value = 435;
    uint32_t uint32Value = 346464;
    uint64_t uint64Value = 343645634577;

    static constexpr uint8_t capacity = 16;

    void SetUp() override
    {
        uut = Factory::Create(sizeof(uint16_t));
        EXPECT_NE(uut, nullptr);
    }

    void TearDown() override
    {
        Factory::Destroy(&uut);
    }
};

class Add : public RingBufferTest
{
};

TEST_F(Add, Should_ReturnTrue_If_ElementSizeEqualOrSmaller)
{
    bool result = uut->Add(uint8Value);
    EXPECT_TRUE(result);

    result = uut->Add(uint16Value);
    EXPECT_TRUE(result);
}

TEST_F(Add, Should_ReturnFalse_If_ElementSizeBigger)
{
    bool result = uut->Add(uint32Value);
    EXPECT_FALSE(result);

    result = uut->Add(uint64Value);
    EXPECT_FALSE(result);
}

TEST_F(Add, Should_ReturnTrue_If_AddingMoreElementsThanCapacity)
{
    for (uint8_t i = 0; i < capacity; i++)
    {
        uut->Add(uint8Value);
    }

    bool result = uut->Add(uint8Value);
    EXPECT_TRUE(result);
}

class Remove : public RingBufferTest
{
};

TEST_F(Remove, Should_ReturnFalse_If_BufferEmpty)
{
    bool result = uut->Remove(uint16Value);
    EXPECT_FALSE(result);
}

TEST_F(Remove, Should_ReturnTrueAndAddedValue_If_ElementAdded)
{
    const uint16_t expectedValue = uint16Value;
    uut->Add(uint16Value);

    bool result = uut->Remove(uint16Value);
    EXPECT_EQ(expectedValue, uint16Value);
    EXPECT_TRUE(result);
}

class IsEmpty : public RingBufferTest
{
};

TEST_F(IsEmpty, Should_ReturnTrue_If_Empty)
{
    EXPECT_TRUE(uut->IsEmpty());
}

class IsFull : public RingBufferTest
{
};

TEST_F(IsFull, Should_ReturnTrue_If_Full)
{
    for (uint8_t i = 0; i < capacity; i++)
    {
        uut->Add(uint8Value);
    }

    EXPECT_TRUE(uut->IsFull());
}

} // namespace Test
} // namespace RingBuffer
