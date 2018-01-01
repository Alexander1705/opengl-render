#ifndef RENDER_CAMERA_HPP
#define RENDER_CAMERA_HPP


#include <glm/glm.hpp>


namespace OpenGL
{
    class Camera
    {
    public:
        Camera(glm::vec3 position, glm::vec3 direction, glm::vec3 up_vector = glm::vec3(0.0f, 1.0f, 0.0f));

        void move_forward(float distance);
        void move_up(float distance);
        void move_right(float distance);

        void add_yaw(float angle);
        void add_roll(float angle);
        void add_pitch(float angle);

        glm::mat4 view_matrix(float aspect_ratio) const;

    private:
        glm::vec3 position;
        glm::vec3 direction;
        glm::vec3 up_vector;


        void rotate(glm::vec3 axis, float angle);
    };
}


#endif //RENDER_CAMERA_HPP
