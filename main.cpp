//#include "Vector.h"
//#include "ndsolve.hpp"
#include <cstdio>
#include <string>
#include <cassert>
#include <iostream>
#include <utility>
//#include "Grid.h"
//#include "Cell.h"


void* allocate(constexpr size_t N)
{

}

template<typename T, typename... Args>
T* allocreate(Args&&... args)
{
    void* mem = allocate(sizeof(T));
    return new(mem) T(std::forward<Args>(args)...);
}

void deallocate(void* pointer, constexpr size_t N)
{

}

template<typename T>
void defree(T* pointer)
{
    deallocate(pointer, sizeof(T));
}

int main()
{




    return 0;
}


