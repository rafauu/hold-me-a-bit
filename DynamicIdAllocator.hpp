#pragma once
#include "IIdAllocator.hpp"
#include "AllocationStrategyFactory.hpp"

template <typename HolderType,
          typename IdType>
class DynamicIdAllocator : public IIdAllocator<IdType>
{
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

    AllocationBehaviour<HolderType, IdType> allocationBehaviour;
    HolderType idHolder;
};
