#pragma once
#include "Vector3D.hpp"
namespace math
{
    struct Matrix3D
    {
        private:
            float n[3][3] {};

        public:
            Matrix3D() = default;
            Matrix3D(   float n00, float n01, float n02,
                        float n10, float n11, float n12,
                        float n20, float n21, float n22 );
            Matrix3D(const Vector3D &a,const Vector3D &b, const Vector3D &c);
            /*
            *================================================
            *   OPERATOR OVERLOAD QUE MODIFICAM (&) A STRUCT 
            *================================================
            */
            float& operator()(int i, int j);
            const float& operator()(int i, int j) const;

            Vector3D& operator[](int j);
            const Vector3D& operator[](int j) const;

            void operator +=(const Matrix3D &rhs);
            void operator -=(const Matrix3D &rhs);
    };    
    inline std::ostream& operator<<(std::ostream &os, const Matrix3D &m)
    {
        os << "Matrix3D(\n" << m(0,0) << ", " << m(0,1) << ", " << m(0,2) << '\n'
                            << m(1,0) << ", " << m(1,1) << ", " << m(1,2) << '\n'
                            << m(2,0) << ", " << m(2,1) << ", " << m(2,2) << "\n)";
        return os;
    }
    /*
    *================================================
    *   OPERATOR OVERLOAD QUE MODIFICAM (&) A STRUCT 
    *================================================
    */    
    Matrix3D operator+(const Matrix3D &lhs, Matrix3D &rhs);
    Matrix3D operator-(const Matrix3D &lhs, Matrix3D &rhs);
    Matrix3D operator*(const Matrix3D& m, float s);
    Matrix3D operator*(float s, const Matrix3D& m); 
} // namespace math

