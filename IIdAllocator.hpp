#pragma once

template <typename IdType>
struct IIdAllocator
{
    virtual ~IIdAllocator() = default;
    virtual IdType allocate() = 0;
    virtual void deallocate() = 0;
    virtual void reset() = 0;
};
