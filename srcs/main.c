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

#include <mesh.h>
#include <shader.h>
#include <GLFW/glfw3.h>
#include <stdio.h>

struct __APP_T
{
    GLFWwindow *window;
    GLFWmonitor *monitor;

    int width;
    int height;
    wrcr_bool_t full_screen;

    wrcr_double_t last_time;
    wrcr_double_t curr_time;
    wrcr_long_t time_counter;
};
typedef struct __APP_T app_t;
app_t _app;

GLfloat vertices[] =
{
    -0.5f, -0.28867f, 0,
    0.5f, -0.28867f, 0,
    0, 0.57735f, 0,
    -0.25f, 0.14433f, 0,
    0.25f, 0.14433f, 0,
    0, -0.28867f, 0
};

GLubyte indices[] =
{
    0, 3, 5,
    3, 2, 4,
    5, 4, 1
};

void wrcr_handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods);
inline void wrcr_calc_fps(void);

int main(void)
{
    const GLFWvidmode *video_mode;
    GLuint shader, vao, vbo, ebo;

    if (glfwInit() == GLFW_FALSE)
    {
        fputs("Failed to initialize the GLFW\n", stderr);
        return 1;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_MAXIMIZED, GLFW_TRUE);

    _app.monitor = glfwGetPrimaryMonitor();
    if (!_app.monitor)
    {
        fputs("Failed to find a monitor\n", stderr);
        glfwTerminate();
        return 1;
    }

    video_mode = glfwGetVideoMode(_app.monitor);
    if (!video_mode)
    {
        fputs("Failed to get the video mode\n", stderr);
        glfwTerminate();
        return 1;
    }

    _app.width = video_mode->width;
    _app.height = video_mode->height;

    _app.window = glfwCreateWindow(_app.width, _app.height, "World Creator", NULL, NULL);
    if (!_app.window)
    {
        fputs("Failed to create a GLFW window\n", stderr);
        glfwTerminate();
        return 1;
    }

    _app.full_screen = WRCR_FALSE;

    glfwMakeContextCurrent(_app.window);
    glfwSetKeyCallback(_app.window, wrcr_handle_inputs);

    gladLoadGL();
    glViewport(0, 0, _app.width, _app.height);

    shader = wrcr_shader_init(WRCR_PROJECT_DIR "glsl/vert.glsl",
        WRCR_PROJECT_DIR "glsl/frag.glsl");

    glCreateVertexArrays(1, &vao);
    vbo = wrcr_vbo_init(vertices, sizeof(vertices));
    ebo = wrcr_ebo_init(indices, sizeof(indices));

    wrcr_vao_link(vao, vbo, ebo);

    _app.last_time = glfwGetTime();
    _app.time_counter = 0;
    while (!glfwWindowShouldClose(_app.window))
    {
        glClearColor(0.07f, 0.13f, 0.17f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);
        glBindVertexArray(vao);
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_BYTE, 0);

        glfwSwapBuffers(_app.window);
        glfwPollEvents();

        wrcr_calc_fps();
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);
    glDeleteBuffers(1, &ebo);
    glDeleteProgram(shader);

    glfwTerminate();
    return 0;
}

void wrcr_handle_inputs(
    GLFWwindow *window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
    case GLFW_KEY_ESCAPE:
        glfwSetWindowShouldClose(_app.window, GLFW_TRUE);
    case GLFW_KEY_F11:
        if (_app.full_screen == WRCR_TRUE)
            glfwSetWindowMonitor(_app.window, NULL,
                0, 0, _app.width, _app.height, GLFW_DONT_CARE);
        else
            glfwSetWindowMonitor(_app.window, _app.monitor,
                0, 0, _app.width, _app.height, GLFW_DONT_CARE);
        _app.full_screen = !_app.full_screen;
    }
}

inline void wrcr_calc_fps(void)
{
    wrcr_double_t time_diff;

    _app.curr_time = glfwGetTime();
    time_diff = _app.curr_time - _app.last_time;
    _app.time_counter++;

    if (time_diff >= 1)
    {
        printf("FPS: %lf\n", _app.time_counter / time_diff);

        _app.last_time = _app.curr_time;
        _app.time_counter = 0;
    }
}
