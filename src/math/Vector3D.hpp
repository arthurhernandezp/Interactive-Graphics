#pragma once
#include <iostream>

namespace math
{
    struct Vector3D
    {
        float x,y,z;
        Vector3D() = default;

        Vector3D(float a, float b, float c) : x{a},y{b},z{c}
        {
            std::cout << "Vector3d constructor called" << '\n';
        }

        ~Vector3D()
        {
            std::cout << "Destroying Vector3d" << '\n';
        }

        float& operator [](int i)
        {
            return ((&x)[i]);
        }

        const float& operator [](int i) const
        {
            return ((&x)[i]);
        }
    };
} // namespace math
