#ifndef RENDER_SCENE_HPP
#define RENDER_SCENE_HPP


#include <map>
#include <glm/vec3.hpp>
#include <memory>
#include "model.hpp"
#include "opengl/shaders.hpp"
#include "mesh.hpp"


class Scene
{
public:
    Scene();
    Scene(const glm::vec3 &camera, const glm::vec3 &look_at);

    void set_camera(const glm::vec3 &camera, const glm::vec3 &look_at);
    void add_model(const std::shared_ptr<OpenGL::Mesh> &mesh, const glm::vec3 &position);
    void remove_model(const std::shared_ptr<OpenGL::Mesh> &mesh);

    static const glm::vec3 UpDirection;

    void render();

private:
    std::map<std::shared_ptr<OpenGL::Mesh>, glm::vec3> objects;
    glm::vec3 camera;
    glm::vec3 look_at;

    OpenGL::ShaderProgram enable_shader();
};


#endif //RENDER_SCENE_HPP
