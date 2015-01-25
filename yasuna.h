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
#define VERSION     0
#define PATCHLEVEL  3
#define SUBLEVEL    5

#define AUTHOR      "sasairc"
#define MAIL_TO     "sasairc@ssiserver.moe.hm"

//#define MONO      /* パスを組み込みたくないときに使うといいかもネ */
#define BUFLEN      256

typedef struct YASUNA_T {
    int lflag;      /* List flag(--list). */
    int dflag;      /* Dictionary flag(--dict=PATH). this flag use getopt_long() */
    int nflag;      /* Number flag(--number=INT). this flag use getopt_long() */
    int narg;       /* Number arguments(--number=INT). this val use getopt_long() */
    char* darg;     /* Dictionary arguments(--dict=PATH). this val use getopt_long()  */
} yasuna_t;

/* This functions is required yasuna.c */
extern int check_file_type(char* filename);
extern int read_file(int lines, char** buf, FILE* fp);
extern int create_rand(int lines);

/* This functions is required memory.c */
extern char** malloc2d(int x, int y);
extern int init2d(char** buf, int x, int y);
extern void free2d(char** buf, int y);

#endif
