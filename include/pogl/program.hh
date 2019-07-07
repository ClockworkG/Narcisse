#pragma once

#include <filesystem>
#include <istream>
#include <list>
#include <ostream>

#include <GL/glew.h>

#include <pogl/shader.hh>
#include <pogl/vertex-attrib-pointer.hh>
#include <pogl/uniform-handle.hh>

namespace pogl
{
    constexpr GLuint INVALID_PROGRAM = 0;

    class Program
    {
    public:
        Program();
        ~Program();
        Program(Program&&);
        Program& operator=(Program&&);

        Program(const Program&) = delete;
        Program& operator=(const Program&) = delete;

        template <GLenum ShaderType>
        Program& attach(const Shader<ShaderType>& shader);

        template <GLenum ShaderType>
        Program& operator+=(const Shader<ShaderType>& shader);

        bool link();
        std::string error() const;

        operator GLuint() const noexcept;

        VertexAttribPointer attrib(const std::string& name) const;
        UniformHandle uniform(const std::string& name) const;

    private:
        GLuint program_id_ = INVALID_PROGRAM;
        std::list<GLuint> shaders_;

        void detach_all();
    };

    using program_ptr_t = std::shared_ptr<Program>;

    program_ptr_t make_program(const std::filesystem::path& vertex,
                               const std::filesystem::path& fragment);

    std::ostream& operator<<(std::ostream& os, const Program& program);
    std::istream& operator>>(std::istream& is, Program& program);

    using display_fun_t = std::function<void(const Program&)>;

    auto with_shader(const Program& shader, display_fun_t&& fun);
} // namespace pogl

#include <pogl/program.hxx>
