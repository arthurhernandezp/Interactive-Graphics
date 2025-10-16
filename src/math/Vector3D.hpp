#pragma once
#include <iostream>

namespace math
{
    struct Vector3D
    {
        float x{};
        float y{};
        float z{};

        Vector3D() = default;
        Vector3D(float a, float b, float c);
        ~Vector3D();

        float magnitude() const;
        Vector3D normalize();
        /*
        *================================================
        *   OPERATOR OVERLOAD
        *================================================
        */
        float& operator [](int i);
        const float& operator [](int i) const;
        Vector3D operator +(const Vector3D &rhs) const;
        Vector3D operator -(const Vector3D &rhs) const;
        Vector3D operator /(float s);
        void operator =(const Vector3D &rhs);
        void operator +=(const Vector3D &rhs);
        void operator -=(const Vector3D &rhs);

    };


} // namespace math
