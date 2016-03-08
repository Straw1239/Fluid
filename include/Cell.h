#ifndef CELL_H
#define CELL_H
#include "Vector.h"

template<unsigned int N = 3>
class Cell
{
    typedef Vector<N> vec;
    vec v;
    double dens;

public:

        Cell()
        {

        }

        Cell(double dens, vec velocity) : dens(density), v(velocity)
        {

        }

    double density() const
    {
        return dens;
    }

    vec velocity() const
    {
        return v;
    }

};

#endif // CELL_H
