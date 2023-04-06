#include "trianglemesh.h"
#include <iostream>

namespace data_representation {

TriangleMesh::TriangleMesh() { Clear(); std::cout << "triangle mesh created" << std::endl;}

TriangleMesh::~TriangleMesh() { std::cout << "triangle mesh destroyed" << std::endl; }

void TriangleMesh::Clear()
{
    vertices_.clear();
    faces_.clear();
    normals_.clear();
    tangents_.clear();
    binormals_.clear();
    texCoords_.clear();

    // Reset min and max
    min_ = Eigen::Vector3f(std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max(),
                           std::numeric_limits<float>::max());
    max_ = Eigen::Vector3f(std::numeric_limits<float>::lowest(),
                           std::numeric_limits<float>::lowest(),
                           std::numeric_limits<float>::lowest());
}

}   // namespace data_representation
