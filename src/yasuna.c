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
#include "./libbenly/src/string.h"
#include "./libpolyaness/src/polyaness.h"
/* WITH_SHARED */
#endif

static void release(FILE* fp, char* path, polyaness_t* pt);

int main(int argc, char* argv[])
{
    int             res     = 0,
                    index   = 0;

    FILE*           fp      = NULL;

    char*           path    = NULL,
        *           quote   = NULL;

    polyaness_t*    pt      = NULL;

    yasuna_t yasuna = { 
        YASUNA_ALLNO_FLAG,
    };

    struct option opts[] = {
        {"file",    required_argument, NULL, 'f'},
        {"speaker", required_argument, NULL, 's'},
        {"number",  required_argument, NULL, 'n'},
        {"list",    no_argument,       NULL, 'l'},
        {"help",    no_argument,       NULL, 'h'},
        {"version", no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    /* processing of arguments */
    while ((res = getopt_long(argc, argv, "f:s:n:lvh", opts, &index)) != -1) {
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

    /* concat file path */
    if (concat_file_path(&path, &yasuna) < 0)
        return 1;

    /* open yasuna-quotes */
    if (open_dict_file(path, &fp) < 0) {
        release(NULL, path, NULL);

        return 2;
    }

    /* read dict file */
    if (read_dict_file(fp, &pt) < 0) {
        release(NULL, path, NULL);

        return 3;
    }

    /* do parse polyaness */
    if (parse_dict_file(fp, &pt) < 0) {
        release(fp, path, pt);

        return 4;
    }

    /* select speaker */
    if (select_by_speaker(yasuna.sarg, &pt, &pt) < 0) {
        release(fp, path, pt);

        return 5;
    }

    /* 
     * print all quotes list and exit
     */
    if (yasuna.flag & YASUNA_LIST) {
        print_all_quotes(pt, &yasuna);
        release(fp, path, pt);

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
    release(fp, path, pt);

    return 0;
}

static
void release(FILE* fp, char* path, polyaness_t* pt)
{
    if (fp != NULL) {
        fclose(fp);
        fp = NULL;
    }
    if (path != NULL) {
        free(path);
        path = NULL;
    }
    if (pt != NULL)
        release_polyaness(pt);

    return;
}
