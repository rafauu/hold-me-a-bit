#pragma once

template <typename Size>
struct IIdAllocator
{
    virtual Size allocate() = 0;
    virtual void deallocate() = 0;
    virtual void reset() = 0;
};
