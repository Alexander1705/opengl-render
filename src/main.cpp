#include <iostream>
#include <glm/gtc/matrix_transform.hpp>

#include "lib/glfw.hpp"
#include "lib/glew.hpp"
#include "lib/opengl.hpp"

#include "window.hpp"
#include "mesh.hpp"
#include "opengl/errors.hpp"
#include "camera.hpp"


int main(int argc, char **argv)
{
    Lib::GLFW::Init();

    Window window("OpenGL Render");

    Lib::GLEW::Init();
    Lib::OpenGL::Init();

    auto rocket = OpenGL::Mesh::Load("../assets/rocket.obj");
    auto ground = OpenGL::Mesh::Load("../assets/ground.obj");

    OpenGL::ShaderProgram shader_progam;
    shader_progam.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_progam.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    shader_progam.use_program();

    OpenGL::Camera camera(glm::vec3(8.0f, 10.0f, 10.0f), glm::vec3(1.0f));

    auto perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 1.0f, 1000.0f);


    float t0 = glfwGetTime();
    float angle = 0.0;

    glm::vec3 rocket_translate(0.0f, 0.0f, 0.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, 640, 360);

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float t = glfwGetTime();

        if (t - t0 > 5.0f)
        {
            rocket_translate = glm::vec3(0, 4 * std::pow((t - 5.0f), 2), 0);
        }

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        camera.add_pitch(glm::radians(360 - y) / 2);
        camera.add_yaw(glm::radians(640 - x) / 2);

        glfwSetCursorPos(window, 640, 360);


        auto view = camera.view_matrix(16.0f / 9.0f);

        auto rocket_transform = glm::translate(glm::mat4(), rocket_translate);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto MVProcket = perspective * view * rocket_transform;
        auto MVPground = perspective * view;

        rocket.draw(MVProcket, rocket_transform, shader_progam);
        ground.draw(MVPground, glm::mat4(), shader_progam);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Lib::OpenGL::Free();
    Lib::GLEW::Free();
    Lib::GLFW::Free();

    return 0;
}
