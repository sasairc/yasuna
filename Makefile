#
#    Makefile for yasuna
#

TARGET	= yasuna
PREFIX	:= /usr/local
BINDIR	:= $(PREFIX)/bin
DICDIR	:= $(PREFIX)/share/$(TARGET)
MANDIR	:= $(PREFIX)/share/man/ja
DOCDIR	:= $(PREFIX)/share/doc/$(TARGET)
MAKE	:= make
CC	:= cc
RM	:= rm
CFLAGS	:= -Wall -O2 -g
LDFLAGS	:=
CMDLINE	:= 0
export

all clean build-dep clean-dep install-dep install-bin:
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
	install-dep		\
	install-bin		\
	install-quotes		\
	install-man		\
	install-doc		\
	install-zsh-compdef	\
	clean
