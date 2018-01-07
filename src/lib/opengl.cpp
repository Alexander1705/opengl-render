#include "opengl.hpp"

#include <GL/glew.h>


void ::Lib::OpenGL::Init()
{
    glClearColor(0.7f, 0.7f, 1.0f, 0.0f);

    glDepthFunc(GL_LESS);
    glEnable(GL_DEPTH_TEST);

    glCullFace(GL_FRONT);
    glFrontFace(GL_CW);
    glEnable(GL_CULL_FACE);
}


void ::Lib::OpenGL::Free()
{

}
