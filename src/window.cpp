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

void Window::loop()
{
    while (!glfwWindowShouldClose(window) && glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        // code goes here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

Window::operator GLFWwindow*() const
{
    return window;
}
