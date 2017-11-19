#version 330 core

// Input vertex data, different for all executions of this shader.
layout(location = 0) in vec3 vertex;
layout(location = 1) in vec3 color;

uniform mat4 MVP;

out vec3 fragment_color;

void main()
{
    gl_Position= MVP * vec4(vertex, 1);

    fragment_color = color;
}
