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
#include <ctype.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>

int concat_file_path(char** path, yasuna_t* yasuna)
{
    if (yasuna->flag & YASUNA_FILE) {
        *path = strlion(1, yasuna->farg);   
    } else {
#ifdef  MONO
        /* with mono build */
        *path = strlion(1, DICNAME);
#else
        *path = strlion(2, DICPATH, DICNAME);
#endif
    }
    if (*path == NULL) {
        fprintf(stderr, "%s: strlion() failure\n",
                PROGNAME);

        return -1;
    }

    return 0;
}

int open_dict_file(char* path, FILE** fp)
{
    struct  stat st;

    if (stat(path, &st) != 0) {
        fprintf(stderr, "%s: %s: %s\n",
                PROGNAME, path, strerror(ENOENT));

        return -1;
    }

    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        fprintf(stderr, "%s: %s: %s\n",
                PROGNAME, path, strerror(EISDIR));

        return -2;
    }

    if ((st.st_mode & S_IREAD) == 0) {
        fprintf(stderr, "%s: %s: %s\n",
                PROGNAME, path, strerror(EACCES));

        return -3;
    }

    if ((*fp = fopen(path, "r")) == NULL) {
        fprintf(stderr, "%s: %s\n",
                PROGNAME, strerror(errno));

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
    int i   = 0;

    if (parse_polyaness(fp, 0, pt) < 0) {
        fprintf(stderr, "%s: parse_polyaness() failure\n",
                PROGNAME);

        return -1;
    }

    if (strcmp_lite("polyaness_dict",
                get_polyaness("filetype", 0, pt)) == 0) {
        /* release header */
        i = (*pt)->record[0]->keys - 1;
        while (i >= 0) {
            if ((*pt)->record[0]->key[i] != NULL)
                free((*pt)->record[0]->key[i]);
            if ((*pt)->record[0]->value[i] != NULL)
                free((*pt)->record[0]->value[i]);
            i--;
        }
        free((*pt)->record[0]->key);
        free((*pt)->record[0]->value);
        free((*pt)->record[0]);

        /* shift record */
        i = 0;
        while (i < (*pt)->recs &&
                ((*pt)->record[i] = (*pt)->record[i + 1]))
            i++;
        (*pt)->recs--;
    } else {
        if (plain_dict_to_polyaness(fp, pt) < 0) {
            fprintf(stderr, "%s: plain_dict_to_polyaness() failure\n",
                    PROGNAME);

            return -2;
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
    if (p_read_file_char(&buf, TH_LINES, TH_LENGTH, fp, 1) < 0) {
        fprintf(stderr, "%s: p_read_file_char() failure\n",
                PROGNAME);

        return -1;
    }

    if ((quote = (char*)
                smalloc(sizeof(char) * (strlen("quote") + 1), NULL)) == NULL) {
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
        (*pt)->record[i]->keys = 1;
        (*pt)->record[j]->keys = 1;
        (*pt)->record[i]->key[0] = quote;
        (*pt)->record[i]->value[0] = *(buf + i);
        (*pt)->record[j]->key[0] = quote;
        (*pt)->record[j]->value[0] = *(buf + j);
        i++;
        j--;
    }
    free(buf);

    return 0;
}

int select_by_speaker(char* speaker, polyaness_t** src, polyaness_t** dest)
{
    int             i       = 0,
                    j       = 0,
                    recs    = 0;

    polyaness_t*    pt      = NULL;

    /* no modify */
    if (speaker == NULL) {
        *dest = *src;

        return 0;
    }

    if ((pt = (polyaness_t*)
                smalloc(sizeof(polyaness_t), NULL)) == NULL)
        return -1;

    /* extraction speaker */
    pt->record = (*src)->record;
    while (i < (*src)->recs) {
        j = (*src)->record[i]->keys - 1;
        while (j >= 0) {
            if (memcmp((*src)->record[i]->key[j], "speaker\0", 8) == 0  &&
                    memcmp((*src)->record[i]->value[j], speaker, strlen(speaker) + 1) == 0) {
                *(pt->record + recs) = (*src)->record[i];
                recs++;
                break;
            }
            j--;
        }
        if (j < 0)
            release_polyaness_cell(&pt->record[i]);
        i++;
    }
    free(*src);
    *src = NULL;

    pt->recs = recs;
    *dest = pt;

    /* no quotes */
    if (recs <= 0)
        return -2;

    return 0;
}

void release_polyaness_cell(polyaness_cell** record)
{
    int i   = 0,
        j   = 0;
    
    j = (*record)->keys - 1;
    while (j >= i) {
        if ((*record)->key[i] != NULL) {
            free((*record)->key[i]);
            (*record)->key[i] = NULL;
        }
        if ((*record)->value[i] != NULL) {
            free((*record)->value[i]);
            (*record)->value[i] = NULL;
        }
        if ((*record)->key[j] != NULL) {
            free((*record)->key[j]);
            (*record)->key[j] = NULL;
        }
        if ((*record)->value[j] != NULL) {
            free((*record)->value[j]);
            (*record)->value[j] = NULL;
        }
        i++;
        j--;
    }
    if ((*record)->key != NULL) {
        free((*record)->key);
        (*record)->key = NULL;
    }
    if ((*record)->value != NULL) {
        free((*record)->value);
        (*record)->value = NULL;
    }
    if (*record != NULL) {
        free(*record);
        *record = NULL;
    }

    return;
}

int strisdigit(char* str)
{
    char*   p   = str;

    while (*p != '\0') {
        if (!isdigit(*p)) {
            fprintf(stderr, "%s: %s: invalid number of quote\n",
                    PROGNAME, str);

            return -1;
        }
        p++;
    }

    return 0;
}

int create_rand(int lines)
{
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
    return (int)(rand()%(lines+1));
}

void print_all_quotes(polyaness_t* pt, yasuna_t* yasuna)
{
    int i   = 0;

    if (yasuna->flag & YASUNA_SPEAKER)
        fprintf(stdout, "*** speaker = %s, %d quotes ***\n",
                yasuna->sarg, pt->recs);

    while (i < pt->recs) {
        fprintf(stdout, "%4d %s\n",
                i, get_polyaness("quote", i, &pt));
        i++;
    }

    return;
}
