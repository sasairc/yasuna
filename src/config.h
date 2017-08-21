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
#define VERSION         8
#define PATCHLEVEL      5
#define SUBLEVEL        2
#define EXTRAVERSION    "-nightly_20170821"

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

#undef MONO             /* パスを組み込みたくないときに使うといいかもネ */

/* CONFIG_H */
#endif
