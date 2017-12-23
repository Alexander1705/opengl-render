#version 330 core

layout(location = 0) in vec3 vertex_ms;
layout(location = 1) in vec3 normal_ms;

const vec3 SunLight = normalize(vec3(1, 3, 2));

uniform mat4 ModelToWorld;
uniform mat4 MVP;

out vec3 vertex_color;

void main()
{
    gl_Position = MVP * vec4(vertex_ms, 1);

    const vec3 ambient = vec3(0.1, 0.1, 0.1);
    const vec3 diffuse = vec3(0.5, 0.5, 0.5);
    vec3 normal_ws = (ModelToWorld * vec4(normal_ms, 0)).xyz;
    float k = clamp(dot(normal_ws, SunLight), 0, 1);
    vertex_color = ambient + k * diffuse;
}
