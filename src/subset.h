/*
 * yasuna - Yasuna Oribe will talk.
 *
 * subset.h
 * 
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef SUBSET_H
#define SUBSET_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include "./yasuna.h"
#include <stdio.h>

#ifdef  WITH_SHARED
#include <polyaness.h>
#else
#include <libpolyaness/src/polyaness.h>
/* WITH_SHARED */
#endif

extern int open_dict_file(FILE** fp, yasuna_t* yasuna);
extern int read_dict_file(FILE* fp, polyaness_t** pt);
extern int parse_dict_file(FILE* fp, polyaness_t** pt);
extern int select_by_speaker(char* speaker, polyaness_t** src, polyaness_t** dest);
extern int create_rand(int lines);
extern int search_all_quotes(char* pattern, polyaness_t* pt, int flag);
extern void print_all_quotes(polyaness_t* pt, yasuna_t* yasuna);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* SUBSET_H */
#endif
