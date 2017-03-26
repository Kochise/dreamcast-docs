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

