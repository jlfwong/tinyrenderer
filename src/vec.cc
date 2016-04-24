#include "vec.h"

// Efficient converters between float and int variants for convenience
template <> template <> Vec3<int>::Vec3(const Vec3<float> &v) :
        Vec3(int(v.x() + 0.5f), int(v.y() + 0.5f), int(v.z() + 0.5f)) {}
template <> template <> Vec3<float>::Vec3(const Vec3<int> &v) :
        Vec3(v.x(), v.y(), v.z()) {}

template <> template <> Vec2<int>::Vec2(const Vec2<float> &v) :
        Vec2(int(v.x() + 0.5f), int(v.y() + 0.5f)) {}
template <> template <> Vec2<float>::Vec2(const Vec2<int> &v) :
        Vec2(v.x(), v.y()) {}
