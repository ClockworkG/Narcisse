#version 450

layout(location = 0) out vec4 outColor;

in vec3 fPosition;
in vec3 fNormal;

uniform vec3 cameraPos;
uniform samplerCube reflectionMap;

void main() {
    vec3 incident = normalize(fPosition - cameraPos);
    vec3 reflected = reflect(incident, fNormal);
    outColor = vec4(texture(reflectionMap, normalize(reflected)).rgb, 1.0);
}
