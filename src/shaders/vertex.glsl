#version 330 core

layout(location = 0) in vec3 m_position;
layout(location = 1) in vec3 m_normal;

uniform mat4 ModelToScreen;
uniform mat4 ModelToCamera;

out vec3 c_position;
out vec3 c_normal;

void main()
{
    gl_Position = ModelToScreen * vec4(m_position, 1);

    c_position = (ModelToCamera * vec4(m_position, 1.0)).xyz;
    c_normal   = (ModelToCamera * vec4(m_normal, 0.0)).xyz;
}
