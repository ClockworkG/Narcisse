#pragma once

#include <pogl/engine.hh>

namespace pogl
{
    inline void Engine::set_current_scene(scene_ptr_t scene)
    {
        current_scene_ = scene;
    }

    inline Engine* Engine::get_instance()
    {
        static Engine instance;
        return &instance;
    }
} // namespace pogl
