#include "opengl.hpp"

#include <GL/glew.h>


void ::Lib::OpenGL::Init()
{
    glClearColor(0.7f, 0.7f, 1.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
}


void ::Lib::OpenGL::Free()
{

}
