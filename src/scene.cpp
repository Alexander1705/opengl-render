#include "scene.hpp"

#include <glm/gtc/matrix_transform.hpp>


const glm::vec3 Scene::UpDirection = glm::vec3(0, 1, 0);


Scene::Scene() : Scene(glm::vec3(4, 3, 4), glm::vec3(0, 0, 0)) {}


Scene::Scene(const glm::vec3 &camera, const glm::vec3 &look_at)
{
    set_camera(camera, look_at);
}

void Scene::set_camera(const glm::vec3 &camera, const glm::vec3 &look_at)
{
    this->camera = camera;
    this->look_at = look_at;
}

void Scene::add_model(const std::shared_ptr<OpenGL::Mesh> &mesh, const glm::vec3 &position)
{
    objects[mesh] = position;
}


void Scene::remove_model(const std::shared_ptr<OpenGL::Mesh> &mesh)
{
    objects.erase(mesh);
}


void Scene::render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.01f, 100.0f);
    auto view = glm::lookAt(camera, look_at, UpDirection);

    for (auto &model_pos_pair : objects)
    {
        glm::mat4 model;
        glm::translate(model, model_pos_pair.second);

//        model_pos_pair.first->render(<#initializer#>);
    }
}
