#include "buffer.hpp"


using namespace OpenGL;


template<typename T>
Buffer<T>::Buffer(GLenum target, const std::vector<T> &buffer) : target(target), object(0), data(buffer)
{
    // TODO: check errors.
    glGenBuffers(1, &object);
    glBindBuffer(target, object);
    glBufferData(target, buffer.size() * sizeof(T), data.data(), GL_STATIC_DRAW);
}


template<typename T>
Buffer<T>::Buffer(Buffer &&moved) noexcept : target(moved.target), object(moved.object), data(std::move(moved.data))
{
    moved.object = 0;
}


template<typename T>
Buffer<T> &Buffer<T>::operator=(Buffer<T> &&moved) noexcept
{
    if (object != 0)
        glDeleteBuffers(1, &object);

    target = moved.target;
    data = std::move(moved.data);

    object = moved.object;
    moved.object = 0;

    return *this;
}


template<typename T>
void Buffer<T>::bind() const
{
    glBindBuffer(target, object);
}


template<typename T>
Buffer<T>::operator GLuint() const
{
    return object;
}


template<typename T>
size_t Buffer<T>::size() const
{
    return data.size();
}


template class Buffer<GLfloat>;
template class Buffer<GLuint>;
template class Buffer<glm::vec2>;
template class Buffer<glm::vec3>;
