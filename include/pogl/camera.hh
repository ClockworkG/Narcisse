#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace pogl
{
    class Camera
    {
    public:
        Camera()
            : view(glm::lookAt(position_, target_, up_))
            , projection(glm::perspective(glm::radians(fov_), aspect_ratio_, z_near_, z_far_))
        {
        }

    private:
        glm::vec3 position_ = glm::vec3(2.0f, 3.0f, 8.0f);
        glm::vec3 target_ = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up_ = glm::vec3(0.0f, 1.0f, 0.0f);
        float fov_ = 45.f;
        float aspect_ratio_ = 1.f;
        float z_near_ = 0.1f;
        float z_far_ = 100.f;

    public:
        glm::mat4 view;
        glm::mat4 projection;
    };
} // namespace pogl
