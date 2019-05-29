#pragma once

#include <filesystem>
#include <memory>

#include <pogl/camera.hh>

#include <GL/glew.h>

namespace fs = std::filesystem;

namespace pogl
{
    class Scene;

    using scene_ptr_t = std::shared_ptr<Scene>;

    class Scene
    {
        friend scene_ptr_t load_scene(const fs::path&);
        friend void set_current_scene(scene_ptr_t);
        friend void run_opengl();

    public:
        Scene() = default;
        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

        void display() const;

    private:
        static inline scene_ptr_t current_scene = nullptr;

        Camera camera_;
    };

    scene_ptr_t load_scene(const fs::path& scene_path);
    void set_current_scene(scene_ptr_t scene);
    void run_opengl();
} // namespace pogl
