#version 330 core

in vec3 position;
in vec3 normal;

out vec3 vNormal;
out vec2 vTexCoord;

uniform mat4 viewProjection;
//uniform vec3 camPos;

const float width = 256;
const float detail = 10;

void main(void) {
    gl_Position = viewProjection * vec4(position, 1);
    vNormal = normal;
    //camDist = distance(position, camPos);
    vTexCoord = position.xz / width * detail;
}
