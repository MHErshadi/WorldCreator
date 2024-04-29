#version 460 core

layout (location = 0) in dvec3 aPos;
layout (location = 1) in vec2 aTex;

out vec2 texCoord;

uniform mat4 camMatrix;
uniform dvec3 camPos;

void main(void)
{
    texCoord = aTex;
    gl_Position = camMatrix * vec4(aPos - camPos, 1);
}
