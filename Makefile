#
#    Makefile for yasuna
#

TARGET	= yasuna
DICNME	= yasuna-quotes
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/yasuna
MANDIR	:= $(PREFIX)/share/man/ja/man6
MAKE	:= make
CC	:= cc
RM	:= rm
CFLAGS	:= -O2 -g -Wall
LDFLAGS	:=
SRCS	= yasuna.c subset.c file.c string.c memory.c
OBJS	= $(SRCS:.c=.o)

all: $(TARGET) $(OBJS)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\"  \
 		-DDICNAME=\"$(DICNME)\" \
		-DDICPATH=\"$(DICDIR)/\" \

yasuna: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

yasuna.o: yasuna.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c yasuna.c -o yasuna.o

subset.o: subset.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c subset.c -o subset.o

file.o: file.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c file.c -o file.o

string.o: string.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c string.c -o string.o

memory.o: memory.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c memory.c -o memory.o

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $(TARGET) $(BINDIR)/

install-quotes:
	install -pd $(DICDIR)
	install -pm 644 ./quotes/$(DICNME) $(DICDIR)/

install-man:
	install -pd $(MANDIR)
	install -pm 644 ./yasuna.6 $(MANDIR)/

install: install-bin install-quotes

.PHONY: clean
clean:
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)
