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

#include <world.h>
#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include <stdlib.h>

bool wrcr_world_init(void)
{
    uint16_t idx;
    uint8_t i, j;

    _world.bg_color = (wrcr_color_t){0.012f, 0.776f, 0.988f};

    _world.shader = wrcr_shader_init(WRCR_PROJECT_DIR "glsl/vert.glsl", WRCR_PROJECT_DIR "glsl/frag.glsl");
    if (_world.shader == (GLuint)-1)
        return false;

    _world.texture = wrcr_texture_init(WRCR_PROJECT_DIR "texs/blockAtlas.png");
    if (_world.texture == (GLuint)-1)
    {
        wrcr_shader_delete(_world.shader);
        return false;
    }

    wrcr_texture_set_sampler(_world.shader);

    _world.chunks = malloc(WRCR_WORLD_CHUNK_AREA * sizeof(wrcr_chunk_t));
    if (_world.chunks == NULL)
    {
        wrcr_shader_delete(_world.shader);
        wrcr_texture_delete(_world.texture);
        return false;
    }

    for (i = 0; i != WRCR_WORLD_CHUNK_SIZE; i++)
    {
        idx = i * WRCR_WORLD_CHUNK_SIZE;
        for (j = 0; j != WRCR_WORLD_CHUNK_SIZE; j++)
            if (!wrcr_chunk_init(_world.chunks + idx + j, i, j))
            {
                wrcr_shader_delete(_world.shader);
                wrcr_texture_delete(_world.texture);
                return false;
            }
    }

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    return true;
}

void wrcr_world_delete(void)
{
    uint16_t i;

    for (i = 0; i != WRCR_WORLD_CHUNK_AREA; i++)
        wrcr_chunk_delete(_world.chunks + i);
    free(_world.chunks);

    wrcr_shader_delete(_world.shader);
    wrcr_texture_delete(_world.texture);
}

void wrcr_world_draw(void)
{
    wrcr_chunk_t *chunk;
    uint16_t i;

    glClearColor(_world.bg_color.r, _world.bg_color.g, _world.bg_color.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    wrcr_shader_use(_world.shader);
    wrcr_texture_bind(_world.texture);

    for (i = 0; i != WRCR_WORLD_CHUNK_AREA; i++)
    {
        chunk = _world.chunks + i;
        wrcr_mesh_draw(chunk->vao, chunk->size * 6);
    }
}
