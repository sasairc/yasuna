#
#    Makefile for yasuna
#

include ../config.mk

ifndef DICNME
DICNME	= yasuna-quotes
endif

install-quotes: $(DICNME)
	install -pd $(DICDIR)
	install -pm 644 $< $(DICDIR)/

.PHONY: install-quotes
