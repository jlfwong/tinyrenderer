#include "mesh.h"

Mesh::Mesh(const tinyobj::shape_t& shape) : name_(shape.name) {
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
