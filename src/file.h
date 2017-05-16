/*
 * yasuna - Yasuna Oribe will talk.
 *
 * file.h
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef FILE_H
#define FILE_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#include <stdio.h>

extern int p_count_file_lines(char** buf);
extern int p_read_file_char(char*** dest, int t_lines, size_t t_length, FILE* fp, int chomp);
extern int watch_fd(int fd, long timeout);

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* FILE_H */
#endif
