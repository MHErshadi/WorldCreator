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

#include <app.h>
#include <stdio.h>
#include <stdlib.h>

void handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods);

int main(void)
{
    const GLFWvidmode *video_mode;

    if (glfwInit() == GLFW_FALSE)
    {
        fputs("Failed to initialize the GLFW\n", stderr);
        return EXIT_FAILURE;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    _app.monitor = glfwGetPrimaryMonitor();
    if (_app.monitor == NULL)
    {
        fputs("Failed to get the primary monitor\n", stderr);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    video_mode = glfwGetVideoMode(_app.monitor);
    _app.width = video_mode->width;
    _app.height = video_mode->height;

    _app.window = glfwCreateWindow(_app.width, _app.height, "World Creator", NULL, NULL);
    if (_app.window == NULL)
    {
        fputs("Failed to create the window\n", stderr);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glfwMakeContextCurrent(_app.window);
    glfwSetKeyCallback(_app.window, handle_inputs);

    if (!gladLoadGL())
    {
        fputs("Failed to load the glad\n", stderr);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, _app.width, _app.height);

    while (!glfwWindowShouldClose(_app.window))
    {
        glfwSwapBuffers(_app.window);
        glfwPollEvents();
    }

    glfwTerminate();
    return EXIT_SUCCESS;
}

void handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(window, GLFW_TRUE);
        break;
    case GLFW_KEY_F11:
        if (_app.full_screen)
        {
            glfwSetWindowMonitor(window, NULL, 0, 0, _app.width, _app.height, GLFW_DONT_CARE);
            _app.full_screen = false;
        }
        else
        {
            glfwSetWindowMonitor(window, _app.monitor, 0, 0, _app.width, _app.height, GLFW_DONT_CARE);
            _app.full_screen = true;
        }
        break;
    }
}
