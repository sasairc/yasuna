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

#include "./yasuna.h"
#include "./file.h"
#include "./string.h"
#include "./memory.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <sys/time.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
    int     res,   index;   /* use getopt_long() */
    int     lines;          /* text lines */
    int     point   = 0;    /* lines pointer */
    int     i       = 0;
    char*   path    = NULL; /* dictionary file path */
    char**  buf     = NULL; /* string buffer */
    FILE*   fp      = NULL; /* quotes file */
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
                fprintf(stdout, "%s %d.%d.%d\n", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL);
                return 0;
            case    'h':
                print_usage();
                break;
            case    '?':
                return -1;
        }
    }

    if (yasuna.fflag == 1) {
        path = strlion(1, yasuna.farg); 
    } else {
#ifdef  MONO
        path = strlion(1, DICNAME);             /* with MONO build */
#else
        path = strlion(2, DICPATH, DICNAME);
#endif
    }
    if (path == NULL) {
        fprintf(stderr, "%s: malloc() failed.\n", PROGNAME);

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
        if (lines >= yasuna.narg)   point = yasuna.narg;
    }

    fprintf(stdout, "%s\n", buf[point]);        /* print of string */
    release(fp, path, lines, buf);              /* release memory */

    return 0;
}

int check_file_stat(char* path)
{
    struct  stat st;        /* file status */

    /* checking type of file or directory */
    if (stat(path, &st) != 0) {
        fprintf(stderr, "%s: %s: no such file or directory\n", PROGNAME, path);

        return 1;
    }
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        fprintf(stderr, "%s: %s: is a directory\n", PROGNAME, path);

        return 2;
    }

    /* checking file permission */
    if (access(path, R_OK) != 0) {
        fprintf(stderr, "%s: %s: permission denied\n", PROGNAME, path);

        return 3;
    }

    return 0;
}

FILE* open_file(char* path)
{
    FILE* fp;

    /* open after checking file type */
    if (check_file_type(path) == 0) {
        fp = fopen(path, "r");
    } else {
        fprintf(stderr, "%s: %s: unknown file type\n", PROGNAME, path);
        
        return NULL;
    }
    if (fp == NULL) {
        fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);

        return NULL;
    }

    return fp;
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

int create_rand(int lines)
{
    int ret;
    struct timeval lo_timeval;

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

int print_usage(void)
{
    fprintf(stdout, "\
%s %d.%d.%d, Yasuna Oribe will talk.\n\
Usage: %s [OPTION]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -l,  --list                print all quotes list and exit\n\
  -n,  --number INT          specify quote number\n\
  -f,  --file=PATH           specfiles the dictionary file\n\
\n\
  -h,  --help                display this help and exit\n\
  -v,  --version             output version infomation and exit\n\
\n\
Report %s bugs to %s <%s>\n\
", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL,
PROGNAME, PROGNAME, AUTHOR, MAIL_TO);

    exit(0);
}
