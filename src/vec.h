#include <cstdlib>
#include <cassert>
#include <iostream>
#include <cmath>

#ifndef TINYRENDERER_VEC_H
#define TINYRENDERER_VEC_H

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

    Vec(T x, T y) {
        assert(DIM == 2);
        data_[0] = x;
        data_[1] = y;
    }

    Vec(T x, T y, T z) {
        assert(DIM == 3);
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    template <typename U> Vec(const Vec<DIM, U>&);

    const T& operator[](const size_t i) const {
        assert(i < DIM);
        return data_[i];
    }

    const bool operator==(const Vec<DIM, T>& other) const;

    const T dot(const Vec<DIM, T>& other) const {
        T ret = T();
        for (size_t i = 0; i < DIM; i++) {
            ret += data_[i] * other[i];
        }
        return ret;
    }

    Vec<DIM, T> operator-(const Vec<DIM, T>& other) const {
        Vec<DIM, T> ret;
        for (size_t i = 0; i < DIM; i++) {
            ret.data_[i] = data_[i] - other[i];
        }
        return ret;
    };

    Vec<DIM, T> normalized() const {
        // This method won't work very well when T is int, but hopefully
        // nobody will try to do that...

        // TODO(jlfwong): This could run into overflow, but let's just hope not?
        T mag_squared = T();
        for (size_t i = 0; i < DIM; i++) {
            mag_squared += data_[i] * data_[i];
        }
        T mag = sqrt(mag_squared);
        Vec<DIM, T> ret;
        for (size_t i = 0; i < DIM; i++) {
            ret.data_[i] = data_[i] / mag;
        }
        return ret;
    };

    T x() const { return data_[0]; }
    T y() const { return data_[1]; }
    T z() const { assert(DIM == 3); return data_[2]; }

    Vec<3, T> cross(const Vec<3, T>&) const;

protected:
    T data_[DIM];
};

template <size_t DIM, typename T> std::ostream& operator<<(
        std::ostream& os, const Vec<DIM, T>& v) {
    os << "Vec<" << DIM << "," << typeid(T).name() << ">(";
    for (size_t i = 0; i < DIM; i++) {
        if (i) {
            os << ", ";
        }
        os << v[i];
    }
    os << ")";
};


// Type aliases for vectors

typedef Vec<2, float> Vec2f;
typedef Vec<2, int> Vec2i;
typedef Vec<3, float> Vec3f;
typedef Vec<3, int> Vec3i;

#endif //TINYRENDERER_GEOMETRY_H
