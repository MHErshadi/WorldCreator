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

struct __COORD_T
{
    GLdouble x;
    GLdouble y;
    GLdouble z;
};
typedef struct __COORD_T coord_t;

struct __TEX_COORD_T
{
    GLfloat x;
    GLfloat y;
};
typedef struct __TEX_COORD_T tex_coord_t;

struct __VERTEX_T
{
    coord_t pos;
    tex_coord_t tex;
};
typedef struct __VERTEX_T vertex_t;

static coord_t wrcr_block_vertices[24] =
{
    // top
    { 0.5f,  0.5f, -0.5f},
    { 0.5f,  0.5f,  0.5f},
    {-0.5f,  0.5f, -0.5f},
    {-0.5f,  0.5f,  0.5f},
    // bottom
    {-0.5f, -0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f, -0.5f,  0.5f},
    // front
    {-0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f,  0.5f},
    { 0.5f, -0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
    // back
    { 0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
    {-0.5f, -0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    // right
    { 0.5f, -0.5f,  0.5f},
    { 0.5f,  0.5f,  0.5f},
    { 0.5f, -0.5f, -0.5f},
    { 0.5f,  0.5f, -0.5f},
    // left
    {-0.5f, -0.5f, -0.5f},
    {-0.5f,  0.5f, -0.5f},
    {-0.5f, -0.5f,  0.5f},
    {-0.5f,  0.5f,  0.5f}
};

#endif
