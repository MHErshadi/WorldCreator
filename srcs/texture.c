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

#include <texture.h>
#include <shader.h>
#include <stdbool.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

GLuint wrcr_texture_init(
    const char *tex)
{
    int width, height, num_col_ch;
    stbi_uc *bytes;
    GLuint id;

    stbi_set_flip_vertically_on_load(true);
    bytes = stbi_load(tex, &width, &height, &num_col_ch, 0);
    if (bytes == NULL)
    {
        fputs("Failed to load the texture\n", stderr);
        return (GLuint)-1;
    }

    glCreateTextures(GL_TEXTURE_2D, 1, &id);

    glTextureParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTextureParameteri(id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(id, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTextureStorage2D(id, 1, GL_RGBA8, width, height);
    glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    glGenerateTextureMipmap(id);

    stbi_image_free(bytes);
    return id;
}

void wrcr_texture_set_sampler(
    GLuint shader)
{
    GLint uniform;

    uniform = glGetUniformLocation(shader, "tex");

    wrcr_shader_use(shader);
    glUniform1i(uniform, 0);
}
