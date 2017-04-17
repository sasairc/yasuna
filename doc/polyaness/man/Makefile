#
#    Makefile for yasuna
#

install-man: polyaness_dict.5
ifeq ($(LANG),ja_JP.UTF-8)
	install -pd $(MANDIR)/man5
	install -pm 644 $< $(MANDIR)/man5/
endif

.PHONY: install-man
