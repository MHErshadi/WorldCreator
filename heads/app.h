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

#ifndef __WRCR_APP__
#define __WRCR_APP__

#include <wrcr.h>

#ifdef __cplusplus
extern "C" {
#endif

struct __WRCR_APP_T
{
    GLFWwindow *window;
    GLFWmonitor *monitor;

    int width;
    int height;

    bool full_screen;
};
struct __WRCR_APP_T _app;

#ifdef __cplusplus
}
#endif

#endif
