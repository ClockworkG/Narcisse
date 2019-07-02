#version 450

in vec3 position;
in vec3 normal;
in vec2 uv_map;

out vec3 normal_vector;
out vec2 uv_vector;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main () {
  normal_vector = normalize(normal);
  uv_vector = uv_map;

  gl_Position = projection * view * model * vec4(position, 1.0);
}
