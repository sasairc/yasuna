#
#    Makefile for yasuna
#

install-man: yasuna.6
	install -pd $(MANDIR)
	install -pm 644 $< $(MANDIR)/

install-doc:
	@$(MAKE) -C ./polyaness	$@

.PHONY: install-man	\
	install-doc
