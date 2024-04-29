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

#include <chunk.h>
#include <mesh.h>
#include <world.h>
#include <stdlib.h>

bool wrcr_add_block(
    chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z);

bool wrcr_chunk_init(
    chunk_t *chunk)
{
    chunk->vertices = malloc(WRCR_CHUNK_DEF_VERT_COUNT * sizeof(vertex_t));
    if (!chunk->vertices)
        return false;

    chunk->indices = malloc(WRCR_CHUNK_DEF_IDX_COUNT * sizeof(GLuint));
    if (!chunk->indices)
    {
        free(chunk->vertices);
        return false;
    }

    chunk->vertex_idx = 0;
    chunk->size = 0;
    chunk->alloc = WRCR_CHUNK_DEF_FACE_COUNT;

    if (!wrcr_add_block(chunk, 0, 0, 0))
    {
        free(chunk->vertices);
        free(chunk->indices);
        return false;
    }

    chunk->vbo = wrcr_mesh_vbo_init(chunk->vertices, chunk->size * 4);
    chunk->ebo = wrcr_mesh_ebo_init(chunk->indices, chunk->size * 6);

    wrcr_mesh_vao_link(chunk->vbo, chunk->ebo);

    free(chunk->vertices);
    free(chunk->indices);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);
    return true;
}

void wrcr_chunk_delete(
    chunk_t *chunk)
{
    wrcr_mesh_buffer_delete(chunk->vbo);
    wrcr_mesh_buffer_delete(chunk->ebo);
}

bool wrcr_add_block(
    chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z)
{
    vertex_t *vertices;
    GLuint *indices;
    uint32_t idx;

    for (uint8_t i = 0; i != 24; i += 4)
    {
        if (chunk->size == chunk->alloc)
        {
            chunk->alloc += WRCR_CHUNK_DEF_FACE_COUNT;

            vertices = realloc(chunk->vertices, chunk->alloc * 4 * sizeof(vertex_t));
            if (vertices == NULL)
                return false;

            indices = realloc(chunk->indices, chunk->alloc * 6 * sizeof(GLuint));
            if (indices == NULL)
                return false;

            chunk->vertices = vertices;
            chunk->indices = indices;
        }

        idx = chunk->size * 4;

        chunk->vertices[idx].pos = wrcr_block_vertices[i];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = (tex_coord_t){      0, 0.9375f};

        chunk->vertices[idx].pos = wrcr_block_vertices[i + 1];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = (tex_coord_t){      0,       1};

        chunk->vertices[idx].pos = wrcr_block_vertices[i + 2];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = (tex_coord_t){0.0625f, 0.9375f};

        chunk->vertices[idx].pos = wrcr_block_vertices[i + 3];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx].tex = (tex_coord_t){0.0625f,       1};

        idx = chunk->size * 6;

        chunk->indices[idx + 0] = chunk->vertex_idx + 0;
        chunk->indices[idx + 1] = chunk->vertex_idx + 1;
        chunk->indices[idx + 2] = chunk->vertex_idx + 2;
        chunk->indices[idx + 3] = chunk->vertex_idx + 2;
        chunk->indices[idx + 4] = chunk->vertex_idx + 1;
        chunk->indices[idx + 5] = chunk->vertex_idx + 3;

        chunk->vertex_idx += 4;
        chunk->size++;
    }

    return true;
}
