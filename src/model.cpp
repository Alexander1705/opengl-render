#include "model.hpp"
#include "opengl/shaders.hpp"


Model::Model(Buffer<glm::vec3> &&vertices, Buffer<glm::vec3> &&normals)
        : vertices(std::move(vertices)), normals(std::move(normals))
{
    glGenVertexArrays(1, &vao);
}


Model::~Model()
{
    glDeleteVertexArrays(1, &vao);
}


void Model::render(const glm::mat4 &transformation)
{
    glBindVertexArray(vao);

    auto &shader = enable_shader();

    GLint MVPMatrix = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &transformation[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, normals);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}


OpenGL::ShaderProgram & Model::enable_shader()
{
    static OpenGL::ShaderProgram shader_program;
    static bool loaded = false;

    if (!loaded)
    {
        loaded = true;

        shader_program.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
        shader_program.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    }

    shader_program.use_program();

    return shader_program;
}
