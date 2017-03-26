INCLUDE_DIRECTORIES ( /opt/csw/include /opt/csw/include/freetype2 /usr/include/freetype2 )

AUX_SOURCE_DIRECTORY ( . VGE_SRCS)
ADD_LIBRARY (vge ${VGE_SRCS})

SET_TARGET_PROPERTIES ( vge PROPERTIES COMPILE_FLAGS "${CFLAGS}" )