#include <iostream>

#include "lib/glfw.hpp"
#include "lib/glew.hpp"
#include "lib/opengl.hpp"

#include "window.hpp"


int main(int argc, char **argv)
{
    Lib::GLFW::Init();

    Window window("OpenGL Render");

    Lib::GLEW::Init();
    Lib::OpenGL::Init();

    auto cube = Model({
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f,-1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f,-1.0f),
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f, 1.0f,-1.0f),
            glm::vec3(1.0f,-1.0f, 1.0f),
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(1.0f,-1.0f,-1.0f),
            glm::vec3(1.0f, 1.0f,-1.0f),
            glm::vec3(1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f,-1.0f),
            glm::vec3(1.0f,-1.0f, 1.0f),
            glm::vec3(-1.0f,-1.0f, 1.0f),
            glm::vec3(-1.0f,-1.0f,-1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(-1.0f,-1.0f, 1.0f),
            glm::vec3(1.0f,-1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f,-1.0f,-1.0f),
            glm::vec3(1.0f, 1.0f,-1.0f),
            glm::vec3(1.0f,-1.0f,-1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f,-1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f,-1.0f),
            glm::vec3(-1.0f, 1.0f,-1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f,-1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f, 1.0f, 1.0f),
            glm::vec3(-1.0f, 1.0f, 1.0f),
            glm::vec3(1.0f,-1.0f, 1.0f),
    }, {
            glm::vec3(0.125f,  0.125f,  0.125f),
            glm::vec3(0.125f,  0.125f,  0.125f),
            glm::vec3(0.125f,  0.125f,  0.125f),

            glm::vec3(0.5f,  0.125f,  0.125f),
            glm::vec3(0.5f,  0.125f,  0.125f),
            glm::vec3(0.5f,  0.125f,  0.125f),

            glm::vec3(0.125f,  0.5f,  0.125f),
            glm::vec3(0.125f,  0.5f,  0.125f),
            glm::vec3(0.125f,  0.5f,  0.125f),

            glm::vec3(0.125f,  0.125f,  0.5f),
            glm::vec3(0.125f,  0.125f,  0.5f),
            glm::vec3(0.125f,  0.125f,  0.5f),

            glm::vec3(0.125f,  0.5f,  0.5f),
            glm::vec3(0.125f,  0.5f,  0.5f),
            glm::vec3(0.125f,  0.5f,  0.5f),

            glm::vec3(0.5f,  0.125f,  0.5f),
            glm::vec3(0.5f,  0.125f,  0.5f),
            glm::vec3(0.5f,  0.125f,  0.5f),

            glm::vec3(0.5f,  0.5f,  0.125f),
            glm::vec3(0.5f,  0.5f,  0.125f),
            glm::vec3(0.5f,  0.5f,  0.125f),

            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),
            glm::vec3(0.5f,  0.5f,  0.5f),

            glm::vec3(0.75f,  0.5f,  0.5f),
            glm::vec3(0.75f,  0.5f,  0.5f),
            glm::vec3(0.75f,  0.5f,  0.5f),

            glm::vec3(0.5f,  0.75f,  0.5f),
            glm::vec3(0.5f,  0.75f,  0.5f),
            glm::vec3(0.5f,  0.75f,  0.5f),

            glm::vec3(0.5f,  0.5f,  0.75f),
            glm::vec3(0.5f,  0.5f,  0.75f),
            glm::vec3(0.5f,  0.5f,  0.75f),

            glm::vec3(0.75f,  0.75f,  0.75f),
            glm::vec3(0.75f,  0.75f,  0.75f),
            glm::vec3(0.75f,  0.75f,  0.75f),
    });

    Scene scene;
    scene.add_model(&cube, glm::vec3(0.0f));

    window.loop(scene);

    Lib::OpenGL::Free();
    Lib::GLEW::Free();
    Lib::GLFW::Free();

    return 0;
}
