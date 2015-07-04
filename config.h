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

#define PROGNAME        "yasuna"
#define VERSION         7
#define PATCHLEVEL      2
#define SUBLEVEL        2
#define EXTRAVERSION    "-devel"

#define AUTHOR          "sasairc"
#define MAIL_TO         "sasairc@ssiserver.moe.hm"

/*
 * # setting of realloc() timing
 * TH_LINES  : threshold of lines
 * TH_LENGTH : threshold of string (sizeof(char) * TH_LENGTH)
 */
#define TH_LINES        512 
#define TH_LENGTH       512

#undef MONO             /* パスを組み込みたくないときに使うといいかもネ */

#endif
