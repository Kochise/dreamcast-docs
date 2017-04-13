PlgBlt Demonstration


SUMMARY
=======

The PlgBlt function can copy a bit image onto an arbitrary parallelogram.
Applications can use this function to easily rotate or shear bitmaps. The
PLGBLT sample is an easy-to-use demonstration of how this can be done.

MORE INFORMATION
================

The program presents a dialog box that displays the input parameters to the 
PlgBlt function. By choosing the "New Src" or "New Mask" button, the user 
can select a new bitmap for use as the source bitmap or as the monochrome 
mask bitmap. The client area of the window is divided into three regions. 
The region on the left contains the result of the PlgBlt operation. The 
region in the middle provides the source HDC, and the region on the right 
provides the mask bitmap for the PlgBlt operation.

In each of the three regions, there is a "direct manipulation object." This 
object may be picked up and moved by clicking the left mouse button in the 
upper-left corner and dragging. The three objects are restricted in their 
response to user actions to correctly reflect the parameters to the PlgBlt 
function. The object in the mask region may be moved only. The object in the 
source region may be moved or sized. The object in the destination region 
may be moved, sized, sheared, or rotated. Please see the WXFORM sample for 
more information on how this direct manipulation is accomplished. 
