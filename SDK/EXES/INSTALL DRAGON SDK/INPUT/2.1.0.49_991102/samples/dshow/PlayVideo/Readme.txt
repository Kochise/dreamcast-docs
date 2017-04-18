DirectShow sample program -- PlayVideo
-----------------------------------------

* Purpose:
This sample is a trivial movie player console application.  
It uses DirectShow to stream any media file (MPEG, AVI or WAV). The
media file is streamed directly to the display; the sample does not
use a WndProc either.  To see how to do either of those, refer to the
"StreamingVideo" sample which has both of those in it.

This sample allows the user to specify a particular video source to play.  The 
source may be specified with a full pathname (ie "\windows\chicken2.mpg"), or
it may be specified with just the filename (ie "chicken2.mpg"), in which case
the sample will look for the file in $(_FLATRELEASEDIR)\<Retail/Debug>\Samples.
The file "Chicken2.mpg" is automatically installed there for test purposes.

* Required Files\Parameters:
Usage: "s PlayVideo <filename or fullpathname>"  
            example: "s PlayVideo chicken2.mpg"
            example: "s PlayVideo \PC\Samples\Chicken2.mpg"

* This sample exits automatically after playing the media.  This sample ignores
user input, and as such cannot be prematurely exited via the 'Send ESC' button
on DCTool.  Refer to the code for information on how to handle input in your app.