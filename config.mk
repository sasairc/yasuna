#
#    Makefile for yasuna
#

WITH_SHARED	= 0
WITH_GLIB	= 1
WITH_REGEX	= 1
ifeq ($(shell uname), Linux)
WITH_GNU	= 1
endif
WITH_TEST	= 0
WITH_MONO	= 0
DICNME		=
TH_LINES	=
TH_LENGTH	=
