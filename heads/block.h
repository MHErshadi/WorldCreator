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

#include <glad/glad.h>

#define ADD 10

struct __VERTEX_T
{
    GLdouble x;
    GLdouble y;
    GLdouble z;

    GLfloat x_tex;
    GLfloat y_tex;
};
typedef struct __VERTEX_T vertex_t;

static vertex_t wrcr_block_vertices[24] =
{
    //Top
    { 0.5 + ADD,  0.5 + ADD, -0.5 + ADD, 0.0625f, 0.9375f},
    { 0.5 + ADD,  0.5 + ADD,  0.5 + ADD, 0.0625f,       1},
    {-0.5 + ADD,  0.5 + ADD, -0.5 + ADD,       0, 0.9375f},
    {-0.5 + ADD,  0.5 + ADD,  0.5 + ADD,       0,       1},
    //Bottom
    {-0.5 + ADD, -0.5 + ADD, -0.5 + ADD, 0.0625f, 0.9375f},
    {-0.5 + ADD, -0.5 + ADD,  0.5 + ADD, 0.0625f,       1},
    { 0.5 + ADD, -0.5 + ADD, -0.5 + ADD,       0, 0.9375f},
    { 0.5 + ADD, -0.5 + ADD,  0.5 + ADD,       0,       1},
    //Front
    {-0.5 + ADD, -0.5 + ADD,  0.5 + ADD, 0.0625f, 0.9375f},
    {-0.5 + ADD,  0.5 + ADD,  0.5 + ADD, 0.0625f,       1},
    { 0.5 + ADD, -0.5 + ADD,  0.5 + ADD,       0, 0.9375f},
    { 0.5 + ADD,  0.5 + ADD,  0.5 + ADD,       0,       1},
    //Back
    { 0.5 + ADD, -0.5 + ADD, -0.5 + ADD, 0.0625f, 0.9375f},
    { 0.5 + ADD,  0.5 + ADD, -0.5 + ADD, 0.0625f,       1},
    {-0.5 + ADD, -0.5 + ADD, -0.5 + ADD,       0, 0.9375f},
    {-0.5 + ADD,  0.5 + ADD, -0.5 + ADD,       0,       1},
    //Right
    { 0.5 + ADD, -0.5 + ADD,  0.5 + ADD, 0.0625f, 0.9375f},
    { 0.5 + ADD,  0.5 + ADD,  0.5 + ADD, 0.0625f,       1},
    { 0.5 + ADD, -0.5 + ADD, -0.5 + ADD,       0, 0.9375f},
    { 0.5 + ADD,  0.5 + ADD, -0.5 + ADD,       0,       1},
    //Left
    {-0.5 + ADD, -0.5 + ADD, -0.5 + ADD, 0.0625f, 0.9375f},
    {-0.5 + ADD,  0.5 + ADD, -0.5 + ADD, 0.0625f,       1},
    {-0.5 + ADD, -0.5 + ADD,  0.5 + ADD,       0, 0.9375f},
    {-0.5 + ADD,  0.5 + ADD,  0.5 + ADD,       0,       1},
};

static GLushort wrcr_block_indices[36] =
{
     0,  1,  2,  2,  1,  3,
     4,  5,  6,  6,  5,  7,
     8,  9, 10, 10,  9, 11,
    12, 13, 14, 14, 13, 15,
    16, 17, 18, 18, 17, 19,
    20, 21, 22, 22, 21, 23,
};

#endif
