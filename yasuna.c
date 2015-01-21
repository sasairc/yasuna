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
        int dflag = 0;          /* Dictionary flag(--dict=PATH). this flag use getopt_long() */
        int nflag = 0;          /* Number flag(--number=INT). this flag use getopt_long() */
        int narg;               /* Number arguments(--number=INT). this val use getopt_long() */
        int res, index;         /* Use getopt_long() */
        int lines, point;       /* Text lines and Lines pointer */
        char* darg = NULL;      /* Dictionary arguments(--dict=PATH). this val use getopt_long()  */
        char** buf = NULL;      /* Buffer */
        FILE* fp = NULL;

        struct option opts[] = {
                {"dict", required_argument, NULL, 0},
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
                                darg = optarg;
                                dflag = 1;
                                break;
                        case    'n':
                                narg = atoi(optarg);
                                nflag = 1;
                                break;
                        case    'l':
                                print_list(dflag, darg, buf, fp);
                                break;
                        case    'v':
                                fprintf(stdout, "%s %s\n", PROGNAME, VERSION);
                                return 0;
                                break;
                        case    'h':
                                print_usage();
                                break;
                        case    '?':
                                return -1;
                                break;
                }
        }

        if (dflag == 1) {
                fp = fopen(darg, "r");          /* Open additional dictionary */
        } else {
#ifdef  MONO
                fp = fopen(DICNAME, "r");
#else
                fp = fopen(DICPATH, "r");       /* Open standard dictionary */
#endif
        }

        if (fp == NULL) {
                fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);
                return 1;
        }

        lines = -1;
        point = 0;

        /* Count line for text-file */
        while ((i = getc(fp)) != EOF) {
                if (i == '\n')  lines++;
        }

        buf = (char**)malloc2d(BUFLEN, (lines + 1));    /* Allocate memory */
        init2d(buf, BUFLEN, lines);                     /* Initialize array */
        read_file(lines, buf, fp);                      /* Reading file to array */

        if (nflag == 0) {
                point = create_rand(lines);             /* Get pseudo-random nuber */
        } else {
                if (lines >= narg)      point = narg;
        }

        fprintf(stdout, "%s", buf[point]);              /* Print of string */

        fclose(fp);                                     /* Close a file */
        free2d(buf, (lines + 1));                       /* Memory release */

        return 0;

}

int print_list(int dflag, char* darg, char** buf, FILE* fp)
{
        int i;
        int lines = -1;

        if (dflag == 1) {
                fp = fopen(darg, "r");          /* Open additional dictionary */
        } else {
#ifdef  MONO
                fp = fopen(DICNAME, "r");
#else
                fp = fopen(DICPATH, "r");       /* Open standard dictionary */
#endif
        }

        /* Count line for text-file */
        if (fp == NULL) {
                fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);
                return 1;
        }
        
        /* Count line for text-file */
        while ((i = getc(fp)) != EOF) {
                if (i == '\n')  lines++;
        }

        buf = (char**)malloc2d(BUFLEN, (lines + 1));    /* Allocate memory */
        init2d(buf, BUFLEN, lines);                     /* Initialize array */
        read_file(lines, buf, fp);                      /* Reading file to array */

        for (i = 0; i <= lines; i++) {
                fprintf(stdout, "%d %s", i, buf[i]);
        }

        fclose(fp);                                     /* Close a file */
        free2d(buf, (lines + 1));                       /* Memory release */
        
        exit(0);
}

int print_usage(void)
{
        fprintf(stdout, "\
%s %s, Yasuna Oribe will talk.\n\
Usage: %s [OPTION]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
       --dict=PATH           specfiles the dictionary\n\
  -l,  --list                print all quotes list and exit\n\
  -n,  --number INT          specify quote number\n\
\n\
  -h,  --help                display this help and exit\n\
  -v,  --version             output version infomation and exit\n\
\n\
Report %s bugs to sasairc@ssiserver.moe.hm\n\
", PROGNAME, VERSION, PROGNAME, PROGNAME);

        exit(0);
}

int read_file(int lines, char** buf, FILE* fp)
{
        int i = 0;

        rewind(fp);        /* Seek file-strem to the top */
        while (fgets(buf[i], sizeof(char) * BUFLEN, fp) != NULL) {
                i++;
        }

        return 0;
}

int create_rand(int lines)
{
        int ret;
        struct timeval lo_timeval;

        gettimeofday(&lo_timeval, NULL);        /* Get localtime */

        /* 
         * # Setting factor for pseudo-random number
         * Current microseconds * PID
         */
        srand((unsigned)(
                lo_timeval.tv_usec * getpid()
        ));

        ret = (int)(rand()%(lines-0+1));        /* Create pseudo-random number */

        return ret;
}

char** malloc2d(int x, int y)
{
        char** buf;
        int i;

        buf = (char**) malloc(sizeof(char*) * y);               /* Allocate array for Y coordinate */
        if (buf == NULL) {
                fprintf(stderr, "malloc2d(): malloc to (char**)var failure.\n");
                exit(2);
        }
        for (i = 0; i < y; i++) {
                buf[i] = (char*)malloc(sizeof(char) * x);        /* Allocate array for X coordinate */
        }

        return buf;
}

int init2d(char** buf, int x, int y)
{
        int i, j;

        /* Initialize each element of array */
        for (i = 0; i < y; i++) {
                if (buf[i] == NULL)     buf[i] = (char*)malloc(sizeof(char) * x);       /* If memory allocation failure, do retry memory allocation. */
                for (j = 0; j < x; j++) {
                        buf[i][j] = ' ';
                }
        }

        return 0;
}
                        
void free2d(char** buf, int y)
{
        int i;

        for (i = 0; i < y; i++) {
                if (buf[i] != NULL) {
                        free(buf[i]);        /* Memory release the Y coordinate. */
                        buf[i] = NULL;
                }
        }
        free(buf);                           /* Release for Memory */

        return;
}
