#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <glm/detail/type_mat.hpp>
#include "mesh.hpp"


using namespace OpenGL;


Mesh::Mesh(const aiMesh *mesh)
{
    std::vector<unsigned int> index_array;
    index_array.reserve(mesh->mNumFaces * 3);

    if (!mesh->HasNormals())
        throw AssetImportError("mesh doesn't contain normals");

    for (int i = 0; i < mesh->mNumFaces; ++i)
    {
        auto face = mesh->mFaces[i];

        if (face.mNumIndices != 3)
            throw AssetImportError("mesh contains non-triangle polygon");

        for (int j = 0; j < 3; ++j)
        {
            index_array.push_back(face.mIndices[j]);
        }
    }

    std::vector<glm::vec3> vertex_array((glm::vec3*)mesh->mVertices, (glm::vec3*)mesh->mVertices + mesh->mNumVertices);
    std::vector<glm::vec3> normal_array((glm::vec3*)mesh->mNormals,  (glm::vec3*)mesh->mNormals  + mesh->mNumVertices);

    index_buffer  = Buffer<unsigned int>(GL_ELEMENT_ARRAY_BUFFER, index_array);
    vertex_buffer = Buffer<glm::vec3>(GL_ARRAY_BUFFER, vertex_array);
    normal_buffer = Buffer<glm::vec3>(GL_ARRAY_BUFFER, normal_array);

    glGenVertexArrays(1, &vao);
}


Mesh Mesh::Load(const std::string &path)
{
    Assimp::Importer importer;

    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_JoinIdenticalVertices);

    if (!scene)
        throw AssetImportError(importer.GetErrorString());

    if (scene->mNumMeshes != 1)
        throw AssetImportError(path + ": file should contain exactly one mesh");

    aiMesh* ai_mesh = scene->mMeshes[0];

    return Mesh(ai_mesh);
}

Mesh::~Mesh()
{
    if (vao != 0)
        glDeleteVertexArrays(1, &vao);
}


Mesh::Mesh(Mesh &&moved) noexcept
        : index_buffer(std::move(moved.index_buffer)),
          vertex_buffer(std::move(moved.vertex_buffer)),
          normal_buffer(std::move(moved.normal_buffer))
{
    moved.vao = 0;
}


void Mesh::draw(const glm::mat4 &MVP, const glm::mat4 &model, OpenGL::ShaderProgram &shader)
{
    shader.use_program();

    GLint MVPMatrix = glGetUniformLocation(shader, "MVP");
    GLint ModelMatrix = glGetUniformLocation(shader, "ModelToWorld");

    glBindVertexArray(vao);

    glUniformMatrix4fv(MVPMatrix, 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(ModelMatrix, 1, GL_FALSE, &model[0][0]);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    vertex_buffer.bind();

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    normal_buffer.bind();
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    index_buffer.bind();

    glDrawElements(
            GL_TRIANGLES,      // mode
            index_buffer.size(),    // count
            GL_UNSIGNED_INT,   // type
            (void*)0           // element array buffer offset
    );

    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);
}
