TARGET	:= yasuna
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/yasuna
DICNME	:= yasuna-quotes
MAKE	:= make
CC		:= cc
RM		:= rm
CFLAGS	:= -g

all: $(TARGET)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\" \
			-DDICNAME=\"$(DICNME)\" \
		-DDICPATH=\"$(DICDIR)/$(DICNME)\"

yasuna: yasuna.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) yasuna.c -o $(TARGET)

clean:
	-$(RM) -f $(TARGET)

install:
	install -pd $(BINDIR)
	install -pd $(DICDIR)
	install -pm 444 $(DICNME) $(DICDIR)/
	install -pm 555 $(TARGET) $(BINDIR)/
