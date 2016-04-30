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

// TODO(jlfwong); The inclusion of VecT in the template arguments here makes
// this thing an abomination. It's necessary in order to make subtraction and
// normalized() return Vec2<T> and Vec3<T> instead of Vec<2, T>, and Vec<3, T>.
// We care about this, because e.g. v.cross() is only defined on Vec3, not Vec2.
//
// There are *probably* more sensible ways of dealing with this (even code
// dupe is probably more reasonable than using CRTP for this.
template <size_t DIM, typename T, typename VecT> class Vec {
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

    const bool operator==(const VecT& other) const;

    const T dot(const VecT& other) const {
        T ret = T();
        for (size_t i = 0; i < DIM; i++) {
            ret += data_[i] * other[i];
        }
        return ret;
    }

    VecT operator-(const VecT& other) const {
        VecT ret;
        for (size_t i = 0; i < DIM; i++) {
            ret.data_[i] = data_[i] - other[i];
        }
        return ret;
    };

    VecT normalized() const {
        // This method won't work very well when T is int, but hopefully
        // nobody will try to do that...

        // TODO(jlfwong): This could run into overflow, but let's just hope not?
        T mag_squared = T();
        for (size_t i = 0; i < DIM; i++) {
            mag_squared += data_[i] * data_[i];
        }
        T mag = sqrt(mag_squared);
        VecT ret;
        for (size_t i = 0; i < DIM; i++) {
            ret.data_[i] = data_[i] / mag;
        }
        return ret;
    };

protected:
    T data_[DIM];
};

template <size_t DIM, typename T, typename VecT> std::ostream& operator<<(
        std::ostream& os, const Vec<DIM, T, VecT>& v) {
    os << "Vec<" << DIM << "," << typeid(T).name() << ">(";
    for (size_t i = 0; i < DIM; i++) {
        if (i) {
            os << ", ";
        }
        os << v[i];
    }
    os << ")";
};

template <typename T> class Vec2 : public Vec<2, T, Vec2<T> > {
public:
    // For converting between Vec2i and Vec2f
    template <typename U> Vec2(const Vec2<U>&);

    Vec2(T x, T y) {
        data_[0] = x;
        data_[1] = y;
    }

    Vec2() : Vec2(0, 0) {}

    T x() const { return data_[0]; }
    T y() const { return data_[1]; }

private:
    using Vec<2, T, Vec2<T> >::data_;

    // Holy crap I can't believe you're allowed to do this.
    // Allows base class to access private members of derived class
    friend Vec<2, T, Vec2<T> >;
};

template <typename T> class Vec3 : public Vec<3, T, Vec3<T> > {
public:
    // For converting between Vec3i and Vec3f
    template <typename U> Vec3(const Vec3<U>&);

    Vec3(T x, T y, T z) {
        data_[0] = x;
        data_[1] = y;
        data_[2] = z;
    }

    Vec3() : Vec3(0, 0, 0) {}

    T x() const { return data_[0]; }
    T y() const { return data_[1]; }
    T z() const { return data_[2]; }

    Vec3<T> cross(const Vec3<T>&) const;

private:
    using Vec<3, T, Vec3<T> >::data_;
    friend Vec<3, T, Vec3<T> >;
};

template <typename T> std::ostream& operator<<(
        std::ostream& os, const Vec2<T>& v) {
    os << static_cast<Vec<2, T, Vec2<T> > >(v);
};

template <typename T> std::ostream& operator<<(
        std::ostream& os, const Vec3<T>& v) {
    os << static_cast<Vec<3, T, Vec3<T> > >(v);
};


// Type aliases for vectors

typedef Vec2<float> Vec2f;
typedef Vec2<int> Vec2i;
typedef Vec3<float> Vec3f;
typedef Vec3<int> Vec3i;

#endif //TINYRENDERER_GEOMETRY_H
