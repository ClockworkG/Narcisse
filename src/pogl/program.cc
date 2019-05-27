#include <pogl/program.hh>

#include <utility>

namespace pogl
{
    Program::Program()
        : program_id_(glCreateProgram())
    {}

    Program::~Program()
    {
        if (program_id_ != INVALID_PROGRAM)
        {
            detach_all();
            glDeleteProgram(program_id_);
            program_id_ = INVALID_PROGRAM;
        }
    }

    Program::Program(Program&& other)
        : program_id_(std::exchange(other.program_id_, INVALID_PROGRAM))
    {}

    Program& Program::operator=(Program&& other)
    {
        if (program_id_ != INVALID_PROGRAM)
            glDeleteProgram(program_id_);

        program_id_ = std::exchange(other.program_id_, INVALID_PROGRAM);
        return *this;
    }

    bool Program::operator()()
    {
        glLinkProgram(program_id_);

        GLint link_success = 0;
        glGetProgramiv(program_id_, GL_LINK_STATUS, &link_success);
        return link_success != GL_FALSE;
    }

    std::string Program::error() const
    {
        GLint max_length = 0;
        glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &max_length);

        std::vector<GLchar> info_log(max_length);
        glGetProgramInfoLog(program_id_,
                            max_length,
                            &max_length,
                            &info_log[0]);

        return std::string(begin(info_log), end(info_log));
    }

    void Program::detach_all()
    {
        for (const GLuint shader_id : shaders_)
            glDetachShader(program_id_, shader_id);
    }
} // namespace pogl
