#version 330 core

in vec3 fragment_color;
// Ouput data
out vec3 color;

void main()
{
    color = fragment_color;
}
