#include <gtest/gtest.h>
#include "IdAllocator.hpp"

class IdAllocatorTestSuite : public ::testing::Test
{
protected:
    IdAllocator idAllocator{};
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
