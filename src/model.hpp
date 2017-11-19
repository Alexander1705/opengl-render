#ifndef RENDER_MODEL_HPP
#define RENDER_MODEL_HPP


#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>


class Model
{
public:
    Model(const std::vector<glm::vec3> &vertices, const std::vector<glm::vec3> &colors);
    ~Model();

    void draw();

private:
    std::vector<glm::vec3> vertices;
    std::vector<glm::vec3> colors;
    GLuint vao;
    GLuint vbo_vertices;
    GLuint vbo_colors;
};


#endif //RENDER_MODEL_HPP
