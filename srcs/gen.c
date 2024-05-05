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

#include <gen.h>
#include <world.h>

wrcr_block_t wrcr_gen_get_block(
    uint32_t x, uint16_t y, uint32_t z)
{
    if (x == 0xffffffff || x == WRCR_WORLD_BLOCK_SIZE ||
        z == 0xffffffff || z == WRCR_WORLD_BLOCK_SIZE)
        return WRCR_BLOCK_AIR;

    if (y == 0)
        return WRCR_BLOCK_BEDROCK;
    if (y % 2)
        return WRCR_BLOCK_STONE;
    if (y != WRCR_CHUNK_HEIGHT - 1)
        return WRCR_BLOCK_DIRT;
    return WRCR_BLOCK_GRASS;
}

void wrcr_gen_get_tcoord(
    wrcr_tcoord_t *coord, wrcr_block_t id)
{
    coord->y = (GLfloat)(id / WRCR_TEXTURE_BLOCK_SIZE);
    coord->x = id - coord->y * WRCR_TEXTURE_BLOCK_SIZE;

    coord->x *= WRCR_TEXTURE_NORM_SIZE;
    coord->y = 1 - (coord->y + 1) * WRCR_TEXTURE_NORM_SIZE;
}
