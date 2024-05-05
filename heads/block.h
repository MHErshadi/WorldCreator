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

#define WRCR_TEXTURE_BLOCK_SIZE 16
#define WRCR_TEXTURE_NORM_SIZE (1.0f / WRCR_TEXTURE_BLOCK_SIZE)

struct __WRCR_COORD_T
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
};
typedef struct __WRCR_COORD_T wrcr_coord_t;

struct __WRCR_TCOORD_T
{
    GLfloat x;
    GLfloat y;
};
typedef struct __WRCR_TCOORD_T wrcr_tcoord_t;

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
    wrcr_tcoord_t tex;
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
    { 0.5,  0.5, -0.5},
    { 0.5,  0.5,  0.5},
    {-0.5,  0.5, -0.5},
    {-0.5,  0.5,  0.5},
    // bottom
    {-0.5, -0.5, -0.5},
    {-0.5, -0.5,  0.5},
    { 0.5, -0.5, -0.5},
    { 0.5, -0.5,  0.5},
    // front
    {-0.5, -0.5,  0.5},
    {-0.5,  0.5,  0.5},
    { 0.5, -0.5,  0.5},
    { 0.5,  0.5,  0.5},
    // back
    { 0.5, -0.5, -0.5},
    { 0.5,  0.5, -0.5},
    {-0.5, -0.5, -0.5},
    {-0.5,  0.5, -0.5},
    // right
    { 0.5, -0.5,  0.5},
    { 0.5,  0.5,  0.5},
    { 0.5, -0.5, -0.5},
    { 0.5,  0.5, -0.5},
    // left
    {-0.5, -0.5, -0.5},
    {-0.5,  0.5, -0.5},
    {-0.5, -0.5,  0.5},
    {-0.5,  0.5,  0.5}
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

static wrcr_tcoord_t wrcr_tex_norms[4] =
{
    {0, 0},
    {0, WRCR_TEXTURE_NORM_SIZE},
    {WRCR_TEXTURE_NORM_SIZE, 0},
    {WRCR_TEXTURE_NORM_SIZE, WRCR_TEXTURE_NORM_SIZE}
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
