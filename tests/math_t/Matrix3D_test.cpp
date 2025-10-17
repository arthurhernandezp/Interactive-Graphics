#include <gtest/gtest.h>
#include "math/Matrix3D.hpp"
#include "math/Matrix3D.hpp"

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
