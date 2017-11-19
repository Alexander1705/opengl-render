#include "shaders.hpp"

#include <iostream>
#include <fstream>
#include <sstream>


using namespace OpenGL;


ShaderProgram::ShaderProgram()
{
    program_id = glCreateProgram();
}


ShaderProgram::~ShaderProgram()
{
    glDeleteProgram(program_id);
}


void ShaderProgram::attach_shader(ShaderType type, const std::string &text)
{
    if (linked)
        throw std::runtime_error("Attaching shader to already linked program");

    if (glGetError() != GL_NO_ERROR)
        throw std::runtime_error("Unhandled OpenGL error");

    GLuint shader = glCreateShader(type == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

    const char *sources[] = { text.c_str() };

    glShaderSource(shader, 1, sources, NULL);
    glCompileShader(shader);


    GLint compile_status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_status);

    GLint info_len;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_len);

    if (info_len > 0) // TODO: Check if debug logs are required
    {
        std::vector<char> buffer(info_len);
        glGetShaderInfoLog(shader, info_len, NULL, buffer.data());

        std::clog << buffer.data() << std::endl;
    }

    if (compile_status == GL_FALSE || glGetError() != GL_NO_ERROR)
    {
        throw std::runtime_error("Failed to compile shader.");
    }

    shaders.push_back(shader);
}

void ShaderProgram::attach_shader_file(ShaderType type, const std::string &path)
{
    std::ifstream file(path);

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open shader file: " + path);
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    attach_shader(type, buffer.str());
}

void ShaderProgram::use_program()
{
    if (!linked)
        link_program();

    if (glGetError() != GL_NO_ERROR)
        throw std::runtime_error("Unhandled OpenGL error");

    glUseProgram(program_id);

    auto error = glGetError();
    if (error != GL_NO_ERROR)
        throw std::runtime_error((char *)gluErrorString(error));
}

void ShaderProgram::link_program()
{
    if (glGetError() != GL_NO_ERROR)
        throw std::runtime_error("Unhandled OpenGL error");

    if (linked)
        return;
    else
        linked = true;

    for (auto shader : shaders)
    {
        glAttachShader(program_id, shader);
    }

    glLinkProgram(program_id);

    GLint link_status;
    glGetProgramiv(program_id, GL_LINK_STATUS, &link_status);

    GLint info_len;
    glGetProgramiv(program_id, GL_INFO_LOG_LENGTH, &info_len);

    if (info_len > 0)
    {
        std::vector<char> buffer(info_len);
        glGetProgramInfoLog(program_id, info_len, NULL, buffer.data());

        std::clog << buffer.data() << std::endl;
    }

    if (link_status == GL_FALSE || glGetError() != GL_NO_ERROR)
    {
        throw std::runtime_error("Failed to link shader program");
    }

    for (auto shader : shaders)
    {
        glDetachShader(program_id, shader);
        glDeleteShader(shader);
    }
}

ShaderProgram::operator GLuint()
{
    return program_id;
}
