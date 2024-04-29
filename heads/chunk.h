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

#ifndef __WRCR_CHUNK__
#define __WRCR_CHUNK__

#include <block.h>

#define WRCR_CHUNK_WIDTH 16
#define WRCR_CHUNK_HEIGHT 1024

#define WRCR_CHUNK_DEF_FACE_COUNT 8192

#define WRCR_CHUNK_DEF_VERT_COUNT (WRCR_CHUNK_DEF_FACE_COUNT * 4)
#define WRCR_CHUNK_DEF_IDX_COUNT (WRCR_CHUNK_DEF_FACE_COUNT * 6)

struct __WRCR_CHUNK_T
{
    wrcr_block_t data[WRCR_CHUNK_WIDTH][WRCR_CHUNK_HEIGHT][WRCR_CHUNK_WIDTH];

    wrcr_vertex_t *vertices;
    GLuint *indices;
    GLuint vertex_idx;

    uint32_t size;
    uint32_t alloc;

    GLuint vbo;
    GLuint ebo;
};
typedef struct __WRCR_CHUNK_T wrcr_chunk_t;

bool wrcr_chunk_init(
    wrcr_chunk_t *chunk);
void wrcr_chunk_delete(
    wrcr_chunk_t *chunk);

#endif
