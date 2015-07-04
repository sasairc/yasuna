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
#include "./string.h"
#include "./file.h"
#include "./memory.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

int main(int argc, char* argv[])
{
    int     i       = 0,
            res     = 0,    /* use getopt_long() */
            index   = 0,
            lines   = 0,    /* text lines */
            point   = 0;    /* lines pointer */
    FILE*   fp      = NULL; /* quotes file */
    char*   path    = NULL, /* dictionary file path */
        **  buf     = NULL; /* string buffer */
    yasuna_t yasuna = {     /* flag and args */
        0, 0, 0, 0 ,NULL,
    };
    struct option opts[] = {
        {"file",    required_argument, NULL, 'f'},
        {"number",  required_argument, NULL, 'n'},
        {"list",    no_argument,       NULL, 'l'},
        {"help",    no_argument,       NULL, 'h'},
        {"version", no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    /* processing of arguments */
    while ((res = getopt_long(argc, argv, "f:n:lvh", opts, &index)) != -1) {
        switch (res) {
            case    'f':
                yasuna.farg = optarg;
                yasuna.fflag = 1;
                break;
            case    'n':
                yasuna.narg = atoi(optarg);
                yasuna.nflag = 1;
                break;
            case    'l':
                yasuna.lflag = 1;
                break;
            case    'v':
                print_version();
            case    'h':
                print_usage();
            case    '?':
                return -1;
        }
    }
    if ((path = concat_file_path(&yasuna)) == NULL) {

        return 1;
    }
    if (check_file_stat(path) != 0) {
        release(NULL, path, 0, NULL);

        return 2;
    }
    if ((fp = open_file(path)) == NULL) {
        release(NULL, path, 0, NULL);

        return 3;
    }
    if ((buf = p_read_file_char(TH_LINES, TH_LENGTH, fp)) == NULL) {
        fprintf(
                stderr,
                "%s: p_read_file_char() failure\n",
                PROGNAME
        );
        release(fp, path, 0, NULL);
            
        return 7;
    }
    lines = p_count_file_lines(buf);            /* count line for text-file */
    for (i = 0; i < lines; i++)
        strlftonull(buf[i]);                    /* rf to null */

    /* 
     * print all quotes list and exit
     */
    if (yasuna.lflag == 1) {
        for (i = 0; i < lines; i++) {
        fprintf(stdout, "%4d %s\n", i, buf[i]);
        }
        release(fp, path, lines, buf);

        return 0;
    }

    if (yasuna.nflag == 0) {
        do {
            point = create_rand(lines);         /* get pseudo-random nuber */
        } while (buf[point] == NULL);
    } else {
        if (lines > yasuna.narg)    point = yasuna.narg;
    }

    fprintf(stdout, "%s\n", buf[point]);        /* print of string */
    release(fp, path, lines, buf);              /* release memory */

    return 0;
}

void release(FILE* fp, char* path, int lines, char** buf)
{
    if (fp != NULL) {
        fclose(fp);
    }
    if (path != NULL) {
        free(path);
        path = NULL;
    }
    if (buf != NULL) {
        free2d(buf, lines);
    }

    return;
}
