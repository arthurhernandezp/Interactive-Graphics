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

        float magnitude() const;
        void normalize();                               // Normaliza o proprio vector        
        Vector3D normalized() const;                    // Retorna uma copia normalizada

        Vector3D crossProduct(const Vector3D &rhs) const;
        float dotProduct(const Vector3D &rhs) const;    

        /*
        *================================================
        *   OPERATOR OVERLOAD QUE MODIFICAM (&) A STRUCT 
        *================================================
        */
        float& operator [](int i);
        const float& operator [](int i) const;

        void operator +=(const Vector3D &rhs);
        void operator -=(const Vector3D &rhs);
        void operator /=(float s);
        void operator *=(float s);
    };

    inline std::ostream& operator<<(std::ostream& os, const Vector3D& v)
    {
        os << "Vector3D(" << v.x << ", " << v.y << ", " << v.z << ")";
        return os;
    }

    /*
    *================================================
    *   OPERATOR OVERLOAD QUE COPIAM A STRUCT
    *================================================
    */
    Vector3D operator +(const Vector3D &lhs,const Vector3D &rhs);
    Vector3D operator -(const Vector3D &lhs,const Vector3D &rhs);
    Vector3D operator /(const Vector3D &lhs, float s);
    Vector3D operator*(const Vector3D& v, float s);
    Vector3D operator*(float s, const Vector3D& v); 
    Vector3D operator -(const Vector3D &lhs);            // Negando o vetor

} // namespace math
