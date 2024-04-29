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

bool wrcr_world_init(void)
{
    _world.bg_color = (color_t){0.012f, 0.776f, 0.988f};

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
    wrcr_mesh_vao_init(_world.vao);

    if (!wrcr_chunk_init(&_world.chunk))
    {
        wrcr_shader_delete(_world.shader);
        wrcr_texture_delete(_world.texture);
        wrcr_mesh_vao_delete(_world.vao);
        return false;
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
    wrcr_chunk_delete(&_world.chunk);
    wrcr_shader_delete(_world.shader);
    wrcr_texture_delete(_world.texture);
    wrcr_mesh_vao_delete(_world.vao);
}

void wrcr_world_draw(void)
{
    glClearColor(_world.bg_color.r, _world.bg_color.g, _world.bg_color.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    wrcr_shader_use(_world.shader);
    wrcr_texture_bind(_world.texture);
    wrcr_mesh_draw(_world.chunk.size * 6);
}
