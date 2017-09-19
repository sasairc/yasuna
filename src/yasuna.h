/*
 * yasuna - Yasuna Oribe will talk.
 *
 * yasuna.h
 * 
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef YASUNA_H
#define YASUNA_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#define YASUNA_ALLNO_FLAG   \
    0, 0, NULL, NULL, NULL

#define YASUNA_FILE                     (1 << 1)
#define YASUNA_SPEAKER                  (1 << 2)
#define YASUNA_NUMBER                   (1 << 3)
#define YASUNA_LIST                     (1 << 4)
#define YASUNA_SEARCH                   (1 << 5)

#ifdef  WITH_REGEX
#define YASUNA_SEARCH_REGEX_EXTENDED    (1 << 6)
#define YASUNA_SEARCH_REGEX_BASIC       (1 << 7)
#define YASUNA_SEARCH_REGEX_IGNORE      (1 << 8)
/* WITH_REGEX */
#endif

typedef struct YASUNA_T {
    int     flag;
    int     narg;       /* --number  */
    char*   sarg;       /* --speaker */
    char*   farg;       /* --file    */
    char*   Karg;       /* --search  */
} yasuna_t;

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* YASUNA_H */
#endif
