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

    const T& operator[](const size_t i) const {
        assert(i < DIM);
        return data_[i];
    }

    const T dot(Vec<DIM, T> other) const {
        T ret = T();
        for (size_t i = 0; i < DIM; i++) {
            ret += data_[i] * other[i];
        }
        return ret;
    }

protected:
    T data_[DIM];
};

template <typename T> class Vec2 : public Vec<2, T> {
public:
    Vec2(T x, T y) {
        data_[0] = x;
        data_[1] = y;
    }

    const T& x() const { return data_[0]; }
    const T& y() const { return data_[1]; }

private:
    using Vec<2, T>::data_;
};

template <typename T> class Vec3 : public Vec<3, T> {
public:
    Vec3(T x, T y, T z) {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    const T& x() const { return data_[0]; }
    const T& y() const { return data_[1]; }
    const T& z() const { return data_[2]; }

private:
    using Vec<3, T>::data_;
};


// Type aliases for vectors

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif //TINYRENDERER_GEOMETRY_H
