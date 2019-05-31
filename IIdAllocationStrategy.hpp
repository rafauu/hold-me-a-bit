#pragma once

template <typename HolderType,
          typename IdType>
struct IIdAllocationStrategy
{
    virtual ~IIdAllocationStrategy() = default;
    virtual IdType allocate(HolderType&) = 0;
    virtual void deallocate(HolderType&) = 0;
};
