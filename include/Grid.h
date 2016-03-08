#ifndef GRID_H
#define GRID_H
#include <vector>

#include <cassert>
using std::vector;

typedef size_t uint;

template<typename Cell, unsigned int Dim>
class Grid
{
public:

typedef Vector<Dim, uint> Position;
typedef Vector<Dim> nVec;

private:

    const int width;
    vector<Cell> grid;
    unsigned size_t size;

    inline unsigned int index(const Position& loc)
    {
        unsigned int index = 0;
        int multi = 1;
        for(int i = 0; i < Dim; i++)
        {
            assert(loc[i] < Dim);
            index += multi * loc[i];
            multi *= Dim;
        }
        return index;
    }
public:
    Grid(int width) : width(width)
    {
        size = 1;
        for(int i = 0; i < Dim; i++)
        {
            size *= width;
        }
        grid.reserve(size);
        for(int i = 0; i < size; i++)
        {
            grid.emplace_back();
        }
    }



    inline Cell& operator[](const Position& loc)
    {
        return grid[index(loc)];
    }

    inline const Cell& operator[](const Position& loc) const
    {
        return grid[index(loc)];
    }


    inline void operator+=(const Grid& rhs)
    {
        assert(rhs.width == width);
        for(int i = 0; i < size; i++)
        {
            grid[i] += rhs.grid[i];
        }
    }

    inline void operator-=(const Grid& rhs)
    {
        assert(rhs.width == width);
        for(int i = 0; i < size; i++)
        {
            grid[i] -= rhs.grid[i];
        }
    }


};

template<typename T> inline T interpolate2D(const T& LL, const T& LR, const T& UL, const T& UR, double x, double y)
{
    return (1-x)*(1-y) * LL + x*(1-y) * LR + y*(1-x) * UL + x*y * UR;
}

class Grid2D : public Grid<Cell<2>, 2>
{
    #define pAt(x, y) grid[index({x, y})].density();
public:
    double density(double x, double y)
    {
        uint xint = uint(x);
        uint yint = uint(y);
        x -= xint;
        y -= yint;
        double LL = pAt(xint, yint);
        double LR = pAt(xint + 1, yint);
        double UL = pAt(xint, yint + 1);
        double UR = pAt(xint + 1, yint + 1);
        return interpolate2D(LL, LR, UL, UR, x, y);
    }



    #undef pAt;
};

double deltaPAdvection(const Grid2D& g, uint x, uint y, double xdir, double ydir, double h)
{
    double newDensity = g.density(x + h*xdir, y + h*ydir);
    return (newDensity - g[{x, y}].density());
}

double deltaP(const Grid2D& g, uint x, uint y, double a, double h)
{
    Vector<2> dir = g[{x, y}].velocity();
    return h*dpdtDiffusion(g, x, y, a) + deltaPAdvection(g, x, y, -dir.x(), -dir.y(), h);
}

double dpdtDiffusion(const Grid2D& g, uint x, uint y, double a)
{
    return a*(g[{x + 1, y}] + g[{x - 1, y}] + g[{x, y+1}] + g[{x, y-1}] - 4*g[{x, y}]);
}

#endif // GRID_H
