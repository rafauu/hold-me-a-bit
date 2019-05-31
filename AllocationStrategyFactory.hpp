#pragma once
#include <memory>
#include "AllocationAlgorithm.hpp"
#include "BasicAllocationStrategy.hpp"
#include "ReversedAllocationStrategy.hpp"

template <typename HolderType,
          typename IdType>
struct AllocationStrategyFactory
{
    using AllocationBehaviour = std::unique_ptr<IAllocationStrategy<HolderType, IdType>>;
    static AllocationBehaviour get(AllocationAlgorithm algorithm)
    {
        if (AllocationAlgorithm::Basic == algorithm)
        {
            return std::make_unique<BasicAllocationStrategy<HolderType, IdType>>(); 
        }
        else if (AllocationAlgorithm::Reversed == algorithm)
        {
            return std::make_unique<ReversedAllocationStrategy<HolderType, IdType>>();
        }
        else
        {
            return nullptr;
        }
    }
};
