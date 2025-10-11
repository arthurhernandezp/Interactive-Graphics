#include <gtest/gtest.h>
#include "math/Vector3D.hpp"

TEST(Vector3DTest,ConstructorWithParams)
{
    math::Vector3D vec(0.0f,0.0f,0.0f);

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.z, 0.0f);
}

TEST(Vector3DTest,AccessVector3DMembers)
{
    math::Vector3D vec(1.0f,2.0f,3.0f);

    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
    EXPECT_EQ(vec[2], 3.0f);
}
