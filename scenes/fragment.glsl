#version 450

layout(location = 0) out vec4 frag_colour;

in vec3 normal_vector;
in vec2 uv_vector;

uniform sampler2D texture_sampler;

void main () {
  frag_colour = texture(texture_sampler, uv_vector);
}
