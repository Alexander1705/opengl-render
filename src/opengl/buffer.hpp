#ifndef RENDER_BUFFER_HPP
#define RENDER_BUFFER_HPP


#include <vector>
#include <GL/glew.h>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>


namespace OpenGL
{
    template <typename T>
    class Buffer
    {
    public:
        Buffer() = default;
        Buffer(GLenum target, const std::vector<T> &buffer);
        Buffer(Buffer<T> &&moved) noexcept;
        Buffer<T> & operator=(Buffer<T> &&moved) noexcept;

        void bind() const;
        size_t size() const;

        operator GLuint() const;

    private:
        GLenum target = 0;
        GLuint object = 0;
        std::vector<T> data;
    };


    extern template class Buffer<GLfloat>;
    extern template class Buffer<GLuint>;
    extern template class Buffer<glm::vec2>;
    extern template class Buffer<glm::vec3>;
}


#endif //RENDER_BUFFER_HPP
