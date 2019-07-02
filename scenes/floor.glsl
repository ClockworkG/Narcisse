#version 450

layout(location = 0) out vec4 frag_colour;

in vec2 uv_vector;

void main() {
    frag_colour = vec4(cos(uv_vector.x), sin(uv_vector.y), tan(uv_vector.x), 1.f);
}
