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

#ifndef __WRCR_GENERATION__
#define __WRCR_GENERATION__

#include <block.h>

wrcr_block_t wrcr_gen_get_block(
    uint32_t x, uint16_t y, uint32_t z);

void wrcr_gen_get_tcoord(
    wrcr_tcoord_t *coord, wrcr_block_t id);

#endif