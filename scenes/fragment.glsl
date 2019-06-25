#version 450

out vec4 frag_colour;
in vec3 normal_vector;

void main () {
  frag_colour = vec4(normal_vector, 1.0);
}
