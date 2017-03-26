# KallistiOS environment variable settings. These are the shared pieces
# for the ia32/i386 platform.

#export KOS_CFLAGS="${KOS_CFLAGS}"
#export KOS_AFLAGS="${KOS_AFLAGS}"
export KOS_LDFLAGS="${KOS_LDFLAGS} -Wl,-Ttext=0x00010000"
