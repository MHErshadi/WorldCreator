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

#include <shader.h>
#include <wrcr.h>
#include <stdlib.h>

GLuint wrcr_shader_init(
    const char *vert, const char *frag)
{
    FILE *vert_file, *frag_file;
    char *vert_data, *frag_data;
    size_t vert_size, frag_size;
    GLuint id, vert_id, frag_id;

    fopen_s(&vert_file, vert, "rb");
    if (vert_file == NULL)
    {
        fputs("Failed to open the vertex shader file\n", stderr);
        return (GLuint)-1;
    }

    fopen_s(&frag_file, frag, "rb");
    if (frag_file == NULL)
    {
        fputs("Failed to open the fragment shader file\n", stderr);
        fclose(vert_file);
        return (GLuint)-1;
    }

    vert_data = wrcr_get_file_data(&vert_size, vert_file);
    fclose(vert_file);
    if (vert_data == NULL)
    {
        fputs("Failed to read data of the vertex shader\n", stderr);
        fclose(frag_file);
        return (GLuint)-1;
    }

    frag_data = wrcr_get_file_data(&frag_size, frag_file);
    fclose(frag_file);
    if (frag_data == NULL)
    {
        fputs("Failed to read data of the fragment shader\n", stderr);
        free(vert_data);
        return (GLuint)-1;
    }

    vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, &vert_data, &(GLint)vert_size);
    glCompileShader(vert_id);

    frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, &frag_data, &(GLint)frag_size);
    glCompileShader(frag_id);

    id = glCreateProgram();
    glAttachShader(id, vert_id);
    glAttachShader(id, frag_id);
    glLinkProgram(id);

    free(vert_data);
    free(frag_data);
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
    return id;
}
