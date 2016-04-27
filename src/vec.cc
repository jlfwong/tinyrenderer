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

template <typename T> Vec3<T> Vec3<T>::cross(const Vec3<T>& b) const {
    const Vec3<T>& a = *this;
    return Vec3<T>(
            a.y() * b.z() - a.z() * b.y(),
            a.z() * b.x() - a.x() * b.z(),
            a.x() * b.y() - a.y() * b.x()
    );
};

// Explicit instantiations
template class Vec2<int>;
template class Vec2<float>;
template class Vec3<int>;
template class Vec3<float>;
