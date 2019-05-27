#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    auto shader = pogl::make_program("vertex.glsl", "fragment.glsl");
    auto obj = pogl::Object({
        0.0f,  0.5f,  0.0f,
        0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    }, shader);
    auto scene = pogl::get_scene();

    scene->add_object(std::move(obj));
    scene->run();

    return EXIT_SUCCESS;
}
