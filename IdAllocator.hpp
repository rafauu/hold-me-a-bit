#pragma once
#include <boost/dynamic_bitset.hpp>

template <typename Size>
class IdAllocator
{
public:
    IdAllocator(Size size) :
        idHolder(size)
    {}
    auto allocate();
    void deallocate();
    void reset();
private:
    void resizeIfNeeded();
    boost::dynamic_bitset<> idHolder;
};


template <typename Size>
auto IdAllocator<Size>::allocate()
{
    resizeIfNeeded();
    auto allocatedId{idHolder.count()};
    idHolder.set(allocatedId);
    std::cout << "Id " << allocatedId << " has been allocated" << std::endl;
    return allocatedId;
}

template <typename Size>
void IdAllocator<Size>::deallocate()
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

template <typename Size>
void IdAllocator<Size>::resizeIfNeeded()
{
    if (idHolder.all())
    {
        std::cout << "Container has been resized from: " << idHolder.size();
        idHolder.resize(2 * idHolder.size());
        std::cout << " to: " << idHolder.size() << std::endl;
    }
}

template <typename Size>
void IdAllocator<Size>::reset()
{
    std::cout << "Container will be cleaned" << std::endl;
    idHolder.reset();
}
