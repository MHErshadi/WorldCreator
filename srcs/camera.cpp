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

#include <camera.h>
#include <glm/gtc/type_ptr.hpp>
#include <app.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/vector_angle.hpp>

struct __CAMERA_CXX_T
{
    glm::dvec3 pos;
    glm::vec3 orient;

    glm::vec3 right;
    glm::vec3 velocity;
};
struct __CAMERA_CXX_T _camera_cxx;

bool wrcr_calculate_velocity(
    float delta_time);

void wrcr_camera_init(
    double x, double y, double z)
{
    _camera.half_width = _app.width >> 1;
    _camera.half_height = _app.height >> 1;
    _camera.mouse_x = _camera.half_width;
    _camera.mouse_y = _camera.half_height;

    _camera.speed = WRCR_CAMERA_WALK_SPEED;
    _camera.sensitivity = 100;

    _camera.fov = 45;
    _camera.screen_ratio = (float)_app.width / (float)_app.height;
    _camera.far_clip = 100;

    _camera.cam_matrix = glGetUniformLocation(_app.shader, "camMatrix");
    _camera.cam_pos = glGetUniformLocation(_app.shader, "camPos");

    _camera.vertical = 0;
    _camera.horizontal = 0;
    _camera.up = 0;

    _camera.sneaking = false;
    _camera.grounded = false;

    _camera_cxx.pos = glm::dvec3(x, y + WRCR_CAMERA_HEIGHT, z);
    _camera_cxx.orient = glm::vec3(0, 0, -1);

    glfwSetInputMode(_app.window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
    glfwSetCursorPos(_app.window, _camera.half_width, _camera.half_height);
}

void wrcr_camera_move(
    float delta_time)
{
    _camera_cxx.right = glm::normalize(glm::vec3(-_camera_cxx.orient.z, 0, _camera_cxx.orient.x));
    if (wrcr_calculate_velocity(delta_time))
        _camera_cxx.pos += _camera_cxx.velocity;

    if (_camera.mouse_y != _camera.half_height)
    {
        glm::vec3 new_orient;
        float rot_x;

        rot_x = _camera.sensitivity * (float)(_camera.mouse_y - _camera.half_height) / (float)_app.height;
        new_orient = glm::rotate(_camera_cxx.orient, glm::radians(-rot_x), _camera_cxx.right);
        if (abs(glm::angle(new_orient, glm::vec3(0, 1, 0)) - glm::radians(90.0f)) <= glm::radians(85.0f))
            _camera_cxx.orient = new_orient;
    }
    if (_camera.mouse_x != _camera.half_width)
    {
        float rot_y;

        rot_y = _camera.sensitivity * (float)(_camera.mouse_x - _camera.half_width) / (float)_app.width;
        _camera_cxx.orient = glm::rotate(_camera_cxx.orient, glm::radians(-rot_y), glm::vec3(0, 1, 0));
    }

    glfwSetCursorPos(_app.window, _camera.half_width, _camera.half_height);
}

void wrcr_camera_set_matrix(void)
{
    glm::mat4 view, proj;

    view = glm::lookAt(glm::vec3(0), _camera_cxx.orient, glm::vec3(0, 1, 0));
    proj = glm::perspective(_camera.fov, _camera.screen_ratio, 0.1f, _camera.far_clip);

    glUniformMatrix4fv(_camera.cam_matrix, 1, GL_FALSE, glm::value_ptr(proj * view));
    glUniform3dv(_camera.cam_pos, 1, glm::value_ptr(_camera_cxx.pos));
}

bool wrcr_calculate_velocity(
    float delta_time)
{
    if (_camera.vertical)
    {
        glm::vec3 forward;

        forward = glm::normalize(glm::vec3(_camera_cxx.orient.x, 0, _camera_cxx.orient.z));
        _camera_cxx.velocity = (float)_camera.vertical * forward;

        if (_camera.horizontal)
        {
            _camera_cxx.velocity += (float)_camera.horizontal * _camera_cxx.right;
            if (_camera.up)
                _camera_cxx.velocity += glm::vec3(0, _camera.up, 0);
        }
        else if (_camera.up)
            _camera_cxx.velocity += glm::vec3(0, _camera.up, 0);
    }
    else if (_camera.horizontal)
    {
        _camera_cxx.velocity = (float)_camera.horizontal * _camera_cxx.right;
        if (_camera.up)
            _camera_cxx.velocity += glm::vec3(0, _camera.up, 0);
    }
    else if (_camera.up)
        _camera_cxx.velocity = glm::vec3(0, _camera.up, 0);
    else
        return false;

    _camera_cxx.velocity *= (float)_camera.speed * delta_time;
    return true;
}
