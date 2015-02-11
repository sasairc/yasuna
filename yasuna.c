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
    int i = 0;
    int res, index;     /* Use getopt_long() */
    int lines, point;   /* Text lines and Lines pointer */
    char* path = NULL;  /* Dictionary file path */
    char** buf = NULL;  /* String buffer */
    FILE* fp = NULL;
    struct stat st;     /* File status */
    yasuna_t yasuna = { /* Flag and args */
        0, 0, 0, 0 ,NULL,
    };

    struct option opts[] = {
        {"dict",    required_argument, NULL,  0 },
        {"number",  required_argument, NULL, 'n'},
        {"list",    no_argument,       NULL, 'l'},
        {"help",    no_argument,       NULL, 'h'},
        {"version", no_argument,       NULL, 'v'},
        {0, 0, 0, 0}
    };

    /* Processing of arguments */
    while ((res = getopt_long(argc, argv, "vhln:", opts, &index)) != -1) {
        switch (res) {
            case    0:
                yasuna.darg = optarg;
                yasuna.dflag = 1;
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

    if (yasuna.dflag == 1) {
        path = strlion(1, yasuna.darg); 
    } else {
#ifdef  MONO
        path = strlion(1, DICNAME);             /* With MONO build */
#else
        path = strlion(2, DICPATH, DICNAME);
#endif
    }
    if (path == NULL) {
        fprintf(stderr, "%s: malloc() failed.\n", PROGNAME);

        return 1;
    }

    /* Checking type of file or directory */
    if (stat(path, &st) != 0) {
        fprintf(stderr, "%s: %s: no such file or directory\n", PROGNAME, path);
        free(path);

        return 2;
    }
    if ((st.st_mode & S_IFMT) == S_IFDIR) {
        fprintf(stderr, "%s: %s: is a directory\n", PROGNAME, path);
        free(path);

        return 3;
    }

    /* Checking file permission */
    if (access(path, R_OK) != 0) {
        fprintf(stderr, "%s: %s: permission denied\n", PROGNAME, path);
        free(path);

        return 4;
    }

    /* Open after checking file type */
    if (check_file_type(path) == 0) {
        fp = fopen(path, "r");
    } else {
        fprintf(stderr, "%s: %s: unknown file type\n", PROGNAME, path);
        free(path);
        
        return 5;
    }
    if (fp == NULL) {
        fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);
        free(path);

        return 6;
    }

    point = 0;
    lines = count_file_lines(fp);                       /* Count line for text-file */
    buf = (char**)malloc(sizeof(char*) * (lines + 1));  /* Allocate array for Y coordinate */

    /* Reading file to array */
    rewind(fp);                                         /* Seek file-strem to the top */
    if (read_file(lines, BUFLEN, buf, fp) == 0) {
        fprintf(
                stderr,
                "%s: capacity of buffer is not enough: BUFLEN=%d\n",
                PROGNAME, BUFLEN
        );
        fclose(fp);
        free(path);
        free2d(buf, (lines + 1));

        return 7;
    }

    /* Print all quotes list and exit */
    if (yasuna.lflag == 1) {
        for (i = 0; i <= lines; i++) {
        fprintf(stdout, "%d %s\n", i, buf[i]);
        }
        free(path);
        free2d(buf, (lines + 1));

        return 0;
    }

    if (yasuna.nflag == 0) {
        point = create_rand(lines);                     /* Get pseudo-random nuber */
    } else {
        if (lines >= yasuna.narg)   point = yasuna.narg;
    }
    fprintf(stdout, "%s\n", buf[point]);                /* Print of string */

    fclose(fp);                                         /* Close a file */
    free(path);                                         /* Memory release (filepath) */
    free2d(buf, (lines + 1));                           /* Memory release (buffer) */

    return 0;
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
       --dict=PATH           specfiles the dictionary\n\
\n\
  -h,  --help                display this help and exit\n\
  -v,  --version             output version infomation and exit\n\
\n\
Report %s bugs to %s <%s>\n\
", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL,
PROGNAME, PROGNAME, AUTHOR, MAIL_TO);

    exit(0);
}

int create_rand(int lines)
{
    int ret;
    struct timeval lo_timeval;

    gettimeofday(&lo_timeval, NULL);    /* Get localtime */

    /* 
     * # Setting factor for pseudo-random number
     * Current microseconds * PID
     */
    srand((unsigned)(
        lo_timeval.tv_usec * getpid()
    ));

    ret = (int)(rand()%(lines+1));      /* Create pseudo-random number */

    return ret;
}
