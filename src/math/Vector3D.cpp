#include "Vector3D.hpp"
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
        return ((&x)[i]);
    }
    const float &Vector3D::operator[](int i) const
    {
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
