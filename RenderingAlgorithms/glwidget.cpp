#include "glwidget.h"
#include <iostream>

GLWidget::GLWidget(QWidget* parent) : QOpenGLWidget(parent)
{
    scene = nullptr;

}

GLWidget::~GLWidget()
{
}

void GLWidget::setScene(Scene* sc)
{
    if (scene) delete scene;
    scene = sc;

    this->makeCurrent();
    scene->initialize(mesh_);

    update();
}

void GLWidget::initializeGL()
{
    glewInit();
    initializeOpenGLFunctions();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void GLWidget::paintGL()
{
    // Clear
    glClearColor(0.64f, 0.74f, 0.85f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Draw
    if (scene) scene->paint(camera);
}

bool GLWidget::loadModel(QString fileName)  // TODO, IMPLEMENT LOADMODEL()
{
    std::string file = fileName.toUtf8().constData();
    size_t pos = file.find_last_of(".");
    std::string type = file.substr(pos + 1);

    if (mesh_) mesh_.reset();
    mesh_ = std::make_shared<data_representation::TriangleMesh>();

    bool res = false;
    if (type.compare("ply") == 0) {
      res = data_representation::ReadFromPly(file, mesh_.get());
    }
    if (!res) return false;
    return true;
}

void GLWidget::chooseModel() // TODO, IMPLEMENT A WINDOW TO SHOOSE A PLY FILE
{
    std::cout << "choose model" << std::endl;
}

void GLWidget::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
        std::cout << "left mouse button pressed" << std::endl;
    if (event->button() == Qt::RightButton)
        std::cout << "right mouse button pressed" << std::endl;
}

void GLWidget::mouseMoveEvent(QMouseEvent*) {
    std::cout << "Mouse moved" << std::endl;
}

void GLWidget::mouseReleaseEvent(QMouseEvent*) {
    std::cout << "mouse release event" << std::endl;
}

void GLWidget::wheelEvent(QWheelEvent* event) {
    std::cout << "wheel event" << std::endl;
}

void GLWidget::keyPressEvent(QKeyEvent *event) {
    std::cout << "key pressed event" << std::endl;
}
