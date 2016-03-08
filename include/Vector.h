#ifndef VECTOR_H
#define VECTOR_H

#include <array>
#include <iostream>
#include <cassert>

template<unsigned int N = 3, typename T = double>
class Vector
{
    std::array<T, N> data;
public:
    Vector()
    {

    }
    Vector(T dat[N]) : data(dat)
    {

    }

    inline T& operator[](unsigned int index)
    {
        assert(index < N);
        return data[index];
    }

    inline const T& operator[](unsigned int index) const
    {
        assert(index < N);
        return data[index];
    }

    inline T lengthSquared() const
    {
        T result;
        for(int i = 0; i < N; i++)
        {
            result += data[i]*data[i];
        }
        return result;
    }

    inline void operator+=(Vector<N, T> rhs)
    {
         for(int i = 0; i < N; i++)
         {
             data[i] += rhs[i];
         }
    }

    inline void operator-=(Vector<N, T> rhs)
    {
        for(int i = 0; i < N; i++)
        {
             data[i] -= rhs[i];
        }
    }

    template<typename S>
    inline void operator*=(const S& s)
    {
        for(int i = 0; i < N; i++)
        {
           data[i] *= s;
        }
    }

    constexpr unsigned int dim()
    {
        return N;
    }
};



template<typename T> class Vector<3, T>
{
    T data[3];

public:
    Vector()
    {
    }

    inline Vector(T x, T y, T z)
    {
        data[0] = x;
        data[1] = y;
        data[2] = z;
    }

    inline T lengthSquared() const
    {
        return data[0]*data[0] + data[1]*data[1] + data[2]*data[2];
    }

    inline T& operator[](int index)
    {
        return data[index];
    }

    inline const T& operator[](int index) const
    {
        return data[index];
    }

    inline T& x()
    {
        return operator[](0);
    }
    inline T& y()
    {
        return operator[](1);
    }
    inline T& z()
    {
        return operator[](2);
    }
    inline const T& x() const
    {
        return operator[](0);
    }
    inline const T& y() const
    {
        return operator[](1);
    }
    inline const T& z() const
    {
        return operator[](2);
    }

    inline void operator*=(const Vector<>& b)
    {
        const Vector<3, T>& a = *this;
        T x = a[1]*b[2]-a[2]*b[1];
        T y = a[2]*b[0]-a[0]*b[2];
        T z = a[0]*b[1]-a[1]*b[0];
        this->x() = x;
        this->y() = y;
        this->z() = z;
    }

    template<typename S>
    inline void operator*=(const S& s)
    {
        x() *= s;
        y() *= s;
        z() *= s;
    }

    inline void operator+=(const Vector<>& rhs)
    {
        x() += rhs.x();
        y() += rhs.y();
        z() += rhs.z();
    }

    inline void operator -=(const Vector<>& rhs)
    {
        x() -= rhs.x();
        y() -= rhs.y();
        z() -= rhs.z();
    }

    constexpr unsigned int dim()
    {
        return 3;
    }




};




template<typename T>
Vector<3, T> operator+(Vector<3, T> a, const Vector<3, T>& b)
{
    a += b;
    return a;
}

Vector<> operator-(Vector<> a, const Vector<>& b)
{
    a -= b;
    return a;
}
template<typename T>
struct vecProduct
{
    const Vector<>& a, b;
    inline vecProduct(const Vector<>& a, const Vector<>& b) : a(a), b(b){}

    void* operator&() = delete;
    const void* operator&() const = delete;

    inline operator T()
    {
        return a.x() * b.x() + a.y() * b.y() + a.z() + b.z();
    }

    inline operator Vector<3, T>()
    {
        Vector<> v = a;
        v *= b;
        return v;
    }


};

template<typename T>
vecProduct<T> operator*(const Vector<3, T>& a, const Vector<3, T>& b)
{
    return vecProduct<T>(a, b);
}

std::ostream& operator<<(std::ostream& os, const Vector<>& obj)
{
    os << '(' << obj.x() << ',' << ' ' << obj.y() << ',' << ' ' << obj.z() << ')';
    return os;
}

template<typename S, typename T>
inline Vector<3, T> operator*(Vector<3, T> a, S s)
{
    a *= s;
    return a;
}

template<typename S, typename T>
inline Vector<3, T> operator*(S s, Vector<3, T> a)
{
    a *= s;
    return a;
}

const Vector<3, int> ZERO(0,0,0);


template<typename T> class Vector<2, T>
{
    T data[2];

public:
    Vector()
    {
    }

    inline Vector(T x, T y)
    {
        data[0] = x;
        data[1] = y;
    }

    inline T lengthSquared() const
    {
        return data[0]*data[0] + data[1]*data[1];
    }

    inline T& operator[](int index)
    {
        return data[index];
    }

    inline const T& operator[](int index) const
    {
        return data[index];
    }

    inline T& x()
    {
        return operator[](0);
    }
    inline T& y()
    {
        return operator[](1);
    }

    inline const T& x() const
    {
        return operator[](0);
    }
    inline const T& y() const
    {
        return operator[](1);
    }




    template<typename S>
    inline void operator*=(const S& s)
    {
        x() *= s;
        y() *= s;

    }

    inline void operator+=(const Vector<>& rhs)
    {
        x() += rhs.x();
        y() += rhs.y();

    }

    inline void operator -=(const Vector<>& rhs)
    {
        x() -= rhs.x();
        y() -= rhs.y();

    }

    constexpr unsigned int dim()
    {
        return 2;
    }




};

#endif // VECTOR_H
