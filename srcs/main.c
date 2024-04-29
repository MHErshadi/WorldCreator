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
#include <mesh.h>
#include <shader.h>
#include <texture.h>
#include <camera.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void wrcr_handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods);
void wrcr_cursor_pos(
    GLFWwindow *window, double xpos, double ypos);
void wrcr_window_resized(
    GLFWwindow *window, int width, int height);

int main(void)
{
    const GLFWvidmode *video_mode;
    GLuint texture, vao, vbo, ebo;
    double curr_time, last_time, new_time;
    float time_diff;
    int32_t fps_counter;

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
    glfwSetCursorPosCallback(_app.window, wrcr_cursor_pos);
    glfwSetWindowSizeCallback(_app.window, wrcr_window_resized);

    if (!gladLoadGL())
    {
        fputs("Failed to load the glad\n", stderr);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    glViewport(0, 0, _app.width, _app.height);

    _app.shader = wrcr_shader_init(
        WRCR_PROJECT_DIR "glsl/vert.glsl",
        WRCR_PROJECT_DIR "glsl/frag.glsl");
    if (_app.shader == (GLuint)-1)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }

    texture = wrcr_texture_init(WRCR_PROJECT_DIR "texs/blockAtlas.png");
    if (texture == (GLuint)-1)
    {
        wrcr_shader_delete(_app.shader);
        glfwTerminate();
        return EXIT_FAILURE;
    }

    wrcr_texture_set_sampler(_app.shader);

    wrcr_mesh_vao_init(vao);
    _app.vao = vao;

    vbo = wrcr_mesh_vbo_init(wrcr_block_vertices, 24);
    ebo = wrcr_mesh_ebo_init(wrcr_block_indices, 36);
    wrcr_mesh_vao_link(vao, vbo, ebo);

    wrcr_camera_init(0 + ADD, -WRCR_CAMERA_HEIGHT + ADD, 2 + ADD);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    glFrontFace(GL_CCW);

    last_time = glfwGetTime();
    curr_time = last_time;
    fps_counter = 0;
    while (!glfwWindowShouldClose(_app.window))
    {
        glClearColor(0.03f, 0.3f, 0.7f, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        wrcr_shader_use(_app.shader);
        wrcr_texture_bind(texture);
        wrcr_mesh_draw(36);

        new_time = glfwGetTime();
        wrcr_camera_move((float)(new_time - curr_time));
        wrcr_camera_set_matrix();

        curr_time = new_time;
        fps_counter++;

        time_diff = (float)(curr_time - last_time);
        if (time_diff >= 1)
        {
            printf("FPS: %f\n", fps_counter / time_diff);
            last_time = curr_time;
            fps_counter = 0;
        }

        glfwSwapBuffers(_app.window);
        glfwPollEvents();
    }

    wrcr_shader_delete(_app.shader);
    wrcr_texture_delete(texture);
    wrcr_mesh_vao_delete(vao);
    wrcr_mesh_buffer_delete(vbo);
    wrcr_mesh_buffer_delete(ebo);
    glfwTerminate();
    return EXIT_SUCCESS;
}

void wrcr_handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_REPEAT)
        return;

    if (action == GLFW_RELEASE)
    {
        switch (key)
        {
        case GLFW_KEY_UP:
            _camera.vertical--;
            break;
        case GLFW_KEY_DOWN:
            _camera.vertical++;
            break;
        case GLFW_KEY_RIGHT:
            _camera.horizontal--;
            break;
        case GLFW_KEY_LEFT:
            _camera.horizontal++;
            break;
        case GLFW_KEY_SPACE:
            _camera.up--;
            break;
        case GLFW_KEY_LEFT_SHIFT:
            _camera.up++;
            _camera.sneaking = false;
            break;
        case GLFW_KEY_LEFT_CONTROL:
            _camera.speed = WRCR_CAMERA_WALK_SPEED;
            break;
        }

        return;
    }

    switch (key)
    {
    case GLFW_KEY_UP:
        _camera.vertical++;
        break;
    case GLFW_KEY_DOWN:
        _camera.vertical--;
        break;
    case GLFW_KEY_RIGHT:
        _camera.horizontal++;
        break;
    case GLFW_KEY_LEFT:
        _camera.horizontal--;
        break;
    case GLFW_KEY_SPACE:
        _camera.up++;
        break;
    case GLFW_KEY_LEFT_SHIFT:
        _camera.up--;
        _camera.sneaking = true;
        break;
    case GLFW_KEY_LEFT_CONTROL:
        _camera.speed = WRCR_CAMERA_SPRINT_SPEED;
        break;
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

void wrcr_cursor_pos(
    GLFWwindow *window, double xpos, double ypos)
{
    _camera.mouse_x = xpos;
    _camera.mouse_y = ypos;
}

void wrcr_window_resized(
    GLFWwindow *window, int width, int height)
{
    _app.width = width;
    _app.height = height;

    glViewport(0, 0, width, height);
}
