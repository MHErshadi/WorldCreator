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

#ifdef __cplusplus
extern "C" {
#endif

struct __WORLD_T
{
    color_t bg_color;

    chunk_t chunk;

    GLuint texture;
    GLuint vao;
    GLuint shader;
};
struct __WORLD_T _world;

bool wrcr_world_init(void);
void wrcr_world_delete(void);

void wrcr_world_draw(void);

#ifdef __cplusplus
}
#endif

#endif
