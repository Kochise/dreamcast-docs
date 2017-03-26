#!/bin/bash
# Dreamcast toolchain makefile    by Jim Ursetto
# adapted from Stalin's build script version 0.3
#
# Interesting parameters:
# erase=0|1                   Erase build directories on the fly to save space
# thread_model=posix|single   Set gcc threading model
# verbose=0|1                 Display  
#
# Interesting targets (you can 'make' any of these):
# all: patch build
# patch: patch-gcc patch-newlib patch-kos
# build: build-sh4 build-arm
# build-sh4: build-sh4-binutils build-sh4-gcc
# build-arm: build-arm-binutils build-arm-gcc
# build-sh4-gcc: build-sh4-gcc-pass1 build-sh4-newlib build-sh4-gcc-pass2
# build-arm-gcc: build-arm-gcc-pass1
# build-sh4-newlib: build-sh4-newlib-only fixup-sh4-newlib

# User configuration
sh_target=sh-elf
arm_target=arm-elf
sh_prefix  := /opt/dc/$(sh_target)
arm_prefix := /opt/dc/$(arm_target)
# kos_root: KOS subversion root (contains kos/ and kos-ports/)
kos_root=~/prj/svn
# kos_base: equivalent of KOS_BASE (contains include/ and kernel/)
kos_base=$(kos_root)/kos
binutils_ver=2.15
gcc_ver=3.4.6
newlib_ver=1.12.0
thread_model=posix
erase=0
verbose=0

# Makefile variables
install=$(prefix)/bin
pwd := $(shell pwd)
patches := $(pwd)/patches
logdir := $(pwd)/logs
PATH := $(sh_prefix)/bin:$(arm_prefix)/bin:$(PATH)
binutils_dir=binutils-$(binutils_ver)
gcc_dir=gcc-$(gcc_ver)
newlib_dir=newlib-$(newlib_ver)

all: patch build

# ---- patch {{{
gcc_patches    := $(wildcard $(patches)/gcc-$(gcc_ver)*.diff)
newlib_patches := $(wildcard $(patches)/newlib-$(newlib_ver)*.diff)
kos_patches    := $(wildcard $(patches)/kos-*.diff)

patch_targets=patch-gcc patch-newlib patch-kos

patch: $(patch_targets)
patch-gcc: $(gcc_patches)
patch-newlib: $(newlib_patches) 
patch-kos: $(kos_patches)

$(newlib_patches):
	cd $(newlib_dir); patch -p1 < $@

$(gcc_patches):
	cd $(gcc_dir); patch -p1 < $@

$(kos_patches):
	cd $(kos_root); patch -p1 < $@

# ---- }}}

# ---- build {{{

build: build-sh4 build-arm
build-sh4: build-sh4-binutils build-sh4-gcc
build-arm: build-arm-binutils build-arm-gcc
build-sh4-gcc: build-sh4-gcc-pass1 build-sh4-newlib build-sh4-gcc-pass2
build-arm-gcc: build-arm-gcc-pass1
	$(clean_arm_hack)
build-sh4-newlib: build-sh4-newlib-only fixup-sh4-newlib

# Ensure that, no matter where we enter, prefix and target are set correctly.
build_sh4_targets=build-sh4-binutils build-sh4-gcc build-sh4-gcc-pass1 build-sh4-newlib build-sh4-newlib-only build-sh4-gcc-pass2
build_arm_targets=build-arm-binutils build-arm-gcc build-arm-gcc-pass1
$(build_sh4_targets): prefix = $(sh_prefix)
$(build_sh4_targets): target = $(sh_target)
$(build_arm_targets): extra_configure_args = ""
$(build_arm_targets): prefix = $(arm_prefix)
$(build_arm_targets): target = $(arm_target)
$(build_arm_targets): extra_configure_args = "--with-arch=armv4"

# To avoid code repetition, we use the same commands for both
# architectures.  But we can't create a single target called 
# build-binutils for both sh4 and arm, because phony targets 
# can't be run multiple times.  So we create multiple targets.
build_binutils     = build-sh4-binutils  build-arm-binutils
build_gcc_pass1    = build-sh4-gcc-pass1 build-arm-gcc-pass1
build_newlib       = build-sh4-newlib-only
build_gcc_pass2    = build-sh4-gcc-pass2

# Here we use the essentially same code for multiple targets,
# differing only by the current state of the variables below.
$(build_binutils): build = build-binutils-$(target)-$(binutils_ver)
$(build_binutils): src_dir = binutils-$(binutils_ver)
$(build_binutils): log = $(logdir)/$(build).log
$(build_binutils): logdir
	@echo "+++ Building $(src_dir) to $(build)..."
	-mkdir -p $(build)
	> $(log)
	cd $(build); ../$(src_dir)/configure --target=$(target) --prefix=$(prefix) $(to_log)
	make -C $(build) all install $(to_log)
	$(clean_up)

$(build_gcc_pass1) $(build_gcc_pass2): build = build-gcc-$(target)-$(gcc_ver)
$(build_gcc_pass1) $(build_gcc_pass2): src_dir = gcc-$(gcc_ver)
$(build_gcc_pass1): log = $(logdir)/$(build)-pass1.log
$(build_gcc_pass1): logdir
	@echo "+++ Building $(src_dir) to $(build) (pass 1)..."
	-mkdir -p $(build)
	> $(log)
	cd $(build);  ../$(src_dir)/configure --target=$(target) --prefix=$(prefix) --without-headers --with-newlib --enable-languages=c $(extra_configure_args) $(to_log)
	make -C $(build) all-gcc install-gcc $(to_log)

$(build_newlib): build = build-newlib-$(target)-$(newlib_ver)
$(build_newlib): src_dir = newlib-$(newlib_ver)
$(build_newlib): log = $(logdir)/$(build).log
$(build_newlib): logdir
	@echo "+++ Building $(src_dir) to $(build)..."
	-mkdir -p $(build)
	> $(log)
	cd $(build); ../$(src_dir)/configure --target=$(target) --prefix=$(prefix) $(to_log)
	make -C $(build) all install CC_FOR_TARGET=$(install)/$(target)-gcc AS_FOR_TARGET=$(install)/$(target)-as \
	        LD_FOR_TARGET=$(install)/$(target)-ld AR_FOR_TARGET=$(install)/$(target)-ar \
	        RANLIB_FOR_TARGET=$(install)/$(target)-ranlib $(to_log)
	$(clean_up)

fixup-sh4-newlib: newlib_inc=$(sh_prefix)/$(sh_target)/include
fixup-sh4-newlib:
	@echo "+++ Fixing up sh4 newlib includes..."
	cp $(kos_base)/include/pthread.h $(newlib_inc)                       # KOS pthread.h is modified
	cp $(kos_base)/include/sys/_pthread.h $(newlib_inc)/sys              # to define _POSIX_THREADS
	cp $(kos_base)/include/sys/sched.h $(newlib_inc)/sys                 # pthreads to kthreads mapping
	ln -nsf $(kos_base)/include/kos $(newlib_inc)                        # so KOS includes are available as kos/file.h
	ln -nsf $(kos_base)/kernel/arch/dreamcast/include/arch $(newlib_inc) # kos/thread.h requires arch/arch.h
	ln -nsf $(kos_base)/kernel/arch/dreamcast/include/dc   $(newlib_inc) # arch/arch.h requires dc/video.h

$(build_gcc_pass2): log = $(logdir)/$(build)-pass2.log
$(build_gcc_pass2): logdir
	@echo "+++ Building $(src_dir) to $(build) (pass 2)..."
	-mkdir -p $(build)
	> $(log)
	cd $(build);  ../$(src_dir)/configure --target=$(target) --prefix=$(prefix) --with-newlib \
	   --enable-threads=$(thread_model) --enable-languages=c,c++ $(to_log)
	make -C $(build) all install $(to_log)
	$(clean_up)

# ---- }}}}

# ---- support {{{

clean:
	-rm -rf build-newlib-$(sh_target)-$(newlib_ver)
	-rm -rf build-newlib-$(arm_target)-$(newlib_ver)
	-rm -rf build-gcc-$(sh_target)-$(gcc_ver)
	-rm -rf build-gcc-$(arm_target)-$(gcc_ver)
	-rm -rf build-binutils-$(sh_target)-$(binutils_ver)
	-rm -rf build-binutils-$(arm_target)-$(binutils_ver)

logdir:
	@mkdir -p $(logdir)

# If erase=1, erase build directories on the fly.
ifeq (1,$(erase))
  define clean_up
    @echo "+++ Cleaning up $(build)..."
    -rm -rf $(build)
  endef
  # Hack to clean up ARM gcc pass 1
  define clean_arm_hack
    @echo "+++ Cleaning up build-gcc-$(arm_target)-$(gcc_ver)..."
    -rm -rf build-gcc-$(arm_target)-$(gcc_ver)
  endef
endif

# If verbose=1, display output to screen as well as log files
ifeq (1,$(verbose))
  to_log = 2>&1 | tee -a $(log)
else
  to_log = >> $(log) 2>&1
endif

# ---- }}}

# ---- phony targets {{{

.PHONY: $(patch_targets)
.PHONY: $(newlib_patches) $(gcc_patches) $(kos_patches)
.PHONY: all build patch build-sh4 build-arm $(build_sh4_targets) $(build_arm_targets) clean
.PHONY: build-binutils build-newlib build-gcc-pass1 build-gcc-pass2 fixup-sh4-newlib

# ---- }}}}

# vim:tw=0:fdm=marker:fdc=2:fdl=1
