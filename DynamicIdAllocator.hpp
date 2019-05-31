#pragma once
#include <boost/dynamic_bitset.hpp>
#include "IIdAllocator.hpp"
#include "AllocationStrategyFactory.hpp"

template <typename HolderType,
          typename IdType>
class DynamicIdAllocator : public IIdAllocator<IdType>
{
private:
    using AllocationBehaviour = std::unique_ptr<IAllocationStrategy<HolderType, IdType>>; //move to common
public:
    DynamicIdAllocator(AllocationAlgorithm algorithm,
                       IdType size) :
        allocationBehaviour(AllocationStrategyFactory<HolderType, IdType>::get(algorithm)),
        idHolder(size)
    {}

    IdType allocate() override
    {
        resizeIfNeeded();
        return allocationBehaviour->allocate(idHolder);
    }

    void deallocate() override
    {
        allocationBehaviour->deallocate(idHolder);
    }

    void reset() override
    {
        std::cout << "Container will be cleaned" << std::endl;
        idHolder.reset();
    }
private:
    void resizeIfNeeded()
    {
        if (idHolder.all())
        {
            std::cout << "Container has been resized from: " << idHolder.size();
            idHolder.resize(2 * idHolder.size());
            std::cout << " to: " << idHolder.size() << std::endl;
        }
    }

    AllocationBehaviour allocationBehaviour;
    HolderType idHolder;
};
