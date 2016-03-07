/*
 * polyaness - standard polyaness parse library for C.
 * 
 * Copyright (c) 2016 sasairc
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE
 * OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "./polyaness.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFLEN  4096    /* realloc(): size += BUFLEN */

#define LF      0x0a    /* \n */
#define TAB     0x09    /* \t */
#define COL     0x3a    /* :  */

int count_keys(const char* str);
int add_data_polyaness(int record, int keys, const char* str, polyaness_t*** polyaness);

/* misc functions */
static int strcmp_lite(const char* str1, const char* str2);

int init_polyaness(FILE* fp, int offset, polyaness_t** polyaness)
{
    if (fp == NULL)
        return -1;

    int             i       = 0,
                    j       = 0,
                    code    = 0,
                    recs    = 0;

    polyaness_t*    pt      = NULL;

    rewind(fp);
    while ((code = fgetc(fp)) != EOF) {
        if (code == LF) {
            if (offset > 0) {
                offset--;
                continue;
            }
            recs++;
        }
    }

    if ((pt = (polyaness_t*)
            malloc(sizeof(polyaness_t))) == NULL)
        return -1;

    if ((pt->record = (polyaness_cell**)
            malloc(sizeof(polyaness_cell*) * (recs + 1))) == NULL)
        goto    ERR;

    pt->recs = recs;
    j = recs;
    while (i <= j) {
        if ((pt->record[i] = (polyaness_cell*)
                malloc(sizeof(polyaness_cell))) == NULL)
            goto    ERR;
        pt->record[i]->key = NULL;
        pt->record[i]->key = NULL;

        if ((pt->record[j] = (polyaness_cell*)
                malloc(sizeof(polyaness_cell))) == NULL)
            goto    ERR;
        pt->record[j]->key = NULL;
        pt->record[j]->key = NULL;

        i++;
        j--;
    }
    *polyaness = pt;

    return 0;

ERR:

    if (pt->record != NULL) {
        while (i >= 0) {
            if (pt->record[i] != NULL) {
                free(pt->record[i]);
                pt->record[i] = NULL;
            }
            i--;
        }
        free(pt->record);
        pt->record = NULL;
    }
    if (pt != NULL) {
        free(pt);
        pt = NULL;
    }

    return -1;
}

int parse_polyaness(FILE* fp, int offset, polyaness_t** polyaness)
{
    if (fp == NULL || *polyaness == NULL)
        return -1;

    int     code    = 0,
            recs    = 0;

    char*   buf     = NULL;

    size_t  len     = 0,
            x_bufl  = BUFLEN;

    if ((buf = (char*)
            malloc(sizeof(char) * x_bufl)) == NULL)
        return -1;

    rewind(fp);
    while ((code = fgetc(fp)) != EOF) {
        if (code == LF) {
            if (offset > 0) {
                offset--;
                continue;
            }
            if (add_data_polyaness(recs, count_keys(buf), buf, &polyaness) < 0)
                goto ERR;
            memset(buf, '\0', x_bufl);
            recs++;
            len = 0;
        } else {
            if (offset > 0)
                continue;
            if (len == (x_bufl - 1)) {
                x_bufl += BUFLEN;
                if ((buf = (char*)
                        realloc(buf, sizeof(char) * x_bufl)) == NULL)
                    goto ERR;
            }
            buf[len] = code;
            len++;
        }
    }
    free(buf);

    return 0;

ERR:

    if (buf != NULL) {
        free(buf);
        buf = NULL;
    }

    return -1;
}

int count_keys(const char* str)
{
    int     keys    = 1;

    while (*str != '\0') {
        if (*str == TAB)
            keys++;
        str++;
    }

    return keys;
}

int add_data_polyaness(int record, int keys, const char* str, polyaness_t*** polyaness)
{
    int     i       = 0;

    size_t  head    = 0,
            tail    = 0;

    (*(*polyaness))->record[record]->key = (char**)
        malloc(sizeof(char*) * keys);
    (*(*polyaness))->record[record]->value = (char**)
        malloc(sizeof(char*) * keys);
    
    if ((*(*polyaness))->record[record]->key == NULL ||
        (*(*polyaness))->record[record]->value == NULL)
        return -1;
        
    (*(*polyaness))->record[record]->keys = keys;
    while (i < keys) {
        if (str[head] == COL) {
            (*(*polyaness))->record[record]->key[i] = (char*)
                malloc(sizeof(char) * (head - tail + 1));

            memcpy((*(*polyaness))->record[record]->key[i],
                    str + tail, head - tail);
            (*(*polyaness))->record[record]->key[i][head - tail] = '\0';

            head++;
            tail = head;
        } else if (str[head] == TAB || str[head] == '\0') {
            (*(*polyaness))->record[record]->value[i] = (char*)
                malloc(sizeof(char) * (head - tail + 1));

            memcpy((*(*polyaness))->record[record]->value[i],
                    str + tail, head - tail);
            (*(*polyaness))->record[record]->value[i][head - tail] = '\0';

            head++;
            tail = head;
            i++;
        }
        head++;
    }

    return 0;
}

char* get_polyaness(const char* key, int record, polyaness_t** polyaness)
{
    if (polyaness == NULL   ||
            key == NULL     ||
            (*polyaness)->recs < record)
        return NULL;

    int     i       = 0,
            j       = 0;
    
    char*   match   = NULL;

    j = (*polyaness)->record[record]->keys - 1;
    while (i < (*polyaness)->record[record]->keys && i <= j) {
        if (strcmp_lite((*polyaness)->record[record]->key[i], key) == 0) {
            match = (*polyaness)->record[record]->value[i];
            break;
        }
        if (strcmp_lite((*polyaness)->record[record]->key[j], key) == 0) {
            match = (*polyaness)->record[record]->value[j];
            break;
        }
        i++;
        j--;
    }

    return match;
}

void release_polyaness(polyaness_t* polyaness)
{
    if (polyaness == NULL)
        return;

    int     i   = 0,
            j   = 0;

    while (i < polyaness->recs) {
        if (polyaness->record[i]->key != NULL) {
            j = 0;
            while (j < polyaness->record[i]->keys) {
                if (polyaness->record[i]->key[j] != NULL)
                    free(polyaness->record[i]->key[j]);
                if (polyaness->record[i]->value[j] != NULL)
                    free(polyaness->record[i]->value[j]);
                j++;
            }
            if (polyaness->record[i]->key != NULL)
                free(polyaness->record[i]->key);
            if (polyaness->record[i]->value != NULL)
                free(polyaness->record[i]->value);
        }
        if (polyaness->record[i] != NULL)
            free(polyaness->record[i]);
        i++;
    }
    if (polyaness->record != NULL)
        free(polyaness->record);

    free(polyaness);
    polyaness = NULL;

    return;
}

/*
 * misc functions
 */

static int strcmp_lite(const char* str1, const char* str2)
{
    if (str1 == NULL || str2 == NULL)
        return -1;

    int     cnt     = 0;

    size_t  len1    = 0,
            len2    = 0;

    len1 = strlen(str1);
    len2 = strlen(str2);

    while (*str1 == *str2 && *str1 != '\0' && *str2 != '\0') {
        str1++;
        str2++;
        cnt++;
    }
    if (cnt == len1 && cnt == len2)
        return 0;

    return 1;
}
