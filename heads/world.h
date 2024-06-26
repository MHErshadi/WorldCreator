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

#ifndef __WRCR_WORLD__
#define __WRCR_WORLD__

#include <chunk.h>

#define WRCR_WORLD_CHUNK_SIZE 16
#define WRCR_WORLD_BLOCK_SIZE (WRCR_WORLD_CHUNK_SIZE * WRCR_CHUNK_WIDTH)

#define WRCR_WORLD_CHUNK_AREA (WRCR_WORLD_CHUNK_SIZE * WRCR_WORLD_CHUNK_SIZE)

#ifdef __cplusplus
extern "C" {
#endif

struct __WRCR_WORLD_T
{
    wrcr_color_t bg_color;

    wrcr_chunk_t *chunks;

    GLuint texture;
    GLuint shader;
};
struct __WRCR_WORLD_T _world;

bool wrcr_world_init(void);
void wrcr_world_delete(void);

void wrcr_world_draw(void);

#ifdef __cplusplus
}
#endif

#endif
