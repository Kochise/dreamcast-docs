IconPro Icon Manager


SUMMARY
=======

The IconPro sample is designed to manipulate icons having images with bit
depths from 1bpp to 32bpp, as well as sizes from 16x16 to 128x128.

IconPro provides no editing capabilities. To create an icon, the user must
first edit the image in DIB format, using a program like PBRUSH. Then the
image can be imported into IconPro without loss of bit depth.

Note that IconPro restricts the size of its child windows, so MDI tiling
can look different than expected.

When extracting icons from DLL and EXE files, IconPro will operate only on
32bit files.

MORE INFORMATION
================

Usage
-----

IconPro displays icons in MDI child windows, showing you one image at a 
time. Since an icon may contain more than one image, a list box is provided 
below the display area to choose which image to look at.

IconPro is capable of reading and writing ICO files, as well as extracting
icons from Win32 PE format DLLs and EXEs. It can also import from/export
to BMP files and copy/paste with the clipboard. 

Holding the Control key and left-clicking on the XOR mask will make the
program calculate new masks, using the pixel color at the mouse location as
the transparent color. 

File Menu
---------

New Icon: Creates a new icon resource and a window in which to display it.
    The newly created icon resource has no images in it. New images would
    need to be created using the Add Format command in the Edit menu.
Open Icon File: Opens an ICO file and creates a new window in which to 
    display its images. The images stored in the ICO file are enumerated in 
    the listbox at the bottom of the display window.
Extract From DLL/EXE: Extracts an icon resource from a 32bit DLL or EXE 
    file. It will fail on 16bit files. If the file contains more than one 
    icon resource, a dialog box is shown allowing the choice of which icon 
    resource to extract.
Close: Closes the current icon resource child window. If the image has been
    modified, a dialog box will be shown asking whether to save changes.
Save ICO File: Saves the current icon resource to its ICO file.
Save As ICO File: Saves the current icon resource to a newly named ICO file.
Exit: Terminates IconPro.

Edit Menu
---------

Copy: Causes the XOR mask of the current icon resource's current image to be
    placed on the clipboard in CF_DIB format.
Paste: Takes the CF_DIB format image from the clipboard and uses it to
    replace the XOR mask of the current icon resource's current image. If
    the clipboard image is larger than the current icon image, only the 
    corner of the image is used. If the clipboard image is smaller than the 
    current icon image, some of the resultant icon image may be black or 
   undefined.
Stretch Paste: Takes the CF_DIB format image from the clipboard and uses it
    to replace the XOR mask of the current icon resource's current image,
    stretching it to fit the dimensions of the icon image.
Import BMP: Reads a BMP file and uses it to replace the XOR mask of the
    current icon resource's current image. If the BMP bitmap is larger than
    the current icon image, only the corner of the image is used. If the BMP
    bitmap is smaller than the current icon image, some of the resultant 
    icon image may be black or undefined.
Stretch Import BMP: Reads a BMP file and uses it to replace the XOR mask of 
    the current icon resource's current image, stretching it to fit the 
    dimensions of the icon image.
Export BMP: Causes the XOR mask of the current icon resource's current
    image to be written to a newly named BMP file.
Add Format: Launches a dialog box that allows the creation of a new icon 
    image in the current icon resource. Slider controls are provided to 
    allow the Width, Height, and Color Depth to be chosen. Valid ranges for 
    these values are:
        Width: Min 16, Max 128
        Height: Min 16, Max 128
        Color Depth: Min 1bpp, Max 32bpp
    Two images with identical Width, Height and Color Depth are not allowed
    in the same icon resource.
Remove Format: Removes the current icon image from the current icon 
    resource.

Window Menu
-----------

Arrange Icons: Arranges the MDI child icons.
Cascade: Arranges the MDI child windows in a cascade effect.
Tile Horizontal: Horizontally tiles the MDI child windows.
Tile Vertical: Vertically tiles the MDI child windows.
Contents: Launches help for IconPro.
About: Displays the About box.

Icons
-----

Icon images are stored in ICO files and as resources in EXEs and DLLs in 
near DIB format - a BITMAPINFO followed by XOR bits followed by AND bits. A 
block of memory like this can be passed to CreateIconFromResourceEx to 
create a HICON from the resource. This API expects the bmiHeader.biHeight 
member of the BITMAPINFO to be the sum of the heights of the XOR and AND 
masks. Further, this API is not implemented on NT at this time, so 
CreateIconFromResource must be used instead.

When creating the AND mask for an icon (or any transparent BitBlt), a simple
method is to BitBlt from the source image to a mono bitmap and let GDI do 
the conversions based on SetBkColor. This will not work with DIBSections. 
Any BitBlt'ing with DIBSections results in color mapping without regard to 
the background color.

DIBSections can not be used in the ICONINFO structure passed to
CreateIconIndirect. DDBs must be used there.

Currently, during the icon selection process in Windows 95, all bit 
depths >= 8 are treated as equal. Therefore, it is pointless to have both
a 24bpp and an 8bpp image in the same ICO file. When running in any video
mode of at least 8bpp, Windows will simply choose the first one. Further,
in 8bpp mode, icons are always displayed using the system palette.

ICO File Format
---------------

Icons are normally stored in ICO files. The ICO file format is documented in
the Windows 3.1 SDK Programmer's Reference, Volume 4: Resources, Chapter 1: 
Graphics File Formats.

The ICO file starts with an ICONDIR structure. The ICONDIR structure is 
defined as:

typedef struct 
{
    WORD           idReserved;   // Reserved
    WORD           idType;       // resource type (1 for icons)
    WORD           idCount;      // how many images?
    ICONDIRENTRY   idEntries[1]; // entries for each image (idCount of 'em)
} ICONDIR, *LPICONDIR;


The ICONDIRENTRY structure is defined as:

typedef struct
{
    BYTE        bWidth;          // Width of the image
    BYTE        bHeight;         // Height of the image (times 2)
    BYTE        bColorCount;     // Number of colors in image (0 if >=8bpp)
    BYTE        bReserved;       // Reserved
    WORD        wPlanes;         // Color Planes
    WORD        wBitCount;       // Bits per pixel
    DWORD       dwBytesInRes;    // how many bytes in this resource?
    DWORD       dwImageOffset;   // where in the file is this image
} ICONDIRENTRY, *LPICONDIRENTRY;


So, the file consists of the header followed by the bits for each image. The
bits for each image can be located by seeking to dwImageOffset in the file. 
The format of the bits follows:

  The bits for each image are stored in something similar to CF_DIB format. 
  First is a BITMAPINFO structure, followed by the DIB bits of the XOR mask,
  followed by the DIB bits of the AND mask. 

  Note the following two caveats:
  1) The bmiHeader.biHeight member of the BITMAPINFO structure indicates
     the height of the XOR mask plus the height of the AND mask.
  2) The AND mask is monochrome, and has no BITMAPINFO.
 
Notes
-----

IconPro is an MDI application. Each child window stores a pointer to a
structure in its GWL_USERDATA location. This structure contains information
such as the handle to the listbox, the locations of various graphical 
elements in the client area, and a pointer to the icon resource data.

The icon resource data is stored in a structure that contains normal
information like the number of images and info for each of those images. The
info for each image includes its width/height/bpp as well as the DIB format
memory blocks for the XOR and AND masks.

In the MDI child window, the icon is displayed using DrawIconEx() once over 
a black background and once over a white background. The XOR and AND masks 
are also displayed using standard DIB functions.

Holding the 'Control' key and left-clicking on the XOR mask will make the
program calculate new masks, using the pixel color at the mouse location as
the transparent color. This is implemented using the following slow, but 
effective method:

    Loop through all the pixels in the source
    If a given pixel matches the transparent color (use GetPixel)
	then clear the bit in the XOR mask and set the bit in the AND mask
    else
        clear the bit in the AND mask
