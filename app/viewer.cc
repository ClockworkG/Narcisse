#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

template<>
std::size_t pogl::FlattenPolicy<glm::vec3>::size()
{
    return 3;
}

template<>
template <typename InIt, typename OutIt>
void pogl::FlattenPolicy<glm::vec3>::copy(InIt in_begin, InIt in_end, OutIt out_begin)
{
    for (auto it = in_begin; it != in_end; it++)
    {
        *out_begin = (*it)[0];
        *(out_begin + 1) = (*it)[1];
        *(out_begin + 2) = (*it)[2];
        out_begin += 3;
    }
}

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    auto shader = pogl::make_program("vertex.glsl", "fragment.glsl");
    auto obj = pogl::Object({
        glm::vec3(0.0f,  0.5f,  0.0f),
        glm::vec3(0.5f, -0.5f,  0.0f),
        glm::vec3(-0.5f, -0.5f,  0.0f)
    }, shader);
    auto scene = pogl::get_scene();

    scene->add_object(std::move(obj));
    scene->run();

    return EXIT_SUCCESS;
}
