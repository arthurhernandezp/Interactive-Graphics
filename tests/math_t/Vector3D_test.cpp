#include <gtest/gtest.h>
#include "math/Vector3D.hpp"

TEST(Vector3DTest,DefaultConstructor)
{
    math::Vector3D vec;

    EXPECT_EQ(vec.x, 0.0f);
    EXPECT_EQ(vec.y, 0.0f);
    EXPECT_EQ(vec.z, 0.0f);
}

TEST(Vector3DTest,ConstructorWithParams)
{
    math::Vector3D vec(1.0f,1.0f,1.0f);

    EXPECT_EQ(vec.x, 1.0f);
    EXPECT_EQ(vec.y, 1.0f);
    EXPECT_EQ(vec.z, 1.0f);
}

TEST(Vector3DTest,AccessVector3DMembers)
{
    math::Vector3D vec(1.0f,2.0f,3.0f);

    EXPECT_EQ(vec[0], 1.0f);
    EXPECT_EQ(vec[1], 2.0f);
    EXPECT_EQ(vec[2], 3.0f);
}

TEST(Vector3DTest,AddVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2(3.0f,3.0f,3.0f);
    math::Vector3D vec3 = vec1 + vec2;
    EXPECT_EQ(vec3.x, 4.0f);
    EXPECT_EQ(vec3.y, 5.0f);
    EXPECT_EQ(vec3.z, 6.0f);
}

TEST(Vector3DTest,SubVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2(3.0f,3.0f,3.0f);
    math::Vector3D vec3 = vec1 - vec2;

    EXPECT_EQ(vec3.x, -2.0f);
    EXPECT_EQ(vec3.y, -1.0f);
    EXPECT_EQ(vec3.z, 0.0f);
}

TEST(Vector3DTest,NegativeVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2 = -vec1;

    EXPECT_EQ(vec2.x, -1.0f);
    EXPECT_EQ(vec2.y, -2.0f);
    EXPECT_EQ(vec2.z, -3.0f);
}

TEST(Vector3DTest,AssignmentVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2 = vec1;

    EXPECT_EQ(vec2.x, 1.0f);
    EXPECT_EQ(vec2.y, 2.0f);
    EXPECT_EQ(vec2.z, 3.0f);
}

TEST(Vector3DTest,PlusEqualVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2(3.0f,3.0f,3.0f);

    vec2 += vec1;

    EXPECT_EQ(vec2.x, 4.0f);
    EXPECT_EQ(vec2.y, 5.0f);
    EXPECT_EQ(vec2.z, 6.0f);
}

TEST(Vector3DTest,MinusEqualVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);
    math::Vector3D vec2(3.0f,3.0f,3.0f);
    vec1 -= vec2;

    EXPECT_EQ(vec1.x, -2.0f);
    EXPECT_EQ(vec1.y, -1.0f);
    EXPECT_EQ(vec1.z, 0.0f);
}

TEST(Vector3DTest,DivideVector3D)
{
    math::Vector3D vec1(2.0f,4.0f,6.0f);
    math::Vector3D vec2 = vec1 / 2;

    EXPECT_EQ(vec2.x, 1.0f);
    EXPECT_EQ(vec2.y, 2.0f);
    EXPECT_EQ(vec2.z, 3.0f);
}

TEST(Vector3DTest,DivideByZeroExceptionVector3D)
{
    math::Vector3D vec1(2.0f,4.0f,6.0f);

    EXPECT_ANY_THROW(vec1 / 0);
}

TEST(Vector3DTest,InvalidAcessVector3D)
{
    math::Vector3D vec1(1.0f,2.0f,3.0f);

    EXPECT_THROW(vec1[4],std::runtime_error);
    EXPECT_THROW(vec1[-1],std::runtime_error);
}

TEST(Vector3DTest,MagnitudeVector3D)
{
    math::Vector3D vec(2.0f,1.0f,2.0f);

    int magnitude = vec.magnitude();

    EXPECT_EQ(magnitude,3);
}

TEST(Vector3DTest, NormalizeZeroVector)
{
    math::Vector3D vec(0.0f, 0.0f, 0.0f);

    auto normalizedVector = vec.normalized();

    EXPECT_EQ(normalizedVector.x, 0.0f);
    EXPECT_EQ(normalizedVector.y, 0.0f);
    EXPECT_EQ(normalizedVector.z, 0.0f);
}

TEST(Vector3DTest,ZeroMagnitudeVector3D)
{
    math::Vector3D vec;

    int magnitude = vec.magnitude();

    EXPECT_EQ(magnitude,0);
}

TEST(Vector3DTest,ScalarMultiplicationMagnitudeVector3D)
{
    math::Vector3D vec1(2.0f,1.0f,2.0f);
    math::Vector3D vec2(4.0f,2.0f,4.0f);

    int magnitudeVec1 = vec1.magnitude();
    int magnitudeVec2 = vec2.magnitude();

    EXPECT_EQ( magnitudeVec1 * 2, magnitudeVec2 );
}

TEST(Vector3DTest,DotProductVector3D)
{
    math::Vector3D a(-6.0f,8.0f,0.0f);
    math::Vector3D b(5.0f,12.0f,0.0f);

    float dotProductResult = a.dotProduct(b);

    EXPECT_EQ(dotProductResult,66);
}

TEST(Vector3DTest,DotProductPerpendicularVector3D)
{
    math::Vector3D a(-12.0f,16.0f,0.0f);
    math::Vector3D b(12.0f,9.0f,0.0f);

    float dotProductResult = a.dotProduct(b);

    EXPECT_EQ(dotProductResult,0);
}

TEST(Vector3DTest,CrossProductVector3D)
{
    math::Vector3D a(2.0f,3.0f,4.0f);
    math::Vector3D b(5.0f,6.0f,7.0f);

    math::Vector3D crossProductResult = a.crossProduct(b);

    ASSERT_EQ(crossProductResult.x,-3);
    ASSERT_EQ(crossProductResult.y,6);
    ASSERT_EQ(crossProductResult.z,-3);
}