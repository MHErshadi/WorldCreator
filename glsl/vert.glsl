#version 460 core

#define TEXTURE_BLOCK_SIZE 16
#define TEXTURE_NORM_SIZE (1.0f / TEXTURE_BLOCK_SIZE)

const vec2 texNorms[4] = vec2[4]
(
    vec2(0, 0),
    vec2(0, TEXTURE_NORM_SIZE),
    vec2(TEXTURE_NORM_SIZE, 0),
    vec2(TEXTURE_NORM_SIZE, TEXTURE_NORM_SIZE)
);

layout (location = 0) in uvec3 aPos;
layout (location = 1) in float aBlockID;

out vec2 texCoord;

uniform mat4 camMatrix;
uniform dvec3 camPos;

vec2 getTexCoord(
    uint blockID)
{
    vec2 coord;
    uint face;

    face = blockID >> 16;
    blockID &= 0xffff;

    coord.y = blockID / TEXTURE_BLOCK_SIZE;
    coord.x = blockID - coord.y * TEXTURE_BLOCK_SIZE;

    coord.x *= TEXTURE_NORM_SIZE;
    coord.y = 1 - (coord.y + 1) * TEXTURE_NORM_SIZE;

    coord += texNorms[face];
    return coord;
}

void main(void)
{
    texCoord = getTexCoord(uint(aBlockID));
    gl_Position = camMatrix * vec4(aPos - camPos, 1);
}
