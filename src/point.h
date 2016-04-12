#ifndef TINYRENDERER_POINT_H
#define TINYRENDERER_POINT_H

class Point2D {
public:
    Point2D(double x, double y) : x_(x), y_(y) {};

private:
    double x_;
    double y_;
};

#endif //TINYRENDERER_POINT_H
