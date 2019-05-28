#pragma once
#include <boost/dynamic_bitset.hpp>

template <typename Size>
class IdAllocator
{
public:
    IdAllocator(Size size) :
        idHolder(size)
    {}
    void method();
private:
    boost::dynamic_bitset<> idHolder;
};

template <typename Size>
void IdAllocator<Size>::method()
{
    ;
}

