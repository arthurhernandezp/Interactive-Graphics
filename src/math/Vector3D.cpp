#include "Vector3D.hpp"
#include <stdexcept>
#include <cmath>
namespace math
{
    Vector3D::Vector3D(float a, float b, float c) : x{a},y{b},z{c}
    {
        std::cout << "Vector3d constructor called : " << *this  << ", Address: " << this << '\n';
    }

    float Vector3D::magnitude() const
    {
        float magnitude = std::sqrt( std::pow(x,2) + std::pow(y,2) + std::pow(z,2) );
        return magnitude;
    }

    void Vector3D::normalize()
    {
        float magnitude = this->magnitude();

        if(magnitude == 0.0f)
        {            
            this->x = 0.0f;
            this->y = 0.0f;
            this->z = 0.0f;
        }

        *this /= magnitude; 
    }

    Vector3D Vector3D::normalized() const
    {
        float magnitude = this->magnitude();

        if(magnitude == 0.0f)
            return Vector3D(0.0f,0.0f,0.0f);

        auto normalizedVector = *this;
        return Vector3D( normalizedVector /magnitude );
    }
    
    float Vector3D::dotProduct(const Vector3D &rhs) const
    {
        return ( (this->x * rhs.x) + (this->y * rhs.y) + (this->z * rhs.z) );
    }

    /*
     *================================================
     *   OPERATOR OVERLOAD QUE MODIFICAM A STRUCT
     *================================================
     */
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

    void Vector3D::operator/=(float s)
    {
        if(s == 0)
            throw std::runtime_error("Error ao dividir por 0");

        s = 1.0f / s;

        this->x *= s; 
        this->y *= s; 
        this->z *= s;
    }

    void Vector3D::operator*=(float s)
    {
        this->x *= s; 
        this->y *= s; 
        this->z *= s;
    }

    /*
    *================================================
    *   OPERATOR OVERLOAD QUE COPIAM A STRUCT
    *================================================
    */
    Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
    {
        return Vector3D(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
    }

    Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
    {
        return Vector3D(lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z);
    }

    Vector3D operator/(const Vector3D &lhs, float s)
    {
        if(s == 0)
            throw std::runtime_error("Error ao dividir por 0");

        s = 1.0f / s;
        return Vector3D(lhs.x * s, lhs.y * s, lhs.z * s);
    }
    Vector3D operator*(const Vector3D &v, float s)
    {
        return Vector3D(v.x * s,v.y * s, v.z * s);
    }
    Vector3D operator*(float s, const Vector3D &v)
    {
        return Vector3D(v.x * s,v.y * s, v.z * s);
    }
    Vector3D operator-(const Vector3D &rhs)
    {
        return Vector3D(-rhs.x,-rhs.y,-rhs.z);
    }
}
