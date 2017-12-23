#include <iostream>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/gtc/matrix_transform.hpp>

#include "lib/glfw.hpp"
#include "lib/glew.hpp"
#include "lib/opengl.hpp"

#include "window.hpp"
#include "mesh.hpp"
#include "opengl/errors.hpp"


int main(int argc, char **argv)
{
    Lib::GLFW::Init();

    Window window("OpenGL Render");

    Lib::GLEW::Init();
    Lib::OpenGL::Init();

    auto cube = OpenGL::Mesh::Load("../assets/cube.obj");

    OpenGL::ShaderProgram shader_progam;
    shader_progam.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_progam.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    shader_progam.use_program();

    OpenGL::Error::Check();

    float t0 = glfwGetTime();
    float angle = 0.0;

    glm::vec3 camera(3.0f, 3.0f, 3.0f);
    GLint MVPMatrix = glGetUniformLocation(shader_progam, "MVP");

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float t = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            angle += t - t0;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            angle -= t - t0;

        t0 = t;

        camera = glm::vec3(4 * std::cos(angle), 3, 4 * std::sin(angle));

        OpenGL::Error::Check();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.01f, 100.0f);
        auto view = glm::lookAt(camera, glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));

        auto transformation = perspective * view;

        OpenGL::Error::Check();

        glBindVertexArray(cube.vao);

        OpenGL::Error::Check();

        glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &transformation[0][0]);

        OpenGL::Error::Check();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        OpenGL::Error::Check();

        cube.vertex_buffer.bind();

        OpenGL::Error::Check();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        OpenGL::Error::Check();

        cube.normal_buffer.bind();
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        OpenGL::Error::Check();

        cube.index_buffer.bind();

        glDrawElements(
                GL_TRIANGLES,      // mode
                cube.index_buffer.size(),    // count
                GL_UNSIGNED_INT,   // type
                (void*)0           // element array buffer offset
        );

        OpenGL::Error::Check();

        glDisableVertexAttribArray(1);
        glDisableVertexAttribArray(0);

        OpenGL::Error::Check();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    Lib::OpenGL::Free();
    Lib::GLEW::Free();
    Lib::GLFW::Free();

    return 0;
}
