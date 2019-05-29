#include <pogl/context.hh>

namespace pogl
{
    using shader_lookup_table_t = std::map<std::string, program_ptr_t>;

    std::unique_ptr<shader_lookup_table_t> loaded_shaders = nullptr;

    bool init_glut_context(const GlutContextArguments& args)
    {
        auto [argc, argv] = args.cli_args;
        glutInit(&argc, argv);

        auto [major, minor] = args.version;
        glutInitContextVersion(major, minor);

        glutInitContextProfile(args.context_profile);
        glutInitDisplayMode(args.display_mode);

        auto [width, height] = args.window_size;
        glutInitWindowSize(width, height);

        glutCreateWindow(args.window_name);

        if (glewInit())
            return false;

        glEnable(GL_DEPTH_TEST);
        loaded_shaders = std::make_unique<shader_lookup_table_t>();

        return true;
    }

    program_ptr_t get_shader(const std::string& name)
    {
        auto it = loaded_shaders->find(name);
        if (it == end(*loaded_shaders))
            return nullptr;

        return it->second;
    }

    void set_shader(const std::string& name, program_ptr_t shader)
    {
        (*loaded_shaders)[name] = shader;
    }
} // namespace pogl
