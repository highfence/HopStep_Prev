#pragma once

namespace HopStep
{
    template <typename T>
    class Vector 
    {
    public :
        Vector(T value);
        Vector(T x, T y, T z = 0);

        Vector<T>& operator=(const Vector<T>& rhs);
        Vector<T>& operator+=(const Vector<T>& rhs);
        Vector<T>& operator-=(const Vector<T>& rhs);
        Vector<T>& operator*=(const Vector<T>& rhs);
        Vector<T>& operator/=(const Vector<T>& rhs);
        Vector<T>& operator+(const Vector<T>& rhs);
        Vector<T>& operator-(const Vector<T>& rhs);
        Vector<T>& operator*(const Vector<T>& rhs);
        Vector<T>& operator/(const Vector<T>& rhs);

        T x;
        T y;
        T z;
    };

    template <typename T>
    inline Vector<T>::Vector(T value)
        : x(value), y(value), z(value) {}

    template <typename T>
    inline Vector<T>::Vector(T x, T y, T z)
        : x(x), y(y), z(z) {}

    template <typename T>
    inline Vector<T>& Vector<T>::operator=(const Vector<T>& rhs)
    {
        if (this == &rhs)
            return *this;

        
        return *this;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator+=(const Vector<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator-=(const Vector<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator*=(const Vector<T>& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator/=(const Vector<T>& rhs)
    {
        if (x == 0 || y == 0 || z == 0)
            return Vector<T>(0);

        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator+(const Vector<T>& rhs)
    {
        return Vector<T>(*this) += rhs;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator-(const Vector<T>& rhs)
    {
        return Vector<T>(*this) -= rhs;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator*(const Vector<T>& rhs)
    {
        return Vector<T>(*this) *= rhs;
    }

    template <typename T>
    inline Vector<T>& Vector<T>::operator/(const Vector<T>& rhs)
    {
        return Vector<T>(*this) /= rhs;
    }
}