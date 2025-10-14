#include "Vector3D.hpp"
#include <stdexcept>
namespace math
{
    Vector3D::Vector3D(float a, float b, float c) : x{a},y{b},z{c}
    {
        std::cout << "Vector3d constructor called" << '\n';
    }
    Vector3D::~Vector3D()
    {
        std::cout << "Destroying Vector3d" << '\n';
    }

    float &Vector3D::operator[](int i)
    {
        if(i < 0 || i >= 3)
            throw std::runtime_error("Acesso de memoria invalido fora do range: " + std::to_string(i));

        return ((&x)[i]);
    }

    const float &Vector3D::operator[](int i) const
    {
        if(i < 0 || i >= 3)
            throw std::runtime_error("Acesso de memoria invalido fora do range: " + std::to_string(i));

        return ((&x)[i]);
    }

    Vector3D Vector3D::operator+(const Vector3D &rhs) const
    {
        return Vector3D(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    }

    Vector3D Vector3D::operator-(const Vector3D &rhs) const
    {
        return Vector3D(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    }

    void Vector3D::operator+=(const Vector3D &rhs)
    {
        this->x  += rhs.x;
        this->y  += rhs.y;
        this->z  += rhs.z;
    }

    void Vector3D::operator-=(const Vector3D &rhs)
    {
        this->x  -= rhs.x;
        this->y  -= rhs.y;
        this->z  -= rhs.z;
    }

    void Vector3D::operator=(const Vector3D &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        this->z = rhs.z;
    }
}
