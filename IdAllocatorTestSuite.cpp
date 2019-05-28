#include <gtest/gtest.h>
#include "IdAllocator.hpp"

namespace
{
constexpr auto DEFAULT_ALLOCATOR_SIZE = 8u;
}

class IdAllocatorTestSuite : public ::testing::Test
{
protected:
    IdAllocator<unsigned> idAllocator{DEFAULT_ALLOCATOR_SIZE};
};

TEST_F(IdAllocatorTestSuite, exampleTest)
{
    idAllocator.method();
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS();
}
