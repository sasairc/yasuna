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
#include <errno.h>

#ifndef BUFLEN
#define BUFLEN  4096    /* realloc(): size += BUFLEN */
/* BUFLEN */
#endif

#define LF      0x0a    /* \n */
#define TAB     0x09    /* \t */
#define COL     0x3a    /* :  */

static int count_keys(const char* str);
static int add_data_polyaness(int record, int keys, const char* str, polyaness_t*** polyaness);

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
            malloc(sizeof(polyaness_t))) == NULL) {
        fprintf(stderr, "polyaness: init_polyaness(): malloc(): %s\n",
                strerror(errno));

        goto ERR;
    }
    if ((pt->record = (polyaness_cell**)
            malloc(sizeof(polyaness_cell*) * (recs + 1))) == NULL) {
        fprintf(stderr, "polyaness: init_polyaness(): malloc(): %s\n",
                strerror(errno));

        goto ERR;
    }

    pt->recs = recs;
    j = recs;
    while (i <= j) {
        if ((pt->record[i] = (polyaness_cell*)
                malloc(sizeof(polyaness_cell))) == NULL) {
            fprintf(stderr, "polyaness: init_polyaness(): malloc(): %s\n",
                    strerror(errno));

            goto ERR;
        }
        pt->record[i]->key = NULL;
        pt->record[i]->key = NULL;

        if ((pt->record[j] = (polyaness_cell*)
                malloc(sizeof(polyaness_cell))) == NULL) {
            fprintf(stderr, "polyaness: init_polyaness(): malloc(): %s\n",
                    strerror(errno));

            goto ERR;
        }
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
        goto ERR;

    rewind(fp);
    while ((code = fgetc(fp)) != EOF) {
        if (code == LF) {
            if (offset > 0) {
                offset--;
                continue;
            }
            if (add_data_polyaness(recs, count_keys(buf), buf, &polyaness) < 0) {
                fprintf(stderr, "polyaness: parse_polyaness(): add_data_polyaness() failure\n");

                goto ERR;
            }
            memset(buf, '\0', x_bufl);
            recs++;
            len = 0;
        } else {
            if (offset > 0)
                continue;
            if (len == (x_bufl - 1)) {
                x_bufl += BUFLEN;
                if ((buf = (char*)
                        realloc(buf, sizeof(char) * x_bufl)) == NULL) {
                    fprintf(stderr, "polyaness: parse_polyaness(): realloc(): %s\n",
                            strerror(errno));

                    goto ERR;
                }
            }
            *(buf + len) = code;
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

static
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

static
int add_data_polyaness(int record, int keys, const char* str, polyaness_t*** polyaness)
{
    int             i       = 0;

    char**          key     = NULL,
        **          value   = NULL;

    size_t          head    = 0,
                    tail    = 0;

    key = (char**)
        malloc(sizeof(char*) * keys);
    value = (char**)
        malloc(sizeof(char*) * keys);

    if (key == NULL || value == NULL) {
        fprintf(stderr, "polyaness: add_data_polyaness(): malloc(): %s\n",
                strerror(errno));

        goto ERR;
    }
    
    while (i < keys) {
        if (*(str + head) == COL) {
            if ((*(key + i) = (char*)
                    malloc(sizeof(char) * (head - tail + 1))) == NULL) {
                fprintf(stderr, "polyaness: add_data_polyaness(): malloc(): %s\n",
                        strerror(errno));

                goto ERR;
            }
            memcpy(*(key + i), str + tail, head - tail);
            *(*(key + i) + head - tail) = '\0';

            head++;
            tail = head;
        } else if (*(str + head) == TAB || *(str + head) == '\0') {
            if ((*(value + i) = (char*)
                    malloc(sizeof(char) * (head - tail + 1))) == NULL) {
                fprintf(stderr, "polyaness: add_data_polyaness(): malloc(): %s\n",
                        strerror(errno));

                goto ERR;
            }
            memcpy(*(value + i), str + tail, head - tail);
            *(*(value + i) + head - tail) = '\0';

            head++;
            tail = head;
            i++;
        }
        head++;
    }

    (*(*polyaness))->record[record]->keys = keys;
    (*(*polyaness))->record[record]->key = key;
    (*(*polyaness))->record[record]->value = value;

    return 0;

ERR:
    keys = i;
    if (key != NULL) {
        i = keys;
        while (i >= 0) {
            if (*(key + i) != NULL)
                free(*(key + i));
            i--;
        }
        free(key);
    }
    if (value != NULL) {
        i = keys;
        while (i >= 0) {
            if (*(value + i) != NULL)
                free(*(value + i));
            i--;
        }
        free(value);
    }

    return -1;
}

char* get_polyaness(const char* key, int record, polyaness_t** polyaness)
{
    if (polyaness == NULL   ||
            key == NULL     ||
            (*polyaness)->recs < record)
        return NULL;

    int     i       = 0,
            j       = 0;
    
    char*   match   = NULL,
        **  keys    = (*polyaness)->record[record]->key;

    j = (*polyaness)->record[record]->keys - 1;
    while (i < (*polyaness)->record[record]->keys && i <= j) {
        if (strcmp_lite(*(keys + i), key) == 0)
            return match = (*polyaness)->record[record]->value[i];
        if (strcmp_lite(*(keys + j), key) == 0)
            return match = (*polyaness)->record[record]->value[j];
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
            j   = 0,
            k   = 0;

    i = 0;
    j = polyaness->recs - 1;
    while (i <= j) {
        if (polyaness->record[i] != NULL) {
            if (polyaness->record[i]->key != NULL) {
                k = polyaness->record[i]->keys - 1;
                while (k >= 0) {
                    if (polyaness->record[i]->key[k] != NULL)
                        free(polyaness->record[i]->key[k]);
                    if (polyaness->record[i]->value[j] != NULL)
                        free(polyaness->record[i]->value[k]);
                    k--;
                }
                if (polyaness->record[i]->key != NULL)
                    free(polyaness->record[i]->key);
                if (polyaness->record[i]->value != NULL)
                    free(polyaness->record[i]->value);
            }
            free(polyaness->record[i]);
            polyaness->record[i] = NULL;
        }
        if (polyaness->record[j] != NULL) {
            if (polyaness->record[j]->key != NULL) {
                k = polyaness->record[j]->keys - 1;
                while (k >= 0) {
                    if (polyaness->record[j]->key[k] != NULL)
                        free(polyaness->record[j]->key[k]);
                    if (polyaness->record[j]->value[j] != NULL)
                        free(polyaness->record[j]->value[k]);
                    k--;
                }
            if (polyaness->record[j]->key != NULL)
                free(polyaness->record[j]->key);
            if (polyaness->record[j]->value != NULL)
                free(polyaness->record[j]->value);
            }
            free(polyaness->record[j]);
            polyaness->record[j] = NULL;
        }
        i++;
        j--;
    }
    if (polyaness->record != NULL)
        free(polyaness->record);

    free(polyaness);
    polyaness = NULL;

    return;
}

void release_polyaness_cell(polyaness_cell** record)
{
    int i   = 0,
        j   = 0;
    
    j = (*record)->keys - 1;
    while (j >= i) {
        if ((*record)->key[i] != NULL) {
            free((*record)->key[i]);
            (*record)->key[i] = NULL;
        }
        if ((*record)->value[i] != NULL) {
            free((*record)->value[i]);
            (*record)->value[i] = NULL;
        }
        if ((*record)->key[j] != NULL) {
            free((*record)->key[j]);
            (*record)->key[j] = NULL;
        }
        if ((*record)->value[j] != NULL) {
            free((*record)->value[j]);
            (*record)->value[j] = NULL;
        }
        i++;
        j--;
    }
    if ((*record)->key != NULL) {
        free((*record)->key);
        (*record)->key = NULL;
    }
    if ((*record)->value != NULL) {
        free((*record)->value);
        (*record)->value = NULL;
    }
    if (*record != NULL) {
        free(*record);
        *record = NULL;
    }

    return;
}

/*
 * misc functions
 */
static
int strcmp_lite(const char* str1, const char* str2)
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
