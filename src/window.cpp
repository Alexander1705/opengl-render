#include "window.hpp"


Window::Window(const std::string &title) : Window(title, 1280, 720) {}


Window::Window(const std::string &title, size_t width, size_t height)
{
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    glfwSetInputMode(window, GLFW_STICKY_KEYS, true);
    glfwSetWindowUserPointer(window, this);
    glfwSetWindowSizeCallback(window, OnResizeCallback);
    glfwMakeContextCurrent(window);
}


Window::~Window()
{
    glfwDestroyWindow(window);
}


void Window::OnResizeCallback(GLFWwindow *window, int new_width, int new_height)
{
    ((Window*)glfwGetWindowUserPointer(window));
}

void Window::loop(Scene &scene)
{
    float t0 = glfwGetTime();
    float angle = 0.0;

    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float t = glfwGetTime();

        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            angle += t - t0;

        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            angle -= t - t0;

        t0 = t;

        scene.set_camera(glm::vec3(4 * std::cos(angle), 3, 4 * std::sin(angle)), glm::vec3(0.0f));
        scene.render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}
