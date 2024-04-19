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
#include <stdio.h>
#include <stdlib.h>

GLuint wrcr_shader_init(
    wrcr_str_ct vert, wrcr_str_ct frag)
{
    FILE *vert_file, *frag_file;
    wrcr_size_t vert_size, frag_size;
    wrcr_str_t vert_code, frag_code;
    GLuint id, vert_id, frag_id;

    vert_file = fopen(vert, "rb");
    if (!vert_file)
    {
        fprintf(stderr, "Failed to open the vertex shader file\n");
        return (GLuint)-1;
    }

    frag_file = fopen(frag, "rb");
    if (!frag_file)
    {
        fprintf(stderr, "Failed to open the fragment shader file\n");
        fclose(vert_file);
        return (GLuint)-1;
    }

    fseek(vert_file, 0, SEEK_END);
    vert_size = ftell(vert_file);
    fseek(vert_file, 0, SEEK_SET);

    fseek(frag_file, 0, SEEK_END);
    frag_size = ftell(frag_file);
    fseek(frag_file, 0, SEEK_SET);

    vert_code = malloc((vert_size + 1) * sizeof(wrcr_chr_t));
    if (!vert_code)
    {
        fprintf(stderr, "Failed to allocate memory for the vertex shader\n");
        fclose(vert_file);
        fclose(frag_file);
        return (GLuint)-1;
    }

    frag_code = malloc((frag_size + 1) * sizeof(wrcr_chr_t));
    if (!frag_code)
    {
        fprintf(stderr, "Failed to allocate memory for the fragment shader\n");
        fclose(vert_file);
        fclose(frag_file);
        free(vert_code);
        return (GLuint)-1;
    }

    fread(vert_code, sizeof(wrcr_chr_t), vert_size, vert_file);
    fread(frag_code, sizeof(wrcr_chr_t), frag_size, frag_file);
    vert_code[vert_size] = '\0';
    frag_code[frag_size] = '\0';

    fclose(vert_file);
    fclose(frag_file);

    vert_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vert_id, 1, &vert_code, NULL);
    glCompileShader(vert_id);

    frag_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(frag_id, 1, &frag_code, NULL);
    glCompileShader(frag_id);

    id = glCreateProgram();
    glAttachShader(id, vert_id);
    glAttachShader(id, frag_id);
    glLinkProgram(id);

    free(vert_code);
    free(frag_code);
    glDeleteShader(vert_id);
    glDeleteShader(frag_id);
    return id;
}
