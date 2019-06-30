#include <pogl/camera.hh>

namespace pogl
{
    Camera::Camera(CameraSettings&& settings)
        : settings_(std::move(settings))
    {
        compute();

        projection_ = glm::perspective(
            glm::radians(settings_.fov),
            settings_.aspect_ratio,
            settings_.z_near,
            settings_.z_far
        );

    }

    void Camera::compute() noexcept
    {
        view_ = glm::lookAt(
            settings_.position,
            settings_.target,
            settings_.up
        );
    }

    void Camera::set_position(const glm::vec3& vec)
    {
        settings_.position = vec;
        compute();
    }

    void Camera::translate(const glm::vec3& vec)
    {
        settings_.position += vec;
        compute();
    }

    void Camera::look(const glm::vec3& vec)
    {
        settings_.target += vec;
        compute();
    }
} // namespace pogl
