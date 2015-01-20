#ifndef _YASUNA_H
#define _YASUNA_H

#include <stdio.h>

#define PROGNAME        "yasuna"
//#define       MONO            /* パスを組み込みたくないときにお使い下さい */
#define VERSION         "0.1"
#define BUFLEN          512

char** malloc2d(int x, int y);
int init2d(char** buf, int x, int y);
void free2d(char** buf, int y);
int read_file(int lines, char** buf, FILE* fp);
int create_rand(int lines);

#endif
