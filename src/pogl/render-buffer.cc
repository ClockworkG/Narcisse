#include <pogl/render-buffer.hh>

#include <utility>

namespace pogl
{
    RenderBuffer::RenderBuffer(unsigned int width, unsigned int height)
    {
        glGenRenderbuffers(1, &buffer_id_);

        glBindRenderbuffer(GL_RENDERBUFFER, buffer_id_);
        glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT,
                              width, height);
        glBindRenderbuffer(GL_RENDERBUFFER, INVALID_RENDER_BUFFER);
    }

    RenderBuffer::~RenderBuffer()
    {
        if (buffer_id_ != INVALID_RENDER_BUFFER)
        {
            glDeleteRenderbuffers(1, &buffer_id_);
            buffer_id_ = INVALID_RENDER_BUFFER;
        }
    }

    RenderBuffer::RenderBuffer(RenderBuffer&& other)
        : buffer_id_(std::exchange(other.buffer_id_, INVALID_RENDER_BUFFER))
    {}

    RenderBuffer& RenderBuffer::operator=(RenderBuffer&& other)
    {
        if (buffer_id_ != INVALID_RENDER_BUFFER)
            glDeleteRenderbuffers(1, &buffer_id_);

        buffer_id_ = std::exchange(other.buffer_id_, INVALID_RENDER_BUFFER);

        return *this;
    }

    RenderBuffer::operator GLuint() const noexcept
    {
        return buffer_id_;
    }
} // namespace pogl
