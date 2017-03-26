SUBDIRS := libbz2 libconio libdcplib libgl libimageload libjpeg libkmg libkosh \
	libmodplug libmp3 liboggvorbis libparallax libpcx libpng libs3m libtga \
	libtremor libtsunami lua lwip zlib SDL

all: $(patsubst %, _dir_%, $(SUBDIRS))

$(patsubst %, _dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _dir_%, %, $@)

clean: $(patsubst %, _clean_dir_%, $(SUBDIRS))

$(patsubst %, _clean_dir_%, $(SUBDIRS)):
	$(MAKE) -C $(patsubst _clean_dir_%, %, $@) clean

