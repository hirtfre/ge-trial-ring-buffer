#include "../../src/RingBuffer.hpp"
#include "../submodules/AbstractionLayer/mock/MemoryMock.h"
#include <RingBuffer/Factory.h>
#include <gmock/gmock.h>
#include <gtest/gtest.h>

namespace RingBuffer {
namespace Test {

class Base : public ::testing::Test
{
  public:
    IRingBuffer *uut = nullptr;
    testing::NiceMock<AbstractionLayer::MemoryMock> memoryMock;

    void TearDown() override
    {
        if (uut != nullptr)
        {
            Factory::Destroy(&uut);
        }
    }
};

class Create : public Base
{
};

TEST_F(Create, Should_ReturnInstance)
{
    uut = Factory::Create(sizeof(uint16_t));

    EXPECT_NE(uut, nullptr);
}

TEST_F(Create, Should_AllocateMemory)
{
    EXPECT_CALL(memoryMock, Calloc(1, testing::_)).Times(3);

    uut = Factory::Create(sizeof(uint16_t));

    EXPECT_NE(uut, nullptr);
}

TEST_F(Create, Should_ReturnNullptr_If_MemoryAllocationFails)
{
    EXPECT_CALL(memoryMock, Calloc(1, sizeof(RingBuffer))).WillOnce(testing::Return(nullptr));

    uut = Factory::Create(sizeof(uint16_t));

    EXPECT_EQ(uut, nullptr);
    memoryMock.CompensateFailedAllocation(1);
}

class Destroy : public Base
{
    void SetUp() override
    {
        uut = Factory::Create(sizeof(uint16_t));
    }
};

TEST_F(Destroy, Should_FreeMemory)
{
    EXPECT_CALL(memoryMock, Free(testing::_)).Times(3);

    Factory::Destroy(&uut);
}

TEST_F(Destroy, Should_SetPointerToNullptr)
{
    Factory::Destroy(&uut);

    EXPECT_EQ(uut, nullptr);
}

} // namespace Test
} // namespace RingBuffer
