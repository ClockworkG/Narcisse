#pragma once

#include <GL/glew.h>
#include <pogl/render-buffer.hh>
#include <pogl/texture.hh>

namespace pogl
{
    constexpr GLuint INVALID_FRAME_BUFFER = 0;

    class RenderTarget
    {
    public:
        RenderTarget();
        ~RenderTarget();
        RenderTarget(RenderTarget&&);
        RenderTarget& operator=(RenderTarget&&);

        RenderTarget(const RenderTarget&) = delete;
        RenderTarget& operator=(const RenderTarget&) = delete;

        operator GLuint() const noexcept;

        void set_depthbuffer(const RenderBuffer& buffer);
        void set_texture(const Texture& texture);

    private:
        GLuint buffer_id_ = INVALID_FRAME_BUFFER;
    };
} // namespace pogl
