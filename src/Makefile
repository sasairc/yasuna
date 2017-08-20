#
#    Makefile for yasuna
#

include ../config.mk

SRCS        = $(wildcard *.c)
OBJS        = $(SRCS:.c=.o)
DEPSRCS     = $(wildcard ./libbenly/src/*.c ./libpolyaness/src/*.c)
DEPOBJS     = $(DEPSRCS:.c=.o)
ARCH        = $(shell gcc -print-multiarch)
DEFCFLAGS   = -DPREFIX=\"$(PREFIX)\"     \
		-DDICPATH=\"$(DICDIR)/\" \
		-DLOCALE=\"\"            \
		-DARCH=\"$(ARCH)\"

# use shared libraries (default: disable)
WITH_SHARED ?= 0
# manually specifies default cowfile
ifdef DICNME
DEFCFLAGS   += -DDICNAME=\"$(DICNME)\"
else
DEFCFLAGS   += -DDICNAME=\"yasuna-quotes\"
# DICNME
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
	@$(CC) $(LDFLAGS) $^ -o $@
else
	$(CC) $(LDFLAGS) $^ -o $@
# CMDLINE
endif
else
DEFLDFLAGS = -lbenly_file -lbenly_memory -lbenly_string -lpolyaness
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
	@$(CC) $(CFLAGS) -c $< -o $@ $(DEFCFLAGS)
else
	$(CC) $(CFLAGS) -c $< -o $@ $(DEFCFLAGS)
endif

build-dep $(DEPOBJS):
	@$(MAKE) -C ./libbenly		all
	@$(MAKE) -C ./libpolyaness	all

clean-dep:
	@$(MAKE) -C ./libpolyaness	clean
	@$(MAKE) -C ./libbenly		clean

install-dep:
	@$(MAKE) -C ./libpolyaness	install
	@$(MAKE) -C ./libbenly		install

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $< $(BINDIR)/

clean: clean-dep
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all		\
        build-dep       \
	clean-dep       \
	install-dep	\
	install-bin	\
	clean
