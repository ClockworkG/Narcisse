#pragma once

#include <pogl/object.hh>

namespace pogl
{
    class Reflecting
    {
    public:
        Reflecting() = default;
        ~Reflecting() = default;
        Reflecting(const Reflecting&) = default;
        Reflecting& operator=(const Reflecting&) = default;
        Reflecting(Reflecting&& other) = default;
        Reflecting& operator=(Reflecting&& other) = default;

        void set_object(Object* object);
        Object* get_object() const;

        Camera mirror_camera(const Camera& camera) const;

    private:
        Object* object_ = nullptr;
    };
} // namespace pogl

#include <pogl/reflecting.hxx>
