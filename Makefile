#
#    Makefile for yasuna
#

TARGET    = yasuna
DICNME    = yasuna-quotes
# DICNME = yasuna-quotes-lite
PREFIX    := /usr/local
BINDIR    := $(PREFIX)/bin
DICDIR    := $(PREFIX)/share/$(TARGET)
MANDIR    := $(PREFIX)/share/man/ja
DOCDIR    := $(PREFIX)/share/doc/$(TARGET)
MAKE      := make
CC        := cc
RM        := rm
CFLAGS    := -O2 -g -Wall
LDFLAGS   :=
CMDLINE   := 0
BUFLEN    := 4096
TH_LINES  := 1024
TH_LENGTH := 640
export

all clean build-dep clean-dep install-bin:
	@$(MAKE) -C ./src	$@

install-quotes:
	@$(MAKE) -C ./quotes	$@
	
install-man:
	@$(MAKE) -C ./doc	$@

install-doc:
	@$(MAKE) -C ./doc	$@
	
install-zsh-compdef: 
	@$(MAKE) -C ./compdef	$@

install: install-bin		\
	 install-quotes		\
	 install-man		\
	 install-doc		\
	 install-zsh-compdef

.PHONY:	all			\
        build-dep		\
	clean-dep		\
	install			\
	install-bin		\
	install-quotes		\
	install-man		\
	install-doc		\
	install-zsh-compdef	\
	clean
