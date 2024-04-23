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
#include <shader.h>
#include <texture.h>
#include <stdio.h>
#include <stdlib.h>

void wrcr_handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods);
void wrcr_window_resized(
    GLFWwindow *window, int width, int height);

int main(void)
{
    const GLFWvidmode *video_mode;
    GLuint shader, texture;

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
    glfwSetKeyCallback(_app.window, wrcr_handle_inputs);
    glfwSetWindowSizeCallback(_app.window, wrcr_window_resized);

    if (!gladLoadGL())
    {
        fputs("Failed to load the glad\n", stderr);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, _app.width, _app.height);

    shader = wrcr_shader_init(
        WRCR_PROJECT_DIR "/glsl/vert.glsl",
        WRCR_PROJECT_DIR "/glsl/frag.glsl");
    if (shader == (GLuint)-1)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    texture = wrcr_texture_init(WRCR_PROJECT_DIR "/texs/blockAtlas.png");
    if (texture == (GLuint)-1)
    {
        wrcr_shader_delete(shader);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    wrcr_texture_set_sampler(shader);

    while (!glfwWindowShouldClose(_app.window))
    {
        wrcr_shader_use(shader);
        wrcr_texture_bind(texture);

        glfwSwapBuffers(_app.window);
        glfwPollEvents();
    }

    wrcr_texture_delete(texture);
    wrcr_shader_delete(shader);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void wrcr_handle_inputs(
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

void wrcr_window_resized(
    GLFWwindow *window, int width, int height)
{
    _app.width = width;
    _app.height = height;

    glViewport(0, 0, width, height);
}
