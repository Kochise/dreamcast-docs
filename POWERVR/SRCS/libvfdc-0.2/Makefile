######################################################################
#                       Video for DreamCast  V 0.2                   #
######################################################################
# including :														 #
#			libmpg2 v0.5 Beta										 #
#			libfli  v0.5 Beta										 #
#																	 #
######################################################################
#																	 #
#									 Makefile (c)2002 from La Cible  #
######################################################################


LIBMPG2:= libmpg.a 
LIBFLI:= libfli.a
LIBPATH := ./lib

MPG2_OBJS = \
	./mpeg2/alloc.o \
	./mpeg2/cpu_accel.o \
	./mpeg2/cpu_state.o \
	./mpeg2/decode.o \
	./mpeg2/header.o \
	./mpeg2/idct.o \
	./mpeg2/motion_comp.o \
	./mpeg2/slice.o \
	./mpeg2/video_out.o \
	./mpeg2/mpgplayer.o \
	./mpeg2/video_out_dc.o \
	./mpeg2/yuv2rgb.o \
	./mpeg2/libads/ads_dc.o

FLI_OBJS = \
	./Fli/fli.o


KOS_CFLAGS += -I./include -I./mpeg2 -O2

all: fli mpg sample

fli: $(FLI_OBJS)
	@rm -f $(LIBPATH)/$(LIBFLI)
	$(KOS_AR) rcs $(LIBPATH)/$(LIBFLI) $(FLI_OBJS)

mpg: $(MPG2_OBJS)
	@rm -f $(LIBPATH)/$(LIBMPG2)
	$(KOS_AR) rcs $(LIBPATH)/$(LIBMPG2) $(MPG2_OBJS)

sample:
	$(KOS_MAKE) -C examples/PSS
	$(KOS_MAKE) -C examples/PAL
	$(KOS_MAKE) -C examples/mpeg

clean:
	@rm -f $(MPG2_OBJS) $(FLI_OBJS) $(LIBPATH)/$(LIBFLI) $(LIBPATH)/$(LIBMPG2)
	$(KOS_MAKE) -C examples/PSS clean
	$(KOS_MAKE) -C examples/PAL clean
	$(KOS_MAKE) -C examples/mpeg clean


include $(KOS_BASE)/Makefile.rules


