DirectShow sample program -- StreamToTexture
-----------------------------------------

* Purpose:
This sample demonstrates how to use DirectShow to render a multimedia stream
onto a texture in Direct3D Immediate-Mode.  A pair of 3D polygons is then drawn
using this texture.

This sample allows the user to specify a particular video source to play.  The 
source may be specified with a full pathname (ie "\windows\chicken2.mpg"), or
it may be specified with just the filename (ie "chicken2.mpg"), in which case
the sample will look for the file in $(_FLATRELEASEDIR)\<Retail/Debug>\Samples.
The file "Chicken2.mpg" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage: "s StreamToTexture <filename or fullpathname>"  
            example: "s StreamToTexture chicken2.mpg"
            example: "s StreamToTexture \PC\Samples\Chicken2.mpg"

* This sample exits automatically after playing the segment.