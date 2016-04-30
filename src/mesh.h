#ifndef TINYRENDERER_MESH_H
#define TINYRENDERER_MESH_H


#include <vector>
#include "vec.h"
#include "third_party/tiny_obj_loader.h"

// Face Interface
// If v-table lookup winds up being slow, can optimize via CRTP
class Face {
public:
    virtual const Vec3f& operator[](const size_t i) const = 0;
    virtual const Vec3f& normal() const = 0;
    virtual const size_t size() const = 0;
};

// Implementation of the Face interface which refrences points within a Mesh.
class MeshFace : Face {
public:
    virtual const Vec3f& operator[](const size_t i) const override {
        return *(points_[i]);
    }

    virtual const Vec3f &normal() const override {
        return normal_;
    }

    virtual const size_t size() const override {
        return points_.size();
    }

private:
    std::vector<const Vec3f*> points_;
    Vec3f normal_;
    friend class Mesh;
};

// Space efficient storage for a Mesh in which positions are de-duplicated.
// Meant to be a direct in-memory representation of Wavefront .obj geometry.
class Mesh {
public:
    Mesh(const tinyobj::shape_t&);

    const std::vector<MeshFace>& faces() const {
        return faces_;
    }

    const std::string& name() const {
        return name_;
    }
private:
    std::vector<Vec3f> positions_;
    std::vector<MeshFace> faces_;
    std::string name_;
};


#endif //TINYRENDERER_MESH_H
