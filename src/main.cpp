#include <iostream>
#include <chrono>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

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
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    OpenGL::ShaderProgram shader_program;
    shader_program.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_program.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    shader_program.use_program();

    auto tetrahedron = Model({
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


    // Projection matrix : 45° Field of View, 16:9 ratio, display range : 0.1 unit <-> 100 units
    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.1f, 100.0f);

    using clock = std::chrono::steady_clock;
    auto start_time = clock::now();
    do {
        float time = std::chrono::duration_cast<std::chrono::milliseconds>(clock::now() - start_time).count() / 1000.0;

        glm::mat4 View = glm::lookAt(
                glm::vec3(4 * std::cos(time), 3, 4 * std::sin(time)), // Camera is at (4,3,3), in World Space
                glm::vec3(0,0,0), // and looks at the origin
                glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
        );

        // Our ModelViewProjection : multiplication of our 3 matrices
        glm::mat4 MVP = Projection * View;

        GLint MVPMatrix = glGetUniformLocation(shader_program, "MVP");
        glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &MVP[0][0]);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        tetrahedron.draw();

        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );

    glfwTerminate();
}

