SUBDIRS = 1st_read dcload
MAKE	= make

.PHONY : subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

1st_read: dcload

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

