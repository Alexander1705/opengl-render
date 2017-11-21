#include "model.hpp"
#include "opengl/shaders.hpp"


Model::Model(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &colors)
        : vertices(vertices), colors(colors)
{
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &vbo_vertices);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &vbo_colors);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(glm::vec3), this->colors.data(), GL_STATIC_DRAW);
}


Model::~Model()
{
    // Cleanup VBO
    glDeleteBuffers(1, &vbo_vertices);
    glDeleteVertexArrays(1, &vao);
}


void Model::render(const glm::mat4 &transformation)
{
    auto &shader = enable_shader();

    GLint MVPMatrix = glGetUniformLocation(shader, "MVP");
    glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &transformation[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_vertices);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_colors);
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
