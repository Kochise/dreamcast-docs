BASE_AUDIO_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/audio/oggvorbis/*.cpp))
BASE_BASE_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/base/*.cpp))
BASE_GL_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/anims/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/drawables/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/triggers/*.cpp))
BASE_HID_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/hid/*.cpp))
BASE_IMAGE_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/image/*.cpp))
BASE_MATH_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/math/*.cpp))
BASE_THREAD_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/thread/*.cpp))

BASE_OBJS = $(BASE_AUDIO_OBJ) $(BASE_BASE_OBJ) $(BASE_GL_OBJ) \
	$(BASE_HID_OBJ) $(BASE_IMAGE_OBJ) $(BASE_MATH_OBJ) \
	$(BASE_THREAD_OBJ)

KOS_CFLAGS +=-I../3rdparty/kglx -I../include -I$(CURDIR)/include

SUBDIRS=src

all: subdirs $(BASE_OBJS)
	$(KOS_AR) ru libtiki.a $(BASE_OBJS)

clean: clean_subdirs
	-rm -f $(BASE_OBJS) libtiki.a

include Makefile.rules
