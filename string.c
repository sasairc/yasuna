/*
 * yasuna - Yasuna Oribe will talk.
 *
 * string.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./string.h"
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>

int strrep(char* src, char* haystack, char* needle)
{
    char* find = NULL;

    if (src == NULL || haystack == NULL || needle == NULL) {
        return 1;
    }

    /* seach strings */
    if ((find = strstr(src, haystack)) == NULL) {
        return 3;       /* word not found */
    }
    if (strlen(haystack) < strlen(needle)) {
        src = (char*)realloc(src, strlen(src) + strlen(needle) + 1 - strlen(haystack)); /* reallocate memory */
        /* move match word to specified location in memory */
        memmove(
            find + strlen(needle),
            find + strlen(haystack),
            strlen(src) - strlen(haystack) - (find - src) + 1
        );
        memcpy(find, haystack, strlen(needle));
    } else {
        memcpy(find, needle, strlen(needle));
        /* move match word to specified location in memory */
        if (strlen(haystack) > strlen(needle)) {
            memmove(
                find + strlen(needle),
                find + strlen(haystack),
                strlen(src) - strlen(haystack) - (find - src) + 1
            );
        }
    }

    return 0;
}

char* strlion(int argnum, ...)
{
    char*   buf     = NULL;
    char**  argmnt  = NULL;
    int     i       = 0;
    size_t  size    = 0;    /* string size */
    va_list list;           /* list of variable arguments */

    argmnt = (char**)malloc(sizeof(char*) * argnum);
    if (argmnt == NULL)
        return NULL;

    /* processing of variable arguments */
    va_start(list, argnum);
    for (i = 0; i < argnum; i++) {
        argmnt[i] = va_arg(list, char*);
    }
    va_end(list);

    /* count of string size */
    for (i = 0; i < argnum; i++) {
        size = size + strlen(argmnt[i]);
    }
    buf = (char*)malloc(sizeof(char) * (size + 1)); /* memory allocation */

    for (i = 0; i < argnum; i++) {
        strcat(buf, argmnt[i]);     /* string concatenate */
    }
    free(argmnt);

    return buf;
}
