#ifndef TINYRENDERER_POLYGON3D_H
#define TINYRENDERER_POLYGON3D_H


#include <vector>
#include <cassert>
#include "point3d.h"

class Polygon3D {
public:
    // TODO(jlfwong): This incurs the cost of copying all the points.
    // This is super wasteful for all the points that are shared between faces.
    // I'm unsure of how to deal with ownership properly yet to get around this.
    Polygon3D(std::vector<Point3D> points) : points_(points) {
        assert(points.size() >= 3);
    }

    const std::vector<Point3D> &points() const {
        return points_;
    }

private:
    const std::vector<Point3D> points_;
};


#endif //TINYRENDERER_POLYGON3D_H
