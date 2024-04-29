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

#ifndef __WRCR_SHADER__
#define __WRCR_SHADER__

#include <wrcr.h>

#define wrcr_shader_use glUseProgram
#define wrcr_shader_delete glDeleteProgram

GLuint wrcr_shader_init(
    const char *vert, const char *frag);

#endif
