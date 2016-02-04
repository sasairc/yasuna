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
#include "./polyaness.h"
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

int open_dict_file(char* path, FILE** fp)
{
    struct  stat st;

    if (stat(path, &st) != 0) {
        fprintf(stderr, "%s: %s: no such file or directory\n",
                PROGNAME, path);

        return -1;
    }

    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        fprintf(stderr, "%s: %s: is a directory\n",
                PROGNAME, path);

        return -2;
    }

    if (access(path, R_OK) != 0) {
        fprintf(stderr, "%s: %s: permission denied\n",
                PROGNAME, path);

        return -3;
    }

    if ((*fp = fopen(path, "r")) == NULL) {
        fprintf(stderr, "%s: fp is NULL\n",
                PROGNAME);

        return -4;
    }

    return 0;
}

int read_dict_file(FILE* fp, polyaness_t** pt)
{
    /* initialize libpolyaness */
    if (init_polyaness(fp, pt) < 0) {
        fprintf(stderr, "%s: init_polyaness() failure\n",
                PROGNAME);
        
        return -1;
    }
    /* no data */
    if ((*pt)->recs == 0) {
        release_polyaness(*pt);

        return -1;
    }

    return 0;
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

void print_all_quotes(polyaness_t* pt)
{
    int     i       = 0;

    char*   speaker = NULL,
        *   quote   = NULL;

    while (i < pt->recs) {
        speaker = get_polyaness("speaker", i, &pt);
        quote = get_polyaness("quote", i, &pt);

        fprintf(stdout, "%4d: %s: %s\n",
                i, speaker, quote);
        i++;
    }

    return;
}
