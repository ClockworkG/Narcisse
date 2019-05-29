#include <spdlog/spdlog.h>
#include <pogl/pogl.hh>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

int main(int argc, char** argv)
{
    if (!pogl::init_glut_context(pogl::GlutContextArguments(argc, argv)))
    {
        spdlog::error("Unable to init GL context");
        return EXIT_FAILURE;
    }

    auto program = pogl::make_program("vertex.glsl", "fragment.glsl");
    glUseProgram(*program);
    glEnable(GL_DEPTH_TEST);

    auto scene = pogl::load_scene("scene.json");

    auto view_loc = glGetUniformLocation(*program, "view");
    auto proj_loc = glGetUniformLocation(*program, "proj");
    glUniformMatrix4fv(view_loc, 1, GL_FALSE, glm::value_ptr(scene->get_camera().get_view()));
    glUniformMatrix4fv(proj_loc, 1, GL_FALSE, glm::value_ptr(scene->get_camera().get_projection()));

    pogl::set_current_scene(scene);
    pogl::run_opengl();

    return EXIT_SUCCESS;
}
