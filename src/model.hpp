#ifndef RENDER_MODEL_HPP
#define RENDER_MODEL_HPP


#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>


class Model
{
public:
    Model(std::initializer_list<glm::vec3> vertices);
    ~Model();

    void draw();

private:
    std::vector<glm::vec3> vertices;
    GLuint vertex_array;
    GLuint vertex_buffer;
};


#endif //RENDER_MODEL_HPP
