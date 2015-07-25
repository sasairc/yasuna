#
#    Makefile for yasuna
#

TARGET	= yasuna
DICNME	= yasuna-quotes
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/$(TARGET)
MANDIR	:= $(PREFIX)/share/man/ja/man6
MAKE	:= make
CC	:= cc
RM	:= rm
CFLAGS	:= -O2 -g -Wall
LDFLAGS	:=
SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)
ARCH	:= $(shell gcc -print-multiarch)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\"  \
 		-DDICNAME=\"$(DICNME)\" \
		-DDICPATH=\"$(DICDIR)/\" \
		-DARCH=\"$(ARCH)\"

all: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(TARGET)

yasuna.o: yasuna.c yasuna.h config.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c yasuna.c -o yasuna.o

info.o:	info.c info.h config.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c info.c -o info.o

subset.o: subset.c subset.h config.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c subset.c -o subset.o

file.o: file.c file.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c file.c -o file.o

string.o: string.c string.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c string.c -o string.o

memory.o: memory.c memory.h
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c memory.c -o memory.o

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $(TARGET) $(BINDIR)/

install-quotes:
	install -pd $(DICDIR)
	install -pm 644 ./quotes/$(DICNME) $(DICDIR)/

install-man:
	install -pd $(MANDIR)
	install -pm 644 $(TARGET).6 $(MANDIR)/

install-zsh-compdef:
	install -pd $(PREFIX)/share/$(TARGET)/zsh
	install -pm 644 _$(TARGET).zsh $(PREFIX)/share/$(TARGET)/zsh

install: install-bin install-quotes install-man install-zsh-compdef

.PHONY: clean
clean:
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)
