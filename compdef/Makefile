#
#    Makefile for yasuna
#

install-zsh-compdef: _yasuna.zsh
	install -pd $(PREFIX)/share/$(TARGET)/zsh
	install -pm 644 $< $(PREFIX)/share/$(TARGET)/zsh

.PHONY: install-zsh-compdef
