#include <iostream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "opengl/shaders.hpp"
#include "model.hpp"


int main(int argc, char **argv)
{
    if(!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow *window = glfwCreateWindow(1280, 720, "OpenGL Render", NULL, NULL);
    if (window == nullptr)
    {
        throw std::runtime_error("Failed to open window");
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE; // Needed for core profile
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }

    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

    OpenGL::ShaderProgram shader_program;
    shader_program.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_program.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");

    Model model = {
            glm::vec3(-1.0f, -1.0f, 0.0f),
            glm::vec3(1.0f, -1.0f, 0.0f),
            glm::vec3(0.0f,  0.0f, 0.0f),

            glm::vec3(-1.0f, 1.0f, 0.0f),
            glm::vec3(1.0f, 1.0f, 0.0f),
            glm::vec3(0.0f,  0.0f, 0.0f),
    };


    do {
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use our shader
        shader_program.use_program();

        // 1rst attribute buffer : vertices
        model.draw();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();
}

