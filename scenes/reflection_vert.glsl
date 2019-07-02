#version 450

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 fPosition;
out vec3 fNormal;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;

void main() {
    fPosition = position;
    fNormal = normal;
    gl_Position = projection * view * model * vec4(position, 1.0);
}
