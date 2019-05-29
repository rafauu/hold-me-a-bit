#include <gtest/gtest.h>
#include "DynamicIdAllocator.hpp"

namespace
{
constexpr auto DEFAULT_ALLOCATOR_SIZE = 3u;
}

class DynamicIdAllocatorTestSuite : public ::testing::Test
{
protected:
    DynamicIdAllocator<unsigned> sut{DEFAULT_ALLOCATOR_SIZE};
};

TEST_F(DynamicIdAllocatorTestSuite, shallAllocateMemoryAndIdWhenRanOutOfBasicCapacity)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(3u, sut.allocate());
    ASSERT_EQ(4u, sut.allocate());
    ASSERT_EQ(5u, sut.allocate());
    ASSERT_EQ(6u, sut.allocate());
}

TEST_F(DynamicIdAllocatorTestSuite, shallReuseIdAfterDeallocation)
{
    ASSERT_EQ(0u, sut.allocate());
    sut.deallocate();
    ASSERT_EQ(0u, sut.allocate());
    sut.deallocate();
}

TEST_F(DynamicIdAllocatorTestSuite, shoulNotCrashWhenDeallocatingMoreIdThanAllocated)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    sut.deallocate();
    sut.deallocate();
    sut.deallocate();
}

TEST_F(DynamicIdAllocatorTestSuite, shallAllocateFromBeginningAfterReset)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    sut.reset();
    ASSERT_EQ(0u, sut.allocate());
}

TEST_F(DynamicIdAllocatorTestSuite, shallDeallocateProperlyAfterResizing)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(3u, sut.allocate());
    sut.deallocate();
    sut.deallocate();
    ASSERT_EQ(2u, sut.allocate());
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
