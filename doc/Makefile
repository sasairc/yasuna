#
#    Makefile for yasuna
#

install-man: $(TARGET).6
ifeq ($(LANG),ja_JP.UTF-8)
	install -pd $(MANDIR)/man6
	install -pm 644 $< $(MANDIR)/man6/
	@$(MAKE) -C ./polyaness	$@
endif

install-doc:
	@$(MAKE) -C ./polyaness	$@

.PHONY: install-man	\
	install-doc
