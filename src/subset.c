/*
 * yasuna - Yasuna Oribe will talk.
 *
 * subset.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./config.h"
#include "./subset.h"
#include "./string.h"
#include "./file.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>

char* concat_file_path(yasuna_t* yasuna)
{
    char*   path = NULL;

    if (yasuna->fflag == 1) {
        path = strlion(1, yasuna->farg);    
    } else {
#ifdef  MONO
        path = strlion(1, DICNAME);             /* with MONO build */
#else
        path = strlion(2, DICPATH, DICNAME);
#endif
    }
    if (path == NULL) {
        fprintf(stderr, "%s: strlion() failure\n",
                PROGNAME);

        return NULL;
    }

    return path;
}

int check_file_stat(char* path)
{
    struct  stat st;        /* file status */

    /* checking type of file or directory */
    if (stat(path, &st) != 0) {
        fprintf(stderr, "%s: %s: no such file or directory\n",
                PROGNAME, path);

        return 1;
    }
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        fprintf(stderr, "%s: %s: is a directory\n",
                PROGNAME, path);

        return 2;
    }

    /* checking file permission */
    if (access(path, R_OK) != 0) {
        fprintf(stderr, "%s: %s: permission denied\n",
                PROGNAME, path);

        return 3;
    }

    return 0;
}

FILE* open_file(char* path)
{
    FILE*   fp;

    /* open after checking file type */
    if (check_file_type(path) == 0) {
        fp = fopen(path, "r");
    } else {
        fprintf(stderr, "%s: %s: unknown file type\n",
                PROGNAME, path);
        
        return NULL;
    }
    if (fp == NULL) {
        fprintf(stderr, "%s : internal error -- 'no quotes file\n",
                PROGNAME);

        return NULL;
    }

    return fp;
}

int create_rand(int lines)
{
    int     ret;
    struct  timeval lo_timeval;

    gettimeofday(&lo_timeval, NULL);    /* get localtime */

    /* 
     * # setting factor for pseudo-random number
     * current microseconds * PID
     */
    srand((unsigned)(
        lo_timeval.tv_usec * getpid()
    ));

    ret = (int)(rand()%(lines+1));      /* create pseudo-random number */

    return ret;
}

void print_all_quotes(int lines, char** buf)
{
    int i   = 0;

    for (i = 0; i < lines; i++)
        fprintf(stdout, "%4d %s\n", i, buf[i]);

    return;
}
