#include "glew.hpp"

#include <stdexcept>

#include <GL/glew.h>


void Lib::GLEW::Init()
{
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        throw std::runtime_error("Failed to initialize GLEW");
    }
}


void Lib::GLEW::Free()
{

}
