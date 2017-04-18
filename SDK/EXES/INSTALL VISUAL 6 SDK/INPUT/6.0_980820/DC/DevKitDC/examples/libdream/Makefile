# This will make all the examples, leaving only the elf files.
# If you want to clean everything, use 'clean'.

SUBDIRS = hello
SUBDIRS += 320x240 640x480 800x608 rgb888 ta
SUBDIRS += cdfs
SUBDIRS += spu
SUBDIRS += keyboard mouse lcd vmu
SUBDIRS += ghettoplay

all: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _dir_%, %, $@)

clean: $(patsubst %, _cleandir_%, $(SUBDIRS))

$(patsubst %, _cleandir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _cleandir_%, %, $@) clean

dist: $(patsubst %, _distdir_%, $(SUBDIRS))

$(patsubst %, _distdir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _distdir_%, %, $@) dist

