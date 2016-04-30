#include <gtest/gtest.h>
#include "vec.h"

TEST(VecTest, ConstructorsAndAccessors) {
    Vec2i v2i(1, 2);
    Vec3i v3i(1, 2, 3);
    EXPECT_EQ(1, v2i.x());
    EXPECT_EQ(2, v2i.y());
    EXPECT_EQ(1, v3i.x());
    EXPECT_EQ(2, v3i.y());
    EXPECT_EQ(3, v3i.z());
}

TEST(VecTest, DotProduct) {
    EXPECT_EQ(1 * 2 + 3 * 5, Vec2i(1, 3).dot(Vec2i(2, 5)));
    EXPECT_EQ(1 * 2 + 3 * 5 + 7 * 9, Vec3i(1, 3, 7).dot(Vec3i(2, 5, 9)));

    EXPECT_FLOAT_EQ(1.5 * 2.5 + 3.5 * 5.5, Vec2f(1.5, 3.5).dot(
            Vec2f(2.5, 5.5)));
}

TEST(VecTest, CrossProduct) {
    EXPECT_EQ(Vec3i(0, 0, 1), Vec3i(1, 0, 0).cross(Vec3i(0, 1, 0)));
    EXPECT_EQ(Vec3i(0, 1, 0), Vec3i(1, 0, 0).cross(Vec3i(0, 0, -1)));
    EXPECT_EQ(Vec3i(0, 0, 0), Vec3i(1, 0, 0).cross(Vec3i(1, 0, 0)));
}

TEST(VecTest, Subtraction) {
    EXPECT_EQ(Vec3i(1, 2, 3), Vec3i(4, 4, 4) - Vec3i(3, 2, 1));
}


TEST(VecTest, ImplicitConversion) {
    Vec2f v2f(1.7, 1.2);
    Vec3f v3f(1.7, 1.2, 2.1);

    EXPECT_EQ(Vec2i(2, 1), Vec2i(v2f));
    EXPECT_EQ(Vec3i(2, 1, 2), Vec3i(v3f));
}

TEST(VecTest, Normalization) {
    EXPECT_EQ(Vec3f(1, 0, 0), Vec3f(1, 0, 0).normalized());
    EXPECT_EQ(Vec3f(1, 0, 0), Vec3f(4, 0, 0).normalized());
    EXPECT_EQ(Vec3f(0, 1, 0), Vec3f(0, 4, 0).normalized());
    float invsqrt2 = 1.0f/sqrt(2);
    EXPECT_EQ(Vec3f(invsqrt2, invsqrt2, 0), Vec3f(1, 1, 0).normalized());
    float invsqrt3 = 1.0f/sqrt(3);
    EXPECT_EQ(Vec3f(invsqrt3, invsqrt3, invsqrt3), Vec3f(1, 1, 1).normalized());
}