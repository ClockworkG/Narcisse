#pragma once

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace pogl
{
    struct CameraSettings
    {
        glm::vec3 position = glm::vec3(2.0f, 4.0f, 8.0f);
        glm::vec3 target = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

        float fov = 45.f;
        float aspect_ratio = 1.f;
        float z_near = 0.1f;
        float z_far = 100.f;
    };

    class Camera
    {
    public:
        Camera() = default;
        Camera(CameraSettings&& settings);
        Camera(const Camera&) = default;
        Camera(Camera&&) = default;
        Camera& operator=(const Camera&) = default;
        Camera& operator=(Camera&&) = default;

        const glm::mat4& get_view() const noexcept;
        const glm::mat4& get_projection() const noexcept;

        void translate(const glm::vec3& vec);
        void look(const glm::vec3& vec);

    private:
        CameraSettings settings_;

        glm::mat4 view_;
        glm::mat4 projection_;

        void compute() noexcept;
    };
} // namespace pogl

#include <pogl/camera.hxx>
