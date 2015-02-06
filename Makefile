TARGET	:= yasuna
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/yasuna
DICNME	:= yasuna-quotes
MAKE	:= make
CC		:= cc
RM		:= rm
CFLAGS	:= -O2 -g -Wall
OBJ		= *.o
UNAME	= $(shell uname)

all: $(TARGET)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\"  \
			-DDICNAME=\"$(DICNME)\" \
			-DDICPATH=\"$(DICDIR)/\"

yasuna: yasuna.c file.c memory.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c yasuna.c -o yasuna.o
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c file.c -o file.o
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c memory.c -o memory.o
	$(CC) $(DEFCFLAGS) $(CFLAGS) \
		yasuna.o \
		file.o   \
		memory.o \
		-o $(TARGET)

clean:
	-$(RM) -f $(OBJ)
	-$(RM) -f $(TARGET)

install-bin:
	install -pd $(BINDIR)
	install -pd $(DICDIR)
	install -pm 755 $(TARGET) $(BINDIR)/
	install -pm 644 ./quotes/$(DICNME) $(DICDIR)/

install-man:
	install -pd $(PREFIX)/share/man/man6
	install -pm 644 yasuna.6 $(PREFIX)/share/man/man6

ifneq ($(UNAME),"Darwin")
install: install-bin install-man
else
install: install-bin
endif
