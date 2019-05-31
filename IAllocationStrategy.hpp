#pragma once

template <typename HolderType,
          typename IdType>
struct IAllocationStrategy
{
    virtual ~IAllocationStrategy() = default;
    virtual IdType allocate(HolderType&) = 0;
};
