#include "glfw.hpp"

#include <stdexcept>

#include <GL/glew.h>
#include <GLFW/glfw3.h>


void Lib::GLFW::Init()
{
    if(!glfwInit())
    {
        throw std::runtime_error("Failed to initialize GLFW");
    }
}


void Lib::GLFW::Free()
{

}
