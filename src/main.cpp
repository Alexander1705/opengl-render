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

    auto rocket = OpenGL::Mesh::Load("../assets/rocket.obj");

    OpenGL::ShaderProgram shader_progam;
    shader_progam.attach_shader_file(OpenGL::ShaderType::Vertex, "../src/shaders/vertex.glsl");
    shader_progam.attach_shader_file(OpenGL::ShaderType::Fragment, "../src/shaders/fragment.glsl");
    shader_progam.use_program();

    OpenGL::Error::Check();

    float t0 = glfwGetTime();
    float angle = 0.0;

    glm::vec3 camera(3.0f, 3.0f, 3.0f);

    auto perspective = glm::perspective(glm::radians(45.0f), 16.0f / 9.0f, 0.01f, 100.0f);
    auto view = glm::lookAt(camera, glm::vec3(), glm::vec3(0.0f, 1.0f, 0.0f));

    GLint MVPMatrix = glGetUniformLocation(shader_progam, "MVP");
    GLint ModelMatrix = glGetUniformLocation(shader_progam, "ModelToWorld");

    OpenGL::Error::Check();


    auto rocket_fix = glm::translate(glm::scale(glm::mat4(), glm::vec3{0.25f, 0.25f, 0.25f}), glm::vec3{0.0f, -4.0f, 0.0f});

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float t = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            angle += t - t0;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            angle -= t - t0;

        t0 = t;

        ;
        auto model = glm::rotate(rocket_fix, 4 * angle, glm::vec3(0, 1, 0));

        OpenGL::Error::Check();

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        auto transformation = perspective * view * model;

        OpenGL::Error::Check();

        glBindVertexArray(rocket.vao);

        OpenGL::Error::Check();

        glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &transformation[0][0]);
        glUniformMatrix4fv(ModelMatrix, 1, GL_FALSE, &model[0][0]);

        OpenGL::Error::Check();

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        OpenGL::Error::Check();

        rocket.vertex_buffer.bind();

        OpenGL::Error::Check();

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        OpenGL::Error::Check();

        rocket.normal_buffer.bind();
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        OpenGL::Error::Check();

        rocket.index_buffer.bind();

        glDrawElements(
                GL_TRIANGLES,      // mode
                rocket.index_buffer.size(),    // count
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
