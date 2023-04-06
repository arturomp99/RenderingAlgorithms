#ifndef TRIANGLEMESH_H
#define TRIANGLEMESH_H


#include <eigen3/Eigen/Geometry>

#include <vector>

namespace data_representation {

struct Texture { // Struct defining the textures
  unsigned int id;
  std::string type;
  std::string path;
};

class TriangleMesh {
 public:

  TriangleMesh();
  ~TriangleMesh();

  /**
   * @brief Clear Empties the data arrays and resets the bounding box vertices.
   */
  void Clear();

 public:
  std::vector<float> vertices_;
  std::vector<int> faces_;
  std::vector<float> normals_;
  std::vector<float> tangents_;
  std::vector<float> binormals_;
  std::vector<float> texCoords_;
  std::vector<Texture> textures_; // A vector with all the textures

  Eigen::Vector3f min_; // The minimum point of the bounding box
  Eigen::Vector3f max_; // The maximum point of the bounding box
};

}  // namespace data_representation

#endif // TRIANGLEMESH_H
