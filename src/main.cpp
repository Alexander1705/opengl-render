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

    auto object = OpenGL::Mesh::Load("../assets/scene.obj");

    OpenGL::ShaderProgram shader_progam;
    shader_progam.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_progam.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    shader_progam.use_program();

    OpenGL::Camera camera(glm::vec3(8.0f, 10.0f, 10.0f), glm::vec3(-8.0f, -10.0f, -10.0f));

    auto perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 1000.0f);


    float t0 = glfwGetTime();
    float tp = t0;
    float angle = 0.0;

    glm::vec3 rocket_translate(0.0f, 0.0f, 0.0f);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(window, 640, 360);

    float rendering_time;
    int frames = 0;

    GLint light_uniform = glGetUniformLocation(shader_progam, "c_light");

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float t = glfwGetTime();

        double x, y;
        glfwGetCursorPos(window, &x, &y);

        camera.add_pitch(glm::radians(360 - y) / 4);
        camera.add_yaw(glm::radians(640 - x) / 4);

        glfwSetCursorPos(window, 640, 360);

        float d = 10 * (t - tp); tp = t;
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) { camera.move_forward(d); }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) { camera.move_forward(-d); }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) { camera.move_right(-d); }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) { camera.move_right(d); }
        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) { camera.move_up(d); }
        if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) { camera.move_up(-d); }
        if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) { camera.add_roll(-d/10); }
        if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) { camera.add_roll(d/10); }


        auto WorldToCamera = camera.view_matrix(16.0f / 9.0f);

        auto rocket_transform = glm::translate(glm::mat4(), rocket_translate);

        auto ModelToScreen = perspective * WorldToCamera;

        float frame_start = glfwGetTime();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        glm::vec4 light = glm::normalize(WorldToCamera * glm::vec4(-1.0, 2.0, 3.0, 0.0));
        glUniform3fv(light_uniform, 1, &light[0]);
        OpenGL::Error::Check();

        object.draw(ModelToScreen, WorldToCamera, shader_progam);

        float frame_end = glfwGetTime();

        frames++;
        rendering_time += frame_end - frame_start;

        if (frames >= 60)
        {
            std::cout << rendering_time * 1000 / 60 << "ms per frame (" << 60 / rendering_time << " fps)" << std::endl;

            frames = 0;
            rendering_time = 0;
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Lib::OpenGL::Free();
    Lib::GLEW::Free();
    Lib::GLFW::Free();

    return 0;
}
