#pragma once
#include "IAllocationStrategy.hpp"

template <typename HolderType,
          typename IdType>
struct ReversedAllocationStrategy : IAllocationStrategy<HolderType,
                                                        IdType>
{
    IdType allocate(HolderType& idHolder)
    {
        auto allocatedId{idHolder.size() - idHolder.count() - 1};
        idHolder.set(idHolder.count());
        std::cout << "Id " << allocatedId << " has been allocated" << std::endl;
        return allocatedId;
    }

    void deallocate(HolderType& idHolder)
    {
        if (idHolder.count() > 0)
        {
            idHolder >>= 1;
            std::cout << "Id " << idHolder.count() << " has been deallocated" << std::endl;
        }
        else
        {
            std::cout << "Nothing to deallocate" << std::endl;
        }
    }
};
