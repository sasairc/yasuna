#
#    Makefile for yasuna
#

install-man:
	$(MAKE)	-C ./man	$@

install-doc: LICENSE cli_spec.md dictionary_spec.md
	install -pd $(DOCDIR)/polyaness
	install -pm 644 LICENSE $(DOCDIR)/polyaness
	install -pm 644 *.md $(DOCDIR)/polyaness
