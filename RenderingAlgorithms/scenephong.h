#ifndef SCENEPHONG_H
#define SCENEPHONG_H

#include "scene.h"
#include "widgetphong.h"
#include "glutils.h"

class ScenePhong : public Scene
{
public:
    ScenePhong();
    virtual ~ScenePhong();

    virtual void initialize(std::shared_ptr<data_representation::TriangleMesh> mesh_ = nullptr);
    virtual void reset();
    virtual void paint(const Camera& cam);

    virtual QWidget* sceneUI() { return widget; }

private:
    WidgetPhong* widget = nullptr;
    GLuint VAO, coordBuffer, texCoordBuffer, normalBuffer, EBO;
    int nTriangles; // amount of triangles to be drawn
};

#endif // SCENEPHONG_H
