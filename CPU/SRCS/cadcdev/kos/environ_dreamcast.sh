# KallistiOS environment variable settings. These are the shared pieces
# for the Dreamcast(tm) platform.

export KOS_CFLAGS="${KOS_CFLAGS} -ml -m4-single-only -fno-optimize-sibling-calls"
export KOS_AFLAGS="${KOS_AFLAGS} -little"
export KOS_LDFLAGS="${KOS_LDFLAGS} -ml -m4-single-only -Wl,-Ttext=0x8c010000"

# If we're building for DC, we need the ARM compiler paths as well.
if [ x${KOS_ARCH} = xdreamcast ]; then
	export DC_ARM_CC="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-gcc"
	export DC_ARM_AS="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-as"
	export DC_ARM_AR="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-ar"
	export DC_ARM_OBJCOPY="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-objcopy"
	export DC_ARM_LD="${DC_ARM_BASE}/bin/${DC_ARM_PREFIX}-ld"
	export DC_ARM_CFLAGS="-mcpu=arm7 -Wall -O2"
	export DC_ARM_AFLAGS="-mcpu=arm7"
fi
