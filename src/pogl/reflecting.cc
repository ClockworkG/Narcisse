#include <pogl/reflecting.hh>

namespace pogl
{
    Camera Reflecting::mirror_camera(const glm::vec3& vec) const
    {
        auto up = (std::abs(vec.y) <= 0.1) ? glm::vec3(0.f, -1.0f, 0.f)
                                           : glm::vec3(0.f, 0.f, -1.f);
        CameraSettings settings
        {
            object_->get_position(),
            vec,
            up,
            90.f,
            1.f,
            0.001f,
            100.f
        };

        return Camera(std::move(settings));
    }
} // namespace pogl
