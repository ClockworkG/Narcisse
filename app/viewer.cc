#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    pogl::scene_ptr_t scene = nullptr;

    try {
        scene = pogl::load_scene("scene.json");
    }
    catch (const std::runtime_error& err)
    {
        spdlog::error("{0}", err.what());
        return EXIT_FAILURE;
    }

    auto engine = pogl::Engine::get_instance();
    engine->set_current_scene(scene);
    engine->run();

    return EXIT_SUCCESS;
}
