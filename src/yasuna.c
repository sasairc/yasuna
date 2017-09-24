/*
 * yasuna - Yasuna Oribe will talk.
 *
 * yasuna.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./config.h"
#include "./yasuna.h"
#include "./info.h"
#include "./subset.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

#ifdef  WITH_SHARED
#include <benly/string.h>
#include <polyaness.h>
#else
#include <libbenly/src/string.h>
#include <libpolyaness/src/polyaness.h>
/* WITH_SHARED */
#endif

static void release(FILE* fp, polyaness_t* pt);

int main(int argc, char* argv[])
{
    int             status  = 0,
                    res     = 0,
                    index   = 0;

    FILE*           fp      = NULL;

    char*           quote   = NULL;

    polyaness_t*    pt      = NULL;

    yasuna_t yasuna = { 
        YASUNA_ALLNO_FLAG,
    };

    struct option opts[] = {
        {"file",            required_argument, NULL, 'f'},
        {"speaker",         required_argument, NULL, 's'},
        {"number",          required_argument, NULL, 'n'},
        {"search",          required_argument, NULL, 'K'},
#ifdef  WITH_REGEX
        {"extended-regexp", no_argument,       NULL, 'E'},
        {"basic-regexp",    no_argument,       NULL, 'G'},
        {"ignore-case",     no_argument,       NULL, 'i'},
/* WITH_REGEX */
#endif
        {"list",            no_argument,       NULL, 'l'},
        {"help",            no_argument,       NULL, 'h'},
        {"version",         no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    /* processing of arguments */
#ifdef  WITH_REGEX
    while ((res = getopt_long(argc, argv, "f:s:n:K:EGilvh", opts, &index)) != -1) {
#else
    while ((res = getopt_long(argc, argv, "f:s:n:K:lvh", opts, &index)) != -1) {
/* WITH_REGEX */
#endif
        switch (res) {
            case    'f':
                yasuna.farg = optarg;
                yasuna.flag |= YASUNA_FILE;
                break;
            case    's':
                yasuna.sarg = optarg;
                yasuna.flag |= YASUNA_SPEAKER;
                break;
            case    'n':
                if (strisdigit(optarg) < 0) {
                    fprintf(stderr, "%s: %s: invalid number of quote\n",
                            PROGNAME, optarg);
                    return -1;
                }
                yasuna.narg = atoi(optarg);
                yasuna.flag |= YASUNA_NUMBER;
                break;
            case    'K':
                yasuna.Karg = optarg;
                yasuna.flag |= YASUNA_SEARCH;
                break;
#ifdef  WITH_REGEX
            case    'E':
                yasuna.flag |= YASUNA_SEARCH_REGEX_EXTENDED;
                break;
            case    'G':
                yasuna.flag |= YASUNA_SEARCH_REGEX_BASIC;
                break;
            case    'i':
                yasuna.flag |= YASUNA_SEARCH_REGEX_IGNORE;
                break;
/* WITH_REGEX */
#endif
            case    'l':
                yasuna.flag |= YASUNA_LIST;
                break;
            case    'v':
                print_version();
            case    'h':
                print_usage();
            case    '?':
                return -1;
        }
    }

    /* open yasuna-quotes */
    if (open_dict_file(&fp, &yasuna) < 0) {
        status = 1; goto ERR;
    }

    /* read dict file */
    if (read_dict_file(fp, &pt) < 0) {
        status = 2; goto ERR;
    }

    /* do parse polyaness */
    if (parse_dict_file(fp, &pt) < 0) {
        status = 3; goto ERR;
    }

    /* select speaker */
    if (select_by_speaker(yasuna.sarg, &pt, &pt) < 0) {
        status = 4; goto ERR;
    }

    /*
     * show all quotes matching regex
     */
    if (yasuna.flag & YASUNA_SEARCH) {
        if (search_all_quotes(yasuna.Karg, pt, yasuna.flag) < 0) {
            status = 5; goto ERR;
        }
        release(fp, pt);

        return 0;
    }

    /* 
     * print all quotes list and exit
     */
    if (yasuna.flag & YASUNA_LIST) {
        print_all_quotes(pt, &yasuna);
        release(fp, pt);

        return 0;
    }

    /*
     * generate output quote
     */
    if (!(yasuna.flag & YASUNA_NUMBER)) {
        quote = get_polyaness("quote",
                create_rand(pt->recs - 1), &pt);
    } else {
        if (yasuna.narg < pt->recs)
            quote = get_polyaness("quote", yasuna.narg, &pt);
        else
            quote = get_polyaness("quote", 0, &pt);
    }

    /* print of string */
    fprintf(stdout, "%s\n",
            quote);

    /* release memory */
    release(fp, pt);

    return 0;

ERR:
    switch (status) {
        case    1:
            break;
        case    2:
            release(NULL, NULL);
            break;
        case    3:
        case    4:
        case    5:
            release(fp, pt);
            break;
    }
    
    return status;
}

static
void release(FILE* fp, polyaness_t* pt)
{
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    if (pt != NULL)
        release_polyaness(pt);

    return;
}
