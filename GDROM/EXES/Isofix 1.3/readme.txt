
ISO LBA fix utility 1.3 (C) 2001 by DeXT


What's new in 1.3:
  ISOfix now extracts ISO header, too (the same as ISOextract)
  Destination ISO image is now named "fixed.iso" by default
  Added "/header" option for header-only extraction (no boot, no fixing)
  Writing padding data is now 50% faster
  Support for new image formats (2056 (Mac), 2336, 2352 b/s)
  New "/mac" and "/iso" options to force destination image format

What's new in 1.2a:
  Fixed stupid bug in progress counter which made it go weird

What's new in 1.2:
  New "/boot" option which just extracts boot area from ISO image and exit

What's new in 1.1:
  Boot file renamed to "bootfile.bin"
  All fields are optional now so you can simply double-clic program's icon
  and it will ask you for required info


Usage: ISOfix image.iso [dest.iso] [LBA] [/options]

image.iso  is source image to fix
dest.iso   is destination image file name (default: "tmp.iso")
LBA        is known start LBA value for that ISO image

/boot      if present it will only extract boot area from image.iso and exit
/header    if present it will only extract ISO header and exit

/mac       will write ISO image in Mac/2056 format (auto if source ISO = 2056)
/iso       will force standard ISO/2048 format for output (only for Mac users)

All of these parameters are optional.


Examples:

isofix image.iso          (will ask for LBA)

isofix image.iso 11700

isofix image.iso my-fixed-image.iso 345678

isofix image.iso /boot    (will only extract boot area to "bootfile.bin")

isofix image.iso /header  (will only extract header to "header.iso")

isofix image.iso /boot /header (will extract boot and header, but won't fix)


You can also simply double-clic on isofix.exe icon and it will ask for both
source image filename and starting LBA for that image.


This utility will fix a given ISO image with a known starting LBA value so
resulting image dest.iso will have starting LBA = 0. This would let ISObuster
and other ISO managing tools to extract the contents of that image.

This is intended for multisession ISO tracks whose contents cannot be
extracted if not burned at right position on a real CD.

If you do not enter any LBA value in the command line the program will ask you
for one. Please note that you MUST enter a valid LBA value for that image,
otherwise resulting image will likely be wrong!

A right starting LBA value can be retrieved from original CDI image when using
CDIrip (look at LBA value for that data track) or from CD itself if it's
already burned (see start sector of data track).

If no name is given for destination image, resulting image will be saved as
"fixed.iso". Note that fixed image is not intended for re-burn directly as
multisession track but for file extraction only! You can, however, burn it
at sector 0 in a real CD, although this probably won't have much sense unless
you know what you are doing.

Also be aware this will only work properly with CD-Extra ISO tracks and not
for real Multisession data tracks with cross references to previous session
(files with starting LBA value below image LBA will be empty).

What this program does is adding padding information at start of image up to
the given LBA value, and also copies original PVD, SVD and VDT found to the
right positions. This will ensure Joliet extensions will be kept, too.

While extracting, if boot area isn't empty it will also copy it into a
"bootfile.bin" file. If "/boot" option is specified in the command line, then
the program will just extract boot area and exit.

From 1.3 version, ISO header will also be automatically extracted to file
"header.iso" (i.e. the same functionality as ISOextract). This can be useful
when converting a CD-Extra type image to simple Multisession one. If "/header"
option is added to the command line, it will only extract header and exit
without fixing ISO image first.

By default, the program will always save fixed ISO image in standard ISO/2048
format, no matter the source one. An exception is made with Mac-ISO/2056
images where format is maintained in destination file (as needed by Mac
users). If you want to force ISO/2048 conversion for these images use "/iso"
option. On the other hand, if you are a Mac user and want to produce a
Mac-2056 ISO image no matter the source format add "/mac" option.

To extract contents with ISObuster, you should select "Creator Image (*.ISO)"
as file type when loading the fixed ISO since the "Standard ISO Image" type
doesn't seem to work right (perhaps a bug in ISObuster?).


This program is based on a smart idea from ciccioriccio. Thanks man!

DeXT

