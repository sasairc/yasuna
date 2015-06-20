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

#include <stdio.h>

/* This functions is required subset.c */
extern int check_file_stat(char* path);
extern FILE* open_file(char* path);
extern int create_rand(int lines);

#endif
