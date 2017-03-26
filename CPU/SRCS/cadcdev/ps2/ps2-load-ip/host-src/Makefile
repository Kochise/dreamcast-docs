#
# Makefile for ps2-load-ip/host-src
#
# Copyright (c)2001 Andrew Kieschnick
# License: GPL
#

SUBDIRS = tool
MAKE	= make

.PHONY : subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

.PHONY : clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

.PHONY : distclean
distclean:
	for dir in $(SUBDIRS) ; do \
		$(MAKE) -C $$dir distclean; \
	done

