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
        int dflag = 0;
        int res, index;
        char* darg = NULL;
        char** buf = NULL;
        FILE* fp = NULL;

        struct option opts[] = {
                {"dict", required_argument, NULL,   0},
                {"help", no_argument, NULL, 'h'},
                {"version", no_argument, NULL, 'v'},
                {0, 0, 0, 0}
        };

        while ((res = getopt_long(argc, argv, "vh", opts, &index)) != -1) {
                switch (res) {
                        case    0:
                                darg = optarg;
                                dflag = 1;
                                break;
                        case    'v':
                                fprintf(stdout, "%s %s\n", PROGNAME, VERSION);
                                return 0;
                                break;
                        case    'h':
                                print_usage();
                                return 0;
                                break;
                        case    '?':
                                return -1;
                                break;
                }
        }

        if (dflag == 1) {
                fp = fopen(darg, "r");
        } else {
#ifdef  MONO
                fp = fopen(DICNAME, "r");
#else
                fp = fopen(DICPATH, "r");
#endif
        }

        if (fp == NULL) {
                fprintf(stderr, "%s : internal error -- 'no quotes file\n", PROGNAME);
                return 1;
        }

        int lines = -1;
        int point = 0;

        while ((i = getc(fp)) != EOF) {
                if (i == '\n')  lines++;
        }

        buf = (char**)malloc2d(BUFLEN, (lines + 1));
        init2d(buf, BUFLEN, lines);
        read_file(lines, buf, fp);

        point = create_rand(lines);
        fprintf(stdout, "%s", buf[point]);

        fclose(fp);
        free2d(buf, (lines + 1));

        return 0;

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
\n\
  -h,  --help                display this help and exit\n\
  -v,  --version             output version infomation and exit\n\
\n\
Report %s bugs to sasairc@ssiserver.moe.hm\n\
", PROGNAME, VERSION, PROGNAME, PROGNAME);
}

int read_file(int lines, char** buf, FILE* fp)
{
        int i = 0;

        rewind(fp);
        while (fgets(buf[i], sizeof(char) * BUFLEN, fp) != NULL) {
                i++;
        }
        return 0;
}

int create_rand(int lines)
{
        int ret;
        struct timeval lo_timeval;

        gettimeofday(&lo_timeval, NULL);

        srand((unsigned)(
                lo_timeval.tv_usec * getpid()
        ));

        ret = (int)(rand()%(lines-0+1));

        return ret;
}

char** malloc2d(int x, int y)
{
        char** buf;
        int i;

        buf = (char**) malloc(sizeof(char*) * y);
        if (buf == NULL) {
                fprintf(stderr, "malloc2d(): malloc to (char**)var failure.\n");
                exit(2);
        }
        for (i = 0; i < y; i++) {
                buf[i] = (char*)malloc(sizeof(char) * x);
        }

        return buf;
}

int init2d(char** buf, int x, int y)
{
        int i, j;

        for (i = 0; i < y; i++) {
                if (buf[i] == NULL)     buf[i] = (char*)malloc(sizeof(char) * x);
                for (j = 0; j < x; j++) {
                        buf[i][j] = ' ';
                }
        }
}
                        
void free2d(char** buf, int y)
{
        int i = 0;

        for (i = 0; i < y; i++) {
                if (buf[i] != NULL) {
                        free(buf[i]);
                        buf[i] = NULL;
                }
        }
        free(buf);

        return;
}
