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
#include <gen.h>
#include <world.h>
#include <stdlib.h>

bool wrcr_generate_chunk(
    wrcr_chunk_t *chunk);
bool wrcr_add_block(
    wrcr_chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z);
bool wrcr_check_block(
    wrcr_chunk_t *chunk, wrcr_bcoord_t coord);

bool wrcr_chunk_init(
    wrcr_chunk_t *chunk, uint8_t x, uint8_t y)
{
    chunk->vertices = malloc(WRCR_CHUNK_DEF_VERT_COUNT * sizeof(wrcr_vertex_t));
    if (!chunk->vertices)
        return false;

    chunk->indices = malloc(WRCR_CHUNK_DEF_IDX_COUNT * sizeof(GLuint));
    if (!chunk->indices)
    {
        free(chunk->vertices);
        return false;
    }

    chunk->coord = (wrcr_ccoord_t){x * WRCR_CHUNK_WIDTH, y * WRCR_CHUNK_WIDTH};
    chunk->vertex_idx = 0;
    chunk->size = 0;
    chunk->alloc = WRCR_CHUNK_DEF_FACE_COUNT;

    if (!wrcr_generate_chunk(chunk))
    {
        free(chunk->vertices);
        free(chunk->indices);
        return false;
    }

    wrcr_mesh_vao_init(chunk->vao);
    chunk->vbo = wrcr_mesh_vbo_init(chunk->vertices, chunk->size * 4);
    chunk->ebo = wrcr_mesh_ebo_init(chunk->indices, chunk->size * 6);

    wrcr_mesh_vao_link(chunk->vao, chunk->vbo, chunk->ebo);

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
    wrcr_chunk_t *chunk)
{
    wrcr_mesh_vao_delete(chunk->vao);
    wrcr_mesh_buffer_delete(chunk->vbo);
    wrcr_mesh_buffer_delete(chunk->ebo);
}

bool wrcr_generate_chunk(
    wrcr_chunk_t *chunk)
{
    for (uint8_t x = 0; x != WRCR_CHUNK_WIDTH; x++)
        for (uint16_t y = 0; y != WRCR_CHUNK_HEIGHT; y++)
            for (uint8_t z = 0; z != WRCR_CHUNK_WIDTH; z++)
                chunk->data[x][y][z] = wrcr_gen_get_block(chunk->coord.x + x, y, chunk->coord.z + z);

    for (uint8_t x = 0; x != WRCR_CHUNK_WIDTH; x++)
        for (uint16_t y = 0; y != WRCR_CHUNK_HEIGHT; y++)
            for (uint8_t z = 0; z != WRCR_CHUNK_WIDTH; z++)
                if (!wrcr_add_block(chunk, x, y, z))
                    return false;
    return true;
}

bool wrcr_add_block(
    wrcr_chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z)
{
    wrcr_vertex_t *vertices;
    GLuint *indices;
    wrcr_fcoord_t fcoord;
    wrcr_bcoord_t bcoord;
    uint32_t idx;
    uint16_t texid;
    uint8_t i4, j;

    if (!wrcr_blocks[chunk->data[x][y][z]].has_mesh)
        return true;

    for (uint8_t i = 0; i != 6; i++)
    {
        fcoord = wrcr_block_faces[i];
        bcoord = (wrcr_bcoord_t){x + fcoord.x, y + fcoord.y, z + fcoord.z};

        if (wrcr_check_block(chunk, bcoord))
            continue;

        if (chunk->size == chunk->alloc)
        {
            chunk->alloc += WRCR_CHUNK_DEF_FACE_COUNT;

            vertices = realloc(chunk->vertices, chunk->alloc * 4 * sizeof(wrcr_vertex_t));
            if (vertices == NULL)
                return false;

            indices = realloc(chunk->indices, chunk->alloc * 6 * sizeof(GLuint));
            if (indices == NULL)
                return false;

            chunk->vertices = vertices;
            chunk->indices = indices;
        }

        idx = chunk->size << 2;
        i4 = i << 2;

        texid = wrcr_blocks[chunk->data[x][y][z]].texid[i];
        for (j = 0; j != 4; j++)
        {
            vertices = chunk->vertices + idx++;
            vertices->pos = wrcr_block_vertices[i4 + j];
            vertices->pos.x += chunk->coord.x + x;
            vertices->pos.y += y;
            vertices->pos.z += chunk->coord.z + z;
            vertices->texid = (GLfloat)texid + ((GLuint)j << 16);
        }

        idx = chunk->size * 6;

        indices = chunk->indices + idx;
        *indices = chunk->vertex_idx;
        indices[1] = chunk->vertex_idx + 1;
        indices[2] = chunk->vertex_idx + 2;
        indices[3] = indices[2];
        indices[4] = indices[1];
        indices[5] = chunk->vertex_idx + 3;

        chunk->vertex_idx += 4;
        chunk->size++;
    }

    return true;
}

bool wrcr_check_block(
    wrcr_chunk_t *chunk, wrcr_bcoord_t coord)
{
    if (coord.y == 0xffff || coord.y == WRCR_CHUNK_HEIGHT)
        return false;

    if (coord.x == -1 || coord.x == WRCR_CHUNK_WIDTH ||
        coord.z == -1 || coord.z == WRCR_CHUNK_WIDTH)
        return wrcr_blocks[wrcr_gen_get_block(chunk->coord.x + coord.x, coord.y, chunk->coord.z + coord.z)].has_mesh;
    return wrcr_blocks[chunk->data[coord.x][coord.y][coord.z]].has_mesh;
}
