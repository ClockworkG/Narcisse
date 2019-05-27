#include <pogl/program.hh>

#include <utility>

namespace pogl
{
    constexpr static inline auto BINARY_TYPE_LEN = sizeof (GLenum);

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

    bool Program::link()
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

        shaders_.clear();
    }

    Program::operator GLuint() const noexcept
    {
        return program_id_;
    }

    std::ostream& operator<<(std::ostream& os, const Program& program)
    {
        int program_len = 0;
        glGetProgramiv(program,
                       GL_PROGRAM_BINARY_LENGTH,
                       &program_len);

        std::vector<char> buffer(program_len + BINARY_TYPE_LEN);
        glGetProgramBinary(program,
                           program_len,
                           &program_len,
                           reinterpret_cast<GLenum*>(buffer.data()),
                           buffer.data() + BINARY_TYPE_LEN);

        os.write(buffer.data(), buffer.size());

        return os;
    }

    std::istream& operator>>(std::istream& is, Program& program)
    {
        auto begin = std::istream_iterator<char>(is);
        auto end = std::istream_iterator<char>();

        std::vector<char> buffer;
        auto buffer_it = std::back_insert_iterator(buffer);

        std::copy(begin, end, buffer_it);

        glProgramBinary(program,
                        reinterpret_cast<GLenum*>(buffer.data())[0],
                        buffer.data() + BINARY_TYPE_LEN,
                        buffer.size() - BINARY_TYPE_LEN);

        return is;
    }
} // namespace pogl
