cmake_minimum_required(VERSION 3.9)
project(render)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)


set(SOURCE_FILES
        src/main.cpp

        src/opengl/shaders.hpp
        src/opengl/shaders.cpp
        src/model.cpp
        src/model.hpp
        )

add_executable(render ${SOURCE_FILES})
target_link_libraries(render ${OPENGL_LIBRARIES} GLEW glm glfw)
