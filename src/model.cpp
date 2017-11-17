#include "model.hpp"


Model::Model(std::initializer_list<glm::vec3> vertices) : vertices(vertices)
{
    glGenVertexArrays(1, &vertex_array);
    glBindVertexArray(vertex_array);

    glGenBuffers(1, &vertex_buffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), this->vertices.data(), GL_STATIC_DRAW);
}


Model::~Model()
{
    // Cleanup VBO
    glDeleteBuffers(1, &vertex_buffer);
    glDeleteVertexArrays(1, &vertex_array);
}


void Model::draw()
{
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);

    glVertexAttribPointer(
            0,                    // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,  // size
            GL_FLOAT,             // type
            GL_FALSE,             // normalized?
            0,                    // stride
            (void*)0              // array buffer offset
    );

    // Draw the triangle !
    glDrawArrays(GL_TRIANGLES, 0, vertices.size());

    glDisableVertexAttribArray(0);
}
