#version 450

layout(location = 0) out vec4 frag_colour;

in vec2 uv_vector;
uniform float time;

void main() {
    frag_colour = vec4(cos(uv_vector.x * time), sin(uv_vector.y * time), tan(uv_vector.x * time), 1.f);
}
