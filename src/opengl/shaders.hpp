#ifndef RENDER_SHADERS_HPP
#define RENDER_SHADERS_HPP


#include <string>

#include <GL/glew.h>
#include <vector>


namespace OpenGL
{
    enum class ShaderType { Fragment, Vertex };


    /**
     * @brief OpenGL shader program RAII wrapper.
     */
    class ShaderProgram
    {
    public:
        ShaderProgram();
        ~ShaderProgram();

        void attach_shader(ShaderType type, const std::string &text);
        void attach_shader_file(ShaderType type, const std::string &path);

        void use_program();
        void link_program();

        operator GLuint();

    private:
        bool linked = false;

        GLuint program_id;
        std::vector<GLuint> shaders;
    };
}


#endif //RENDER_SHADERS_HPP
