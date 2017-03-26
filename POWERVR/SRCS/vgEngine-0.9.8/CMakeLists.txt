
PROJECT (vgengine)

#if you don't want the full compiler output, remove the following line
#SET(CMAKE_VERBOSE_MAKEFILE ON)

#add definitions, compiler switches, etc.
ADD_DEFINITIONS (-O2 -g)

INCLUDE_DIRECTORIES ( vge )
INCLUDE_DIRECTORIES ( x11 )


ADD_SUBDIRECTORY (vge)
ADD_SUBDIRECTORY (x11)
#ADD_SUBDIRECTORY (dmu)

#list all source files here

ADD_EXECUTABLE (vge_test src/vgengine_test.cpp)
TARGET_LINK_LIBRARIES(vge_test vge vgx11 X11 freetype)

ADD_EXECUTABLE (example1 examples/example1.cpp)
TARGET_LINK_LIBRARIES(example1 vge vgx11 X11 freetype)

ADD_EXECUTABLE (example2 examples/example2.cpp examples/tiger.c)
TARGET_LINK_LIBRARIES(example2 vge vgx11 X11 freetype)

ADD_EXECUTABLE (example3 examples/example3.cpp)
TARGET_LINK_LIBRARIES(example3 vge vgx11 X11 freetype)
 
ADD_EXECUTABLE (example4 examples/example4.cpp examples/agg_platform_support.cpp)
TARGET_LINK_LIBRARIES(example4 vge vgx11 X11 freetype)
 
#ADD_EXECUTABLE (example5 examples/example5.cpp)
#TARGET_LINK_LIBRARIES(example5 vge vgx11 X11 freetype dmu)
 
