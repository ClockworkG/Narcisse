#pragma once

#include <GL/glew.h>

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

    private:
        GLuint buffer_id_ = INVALID_FRAME_BUFFER;
    };
} // namespace pogl
