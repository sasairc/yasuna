#
#    Makefile for yasuna
#

SRCS	= $(wildcard *.c)
OBJS	= $(SRCS:.c=.o)
ARCH	= $(shell gcc -print-multiarch)

DEFCFLAGS = -DPREFIX=\"$(PREFIX)\"       \
		-DDICNAME=\"$(DICNME)\"  \
		-DDICPATH=\"$(DICDIR)/\" \
		-DARCH=\"$(ARCH)\"

all: $(TARGET) $(OBJS)

$(TARGET): $(OBJS)
ifeq ($(CMDLINE), 0)
	@echo "  BUILD   $@"
	@$(CC) $(LDFLAGS) $^ -o $@
else
	$(CC) $(LDFLAGS) $^ -o $@
endif

%.o: %.c %.h
ifeq ($(CMDLINE), 0)
	@echo "  CC      $@"
	@$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
else
	$(CC) $(DEFCFLAGS) $(CFLAGS) -c $< -o $@
endif

install-bin: $(TARGET)
	install -pd $(BINDIR)
	install -pm 755 $< $(BINDIR)/

clean:
	-$(RM) -f $(OBJS)
	-$(RM) -f $(TARGET)

.PHONY: all		\
	install-bin	\
	clean