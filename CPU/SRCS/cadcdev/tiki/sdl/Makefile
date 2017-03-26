
BASE_AUDIO_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/audio/*.cpp))
BASE_AUDIO_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/audio/oggvorbis/*.cpp))
BASE_BASE_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/base/*.cpp))
BASE_GL_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/anims/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/drawables/*.cpp))
BASE_GL_OBJ+=$(patsubst %.cpp,%.o,$(wildcard ../src/gl/triggers/*.cpp))
BASE_HID_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/hid/*.cpp))
BASE_IMAGE_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/image/*.cpp))
BASE_MATH_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/math/*.cpp))
BASE_THREAD_OBJ=$(patsubst %.cpp,%.o,$(wildcard ../src/thread/*.cpp))

JPEG_OBJ=$(patsubst %.c,%.o,$(wildcard ../3rdparty/libjpeg/*.c))
PNG_OBJ=$(patsubst %.c,%.o,$(wildcard ../3rdparty/libpng/*.c))
ZLIB_OBJ=$(patsubst %.c,%.o,$(wildcard ../3rdparty/zlib/*.c))
OGG_OBJ=$(patsubst %.c,%.o,$(wildcard ../3rdparty/libogg/src/*.c))
VORBIS_OBJ=../3rdparty/libvorbis/lib/analysis.o \
	../3rdparty/libvorbis/lib/bitrate.o \
	../3rdparty/libvorbis/lib/block.o \
	../3rdparty/libvorbis/lib/codebook.o \
	../3rdparty/libvorbis/lib/envelope.o \
	../3rdparty/libvorbis/lib/floor0.o \
	../3rdparty/libvorbis/lib/floor1.o \
	../3rdparty/libvorbis/lib/info.o \
	../3rdparty/libvorbis/lib/lookup.o \
	../3rdparty/libvorbis/lib/lpc.o \
	../3rdparty/libvorbis/lib/lsp.o \
	../3rdparty/libvorbis/lib/mapping0.o \
	../3rdparty/libvorbis/lib/mdct.o \
	../3rdparty/libvorbis/lib/psy.o \
	../3rdparty/libvorbis/lib/registry.o \
	../3rdparty/libvorbis/lib/res0.o \
	../3rdparty/libvorbis/lib/sharedbook.o \
	../3rdparty/libvorbis/lib/smallft.o \
	../3rdparty/libvorbis/lib/synthesis.o \
	../3rdparty/libvorbis/lib/vorbisfile.o \
	../3rdparty/libvorbis/lib/window.o

BASE_OBJS = $(BASE_AUDIO_OBJ) $(BASE_BASE_OBJ) $(BASE_GL_OBJ) \
	$(BASE_HID_OBJ) $(BASE_IMAGE_OBJ) $(BASE_MATH_OBJ) \
	$(BASE_THREAD_OBJ)
	
THIRD_PARTY_OBJS = $(JPEG_OBJ) $(OGG_OBJ) $(VORBIS_OBJ) $(PNG_OBJ) $(ZLIB_OBJ)

CFLAGS=-I../include -I$(CURDIR)/include -g
CFLAGS+=-I../3rdparty/libogg/include -I../3rdparty/libvorbis/include -I../3rdparty/libvorbis/lib

SUBDIRS=src

all: subdirs $(BASE_OBJS) $(THIRD_PARTY_OBJS)
	$(AR) ru libtiki.a $(BASE_OBJS) $(THIRD_PARTY_OBJS)

clean: clean_subdirs
	-rm -f $(BASE_OBJS) libtiki.a

include Makefile.rules
