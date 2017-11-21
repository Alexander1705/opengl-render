#ifndef RENDER_WINDOW_HPP
#define RENDER_WINDOW_HPP


#include <string>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "scene.hpp"


class Window
{
public:
    explicit Window(const std::string &title);
    Window(const std::string &title, size_t width, size_t height);
    ~Window();

    Window(const Window &) = delete;

    void loop(Scene &scene);

protected:
    static void OnResizeCallback(GLFWwindow *window, int new_width, int new_height);

private:
    GLFWwindow *window;
};


#endif //RENDER_WINDOW_HPP
