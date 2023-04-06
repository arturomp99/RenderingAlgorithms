#include "glutils.h"

bool glutils::ReadFile(const std::string filename, std::string *shader_source) {
  /*// Log the current working directory
  char tmp[256];
  _getcwd(tmp, 256);
  std::cout << "Current working directory: " << tmp << std::endl;*/
  std::ifstream infile(filename.c_str());
  if (!infile.is_open() || !infile.good()) {
    std::cerr << "Error " + filename + " not found." << std::endl;
    return false;
  }

  std::stringstream stream;
  stream << infile.rdbuf();
  infile.close();

  *shader_source = stream.str();
  return true;
}


bool glutils::LoadProgram(const std::string &vertex, const std::string &fragment,
                 QOpenGLShaderProgram *program) {
  std::string vertex_shader, fragment_shader;
  bool res =
      ReadFile(vertex, &vertex_shader) && ReadFile(fragment, &fragment_shader);

  if (res) {
    program->addShaderFromSourceCode(QOpenGLShader::Vertex,
                                     vertex_shader.c_str());
    program->addShaderFromSourceCode(QOpenGLShader::Fragment,
                                     fragment_shader.c_str());
    program->bindAttributeLocation("vertex", 0);
    program->bindAttributeLocation("aTexCoords", 1);
    program->bindAttributeLocation("normal", 2);
    program->bindAttributeLocation("tangent", 3);
    program->bindAttributeLocation("binormal", 4);
    program->link();
  }

  return res;
}

void glutils::GLClearError()
{
    while (glGetError() != GL_NO_ERROR);
}

void glutils::GLCheckError()
{
    while (GLenum error = glGetError())
    {
        std::cout << "[OpenGL Error] (" << error << ")" << std::endl;
    }

    std::cout <<"\tno more errors" << std::endl;
}
