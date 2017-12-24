cmake_minimum_required(VERSION 3.9)
project(render)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)
find_package(assimp REQUIRED)


set(SOURCE_FILES
        src/main.cpp
        src/window.cpp
        src/window.hpp
        src/mesh.cpp
        src/mesh.hpp


        src/opengl/shaders.hpp
        src/opengl/shaders.cpp
        src/opengl/buffer.cpp
        src/opengl/buffer.hpp
        src/opengl/errors.cpp
        src/opengl/errors.hpp

        src/lib/glfw.cpp
        src/lib/glfw.hpp
        src/lib/glew.cpp
        src/lib/glew.hpp
        src/lib/opengl.cpp
        src/lib/opengl.hpp
        )

add_executable(render ${SOURCE_FILES})
target_link_libraries(render ${OPENGL_LIBRARIES} GLEW glm glfw ${ASSIMP_LIBRARIES})
