#include <cmath>
#include "vec.h"

// Efficient converters between float and int variants for convenience
template <> template <> Vec<3, int>::Vec(const Vec<3, float> &v) :
        Vec(int(v.x() + 0.5f), int(v.y() + 0.5f), int(v.z() + 0.5f)) {}
template <> template <> Vec<3, float>::Vec(const Vec<3, int> &v) :
        Vec(v.x(), v.y(), v.z()) {}
template <> template <> Vec<2, int>::Vec(const Vec<2, float> &v) :
        Vec(int(v.x() + 0.5f), int(v.y() + 0.5f)) {}
template <> template <> Vec<2, float>::Vec(const Vec<2, int> &v) :
        Vec(v.x(), v.y()) {}

template <size_t DIM, typename T> Vec<3, T> Vec<DIM, T>::cross(const Vec<3, T>& b) const {
    assert(DIM == 3);
    const Vec<DIM, T>& a = *this;
    return Vec<3, T>(
            a.y() * b.z() - a.z() * b.y(),
            a.z() * b.x() - a.x() * b.z(),
            a.x() * b.y() - a.y() * b.x()
    );
};

template <> const bool Vec<2, int>::operator==(const Vec<2, int>& other) const {
    return data_[0] == other[0] &&
           data_[1] == other[1];
};
template <> const bool Vec<3, int>::operator==(const Vec<3, int>& other) const {
    return data_[0] == other[0] &&
           data_[1] == other[1] &&
           data_[2] == other[2];
};

const double float_eq(float a, float b) {
    return std::abs(a - b) < 1e-6;
}

template <> const bool Vec<2, float>::operator==(const Vec<2, float>& other) const {
    return float_eq(data_[0], other[0]) &&
           float_eq(data_[1], other[1]);
};
template <> const bool Vec<3, float>::operator==(const Vec<3, float>& other) const {
    return float_eq(data_[0], other[0]) &&
           float_eq(data_[1], other[1]) &&
           float_eq(data_[2], other[2]);
};

// Explicit instantiations
template class Vec<2, int>;
template class Vec<2, float>;
template class Vec<3, int>;
template class Vec<3, float>;
