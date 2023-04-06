#ifndef SCENE_H
#define SCENE_H

#include <GL/glew.h>
#include <QWidget>
#include <QMouseEvent>
#include <QOpenGLShaderProgram>
#include "camera.h"
#include "trianglemesh.h"
#include <iostream>

class Scene : public QObject
{
    Q_OBJECT
public:
    Scene() {}
    virtual ~Scene() {};

    virtual void initialize(std::shared_ptr<data_representation::TriangleMesh> mesh_ = nullptr) = 0;
    virtual void reset() = 0;
    virtual void paint(const Camera& cam) = 0;

    virtual void mousePressed (const QMouseEvent*, const Camera&) {};
    virtual void mouseMoved   (const QMouseEvent*, const Camera&) {};
    virtual void mouseReleased(const QMouseEvent*, const Camera&) {};
    virtual void keyPressed   (const QKeyEvent*,   const Camera&) {};

    virtual QWidget* sceneUI() = 0;

protected:
    std::unique_ptr<QOpenGLShaderProgram> program_;
    Camera camera_;
    std::shared_ptr<data_representation::TriangleMesh> mesh;

    int mouseX, mouseY;
};

inline void mousePressed (const QMouseEvent*, const Camera&) {
    std::cout << "mousePressed" << std::endl;
}

#endif // SCENE_H
