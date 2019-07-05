#include <pogl/reflecting.hh>

namespace pogl
{
    Camera Reflecting::mirror_camera(const glm::vec3& vec) const
    {
        CameraSettings settings
        {
            object_->get_position(),
            vec,
            glm::vec3(0.0f, -1.0f, 0.0f),
            60.f,
            1.f,
            0.1f,
            100.f
        };

        return Camera(std::move(settings));
    }
} // namespace pogl
