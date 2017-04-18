Readme for D3DEx1 Sample
========================

This sample displays a spinning triangle in a window.
It uses Direct3D Immediate mode and execute buffers.

This application is a good place to look for a good way to determine
what Direct3D device to use.

Further pointers:
The D3dEx2 sample application shows how just a few changes are needed to
work well on a multi-monitor system.


3/5/97 Known limitations:

On MMX machines, RGB is faster than RAMP. Currently it chooses RAMP.

Resizing of the window is not supported. (Because of the varying amounts
of video-card memory, a resize may force the application to have to stop
using the h/w and resort to emulation.)



