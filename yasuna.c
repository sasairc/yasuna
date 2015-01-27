/*
 * yasuna - Yasuna Oribe will talk.
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./yasuna.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <time.h>

int main(int argc, char* argv[])
{
    int i = 0;
    int res, index;     /* Use getopt_long() */
    int lines, point;   /* Text lines and Lines pointer */
    char** buf = NULL;  /* Buffer */
    FILE* fp = NULL;
    yasuna_t yasuna = { /* flag and args */
        0, 0, 0, 0 ,NULL,
    };

    struct option opts[] = {
        {"dict", required_argument, NULL,   0},
        {"number", required_argument, NULL, 'n'},
        {"list", no_argument, NULL, 'l'},
        {"help", no_argument, NULL, 'h'},
        {"version", no_argument, NULL, 'v'},
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

    /* Open after checking file type */
    if (yasuna.dflag == 1) {
        if (check_file_type(yasuna.darg) == 0) {
            fp = fopen(yasuna.darg, "r");       /* Open additional dictionary */
        } else {
            return 1;
        }
    } else {
#ifdef  MONO
        if (check_file_type(DICNAME) == 0) {
            fp = fopen(DICNAME, "r");
        } else {
            return 2;
        }
#else
        if (check_file_type(DICPATH) == 0) {
            fp = fopen(DICPATH, "r");   /* Open standard dictionary */
        } else {
            return 3;
        }
#endif
    }

    if (fp == NULL) {
        fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);
        return 4;
    }

    lines = -1;
    point = 0;

    /* Count line for text-file */
    while ((i = getc(fp)) != EOF) {
        if (i == '\n')  lines++;
    }

    buf = (char**)malloc(sizeof(char*) * (lines + 1));  /* Allocate array for Y coordinate */
    read_file(lines, buf, fp);                          /* Reading file to array */

    if (yasuna.lflag == 1) {                            /* Print all quotes list and exit */
        for (i = 0; i <= lines; i++) {
        fprintf(stdout, "%d %s\n", i, buf[i]);
        }
        return 0;
    }

    if (yasuna.nflag == 0) {
        point = create_rand(lines);                     /* Get pseudo-random nuber */
    } else {
        if (lines >= yasuna.narg)   point = yasuna.narg;
    }

    fprintf(stdout, "%s\n", buf[point]);                /* Print of string */

    fclose(fp);                                         /* Close a file */
    free2d(buf, (lines + 1));                           /* Memory release */

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

int check_file_type(char* filename)
{
    int i, c;
    FILE* fp = NULL;

    int rtf[5] = {0x7B, 0x5C, 0x72, 0x74, 0x66};    /* {\rtf is Ritch-test format's header */

    fp = fopen(filename, "rb");
    if (fp == NULL) {
        return -1;
    }

    while (0 == feof(fp)) {
        c = fgetc(fp);
        if (c == EOF) {             /* Plain text */
            break;
        } else if (c <= 8) {        /* Binary or Unknown format */
            fclose(fp);
            return 1;
        } else if (c == 0x7B) {     /* Ritch text format */
            rewind(fp);
            for (i = 0; i < 5; i++) {
                c = fgetc(fp);
                if (c == rtf[i]) {
                    continue;
                } else {
                    fclose(fp);
                    return 0;
                }
            }
            fclose(fp);

            return 2;
        }
    }
    fclose(fp);

    return 0;
}   

int read_file(int lines, char** buf, FILE* fp)
{
    int i = 0;
    char str[BUFLEN] = {"\0"};

    rewind(fp);     /* Seek file-strem to the top */

    while (fgets(str, sizeof(char) * BUFLEN, fp) != NULL) {
        if (str[strlen(str) - 1] == '\n') { /* Checking string length */
            /* 0: string < BUFLEN */
            str[strlen(str) - 1] = '\0';
            buf[i] = (char*)malloc(         /* Allocate array for X coordinate */
                    (strlen(str) + 1) * sizeof(char)
            );
            strcpy(buf[i], str);            /* Copy, str to buffer */
        } else {
            /* 1: string > BUFLEN */
            fprintf(stderr, "%s: capacity of buffer is not enough: BUFLEN=%d\n", PROGNAME, BUFLEN);
            fclose(fp);                     /* Close a file */
            free2d(buf, (i + 1));           /* Memory release */

            exit(5);
        }
        i++;
    }

    return 0;
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
