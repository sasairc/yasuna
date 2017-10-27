/*
 * yasuna - Yasuna Oribe will talk.
 *
 * config.h
 * 
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#ifndef CONFIG_H
#define CONFIG_H
#ifdef  __cplusplus
extern "C" {
/* __cplusplus */
#endif

#define PROGNAME        "yasuna"
#define VERSION         9
#define PATCHLEVEL      6
#define SUBLEVEL        1
#define EXTRAVERSION    "-devel"

#define AUTHOR          "sasairc"
#define MAIL_TO         "sasairc@ssiserver.moe.hm"

/*
 * # setting of realloc() timing
 * TH_LINES  : threshold of lines
 * TH_LENGTH : threshold of string (sizeof(char) * TH_LENGTH)
 */
#ifndef TH_LINES
#define TH_LINES        1024
/* TH_LINES */
#endif
#ifndef TH_LENGTH
#define TH_LENGTH       640
/* TH_LENGTH */
#endif

#ifdef  __cplusplus
}
/* __cplusplus */
#endif
/* CONFIG_H */
#endif
