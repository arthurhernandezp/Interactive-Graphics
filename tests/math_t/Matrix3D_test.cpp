#include <gtest/gtest.h>
#include "math/Matrix3D.hpp"
#include "math/Matrix3D.hpp"
#include <iostream>

TEST(Matrix3DTest,DefaultConstructor)
{
    math::Matrix3D n;

    EXPECT_EQ(n(0,0),0);EXPECT_EQ(n(0,1),0);EXPECT_EQ(n(0,2),0);
    EXPECT_EQ(n(1,0),0);EXPECT_EQ(n(1,1),0);EXPECT_EQ(n(1,2),0);
    EXPECT_EQ(n(2,0),0);EXPECT_EQ(n(2,1),0);EXPECT_EQ(n(2,2),0);
}

TEST(Matrix3DTest,Vector3DConstructor)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D n(a,b,c);

    EXPECT_EQ(n(0,0),1.0f);  EXPECT_EQ(n(0,1),4.0f);  EXPECT_EQ(n(0,2),7.0f);
    EXPECT_EQ(n(1,0),2.0f);  EXPECT_EQ(n(1,1),5.0f);  EXPECT_EQ(n(1,2),8.0f);
    EXPECT_EQ(n(2,0),3.0f);  EXPECT_EQ(n(2,1),6.0f);  EXPECT_EQ(n(2,2),9.0f);
}

TEST(Matrix3DTest,GetVector3DFromDefaultMatrix3D)
{
    math::Matrix3D n;

    math::Vector3D v = n[1];

    EXPECT_EQ(v.x,0);
    EXPECT_EQ(v.y,0);
    EXPECT_EQ(v.z,0);
}

TEST(Matrix3DTest, SumMatrix3D)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);
    math::Matrix3D m2(a,b,c);

    math::Matrix3D m3 = m1 + m2;

    EXPECT_EQ(m3(0,0),2.0f);  EXPECT_EQ(m3(0,1),8.0f);   EXPECT_EQ(m3(0,2),14.0f);
    EXPECT_EQ(m3(1,0),4.0f);  EXPECT_EQ(m3(1,1),10.0f);  EXPECT_EQ(m3(1,2),16.0f);
    EXPECT_EQ(m3(2,0),6.0f);  EXPECT_EQ(m3(2,1),12.0f);  EXPECT_EQ(m3(2,2),18.0f);

}

TEST(Matrix3DTest, SubMatrix3D)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);
    math::Matrix3D m2(a,b,c);

    math::Matrix3D m3 = m1 - m2;

    EXPECT_EQ(m3(0,0),0.0f);  EXPECT_EQ(m3(0,1),0.0f);   EXPECT_EQ(m3(0,2),0.0f);
    EXPECT_EQ(m3(1,0),0.0f);  EXPECT_EQ(m3(1,1),0.0f);  EXPECT_EQ(m3(1,2),0.0f);
    EXPECT_EQ(m3(2,0),0.0f);  EXPECT_EQ(m3(2,1),0.0f);  EXPECT_EQ(m3(2,2),0.0f);
}

TEST(Matrix3DTest, Multiplica_Matrix3DXScalar)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);

    math::Matrix3D m3 = m1 * 2;

    EXPECT_EQ(m3(0,0),2.0f);  EXPECT_EQ(m3(0,1),8.0f);   EXPECT_EQ(m3(0,2),14.0f);
    EXPECT_EQ(m3(1,0),4.0f);  EXPECT_EQ(m3(1,1),10.0f);  EXPECT_EQ(m3(1,2),16.0f);
    EXPECT_EQ(m3(2,0),6.0f);  EXPECT_EQ(m3(2,1),12.0f);  EXPECT_EQ(m3(2,2),18.0f);
}

TEST(Matrix3DTest, Multiplica_ScalarXMatrix3D)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);

    math::Matrix3D m3 = 2 * m1;

    EXPECT_EQ(m3(0,0),2.0f);  EXPECT_EQ(m3(0,1),8.0f);   EXPECT_EQ(m3(0,2),14.0f);
    EXPECT_EQ(m3(1,0),4.0f);  EXPECT_EQ(m3(1,1),10.0f);  EXPECT_EQ(m3(1,2),16.0f);
    EXPECT_EQ(m3(2,0),6.0f);  EXPECT_EQ(m3(2,1),12.0f);  EXPECT_EQ(m3(2,2),18.0f);
}

TEST(Matrix3DTest, PlusEqualMatrix3D)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);
    math::Matrix3D m2(a,b,c);

    m1 += m2;

    EXPECT_EQ(m1(0,0),2.0f);  EXPECT_EQ(m1(0,1),8.0f);   EXPECT_EQ(m1(0,2),14.0f);
    EXPECT_EQ(m1(1,0),4.0f);  EXPECT_EQ(m1(1,1),10.0f);  EXPECT_EQ(m1(1,2),16.0f);
    EXPECT_EQ(m1(2,0),6.0f);  EXPECT_EQ(m1(2,1),12.0f);  EXPECT_EQ(m1(2,2),18.0f);
}

TEST(Matrix3DTest, SubEqualMatrix3D)
{
    math::Vector3D a(1.0f,2.0f,3.0f);
    math::Vector3D b(4.0f,5.0f,6.0f);
    math::Vector3D c(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a,b,c);
    math::Matrix3D m2(a,b,c);

    m1 -= m2;

    EXPECT_EQ(m1(0,0),0.0f);  EXPECT_EQ(m1(0,1),0.0f);  EXPECT_EQ(m1(0,2),0.0f);
    EXPECT_EQ(m1(1,0),0.0f);  EXPECT_EQ(m1(1,1),0.0f);  EXPECT_EQ(m1(1,2),0.0f);
    EXPECT_EQ(m1(2,0),0.0f);  EXPECT_EQ(m1(2,1),0.0f);  EXPECT_EQ(m1(2,2),0.0f);
}

TEST(Matrix3DTest, ProductMatrix3DXMatrix3D)
{
    math::Vector3D a1(1.0f,2.0f,3.0f);
    math::Vector3D b1(4.0f,5.0f,6.0f);
    math::Vector3D c1(7.0f,8.0f,9.0f);

    math::Matrix3D m1(a1,b1,c1);
    
    math::Vector3D a2(9.0f,8.0f,7.0f);
    math::Vector3D b2(6.0f,5.0f,4.0f);
    math::Vector3D c2(3.0f,2.0f,1.0f);

    math::Matrix3D m2(a2,b2,c2);
    
    math::Matrix3D m3 = m1 * m2;

    EXPECT_EQ(m3(0,0),30.0f);  EXPECT_EQ(m3(0,1),24.0f);  EXPECT_EQ(m3(0,2),18.0f);
    EXPECT_EQ(m3(1,0),84.0f);  EXPECT_EQ(m3(1,1),69.0f);  EXPECT_EQ(m3(1,2),54.0f);
    EXPECT_EQ(m3(2,0),138.0f);  EXPECT_EQ(m3(2,1),114.0f);  EXPECT_EQ(m3(2,2),90.0f);
}