# KallistiOS environment variable settings. These are the shared pieces
# for the GBA(tm) platform.

# This is currently configured to produce only Thumb code
export KOS_CFLAGS="${KOS_CFLAGS} -mcpu=arm7tdmi -mthumb -ffreestanding"
export KOS_AFLAGS="${KOS_AFLAGS} -marm7tdmi"
export KOS_LDFLAGS="${KOS_LDFLAGS} -Wl,-Ttext=0x08000000,-Tdata=0x02000000,-T,$KOS_BASE/kernel/arch/gba/gba.ld.script"
