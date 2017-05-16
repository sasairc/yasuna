/*
 * yasuna - Yasuna Oribe will talk.
 *
 * yasuna.h
 * 
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef _YASUNA_H
#define _YASUNA_H

#include <stdio.h>
#include "./polyaness.h"

#define YASUNA_ALLNO_FLAG   \
    0,  0,  NULL,   NULL

#define YASUNA_FILE     (1 << 1)
#define YASUNA_SPEAKER  (1 << 2)
#define YASUNA_NUMBER   (1 << 3)
#define YASUNA_LIST     (1 << 4)

typedef struct YASUNA_T {
    int     flag;
    int     narg;       /* Number arguments */
    char*   sarg;       /* Speaker arguments */
    char*   farg;       /* Dictionary arguments */
} yasuna_t;

extern void release(FILE* fp, char* path, polyaness_t* pt);

/* _YASUNA_H */
#endif
