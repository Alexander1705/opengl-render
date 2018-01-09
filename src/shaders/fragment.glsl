#version 330 core

out vec3 color;

in vec4 c_position;
in vec4 c_normal;

uniform vec3 c_light;

const float intensity = 0.5;
const float Ka = 0.25;
const float Kd = 1.0;
const float Ks = 0.5;
const float shininess = 5.0;

void main()
{
    vec3 ambient = vec3(Ka * intensity);

    float k = clamp(dot(c_light, c_normal.xyz), 0.0, 1.0);
    vec3 diffuse = vec3(Kd * k * intensity);

    vec3 c_view = normalize(- c_position.xyz);
    vec3 c_reflection = reflect(-c_light, c_normal.xyz);

    k = clamp(dot(c_reflection, c_view), 0.0, 1.0);
    vec3 specular = vec3(Ks * pow(k, shininess));

    color = ambient + diffuse + specular;
}
