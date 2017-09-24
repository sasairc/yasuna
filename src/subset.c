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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/stat.h>

#ifdef  WITH_SHARED
#include <benly/file.h>
#include <benly/string.h>
#include <benly/memory.h>
#include <polyaness.h>
#else
#include <libbenly/src/file.h>
#include <libbenly/src/string.h>
#include <libbenly/src/memory.h>
#include <libpolyaness/src/polyaness.h>
/* WITH_SHARED */
#endif

#ifdef  WITH_REGEX
#include <regex.h>

static int search_all_quotes_with_regexp_string(char* pattern, polyaness_t* pt, int cflags);
/* WITH_REGEX */
#endif

static int concat_file_path(char** path, yasuna_t* yasuna);
static int plain_dict_to_polyaness(FILE* fp, polyaness_t** pt);
static int search_all_quotes_with_fixed_string(char* pattern, polyaness_t* pt);
static char* strstr2(char* str1, char* str2);

static 
int concat_file_path(char** path, yasuna_t* yasuna)
{
    size_t  len     = 0;

    if (yasuna->flag & YASUNA_FILE) {
        len = strlen(yasuna->farg);
        if ((*path = (char*)
                    malloc(sizeof(char) * (len + 1))) == NULL)
            return -1;

        memset(*path, '\0', len + 1);
        memcpy(*path, yasuna->farg, len + 1);
    } else {
#ifdef  WITH_MONO
        len = strlen(DICNAME);
        if ((*path = (char*)
                    malloc(sizeof(char) * (len + 1))) == NULL)
            return -2;
        memset(*path, '\0', len + 1);
        memcpy(*path, DICNAME, len);
#else
        len = strlen(DICPATH) + strlen(DICNAME);
        if ((*path = (char*)
                    malloc(sizeof(char) * (len + 1))) == NULL)
            return -2;

        memset(*path, '\0', len + 1);
        memcpy(*path, DICPATH, strlen(DICPATH));
        memcpy(*path + strlen(DICPATH), DICNAME, strlen(DICNAME) + 1);
/* WITH_MONO */
#endif
    }

    return 0;
}

int open_dict_file(FILE** fp, yasuna_t* yasuna)
{
    int     status  = 0;

    char*   path    = NULL;

    struct  stat st;

    if (concat_file_path(&path, yasuna) < 0) {
        status = -1; goto ERR;
    }

    if (stat(path, &st) != 0) {
        status = -2; goto ERR;
    }

    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        status = -3; goto ERR;
    }

    if ((st.st_mode & S_IREAD) == 0) {
        status = -4; goto ERR;
    }

    if ((*fp = fopen(path, "r")) == NULL) {
        status = -5; goto ERR;
    }
    free(path);

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s: malloc(): %s\n",
                    PROGNAME, strerror(errno));
        case    -2:
            fprintf(stderr, "%s: %s: %s\n",
                    PROGNAME, path, strerror(ENOENT));
            break;
        case    -3:
            fprintf(stderr, "%s: %s: %s\n",
                    PROGNAME, path, strerror(EISDIR));
            break;
        case    -4:
            fprintf(stderr, "%s: %s: %s\n",
                    PROGNAME, path, strerror(EACCES));
            break;
        case    -5:
            fprintf(stderr, "%s: %s: %s\n",
                    PROGNAME, path, strerror(errno));
            break;
    }
    if (path != NULL)
        free(path);

    return status;
}

int read_dict_file(FILE* fp, polyaness_t** pt)
{
    int     status  = 0;

    /* initialize libpolyaness */
    if (init_polyaness(fp, 0, pt) < 0) {
        status = -1; goto ERR;
    }

    /* no data */
    if ((*pt)->recs == 0) {
        status = -2; goto ERR;
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s: init_polyaness() failure\n",
                    PROGNAME);
            break;
        case    -2:
            release_polyaness(*pt);
            break;
    }

    return status;
}

int parse_dict_file(FILE* fp, polyaness_t** pt)
{
    int     i       = 0,
            status  = 0;

    if (parse_polyaness(fp, 0, pt) < 0) {
        status = -1; goto ERR;
    }

    /*
     * 1. polyaness dict
     * 2. plain dict
     */
    if (strcmp_lite("polyaness_dict",
                get_polyaness("filetype", 0, pt)) == 0) {
        /* release header */
        release_polyaness_cell(&(*pt)->record[0]);

        /* shift record */
        i = 0;
        while (i < (*pt)->recs &&
                ((*pt)->record[i] = (*pt)->record[i + 1]))
            i++;
        (*pt)->recs--;
    } else {
        if (plain_dict_to_polyaness(fp, pt) < 0) {
            status = -2; goto ERR;
        }
    }

    return 0;

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s: parse_polyaness() failure\n",
                    PROGNAME);
            break;
        case    -2:
            fprintf(stderr, "%s: plain_dict_to_polyaness() failure\n",
                    PROGNAME);
            break;
    }

    return status;
}

static
int plain_dict_to_polyaness(FILE* fp, polyaness_t** pt)
{
    int     i       = 0,
            j       = 0,
            status  = 0;

    char*   quote   = NULL,
        **  buf     = NULL;

    rewind(fp);
    if (p_read_file_char(&buf, TH_LINES, TH_LENGTH, fp, 1) < 0) {
        status = -1; goto ERR;
    }

    if ((quote = (char*)
                smalloc(sizeof(char) * (strlen("quote") + 1), NULL)) == NULL) {
        status = -2; goto ERR;
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

ERR:
    switch (status) {
        case    -1:
            fprintf(stderr, "%s: p_read_file_char() failure\n",
                    PROGNAME);
            break;
        case    -2:
            if (quote != NULL)
                free(quote);
            if (buf != NULL)
                free2d(buf, p_count_file_lines(buf));
            break;
    }

    return status;
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

int search_all_quotes(char* pattern, polyaness_t* pt, int flag)
{
#ifdef  WITH_REGEX
    int     cflags  = 0;

    /*
     * extended regular expression
     */
    if (flag & YASUNA_SEARCH_REGEX_IGNORE       ||
            flag & YASUNA_SEARCH_REGEX_EXTENDED ||
            flag & YASUNA_SEARCH_REGEX_BASIC) {
        /* POSIX extended regular expression */
        if (flag & YASUNA_SEARCH_REGEX_EXTENDED)
            cflags |= REG_EXTENDED;
        /* POSIX basic regular expression */
        if (flag & YASUNA_SEARCH_REGEX_BASIC)
            cflags &= ~REG_EXTENDED;
        /* ignore case distinctions */
        if (flag & YASUNA_SEARCH_REGEX_IGNORE)
            cflags |= REG_ICASE;

        return search_all_quotes_with_regexp_string(pattern, pt, cflags);
    }
/* WITH_REGEX */
#endif
    
    /* 
     * fixed string
     */
    return search_all_quotes_with_fixed_string(pattern, pt);
}

static
int search_all_quotes_with_fixed_string(char* pattern, polyaness_t* pt)
{
    int     i       = 0;

    short   match   = 0;

    char*   quote   = 0;

    while (i < pt->recs) {
        quote = get_polyaness("quote", i, &pt);
        if (strstr2(quote, pattern) != NULL) {
            match |= 1;
            fprintf(stdout, "%4d %s\n",
                    i, quote);
        }
        i++;
    }
    /* no match */
    if (match == 0)
        return -1;

    return 0;
}

#ifdef  WITH_REGEX
static
int search_all_quotes_with_regexp_string(char* pattern, polyaness_t* pt, int cflags)
{
    int         i           = 0,
                status      = 0;

    short       match       = 0;

    char        errbuf[64]  = {'\0'},
        *       quote       = NULL;

    regex_t     reg;

    if ((status = regcomp(&reg, pattern, cflags | REG_NOSUB)) != 0)
        goto ERR;

    while (i < pt->recs) {
        quote = get_polyaness("quote", i, &pt);
        if (regexec(&reg, quote, 8, 0, 0) == 0) {
            match |= 1;
            fprintf(stdout, "%4d %s\n",
                    i, quote);
        }
        i++;
    }
    regfree(&reg);

    /* no match */
    if (match == 0)
        return -1;

    return 0;

ERR:
    regerror(status, &reg, errbuf, sizeof(errbuf));
    fprintf(stderr, "%s: regexec(): %s: %s\n",
            PROGNAME, pattern, errbuf);

    return -2;
}
/* WITH_REGEX */
#endif

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

static
char* strstr2(char* str1, char* str2)
{
    size_t  off = 0;

    char*   p1  = str1,
        *   p2  = NULL;

    while (*p1 != '\0') {
        p2 = str2;
        while (*p1 == *p2 && *p2 != '\0') {
            p1++;
            p2++;
        }
        if (*p2 == '\0')
            return p1;
        p1 = str1 + (off++);
    }

    return NULL;
}
