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

#define PROGNAME    "yasuna"
#define VERSION     0
#define PATCHLEVEL  4
#define SUBLEVEL    2

#define AUTHOR      "sasairc"
#define MAIL_TO     "sasairc@ssiserver.moe.hm"

//#define MONO        /* パスを組み込みたくないときに使うといいかもネ */
#define BUFLEN      512

typedef struct YASUNA_T {
    int lflag;      /* List flag(--list). */
    int fflag;      /* Dictionary flag(--dict=PATH). this flag use getopt_long() */
    int nflag;      /* Number flag(--number=INT). this flag use getopt_long() */
    int narg;       /* Number arguments(--number=INT). this val use getopt_long() */
    char* farg;     /* Dictionary arguments(--dict=PATH). this val use getopt_long()  */
} yasuna_t;

/* This functions is required yasuna.c */
extern int check_file_stat(char* path);
extern FILE* open_file(char* path);
extern void release(FILE* fp, char* path, int lines, char** buf);
extern int create_rand(int lines);
extern int print_usage(void);

#endif
