#include <pogl/camera.hh>

namespace pogl
{
    Camera::Camera(CameraSettings&& settings)
        : settings_(std::move(settings))
        , view_(
            glm::lookAt(
                settings.position,
                settings.target,
                settings.up
            )
        )
        , projection_(
            glm::perspective(
                glm::radians(settings.fov),
                settings.aspect_ratio,
                settings.z_near,
                settings.z_far
            )
        )
    {}
} // namespace pogl
