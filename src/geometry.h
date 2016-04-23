#include <cstdlib>
#include <cassert>

#ifndef TINYRENDERER_GEOMETRY_H
#define TINYRENDERER_GEOMETRY_H

// General definition for a mathematical vector class.
//
// You probably don't want to use this directly. See the type aliases
// for Vec2f, Vec2i, Vec3f, etc. at the bottom of this file.

template <size_t DIM, typename T> class Vec {
public:
    Vec() {
        for (size_t i = 0; i < DIM; i++) {
            data_[i] = T();
        }
    }

    // Only implemented for 2D vectors
    Vec(T x, T y);

    // Only implemented for 3D vectors
    Vec(T x, T y, T z);

    const T& x() const;
    const T& y() const;
    const T& z() const;

    const T& operator[](const size_t i) const {
        assert(i < DIM);
        return data_[i];
    }

    const T dot(Vec<DIM, T> other) const {
        T ret = T();
        for (size_t i = 0; i <= DIM; i++) {
            ret += this[i] * other[i];
        }
        return ret;
    }

private:
    T data_[DIM];
};

// Specialization for 2D vectors
template <typename T> Vec<2, T>::Vec(T x, T y) {
    data_[0] = x;
    data_[1] = y;
}
template <typename T> const T& Vec<2, T>::x() const {
    return data_[0];
}
template <typename T> const T& Vec<2, T>::y() const {
    return data_[1];
}

// Specialization for 3D vectors
template <typename T> Vec<3, T>::Vec(T x, T y, T z) {
    data_[0] = x;
    data_[1] = y;
    data_[2] = z;
}
template <typename T> const T& Vec<3, T>::x() const {
    return data_[0];
}
template <typename T> const T& Vec<3, T>::y() const {
    return data_[1];
}
template <typename T> const T& Vec<3, T>::z() const {
    return data_[2];
}



// Type aliases for vectors

typedef Vec<2, float> Vec2f;
typedef Vec<2, int> Vec2i;
typedef Vec<3, float> Vec3f;
typedef Vec<3, int> Vec3i;

#endif //TINYRENDERER_GEOMETRY_H
