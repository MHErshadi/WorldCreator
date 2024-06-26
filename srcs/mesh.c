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

#include <mesh.h>

GLuint wrcr_mesh_vbo_init(
    wrcr_vertex_t *vertices, GLsizeiptr size)
{
    GLuint id;

    glCreateBuffers(1, &id);
    glNamedBufferData(id, size * sizeof(wrcr_vertex_t), vertices, GL_STATIC_DRAW);
    return id;
}

GLuint wrcr_mesh_ebo_init(
    GLuint *indices, GLsizeiptr size)
{
    GLuint id;

    glCreateBuffers(1, &id);
    glNamedBufferData(id, size * sizeof(GLuint), indices, GL_STATIC_DRAW);
    return id;
}

void wrcr_mesh_vao_link(
    GLuint vao, GLuint vbo, GLuint ebo)
{
    glEnableVertexArrayAttrib(vao, 0);
    glVertexArrayAttribBinding(vao, 0, 0);
    glVertexArrayAttribIFormat(vao, 0, 3, GL_UNSIGNED_INT, 0);

    glEnableVertexArrayAttrib(vao, 1);
    glVertexArrayAttribBinding(vao, 1, 0);
    glVertexArrayAttribFormat(vao, 1, 1, GL_FLOAT, GL_FALSE, sizeof(wrcr_coord_t));

    glVertexArrayVertexBuffer(vao, 0, vbo, 0, sizeof(wrcr_vertex_t));
    glVertexArrayElementBuffer(vao, ebo);
}

void wrcr_mesh_draw(
    GLuint vao, GLsizei size)
{
    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, size, GL_UNSIGNED_INT, 0);
}
