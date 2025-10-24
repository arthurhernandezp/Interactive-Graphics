#include "Matrix3D.hpp"

namespace math
{
    Matrix3D::Matrix3D(float n00, float n01, float n02, 
                       float n10, float n11, float n12, 
                       float n20, float n21, float n22)
    {
        n[0][0] = n00; n[0][1] = n10; n[0][2] = n20;
        n[1][0] = n01; n[1][1] = n11; n[1][2] = n21;
        n[2][0] = n02; n[2][1] = n12; n[2][2] = n22;
    }

    Matrix3D::Matrix3D(const Vector3D &a, const Vector3D &b, const Vector3D &c)
    {
        n[0][0] = a.x; n[0][1] = a.y; n[0][2] = a.z;
        n[1][0] = b.x; n[1][1] = b.y; n[1][2] = b.z;
        n[2][0] = c.x; n[2][1] = c.y; n[2][2] = c.z;
    }

    float &Matrix3D::operator()(int i, int j)
    {
        return (n[j][i]);
    }

    const float &Matrix3D::operator()(int i, int j) const
    {
        return (n[j][i]);
    }

    Vector3D &Matrix3D::operator[](int j)
    {
        return (*reinterpret_cast<Vector3D *>(n[j]));
    }

    const Vector3D &Matrix3D::operator[](int j) const
    {
       return (*reinterpret_cast<const Vector3D *>(n[j]));
    }

    void Matrix3D::operator+=(const Matrix3D &rhs)
    {
        (*this)(0,0) +=  rhs(0,0); (*this)(0,1) += rhs(0,1); (*this)(0,2) += rhs(0,2);
        (*this)(1,0) +=  rhs(1,0); (*this)(1,1) += rhs(1,1); (*this)(1,2) += rhs(1,2);
        (*this)(2,0) +=  rhs(2,0); (*this)(2,1) += rhs(2,1); (*this)(2,2) += rhs(2,2);
    }

    void Matrix3D::operator-=(const Matrix3D &rhs)
    {
        (*this)(0,0) -=  rhs(0,0); (*this)(0,1) -= rhs(0,1); (*this)(0,2) -= rhs(0,2);
        (*this)(1,0) -=  rhs(1,0); (*this)(1,1) -= rhs(1,1); (*this)(1,2) -= rhs(1,2);
        (*this)(2,0) -=  rhs(2,0); (*this)(2,1) -= rhs(2,1); (*this)(2,2) -= rhs(2,2);
    }

    Matrix3D operator+(const Matrix3D &lhs, const Matrix3D &rhs)
    {
        return Matrix3D(lhs(0,0) + rhs(0,0),lhs(1,0) + rhs(1,0),lhs(2,0) + rhs(2,0),
                        lhs(0,1) + rhs(0,1),lhs(1,1) + rhs(1,1),lhs(2,1) + rhs(2,1),
                        lhs(0,2) + rhs(0,2),lhs(1,2) + rhs(1,2),lhs(2,2) + rhs(2,2));
    }

    Matrix3D operator-(const Matrix3D &lhs, const Matrix3D &rhs)
    {
        return Matrix3D(lhs(0,0) - rhs(0,0),lhs(1,0) - rhs(1,0),lhs(2,0) - rhs(2,0),
                        lhs(0,1) - rhs(0,1),lhs(1,1) - rhs(1,1),lhs(2,1) - rhs(2,1),
                        lhs(0,2) - rhs(0,2),lhs(1,2) - rhs(1,2),lhs(2,2) - rhs(2,2));
    }

    Matrix3D operator*(const Matrix3D &m, float s)
    {
        return Matrix3D(m(0,0) * s, m(1,0) * s, m(2,0) * s,
                        m(0,1) * s, m(1,1) * s, m(2,1) * s,
                        m(0,2) * s, m(1,2) * s, m(2,2) * s);
    }

    Matrix3D operator*(float s, const Matrix3D &m)
    {
        return Matrix3D(m(0,0) * s, m(1,0) * s, m(2,0) * s,
                        m(0,1) * s, m(1,1) * s, m(2,1) * s,
                        m(0,2) * s, m(1,2) * s, m(2,2) * s);
    }

    Matrix3D operator*(const Matrix3D &A, const Matrix3D &B)
    {
        /*
            math::Vector3D a1(1.0f,2.0f,3.0f);
            math::Vector3D b1(4.0f,5.0f,6.0f);
            math::Vector3D c1(7.0f,8.0f,9.0f);

            math::Matrix3D m1(a1,b1,c1);
            
            math::Vector3D a2(9.0f,8.0f,7.0f);
            math::Vector3D b2(6.0f,5.0f,4.0f);
            math::Vector3D c2(3.0f,2.0f,1.0f);
        
        */
    //    std::cout << A(0,0) * B(0,0) + A(1,0) * B(0,1) + A(2,0) * B(0,2) << '|';
    //    std::cout << A(0,0) * B(1,0) + A(1,0) * B(1,1) + A(2,0) * B(1,2) << '|';
    //    std::cout << A(0,0) * B(2,0) + A(1,0) * B(2,1) + A(2,0) * B(2,2);
    //    std::cout << '\n';

    //    std::cout << A(0,1) * B(0,0) + A(1,1) * B(0,1) + A(2,1) * B(0,2) << '|';
    //    std::cout << A(0,1) * B(1,0) + A(1,1) * B(1,1) + A(2,1) * B(1,2) << '|';
    //    std::cout << A(0,1) * B(2,0) + A(1,1) * B(2,1) + A(2,1) * B(2,2);
    //    std::cout << '\n';

    //    std::cout << A(0,2) * B(0,0) + A(1,2) * B(0,1) + A(2,2) * B(0,2) << '|';
    //    std::cout << A(0,2) * B(1,0) + A(1,2) * B(1,1) + A(2,2) * B(1,2) << '|';
    //    std::cout << A(0,2) * B(2,0) + A(1,2) * B(2,1) + A(2,2) * B(2,2);
    //    std::cout << '\n';
        return Matrix3D(A(0,0) * B(0,0) + A(1,0) * B(0,1) + A(2,0) * B(0,2),
                        A(0,0) * B(1,0) + A(1,0) * B(1,1) + A(2,0) * B(1,2),
                        A(0,0) * B(2,0) + A(1,0) * B(2,1) + A(2,0) * B(2,2),

                        A(0,1) * B(0,0) + A(1,1) * B(0,1) + A(2,1) * B(0,2),
                        A(0,1) * B(1,0) + A(1,1) * B(1,1) + A(2,1) * B(1,2),
                        A(0,1) * B(2,0) + A(1,1) * B(2,1) + A(2,1) * B(2,2),

                        A(0,2) * B(0,0) + A(1,2) * B(0,1) + A(2,2) * B(0,2),
                        A(0,2) * B(1,0) + A(1,2) * B(1,1) + A(2,2) * B(1,2),
                        A(0,2) * B(2,0) + A(1,2) * B(2,1) + A(2,2) * B(2,2));

    }
} // namespace math
