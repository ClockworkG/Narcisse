#version 450

in vec3 position;
in vec3 normal;
out vec3 normal_vector;

uniform mat4 mvp;

void main () {
  gl_Position = mvp * vec4(position, 1.0);
  normal_vector = normalize(normal);
}
