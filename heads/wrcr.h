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

#ifndef __WRCR__
#define __WRCR__

#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

struct __WRCR_COLOR_T
{
    float r;
    float g;
    float b;
};
typedef struct __WRCR_COLOR_T wrcr_color_t;

char *wrcr_get_file_data(size_t *size, FILE *file);

#endif
