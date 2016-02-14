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
#include "./file.h"
#include "./string.h"
#include "./memory.h"
#include "./polyaness.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    if (init_polyaness(fp, 0, pt) < 0) {
        fprintf(stderr, "%s: init_polyaness() failure\n",
                PROGNAME);
        
        return -1;
    }
    /* no data */
    if ((*pt)->recs == 0) {
        release_polyaness(*pt);

        return -2;
    }

    return 0;
}

int parse_dict_file(FILE* fp, polyaness_t** pt)
{
    int     i       = 0;

    if (parse_polyaness(fp, 0, pt) < 0) {
        fprintf(stderr, "%s: parse_polyaness() failure\n",
                PROGNAME);

        return -1;
    }

    if (strcmp_lite("polyaness_dict",
                get_polyaness("filetype", 0, pt)) == 0) {
        /* release header */
        while (i < (*pt)->record[0]->keys) {
            if ((*pt)->record[0]->key[i] != NULL)
                free((*pt)->record[0]->key[i]);
            if ((*pt)->record[0]->value[i] != NULL)
                free((*pt)->record[0]->value[i]);
            i++;
        }
        free((*pt)->record[0]->key);
        free((*pt)->record[0]->value);
        free((*pt)->record[0]);

        /* shift record */
        i = 0;
        while (i < (*pt)->recs) {
            (*pt)->record[i] = (*pt)->record[i + 1];
            i++;
        }
        (*pt)->recs--;
    } else {
        if (plain_dict_to_polyaness(fp, pt) < 0) {
            fprintf(stderr, "%s: plain_dict_to_polyaness() failure\n",
                    PROGNAME);

            return -3;
        }
    }

    return 0;
}

int plain_dict_to_polyaness(FILE* fp, polyaness_t** pt)
{
    int     i       = 0,
            j       = 0;

    char*   quote   = NULL,
        **  buf     = NULL;

    rewind(fp);
    if ((buf = p_read_file_char(TH_LINES, TH_LENGTH, fp)) == NULL) {
        fprintf(stderr, "%s: p_read_file_char() failure\n",
                PROGNAME);

        return -1;
    }

    if ((quote = (char*)
                malloc(sizeof(char) * (strlen("quote") + 1))) == NULL) {
        fprintf(stderr, "%s: malloc() failure\n",
                PROGNAME);

        if (quote != NULL)
            free(quote);
    
        if (buf != NULL)
            free2d(buf, p_count_file_lines(buf));

        return -2;
    }

    /* mapping char* address to polyaness_t */
    memcpy(quote, "quote\0", strlen("quote") + 1);
    j = (*pt)->recs - 1;
    while (i < (*pt)->recs && i <= j) {
        (*pt)->record[i]->key[0] = quote;
        (*pt)->record[i]->value[0] = buf[i];
        (*pt)->record[j]->key[0] = quote;
        (*pt)->record[j]->value[0] = buf[j];
        i++;
        j--;
    }
    free(buf);

    return 0;
}

int create_rand(int lines)
{
    int     ret = 0;

    struct  timeval lo_timeval;

    /* get localtime */
    gettimeofday(&lo_timeval, NULL);

    /* 
     * # setting factor for pseudo-random number
     * current microseconds * PID
     */
    srand((unsigned)(
        lo_timeval.tv_usec * getpid()
    ));

    /* create pseudo-random number */
    ret = (int)(rand()%(lines+1));

    return ret;
}

void print_all_quotes(polyaness_t* pt)
{
    int     i       = 0;

    while (i < pt->recs) {
        fprintf(stdout, "%4d %s\n",
                i, get_polyaness("quote", i, &pt));
        i++;
    }

    return;
}
