#version 330 core

out vec3 color;

in vec3 c_position;
in vec3 c_normal;

uniform vec3 c_light;

const float intensity = 0.5;
const float Ka = 0.25;
const float Kd = 0.75;
const float Ks = 0.5;
const float shininess = 25.0;

void main()
{
    vec3 ambient = vec3(Ka * intensity);

    float k = max(0.0, dot(c_light, c_normal.xyz));
    vec3 diffuse = vec3(Kd * k * intensity);

    vec3 c_view = normalize(- c_position.xyz);
    vec3 c_halfway = normalize(c_view + c_light);

    k = max(0.0, dot(c_normal, c_halfway));
    vec3 specular = vec3(Ks * pow(k, shininess));

    color = ambient + diffuse + specular;
}
