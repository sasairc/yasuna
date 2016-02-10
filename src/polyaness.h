/*
 * polyaness - standard polyaness parse library for C.
 * 
 * Copyright (c) 2016 sasairc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef POLYANESS_H
#define POLYANESS_H

#include <stdio.h>

typedef struct POLYANESS_CELL {
    int     keys;
    char**  key;
    char**  value;
} polyaness_cell;

typedef struct POLYANESS_T {
    int                     recs;
    struct POLYANESS_CELL** record;
} polyaness_t;

extern int init_polyaness(FILE* fp, int offset, polyaness_t** polyaness);
extern int parse_polyaness(FILE* fp, int offset, polyaness_t** polyaness);
extern char* get_polyaness(const char* key, int record, polyaness_t** polyaness);
extern void release_polyaness(polyaness_t* polyaness);

/* POLYANESS_H */
#endif
