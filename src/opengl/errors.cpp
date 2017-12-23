#include "errors.hpp"
#include <GL/glew.h>


using namespace OpenGL;


void Error::Check()
{
    switch (glGetError())
    {
        case GL_NO_ERROR:
            return;

        case GL_INVALID_ENUM:
            throw Error("GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument. The offending command is ignored and has no other side effect than to set the error flag.");

        case GL_INVALID_VALUE:
            throw Error("GL_INVALID_VALUE: A numeric argument is out of range. The offending command is ignored and has no other side effect than to set the error flag.");

        case GL_INVALID_OPERATION:
            throw Error("GL_INVALID_OPERATION: The specified operation is not allowed in the current state. The offending command is ignored and has no other side effect than to set the error flag.");

        case GL_INVALID_FRAMEBUFFER_OPERATION:
            throw Error("GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete. The offending command is ignored and has no other side effect than to set the error flag.");

        case GL_OUT_OF_MEMORY:
            throw Error("GL_OUT_OF_MEMORY: There is not enough memory left to execute the command. The state of the GL is undefined, except for the state of the error flags, after this error is recorded.");

        case GL_STACK_UNDERFLOW:
            throw Error("GL_STACK_UNDERFLOW: An attempt has been made to perform an operation that would cause an internal stack to underflow.");

        case GL_STACK_OVERFLOW:
            throw Error("GL_STACK_OVERFLOW: An attempt has been made to perform an operation that would cause an internal stack to overflow.");

        default:
            throw Error("Undefined OpenGL error.");
    }
}
