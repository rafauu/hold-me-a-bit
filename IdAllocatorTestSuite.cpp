#include <gtest/gtest.h>
#include "IdAllocator.hpp"

namespace
{
constexpr auto DEFAULT_ALLOCATOR_SIZE = 3u;
}

class IdAllocatorTestSuite : public ::testing::Test
{
protected:
    IdAllocator<unsigned> idAllocator{DEFAULT_ALLOCATOR_SIZE};
};

TEST_F(IdAllocatorTestSuite, shallAllocateMemoryAndIdWhenRanOutOfBasicCapacity)
{
    ASSERT_EQ(0u, idAllocator.allocate());
    ASSERT_EQ(1u, idAllocator.allocate());
    ASSERT_EQ(2u, idAllocator.allocate());
    ASSERT_EQ(3u, idAllocator.allocate());
    ASSERT_EQ(4u, idAllocator.allocate());
    ASSERT_EQ(5u, idAllocator.allocate());
    ASSERT_EQ(6u, idAllocator.allocate());
}

TEST_F(IdAllocatorTestSuite, shallReuseIdAfterDeallocation)
{
    ASSERT_EQ(0u, idAllocator.allocate());
    idAllocator.deallocate();
    ASSERT_EQ(0u, idAllocator.allocate());
    idAllocator.deallocate();
}

TEST_F(IdAllocatorTestSuite, shoulNotCrashWhenDeallocatingMoreIdThanAllocated)
{
    ASSERT_EQ(0u, idAllocator.allocate());
    ASSERT_EQ(1u, idAllocator.allocate());
    idAllocator.deallocate();
    idAllocator.deallocate();
    idAllocator.deallocate();
}

TEST_F(IdAllocatorTestSuite, shallAllocateFromBeginningAfterReset)
{
    ASSERT_EQ(0u, idAllocator.allocate());
    ASSERT_EQ(1u, idAllocator.allocate());
    ASSERT_EQ(2u, idAllocator.allocate());
    idAllocator.reset();
    ASSERT_EQ(0u, idAllocator.allocate());
}

TEST_F(IdAllocatorTestSuite, shallDeallocateProperlyAfterResizing)
{
    ASSERT_EQ(0u, idAllocator.allocate());
    ASSERT_EQ(1u, idAllocator.allocate());
    ASSERT_EQ(2u, idAllocator.allocate());
    ASSERT_EQ(3u, idAllocator.allocate());
    idAllocator.deallocate();
    idAllocator.deallocate();
    idAllocator.deallocate();
    idAllocator.deallocate();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
