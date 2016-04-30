#include <gtest/gtest.h>
#include "third_party/tiny_obj_loader.h"
#include "mesh.h"

const char* SIMPLE_CUBE = R"cube(
g cube

v  0.0  0.0  0.0
v  0.0  0.0  1.0
v  0.0  1.0  0.0
v  0.0  1.0  1.0
v  1.0  0.0  0.0
v  1.0  0.0  1.0
v  1.0  1.0  0.0
v  1.0  1.0  1.0

f  1  7  5
f  1  3  7
f  1  4  3
f  1  2  4
f  3  8  7
f  3  4  8
f  5  7  8
f  5  8  6
f  1  5  6
f  1  6  2
f  2  6  8
f  2  8  4
)cube";

class MeshTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string err;
        std::stringstream ss(SIMPLE_CUBE);
        tinyobj::MaterialFileReader mr("data");

        tinyobj::LoadObj(shapes, materials, err, ss, mr);

        cube_mesh = new Mesh(shapes[0]);
    }

    virtual void TearDown() {
        delete cube_mesh;
    }

    Mesh* cube_mesh;
};

TEST_F(MeshTest, NameSet) {
    EXPECT_EQ("cube", cube_mesh->name());
}

TEST_F(MeshTest, FaceCount) {
    EXPECT_EQ(12, cube_mesh->faces().size());  // 16 because faces are triangularized
}

TEST_F(MeshTest, FaceNormal) {
    EXPECT_EQ(Vec3f(0, 0, -1), cube_mesh->faces()[0].normal());
}