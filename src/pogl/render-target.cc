#include <pogl/render-target.hh>

#include <utility>

namespace pogl
{
    RenderTarget::RenderTarget()
    {
        glGenFramebuffers(1, &buffer_id_);
    }

    RenderTarget::~RenderTarget()
    {
        if (buffer_id_ != INVALID_FRAME_BUFFER)
        {
            glDeleteFramebuffers(1, &buffer_id_);
            buffer_id_ = INVALID_FRAME_BUFFER;
        }
    }

    RenderTarget::RenderTarget(RenderTarget&& other)
        : buffer_id_(std::exchange(other.buffer_id_, INVALID_FRAME_BUFFER))
    {}

    RenderTarget& RenderTarget::operator=(RenderTarget&& other)
    {
        if (buffer_id_ != INVALID_FRAME_BUFFER)
            glDeleteFramebuffers(1, &buffer_id_);

        buffer_id_ = std::exchange(other.buffer_id_, INVALID_FRAME_BUFFER);

        return *this;
    }

    RenderTarget::operator GLuint() const noexcept
    {
        return buffer_id_;
    }

    void RenderTarget::set_depthbuffer(const RenderBuffer& buffer)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_);
        glFramebufferRenderbuffer(GL_FRAMEBUFFER,
                                  GL_DEPTH_ATTACHMENT,
                                  GL_RENDERBUFFER, buffer);
    }

    void RenderTarget::set_texture(const Texture& texture)
    {
        glBindFramebuffer(GL_FRAMEBUFFER, buffer_id_);
        glFramebufferTexture(GL_FRAMEBUFFER,
                             GL_COLOR_ATTACHMENT0,
                             texture, 0);
    }
} // namespace pogl
