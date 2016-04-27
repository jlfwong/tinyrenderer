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

    EXPECT_DOUBLE_EQ(1.5 * 2.5 + 3.5 * 5.5, Vec2f(1.5, 3.5).dot(
            Vec2f(2.5, 5.5)));
}

TEST(VecTest, CrossProduct) {
    Vec3i cross = Vec3i(1, 0, 0).cross(Vec3i(0, 1, 0));
    EXPECT_EQ(0, cross.x());
    EXPECT_EQ(0, cross.y());
    EXPECT_EQ(1, cross.z());
}

TEST(VecTest, ImplicitConversion) {
    Vec2f v2f(1.7, 1.2);
    Vec3f v3f(1.7, 1.2, 2.1);

    Vec2i v2i(v2f);
    Vec3i v3i(v3f);

    EXPECT_EQ(2, v2i.x());
    EXPECT_EQ(1, v2i.y());

    EXPECT_EQ(2, v3i.x());
    EXPECT_EQ(1, v3i.y());
    EXPECT_EQ(2, v3i.z());
}