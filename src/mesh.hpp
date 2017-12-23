#ifndef RENDER_MESH_HPP
#define RENDER_MESH_HPP


#include <string>
#include <vector>
#include <stdexcept>

#include <glm/vec3.hpp>
#include <assimp/mesh.h>
#include <glm/detail/type_mat.hpp>
#include "opengl/buffer.hpp"


namespace OpenGL
{
    class AssetImportError : public std::runtime_error
    {
    public:
        using runtime_error::runtime_error;
    };


    class Mesh
    {
    public:
        explicit Mesh(const aiMesh *mesh);
        ~Mesh();
        Mesh(Mesh &&) noexcept;

        static Mesh Load(const std::string &path);

//    private:
        GLuint vao = 0;

        Buffer<unsigned int> index_buffer;
        Buffer<glm::vec3> vertex_buffer;
        Buffer<glm::vec3> normal_buffer;
    };
}


#endif //RENDER_MESH_HPP
