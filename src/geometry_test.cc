#include <gtest/gtest.h>
#include "geometry.h"

TEST(VectorTest, ConstructorsAndAccessors) {
    auto v1 = Vec2i(1, 2);
    auto v2 = Vec3i(1, 2, 3);
    EXPECT_EQ(1, v1.x());
    EXPECT_EQ(2, v1.y());
    EXPECT_EQ(1, v2.x());
    EXPECT_EQ(2, v2.y());
    EXPECT_EQ(3, v2.z());
}

TEST(VectorTest, DotProduct) {
    EXPECT_EQ(1 * 2 + 3 * 5, Vec2i(1, 3).dot(Vec2i(2, 5)));
    EXPECT_EQ(1 * 2 + 3 * 5 + 7 * 9, Vec3i(1, 3, 7).dot(Vec3i(2, 5, 9)));

    EXPECT_DOUBLE_EQ(1.5 * 2.5 + 3.5 * 5.5, Vec2f(1.5, 3.5).dot(
            Vec2f(2.5, 5.5)));
}