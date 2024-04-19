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

#ifndef __WRCR_TYPES__
#define __WRCR_TYPES__

#include <inttypes.h>

typedef uint8_t wrcr_bool_t;
typedef uint32_t wrcr_long_t;

typedef double wrcr_double_t;

typedef char wrcr_chr_t;
typedef wrcr_chr_t *wrcr_str_t;

#define WRCR_TRUE (wrcr_bool_t)1
#define WRCR_FALSE (wrcr_bool_t)0

#endif
