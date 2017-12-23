#ifndef RENDER_ERRORS_HPP
#define RENDER_ERRORS_HPP


#include <stdexcept>


namespace OpenGL
{
    class Error : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;

        static void Check();
    };
}


#endif //RENDER_ERRORS_HPP
