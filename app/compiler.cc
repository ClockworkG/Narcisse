#include <narcisse/shader.hh>
#include <narcisse/context.hh>

#include <spdlog/spdlog.h>
#include <CLI/CLI.hpp>

template <typename ShaderType>
int compile_shader(const std::filesystem::path& source_path)
{
    spdlog::info("Compiling shader {0}", source_path.stem().c_str());
    auto shader = pogl::make_shader<pogl::vertex_shader_t>(source_path);
    if (!shader)
    {
        spdlog::error(shader.error());
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

using compile_function_t = std::function<int(const std::filesystem::path&)>;

static std::map<std::string, compile_function_t> compile_function_map
{
    {"vertex", std::bind(compile_shader<pogl::vertex_shader_t>, std::placeholders::_1)},
    {"fragment", std::bind(compile_shader<pogl::fragment_shader_t>, std::placeholders::_1)},
};

int main(int argc, char** argv)
{
    CLI::App app{"OpenGL compiler"};
    pogl::init_glut_context(
        pogl::GlutContextArguments(argc, argv)
    );

    std::string shader_kind = "vertex";
    std::filesystem::path shader_path;

    app.add_option("-k,--kind", shader_kind, "Kind of shader");
    app.add_option("-s,--shader", shader_path, "Shader source file")
        ->required()
        ->check(CLI::ExistingFile);

    CLI11_PARSE(app, argc, argv);

    spdlog::info("Starting shader compiler");

    auto query = compile_function_map.find(shader_kind);

    if (query == end(compile_function_map))
    {
        spdlog::error("Unknown shader kind {0}", shader_kind);
        return EXIT_FAILURE;
    }

    const auto& [_, compile] = *query;
    int exit_code = compile(shader_path);

    spdlog::info("Finished shader compilation");

    return exit_code;
}
