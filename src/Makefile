#
#    Makefile for yasuna
#

include ../config.mk

SRCS        = $(wildcard *.c)
OBJS        = $(SRCS:.c=.o)
DEPSRCS     = $(wildcard ./libbenly/src/*.c ./libpolyaness/src/*.c)
DEPOBJS     = $(DEPSRCS:.c=.o)
ARCH        = $(shell $(CC) -dumpmachine)
DEFCFLAGS   = -DPREFIX=\"$(PREFIX)\"     \
		-DDICPATH=\"$(DICDIR)/\" \
		-DLOCALE=\"\"            \
		-DARCH=\"$(ARCH)\"

# use shared libraries (default: disable)
ifeq ($(WITH_SHARED), 1)
DEFCFLAGS   += -DWITH_SHARED
else
INCLUDE     += -I.
DEFCFLAGS   += $(INCLUDE)
# WITH_SHARED
endif
# enable use of GLib (libglib-2.0) with the libbenly
ifeq ($(WITH_GLIB), 1)
WITH_GLIB   ?= 1
DEFCFLAGS   += -DWITH_GLIB `pkg-config --cflags glib-2.0`
DEFLDFLAGS  += `pkg-config --libs glib-2.0`
# WITH_GLIB
endif
# enable use of POSIX Regular Expressions (regex.h) with the libbenly
ifeq ($(WITH_REGEX), 1)
WITH_REGEX  ?= 1
DEFCFLAGS   += -DWITH_REGEX
# WITH_REGEX
endif
# build code coverage information (default: disable)
GCOV_GCDAS  = $(SRCS:.c=.gcda)
GCOV_GCOVS  = $(SRCS:.c=.c.gcov)
ifeq ($(WITH_GCOV), 1)
CFLAGS      += -coverage
LDFLAGS     += -coverage
# WITH_GCOV
endif
# manually specifies default cowfile
ifdef DICNME
DEFCFLAGS   += -DDICNAME=\"$(DICNME)\"
else
DEFCFLAGS   += -DDICNAME=\"yasuna-quotes\"
# DICNME
endif
# mono build
ifeq ($(WITH_MONO), 1)
DEFCFLAGS   += -DWITH_MONO
# WITH_MONO
endif
# threshold of lines (sizeof(char*) * TH_LINES)
ifdef TH_LINES
DEFCFLAGS   += -DTH_LINES=$(TH_LINES)
# TH_LINES
endif
# threshold of string (sizeof(char) * TH_LENGTH)
ifdef TH_LENGTH
DEFCFLAGS   += -DTH_LENGTH=$(TH_LENGTH)
# TH_LENGTH
endif
export

all: $(TARGET)

ifeq ($(WITH_SHARED), 0)
$(TARGET): $(DEPOBJS) $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@ $(DEFLDFLAGS)
else
	$(CC) $(LDFLAGS) $^ -o $@ $(DEFLDFLAGS)
# CMDLINE
endif
else
DEFLDFLAGS += -lbenly_file -lbenly_memory -lbenly_string -lbenly_typestring -lpolyaness
$(TARGET): $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@ $(DEFLDFLAGS)
else
	$(CC) $(LDFLAGS) $^ -o $@ $(DEFLDFLAGS)
# CMDLINE
endif
# WITH_SHARED
endif

%.o: %.c %.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      $@"
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(DEFCFLAGS)
else
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@ $(DEFCFLAGS)
endif

build-dep $(DEPOBJS):
	@$(MAKE) -C ./libbenly     CFLAGS="$(CFLAGS)"	all
	@$(MAKE) -C ./libpolyaness CFLAGS="$(CFLAGS)"	all

clean-dep:
	-$(MAKE) -C ./libpolyaness	clean
	-$(MAKE) -C ./libbenly		clean

install-dep:
	@$(MAKE) -C ./libpolyaness	install
	@$(MAKE) -C ./libbenly		install

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $< $(BINDIR)/

coverage-gcov: all
	@bash ../testsuite/gcov.bash
	@gcov -lp $(GCOV_GCDAS) > ../testsuite/result.gcov
	@tail -n +1 $(GCOV_GCOVS) >> ../testsuite/result.gcov
	@cat ../testsuite/result.gcov

clean-gcov:
	-$(RM) -f *.gcno *.gcda *.gcov
	-$(RM) -f libbenly/src/*.gcno libbenly/src/*.gcda libbenly/src/*.gcov
	-$(RM) -f libpolyaness/src/*.gcno libpolyaness/src/*.gcda libpolyaness/src/*.gcov

clean: clean-dep clean-gcov
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all		\
        build-dep       \
	clean-dep       \
	install-dep	\
	install-bin	\
	coverage-gcov	\
	clean
