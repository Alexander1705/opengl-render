#ifndef RENDER_SCENE_HPP
#define RENDER_SCENE_HPP


#include <map>
#include <glm/vec3.hpp>
#include "model.hpp"
#include "opengl/shaders.hpp"


class Scene
{
public:
    Scene();
    Scene(const glm::vec3 &camera, const glm::vec3 &look_at);

    void set_camera(const glm::vec3 &camera, const glm::vec3 &look_at);
    void add_model(Model *model, const glm::vec3 &position);
    void remove_model(Model *model);

    static const glm::vec3 UpDirection;

    void render();

private:
    std::map<Model*, glm::vec3> objects;
    glm::vec3 camera;
    glm::vec3 look_at;

    OpenGL::ShaderProgram enable_shader();
};


#endif //RENDER_SCENE_HPP
