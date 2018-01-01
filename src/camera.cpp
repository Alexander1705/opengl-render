#include "camera.hpp"
#include <glm/gtx/transform.hpp>


OpenGL::Camera::Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up_vector)
        : position(position), direction(direction), up_vector(up_vector) {}


void OpenGL::Camera::add_yaw(float angle)
{
    rotate(up_vector, angle);
}


void OpenGL::Camera::add_roll(float angle)
{
    rotate(direction, angle);
}


void OpenGL::Camera::add_pitch(float angle)
{
    rotate(glm::cross(direction, up_vector), angle);
}


glm::mat4 OpenGL::Camera::view_matrix(float aspect_ratio) const
{
    return glm::lookAt(position, position + direction, up_vector);
}


void OpenGL::Camera::rotate(glm::vec3 axis, float angle)
{
    glm::mat4 rotation;
    rotation = glm::rotate(rotation, angle, axis);

    direction = rotation * glm::vec4(direction, 0.0f);
    up_vector = rotation * glm::vec4(up_vector, 0.0f);
}


void OpenGL::Camera::move_forward(float distance)
{
    position += glm::normalize(direction) * distance;
}


void OpenGL::Camera::move_up(float distance)
{
    position += glm::normalize(up_vector) * distance;
}


void OpenGL::Camera::move_right(float distance)
{
    position += glm::normalize(glm::cross(direction, up_vector)) * distance;
}
