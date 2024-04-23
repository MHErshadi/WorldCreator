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

#include <wrcr.h>
#include <stdlib.h>

char *wrcr_get_file_data(size_t *size, FILE *file)
{
    char *data;
    size_t len;

    fseek(file, 0, SEEK_END);
    len = ftell(file);
    fseek(file, 0, SEEK_SET);

    data = malloc(len * sizeof(char));
    if (!data)
        return NULL;

    fread(data, sizeof(char), len, file);

    *size = len;
    return data;
}
