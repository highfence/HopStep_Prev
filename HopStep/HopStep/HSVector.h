#pragma once

namespace HopStep
{
    template <typename T>
    class HSVector 
    {
    public :
        HSVector(T value);
        HSVector(T x, T y, T z = 0);

        HSVector<T>& operator=(const HSVector<T>& rhs);
        HSVector<T>& operator+=(const HSVector<T>& rhs);
        HSVector<T>& operator-=(const HSVector<T>& rhs);
        HSVector<T>& operator*=(const HSVector<T>& rhs);
        HSVector<T>& operator/=(const HSVector<T>& rhs);
        HSVector<T>& operator+(const HSVector<T>& rhs);
        HSVector<T>& operator-(const HSVector<T>& rhs);
        HSVector<T>& operator*(const HSVector<T>& rhs);
        HSVector<T>& operator/(const HSVector<T>& rhs);

        T x;
        T y;
        T z;
    };

    template <typename T>
    inline HSVector<T>::HSVector(T value)
        : x(value), y(value), z(value) {}

    template <typename T>
    inline HSVector<T>::HSVector(T x, T y, T z)
        : x(x), y(y), z(z) {}

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator=(const HSVector<T>& rhs)
    {
        if (this == &rhs)
            return *this;

        
        return *this;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator+=(const HSVector<T>& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator-=(const HSVector<T>& rhs)
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator*=(const HSVector<T>& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator/=(const HSVector<T>& rhs)
    {
        if (x == 0 || y == 0 || z == 0)
            return HSVector<T>(0);

        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator+(const HSVector<T>& rhs)
    {
        return HSVector<T>(*this) += rhs;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator-(const HSVector<T>& rhs)
    {
        return HSVector<T>(*this) -= rhs;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator*(const HSVector<T>& rhs)
    {
        return HSVector<T>(*this) *= rhs;
    }

    template <typename T>
    inline HSVector<T>& HSVector<T>::operator/(const HSVector<T>& rhs)
    {
        return HSVector<T>(*this) /= rhs;
    }
}