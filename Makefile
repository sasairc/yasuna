TARGET	:= yasuna
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/yasuna
DICNME	:= old-yasuna-quotes
MAKE	:= make
CC		:= cc
RM		:= rm
CFLAGS	:= -O2 -g -Wall
OBJ		= *.o

all: $(TARGET)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\" \
			-DDICNAME=\"$(DICNME)\" \
		-DDICPATH=\"$(DICDIR)/$(DICNME)\"

yasuna: yasuna.c
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c yasuna.c -o yasuna.o
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c memory.c -o memory.o
	$(CC) $(DEFCFLAGS) $(CFLAGS) \
		yasuna.o \
		memory.o \
		-o $(TARGET)

clean:
	-$(RM) -f $(OBJ)
	-$(RM) -f $(TARGET)

install:
	install -pd $(BINDIR)
	install -pd $(DICDIR)
	install -pm 755 $(TARGET) $(BINDIR)/
	install -pm 644 ./quotes/$(DICNME) $(DICDIR)/
