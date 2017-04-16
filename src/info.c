/*
 * yasuna - Yasuna Oribe will talk.
 *
 * info.c
 *
 * Copyright (c) 2015 sasairc
 * This work is free. You can redistribute it and/or modify it under the
 * terms of the Do What The Fuck You Want To Public License, Version 2,
 * as published by Sam Hocevar.HocevarHocevar See the COPYING file or http://www.wtfpl.net/
 * for more details.
 */

#include "./config.h"
#include "./info.h"
#include <stdio.h>
#include <stdlib.h>

int print_version(void)
{
    fprintf(stdout, "%s %d.%d.%d%s (%s)\n",
            PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL, EXTRAVERSION, ARCH);

    exit(0);
}

int print_usage(void)
{
    fprintf(stdout, "\
%s %d.%d.%d%s, Yasuna Oribe will talk.\n\
Usage: %s [OPTION]...\n\
\n\
Mandatory arguments to long options are mandatory for short options too.\n\
\n\
  -l,  --list                print all quotes list and exit\n\
  -s,  --speaker=STR         specify speaker\n\
  -n,  --number INT          specify quote number\n\
  -f,  --file=PATH           specfiles the dictionary file\n\
\n\
  -h,  --help                display this help and exit\n\
  -v,  --version             output version infomation and exit\n\
\n\
Report %s bugs to %s <%s>\n\
", PROGNAME, VERSION, PATCHLEVEL, SUBLEVEL, EXTRAVERSION,
PROGNAME, PROGNAME, AUTHOR, MAIL_TO);

    exit(0);
}
