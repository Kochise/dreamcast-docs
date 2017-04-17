include Makefile.cfg

SUBDIRS = host-src target-src example-src
MAKE	= make

all: subdirs

.PHONY : subdirs $(SUBDIRS)

subdirs: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

target-src: host-src

.PHONY : install
install: 
	$(MAKE) -C host-src/tool install

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

