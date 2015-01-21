/*
 * yasuna - Yasuna Oribe will talk.
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

#define PROGNAME    "yasuna"
//#define MONO      /* パスを組み込みたくないときにお使い下さい */
#define VERSION     "0.2"
#define BUFLEN      512

char** malloc2d(int x, int y);
int init2d(char** buf, int x, int y);
void free2d(char** buf, int y);
int read_file(int lines, char** buf, FILE* fp);
int create_rand(int lines);

#endif
