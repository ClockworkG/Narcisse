#pragma once

#include <pogl/scene.hh>
#include <pogl/render-target.hh>
#include <pogl/render-buffer.hh>
#include <pogl/texture.hh>
#include <pogl/cube-map.hh>

namespace pogl
{
    struct RenderContext
    {
        const Camera& camera;
        RenderTarget* target;
    };

    class Engine
    {
    public:
        void run();
        void set_current_scene(scene_ptr_t scene);
        void render();
        void update(float elapsed);

        static Engine* get_instance();

    private:
        Engine();

        void prerender_reflection();

        scene_ptr_t current_scene_ = nullptr;
        CubeMap reflection_map_;
    };
} // namespace pogl

#include <pogl/engine.hxx>
