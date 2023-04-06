#ifndef GLUTILS_H
#define GLUTILS_H

#include <GL/glew.h>
#include <iostream>
#include <QOpenGLShaderProgram>
#include <sstream>
#include <fstream>

namespace glutils {

    bool ReadFile(const std::string filename, std::string *shader_source);
    bool LoadProgram(const std::string &vertex, const std::string &fragment, QOpenGLShaderProgram *program);

    void GLClearError();
    void GLCheckError();
}

#endif // GLUTILS_H
