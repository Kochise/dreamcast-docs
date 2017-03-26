# KallistiOS environment variable settings. These are the shared pieces
# that are generated from the user config. Configure if you like.

# Pull in the arch environ file
. ${KOS_BASE}/environ_${KOS_ARCH}.sh

# Add the gnu wrappers dir to the path
export PATH="${PATH}:${KOS_BASE}/utils/gnu_wrappers"

# Our includes
export KOS_INC_PATHS="${KOS_INC_PATHS} -I${KOS_BASE}/include \
-I${KOS_BASE}/kernel/arch/${KOS_ARCH}/include -I${KOS_BASE}/addons/include"

#export KOS_INC_PATHS_CPP="${KOS_INC_PATHS_CPP} -I${KOS_BASE}/libk++/stlport"

# "System" libraries
export KOS_LIB_PATHS="-L${KOS_BASE}/lib/${KOS_ARCH} -L${KOS_BASE}/addons/lib/${KOS_ARCH}"
export KOS_LIBS="-Wl,--start-group -lkallisti -lc -lgcc -Wl,--end-group"

# Main arch compiler paths
export KOS_CC="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-gcc"
export KOS_CCPLUS="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-g++"
export KOS_AS="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-as"
export KOS_AR="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ar"
export KOS_OBJCOPY="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-objcopy"
export KOS_LD="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ld"
export KOS_RANLIB="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-ranlib"
export KOS_STRIP="${KOS_CC_BASE}/bin/${KOS_CC_PREFIX}-strip"
export KOS_CFLAGS="${KOS_CFLAGS} ${KOS_INC_PATHS} -D_arch_${KOS_ARCH} -D_arch_sub_${KOS_SUBARCH} -Wall -g -fno-builtin -fno-strict-aliasing"
export KOS_CPPFLAGS="${KOS_CPPFLAGS} ${KOS_INC_PATHS_CPP} -fno-operator-names -fno-rtti -fno-exceptions"
#export KOS_AFLAGS="${KOS_AFLAGS}"
export KOS_LDFLAGS="${KOS_LDFLAGS} -nostartfiles -nostdlib ${KOS_LIB_PATHS}"

# Some extra vars based on architecture
export KOS_ARCH_DIR="${KOS_BASE}/kernel/arch/${KOS_ARCH}"
export KOS_START="${KOS_ARCH_DIR}/kernel/startup.o"
