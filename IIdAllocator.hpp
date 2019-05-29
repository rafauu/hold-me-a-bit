#pragma once

template <typename T>
struct IIdAllocator
{
    virtual T allocate() = 0;
    virtual void deallocate() = 0;
    virtual void reset() = 0;
};
