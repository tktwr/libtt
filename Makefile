include config/makefile.mk

tags: tags.libtt

.PHONY: tags.libtt
tags.libtt:
	ctags -f tags.libtt -R tt

