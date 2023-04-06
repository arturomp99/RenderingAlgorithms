#include "scenephong.h"
#include <iostream>

ScenePhong::ScenePhong()
{
    widget = new WidgetPhong();
    std::cout << "Phong scene loaded" << std::endl;
}

ScenePhong::~ScenePhong()
{
    if (widget) delete widget;
}

void ScenePhong::initialize(std::shared_ptr<data_representation::TriangleMesh> mesh_)
{
    // Create the program
    program_= std::make_unique<QOpenGLShaderProgram>();
    if (!glutils::LoadProgram("../RenderingAlgorithms/shaders/phong.vert", "../RenderingAlgorithms/shaders/phong.frag", program_.get()))
        exit(0);

    // Buffers creation
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &coordBuffer);
    glGenBuffers(1, &texCoordBuffer);
    glGenBuffers(1, &normalBuffer);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, coordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(mesh_->vertices_.size()), &mesh_->vertices_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, texCoordBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(mesh_->texCoords_.size()), &mesh_->texCoords_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float)*(mesh_->normals_.size()), &mesh_->normals_[0], GL_STATIC_DRAW);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    nTriangles = mesh_->faces_.size();
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float)*(nTriangles), &mesh_->faces_[0], GL_STATIC_DRAW);
    glBindVertexArray(0);


}

void ScenePhong::reset()
{

}

void ScenePhong::paint(const Camera& cam)
{
    // Get projection matrices

    // Bind shader
    program_->bind();

    // Set uniforms

    // Bind textures

    // Draw
    glBindVertexArray(VAO);
    glutils::GLClearError();
    glDrawElements(GL_TRIANGLES, nTriangles, GL_UNSIGNED_INT, (void*) 0);
    glutils::GLCheckError();
    glBindVertexArray(0);
}
