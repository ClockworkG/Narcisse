#include <pogl/reflecting.hh>

namespace pogl
{
    Camera Reflecting::mirror_camera(const Camera& camera) const
    {
        if (object_ == nullptr)
            return camera;

        CameraSettings settings
        {
            object_->get_position(),
            camera.get_position(),
            glm::vec3(0.0f, -1.0f, 0.0f),
            100.f,
            1.f,
            0.1f,
            100.f
        };

        return Camera(std::move(settings));
    }
} // namespace pogl
