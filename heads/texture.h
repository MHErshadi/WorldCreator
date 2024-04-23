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

#ifndef __WRCR_TEXTURE__
#define __WRCR_TEXTURE__

#include <glad/glad.h>

#define wrcr_texture_bind(id) glBindTextureUnit(0, id)
#define wrcr_texture_delete(id) glDeleteTextures(1, &(id))

GLuint wrcr_texture_init(
    const char *tex);

void wrcr_texture_set_sampler(
    GLuint shader);

#endif
