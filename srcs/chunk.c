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
#include <generation.h>
#include <world.h>
#include <stdlib.h>

bool wrcr_generate_chunk(
    wrcr_chunk_t *chunk);
bool wrcr_add_block(
    wrcr_chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z);
bool wrcr_check_block(
    wrcr_chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z);

bool wrcr_chunk_init(
    wrcr_chunk_t *chunk)
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

    chunk->vertex_idx = 0;
    chunk->size = 0;
    chunk->alloc = WRCR_CHUNK_DEF_FACE_COUNT;

    if (!wrcr_generate_chunk(chunk))
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
    wrcr_chunk_t *chunk)
{
    wrcr_mesh_buffer_delete(chunk->vbo);
    wrcr_mesh_buffer_delete(chunk->ebo);
}

bool wrcr_generate_chunk(
    wrcr_chunk_t *chunk)
{
    for (uint8_t x = 0; x != WRCR_CHUNK_WIDTH; x++)
        for (uint16_t y = 0; y != WRCR_CHUNK_HEIGHT; y++)
            for (uint8_t z = 0; z != WRCR_CHUNK_WIDTH; z++)
                chunk->data[x][y][z] = wrcr_generation_get_block(x, y, z);

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
    wrcr_tcoord_t tcoord;
    uint32_t idx;
    uint8_t j;

    for (uint8_t i = 0; i != 6; i++)
    {
        if (wrcr_check_block(chunk, x + wrcr_block_faces[i][0], y + wrcr_block_faces[i][1], z + wrcr_block_faces[i][2]))
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

        wrcr_generation_get_tcoord(&tcoord, wrcr_blocks[chunk->data[x][y][z]].texid[i]);

        idx = chunk->size << 2;
        j = i << 2;

        chunk->vertices[idx].pos = wrcr_block_vertices[j];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = tcoord;

        chunk->vertices[idx].pos = wrcr_block_vertices[j + 1];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = (wrcr_tcoord_t){tcoord.x, tcoord.y + WRCR_TEXTURE_NORM_SIZE};

        chunk->vertices[idx].pos = wrcr_block_vertices[j + 2];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx++].tex = (wrcr_tcoord_t){tcoord.x + WRCR_TEXTURE_NORM_SIZE, tcoord.y};

        chunk->vertices[idx].pos = wrcr_block_vertices[j + 3];
        chunk->vertices[idx].pos.x += x;
        chunk->vertices[idx].pos.y += y;
        chunk->vertices[idx].pos.z += z;
        chunk->vertices[idx].tex = (wrcr_tcoord_t){tcoord.x + WRCR_TEXTURE_NORM_SIZE, tcoord.y + WRCR_TEXTURE_NORM_SIZE};

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

bool wrcr_check_block(
    wrcr_chunk_t *chunk, uint8_t x, uint16_t y, uint8_t z)
{
    if (x == 255 || x == WRCR_CHUNK_WIDTH ||
        z == 255 || z == WRCR_CHUNK_WIDTH ||
        y == 0xffff || y == WRCR_CHUNK_HEIGHT)
        return false;
    return wrcr_blocks[chunk->data[x][y][z]].is_solid;
}
