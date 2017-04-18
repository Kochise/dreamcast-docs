DirectShow sample program -- Streaming Video
-----------------------------------------

* Purpose:
This sample demonstrates the use of the Multimedia Streaming APIs to display
a DirectShow video stream.  It also shows how to draw text on top of a video
stream.

This sample allows the user to specify a particular video source to play.  The 
source may be specified with a full pathname (ie "\windows\chicken2.mpg"), or
it may be specified with just the filename (ie "chicken2.mpg"), in which case
the sample will look for the file in $(_FLATRELEASEDIR)\<Retail/Debug>\Samples.
The file "Chicken2.mpg" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage: "s StreamingVideo <filename or fullpathname>"  
            example: "s StreamingVideo chicken2.mpg"
            example: "s StreamingVideo \PC\Samples\Chicken2.mpg"

* This sample exits automatically after playing the video.