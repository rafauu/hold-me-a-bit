#pragma once
#include "IAllocationStrategy.hpp"

template <typename HolderType,
          typename IdType>
struct BasicAllocationStrategy : IAllocationStrategy<HolderType,
                                                     IdType>
{
    IdType allocate(HolderType& idHolder)
    {
        auto allocatedId{idHolder.count()};
        idHolder.set(allocatedId);
        std::cout << "Id " << allocatedId << " has been allocated" << std::endl;
        return allocatedId;
    }
};
