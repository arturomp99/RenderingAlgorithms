#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <GL/glew.h>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLWidget>
#include <QKeyEvent>
#include <QElapsedTimer>
#include "camera.h"
#include "scene.h"
#include "mesh_io.h"

class GLWidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    GLWidget(QWidget* = nullptr);
    ~GLWidget();

    void setScene(Scene* sc);
    bool loadModel(QString fileName);

public slots:
    void chooseModel();

    virtual void mousePressEvent(QMouseEvent*);
    virtual void mouseMoveEvent(QMouseEvent*);
    virtual void mouseReleaseEvent(QMouseEvent*);
    virtual void wheelEvent(QWheelEvent* event);
    virtual void keyPressEvent(QKeyEvent *event);

protected:
    virtual void initializeGL();
    virtual void paintGL();

    // Scene
    Scene* scene;

    // Camera
    Camera camera;

    // Mesh
    std::shared_ptr<data_representation::TriangleMesh> mesh_;
};

#endif // GLWIDGET_H
