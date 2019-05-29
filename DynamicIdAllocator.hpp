#pragma once
#include "IIdAllocator.hpp"
#include <boost/dynamic_bitset.hpp>

template <typename T = unsigned>
class DynamicIdAllocator : public IIdAllocator<T>
{
public:
    explicit DynamicIdAllocator(T size);
    T allocate() override;
    void deallocate() override;
    void reset() override;
private:
    void resizeIfNeeded();
    boost::dynamic_bitset<> idHolder;
};

template <typename T>
DynamicIdAllocator<T>::DynamicIdAllocator(T size) :
    idHolder(size)
{}

template <typename T>
T DynamicIdAllocator<T>::allocate()
{
    resizeIfNeeded();
    auto allocatedId{idHolder.count()};
    idHolder.set(allocatedId);
    std::cout << "Id " << allocatedId << " has been allocated" << std::endl;
    return allocatedId;
}

template <typename T>
void DynamicIdAllocator<T>::deallocate()
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

template <typename T>
void DynamicIdAllocator<T>::resizeIfNeeded()
{
    if (idHolder.all())
    {
        std::cout << "Container has been resized from: " << idHolder.size();
        idHolder.resize(2 * idHolder.size());
        std::cout << " to: " << idHolder.size() << std::endl;
    }
}

template <typename T>
void DynamicIdAllocator<T>::reset()
{
    std::cout << "Container will be cleaned" << std::endl;
    idHolder.reset();
}
