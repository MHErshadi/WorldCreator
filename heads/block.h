/*
MIT License

Copyright (c) 2023 MetaReal

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
*/

#ifndef __WRCR_BLOCK__
#define __WRCR_BLOCK__

#include <wrcr.h>

struct __WRCR_COORD_T
{
    GLuint x;
    GLuint y;
    GLuint z;
};
typedef struct __WRCR_COORD_T wrcr_coord_t;

struct __WRCR_FCOORD_T
{
    int8_t x;
    int8_t y;
    int8_t z;
};
typedef struct __WRCR_FCOORD_T wrcr_fcoord_t;

struct __WRCR_VERTEX_T
{
    wrcr_coord_t pos;
    GLfloat texid;
};
typedef struct __WRCR_VERTEX_T wrcr_vertex_t;

struct __WRCR_BLOCK_T
{
    uint16_t texid[6];

    bool has_mesh : 1;
};

enum __WRCR_BLOCK_ENUM
{
    WRCR_BLOCK_AIR,
    WRCR_BLOCK_BEDROCK,

    WRCR_BLOCK_STONE,
    WRCR_BLOCK_GRASS,
    WRCR_BLOCK_DIRT
};
typedef uint16_t wrcr_block_t;

static wrcr_coord_t wrcr_block_vertices[24] =
{
    // top
    {1, 1, 0},
    {1, 1, 1},
    {0, 1, 0},
    {0, 1, 1},
    // bottom
    {0, 0, 0},
    {0, 0, 1},
    {1, 0, 0},
    {1, 0, 1},
    // front
    {0, 0, 1},
    {0, 1, 1},
    {1, 0, 1},
    {1, 1, 1},
    // back
    {1, 0, 0},
    {1, 1, 0},
    {0, 0, 0},
    {0, 1, 0},
    // right
    {1, 0, 1},
    {1, 1, 1},
    {1, 0, 0},
    {1, 1, 0},
    // left
    {0, 0, 0},
    {0, 1, 0},
    {0, 0, 1},
    {0, 1, 1}
};

static wrcr_fcoord_t wrcr_block_faces[6] =
{
    { 0,  1,  0},
    { 0, -1,  0},
    { 0,  0,  1},
    { 0,  0, -1},
    { 1,  0,  0},
    {-1,  0,  0}
};

static struct __WRCR_BLOCK_T wrcr_blocks[5] =
{
    {{0, 0, 0, 0, 0, 0}, false}, // air
    {{9, 9, 9, 9, 9, 9}, true},  // bedrock
    {{0, 0, 0, 0, 0, 0}, true},  // stone
    {{7, 1, 2, 2, 2, 2}, true},  // grass
    {{1, 1, 1, 1, 1, 1}, true}   // dirt
};

#endif
