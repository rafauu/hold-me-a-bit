#include <gtest/gtest.h>
#include <boost/dynamic_bitset.hpp>
#include "DynamicIdAllocator.hpp"

namespace
{
constexpr auto DEFAULT_ALLOCATOR_SIZE{3u};
}

class DynamicIdAllocatorTestSuite : public ::testing::Test
{
protected:
    using HolderType = boost::dynamic_bitset<>;
    using IdType = unsigned;
};


class BasicDynamicIdAllocatorTestSuite : public DynamicIdAllocatorTestSuite
{
protected:
    DynamicIdAllocator<HolderType, IdType> sut{AllocationAlgorithm::Basic,
                                               DEFAULT_ALLOCATOR_SIZE};
};

TEST_F(BasicDynamicIdAllocatorTestSuite, shallAllocateMemoryAndIdWhenRanOutOfBasicCapacity)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(3u, sut.allocate());
    ASSERT_EQ(4u, sut.allocate());
    ASSERT_EQ(5u, sut.allocate());
    ASSERT_EQ(6u, sut.allocate());
}

TEST_F(BasicDynamicIdAllocatorTestSuite, shallReuseIdAfterDeallocation)
{
    ASSERT_EQ(0u, sut.allocate());
    sut.deallocate();
    ASSERT_EQ(0u, sut.allocate());
    sut.deallocate();
}

TEST_F(BasicDynamicIdAllocatorTestSuite, shoulNotCrashWhenDeallocatingMoreIdThanAllocated)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    sut.deallocate();
    sut.deallocate();
    sut.deallocate();
}

TEST_F(BasicDynamicIdAllocatorTestSuite, shallAllocateFromBeginningAfterReset)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    sut.reset();
    ASSERT_EQ(0u, sut.allocate());
}

TEST_F(BasicDynamicIdAllocatorTestSuite, shallDeallocateProperlyAfterResizing)
{
    ASSERT_EQ(0u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(3u, sut.allocate());
    sut.deallocate();
    sut.deallocate();
    ASSERT_EQ(2u, sut.allocate());
}


class ReversedDynamicIdAllocatorTestSuite : public DynamicIdAllocatorTestSuite
{
protected:
    DynamicIdAllocator<HolderType, IdType> sut{AllocationAlgorithm::Reversed,
                                               DEFAULT_ALLOCATOR_SIZE};
};

TEST_F(ReversedDynamicIdAllocatorTestSuite, shouldAssignIdsReversed)
{
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    ASSERT_EQ(0u, sut.allocate());
    sut.reset();
    ASSERT_EQ(2u, sut.allocate());
    ASSERT_EQ(1u, sut.allocate());
    sut.deallocate();
    ASSERT_EQ(1u, sut.allocate());
}


int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
