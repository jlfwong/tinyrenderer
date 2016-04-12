#ifndef TINYRENDERER_POINT3D_H
#define TINYRENDERER_POINT3D_H

class Point3D {
public:
    Point3D(double x, double y, double z) : x_(x), y_(y), z_(z) {};

    double x() const {
        return x_;
    }
    double y() const {
        return y_;
    }
    double z() const {
        return z_;
    }

private:
    double x_;
    double y_;
    double z_;
};

#endif //TINYRENDERER_POINT3D_H
