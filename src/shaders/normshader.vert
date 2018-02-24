#version 330 core

in vec3 position;
in vec3 normal;

out vec3 vNormal;

void main() {
    gl_Position = vec4(position, 1);
    vNormal = normal;
}
