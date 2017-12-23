#ifndef RENDER_MODEL_HPP
#define RENDER_MODEL_HPP


#include <vector>

#include <GL/glew.h>
#include <glm/glm.hpp>
#include "opengl/shaders.hpp"
#include "opengl/buffer.hpp"


using OpenGL::Buffer;


class Model
{
public:
    Model(Buffer<glm::vec3> &&vertices, Buffer<glm::vec3> &&normals);
    ~Model();

    void render(const glm::mat4 &transformation);
    OpenGL::ShaderProgram & enable_shader();

private:
    GLuint vao;

    Buffer<glm::vec3> vertices;
    Buffer<glm::vec3> normals;
};


#endif //RENDER_MODEL_HPP
