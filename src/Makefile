#
#    Makefile for yasuna
#

SRCS       = $(wildcard *.c)
OBJS       = $(SRCS:.c=.o)
DEPSRCS    = $(wildcard ./libbenly/src/*.c ./libpolyaness/src/*.c)
DEPOBJS    = $(DEPSRCS:.c=.o)
ARCH       = $(shell gcc -print-multiarch)
DEFCFLAGS  = -DPREFIX=\"$(PREFIX)\"      \
		-DDICNAME=\"$(DICNME)\"  \
		-DDICPATH=\"$(DICDIR)/\" \
		-DLOCALE=\"\"            \
		-DBUFLEN=$(BUFLEN)       \
		-DTH_LINES=$(TH_LINES)   \
		-DTH_LENGTH=$(TH_LENGTH) \
		-DARCH=\"$(ARCH)\"
export

all: $(TARGET)

$(TARGET): $(DEPOBJS) $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@
else
	$(CC) $(LDFLAGS) $^ -o $@
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

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $< $(BINDIR)/

clean: clean-dep
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all		\
        build-dep       \
	clean-dep       \
	install-bin	\
	clean
