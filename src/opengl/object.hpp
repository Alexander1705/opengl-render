#ifndef RENDER_OBJECT_HPP
#define RENDER_OBJECT_HPP


#include <GL/glew.h>


namespace OpenGL
{
    using GLGenFunc = void (*)(GLsizei, GLuint *);
    using GLDelFunc = void (*)(GLsizei, const GLuint *);
    using GLBindFunc = void (*)(GLenum, GLuint);


    template<GLGenFunc gl_gen, GLBindFunc gl_bind, GLDelFunc gl_del>
    class Object
    {
    public:
        explicit Object(GLenum target) : target(target)
        {
            gl_gen(1, &object);
        }

        ~Object()
        {
            if (object != 0)
                gl_del(1, &object);
        }

        Object(Object &&moved) noexcept : target(moved.target)
        {
            object = moved.object;
            moved.object = 0;
        };

        void bind()
        {
            gl_bind(target, object);
        }

        operator GLuint() const
        {
            return object;
        }

    protected:
        GLenum target;
        GLuint object = 0;
    };
}


#endif //RENDER_OBJECT_HPP
