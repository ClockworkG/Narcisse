#include <pogl/camera.hh>

namespace pogl
{
    Camera::Camera(const CameraSettings& settings)
        : view_(
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
