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

#include "./yasuna.h"
#include "./polyaness.h"
#include <stdio.h>

extern int concat_file_path(char** path, yasuna_t* yasuna);
extern int open_dict_file(char* path, FILE** fp);
extern int read_dict_file(FILE* fp, polyaness_t** pt);
extern int parse_dict_file(FILE* fp, polyaness_t** pt);
extern int plain_dict_to_polyaness(FILE* fp, polyaness_t** pt);
extern int select_by_speaker(char* speaker, polyaness_t** src, polyaness_t** dest);
extern void release_polyaness_cell(polyaness_cell** record);
extern int strisdigit(char* str);
extern int create_rand(int lines);
extern void print_all_quotes(polyaness_t* pt);

/* SUBSET_H */
#endif
