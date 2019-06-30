#pragma once

#include <filesystem>
#include <list>
#include <memory>

#include <pogl/camera.hh>
#include <pogl/object.hh>
#include <pogl/reflecting.hh>

namespace fs = std::filesystem;

namespace pogl
{
    class Scene;

    using scene_ptr_t = std::shared_ptr<Scene>;

    struct SceneSettings
    {
        Camera camera;
        glm::vec3 background;
    };

    class Scene
    {
        template <typename T>
        using data_type = std::list<T>;

    public:
        using const_iterator = data_type<Object>::const_iterator;
        using iterator = data_type<Object>::iterator;

        Scene() = default;
        Scene(SceneSettings&& settings);
        Scene(const Scene&) = delete;
        Scene(Scene&&) = delete;
        Scene& operator=(const Scene&) = delete;
        Scene& operator=(Scene&&) = delete;

        void display();
        void add_object(Object&& object, bool reflecting = false);
        void mouse_move(int x, int y);

        const Camera& get_camera() const noexcept;
        Camera& get_camera() noexcept;

        const Reflecting& get_reflecting() const noexcept;
        Reflecting& get_reflecting() noexcept;

        const_iterator begin() const;
        const_iterator end() const;
        iterator begin();
        iterator end();

    private:
        SceneSettings settings_;
        data_type<Object> objects_;
        Reflecting reflecting_;
    };

    scene_ptr_t load_scene(const fs::path& scene_path);
} // namespace pogl

#include <pogl/scene.hxx>
