# KallistiOS environment variable settings. These are the shared pieces
# for the PS2(tm) platform.

#export KOS_CFLAGS="${KOS_CFLAGS}"
export KOS_AFLAGS="${KOS_AFLAGS} -Wa,-EL -Wa,-mips3 -Wa,-mcpu=r5900 -I${KOS_BASE}/kernel/arch/${KOS_ARCH}/include -c"
export KOS_LDFLAGS="${KOS_LDFLAGS} -Wl,-T${KOS_BASE}/kernel/arch/${KOS_ARCH}/link-${KOS_SUBARCH}.ld"
