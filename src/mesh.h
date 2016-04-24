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
    virtual const size_t size() const = 0;
};

// Implementation of the Face interface which refrences points within a Mesh.
class MeshFace : Face {
public:
    virtual const Vec3f& operator[](const size_t i) const override {
        return *points_[i];
    }

    virtual const size_t size() const override {
        return points_.size();
    }

private:
    std::vector<const Vec3f*> points_;
    friend class Mesh;
};

// Space efficient storage for a Mesh in which positions are de-duplicated.
// Meant to be a direct in-memory representation of Wavefront .obj geometry.
class Mesh {
public:
    Mesh(const tinyobj::shape_t& shape) : name_(shape.name) {
        const size_t num_positions = shape.mesh.positions.size() / 3;

        const auto& positions = shape.mesh.positions;
        const auto& indices = shape.mesh.indices;

        for (size_t i = 0; i < num_positions; ++i) {
            positions_.push_back(Vec3f(positions[3 * i],
                                       positions[3 * i + 1],
                                       positions[3 * i + 2]));

        }

        int index_offset = 0;
        for (auto const& n_vertices_in_face : shape.mesh.num_vertices) {
            MeshFace face;

            for (auto index_in_face = 0;
                 index_in_face < n_vertices_in_face;
                 index_in_face++) {

                auto vertex_index = index_offset + index_in_face;
                auto position_index = indices[vertex_index];

                face.points_.push_back(&positions_[position_index]);
            }

            faces_.push_back(face);

            index_offset += n_vertices_in_face;
        }
    }

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
