#include "../../src/RingBuffer.hpp"
#include "../submodules/AbstractionLayer/mock/MemoryMock.h"
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace RingBuffer {
namespace Test {

class RingBufferTest : public ::testing::Test
{
  protected:
    std::unique_ptr<RingBuffer> uut = nullptr;
    testing::NiceMock<AbstractionLayer::MemoryMock> memoryMock;

    uint8_t uint8Value = 34;
    uint16_t uint16Value = 435;
    uint32_t uint32Value = 346464;
    uint64_t uint64Value = 343645634577;

    void SetUp() override
    {
        uut = std::make_unique<RingBuffer>();
        bool result = uut->Init(sizeof(uint16_t));
        EXPECT_TRUE(result);
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

class Remove : public RingBufferTest
{
  protected:
    uint8_t uint8Value = 34;
    uint16_t uint16Value = 435;
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

class IsFull : public RingBufferTest
{
};

class IsEmtry : public RingBufferTest
{
};

} // namespace Test
} // namespace RingBuffer
