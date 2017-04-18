Notes for the Middleware V2.30 libraries
========================================

The new Middleware libraries as distributed with this SDK support both
Manatee and Audio64 as sound output options.  For Audio64, both the AC layer
and the AM layer are supported.

Depending on the audio renderer that you choose to use, you will require a
different libraries and source files.

For Audio64 AC layer, you will require the following:
Source files:	bpacsetup.c

Libraries:	sofdec
		sg_mwk2a
		audio64

For the Audio64 AM layer (the default), you will require the following:
Source files:	bpacsetup.c
		bpamsetup.c

Libraries:	sofdec
		sg_mwk2a
		audio64

To use Manatee for sound output, you will not require either bpacsetup.c or
bpamsetup.c.  However, you will have to change the libraries, so now you will
require:

Libraries:	sofdec
		sg_mwk2
		sg_sd

These are the samples and what they do:

ADXGDPLY	This sample plays an ADX stream from the GD-ROM
ADXMEM		Plays an ADX stream from memory
ADXMLT		Plays multiple ADX streams simultaneously
ADXSLPLY	Seamless ADX streaming from the GD-ROM
MW_MPA		Plays an MPEG Level 1.0 (layer 1 or 2) audio file from the
		GD-ROM
MW_WAV		Plays a Wave file from the GD-ROM
SFDGDPLY	Plays an SFD (MPEG Sofdec encoded) movie file from the GD-ROM
SFDMLT		Plays multiple (four) SFD files in seperate areas of the screen
		from the GD-ROM
SFDSLPLY	Seamless SFD playing from the GD-ROM
SFDTEX		Plays an SFD file from the GD-ROM onto a Kamui2 surface
SFDVFX		Shows how to use the Sofdec library for special effects

Joe Votour
Sega of America Dreamcast DTS
March 27, 2000

