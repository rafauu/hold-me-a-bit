#pragma once

struct IIdAllocator
{
    virtual unsigned allocate() = 0;
    virtual void deallocate() = 0;
    virtual void reset() = 0;
};
