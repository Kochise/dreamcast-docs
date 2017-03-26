# KallistiOS ##version##
#
# SDL Makefile
# Lawrence Sebald
#
# Based on:
# addons/libjpeg Makefile
# (c)2001 Dan Potter
# and
# Makefile.dc found in SDL-1.2.5 by BERO
#

# This controls GL support, uncomment for GL support using BERO's libgl (not KGL)
#GL=1

KOS_LOCAL_CFLAGS = -I$(KOS_ADDONS_BASE)/include/SDL -Isrc -Isrc/audio -Isrc/cdrom -Isrc/endian
KOS_LOCAL_CFLAGS += -Isrc/events -Isrc/joystick -Isrc/thread/dc -Isrc/thread -Isrc/timer
KOS_LOCAL_CFLAGS += -Isrc/video -DNO_SIGNAL_H -DENABLE_DC

ifdef GL
KOS_LOCAL_CFLAGS += -DHAVE_OPENGL
endif

OBJS = \
	src/audio/dc/SDL_dcaudio.o \
	src/audio/dc/aica.o \
	src/audio/SDL_audio.o \
	src/audio/SDL_audiocvt.o \
	src/audio/SDL_audiodev.o \
	src/audio/SDL_audiomem.o \
	src/audio/SDL_mixer.o \
	src/audio/SDL_wave.o \
	src/cdrom/dc/SDL_syscdrom.o \
	src/cdrom/SDL_cdrom.o \
	src/endian/SDL_endian.o \
	src/events/SDL_active.o \
	src/events/SDL_events.o \
	src/events/SDL_expose.o \
	src/events/SDL_keyboard.o \
	src/events/SDL_mouse.o \
	src/events/SDL_quit.o \
	src/events/SDL_resize.o \
	src/file/SDL_rwops.o \
	src/joystick/dc/SDL_sysjoystick.o \
	src/joystick/SDL_joystick.o \
	src/SDL.o \
	src/SDL_error.o \
	src/SDL_fatal.o \
	src/SDL_getenv.o \
	src/SDL_loadso.o \
	src/thread/dc/SDL_syscond.o \
	src/thread/dc/SDL_sysmutex.o \
	src/thread/dc/SDL_syssem.o \
	src/thread/dc/SDL_systhread.o \
	src/thread/SDL_thread.o \
	src/timer/dc/SDL_systimer.o \
	src/timer/SDL_timer.o \
	src/video/dc/SDL_dcevents.o \
	src/video/dc/SDL_dcvideo.o \
	src/video/SDL_blit.o \
	src/video/SDL_blit_0.o \
	src/video/SDL_blit_1.o \
	src/video/SDL_blit_A.o \
	src/video/SDL_blit_N.o \
	src/video/SDL_bmp.o \
	src/video/SDL_cursor.o \
	src/video/SDL_gamma.o \
	src/video/SDL_pixels.o \
	src/video/SDL_RLEaccel.o \
	src/video/SDL_stretch.o \
	src/video/SDL_surface.o \
	src/video/SDL_video.o \
	src/video/SDL_yuv.o \
	src/video/SDL_yuv_sw.o


myall: $(OBJS)
	rm -f $(KOS_ADDONS_BASE)/lib/libSDL.a
	$(KOS_AR) rcs $(KOS_ADDONS_BASE)/lib/libSDL.a $(OBJS)

include $(KOS_BASE)/Makefile.prefab


