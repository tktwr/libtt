include config/makefile.mk

.PHONY: tags.libtt
tags.libtt:
	ctags -f tags.libtt -R tt

