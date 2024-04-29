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

#ifndef __WRCR_MESH__
#define __WRCR_MESH__

#include <block.h>

#define wrcr_mesh_buffer_delete(id) glDeleteBuffers(1, &(id))

#define wrcr_mesh_vao_init(id) glCreateVertexArrays(1, &(id))
#define wrcr_mesh_vao_delete(id) glDeleteVertexArrays(1, &(id))

GLuint wrcr_mesh_vbo_init(
    vertex_t *vertices, GLsizeiptr size);
GLuint wrcr_mesh_ebo_init(
    GLuint *indices, GLsizeiptr size);

void wrcr_mesh_vao_link(
    GLuint vbo, GLuint ebo);
void wrcr_mesh_draw(
    GLsizei size);

#endif
