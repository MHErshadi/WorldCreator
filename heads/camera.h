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

#ifndef __WRCR_CAMERA__
#define __WRCR_CAMERA__

#include <wrcr.h>

#define WRCR_CAMERA_WALK_SPEED 10 * 4.317f
#define WRCR_CAMERA_SPRINT_SPEED 5.612f
#define WRCR_CAMERA_SNEAK_SPEED 1.295f

#define WRCR_CAMERA_HEIGHT 1.8f
#define WRCR_CAMERA_SNEAK_HEIGHT 1.5f

#ifdef __cplusplus
extern "C" {
#endif

struct __WRCR_CAMERA_T
{
    double mouse_x;
    double mouse_y;

    int half_width;
    int half_height;

    float speed;
    float sensitivity;

    float fov;
    float screen_ratio;
    float far_clip;

    GLint cam_matrix;
    GLint cam_pos;

    int8_t vertical;
    int8_t horizontal;
    int8_t up;

    bool sneaking : 1;
    bool grounded : 1;
};
struct __WRCR_CAMERA_T _camera;

void wrcr_camera_init(
    double x, double y, double z);

void wrcr_camera_move(
    float delta_time);
void wrcr_camera_set_matrix(void);

#ifdef __cplusplus
}
#endif

#endif
