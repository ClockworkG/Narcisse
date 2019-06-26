#pragma once

#include <pogl/scene.hh>

namespace pogl
{
    struct RenderContext
    {
        const Camera& camera;
    };

    class Engine
    {
    public:
        void run();
        void set_current_scene(scene_ptr_t scene);
        void render();

        static Engine* get_instance();

    private:
        Engine();

        scene_ptr_t current_scene_ = nullptr;
    };
} // namespace pogl

#include <pogl/engine.hxx>
