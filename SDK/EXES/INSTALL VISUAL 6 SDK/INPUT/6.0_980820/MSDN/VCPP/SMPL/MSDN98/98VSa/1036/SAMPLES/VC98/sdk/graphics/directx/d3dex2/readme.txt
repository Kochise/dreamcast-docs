this is a version of d3dex1 that demonstrates how a windowed direct draw
app can/should handle multiple monitors. 

files:
    d3dex2.cpp      - about the same as the original d3dex1

                      look at how this app uses the routines
                      in ddmm.cpp

                      look at how this app handles WM_MOVE to
                      detect when the window moves monitors.

                      look at how it converts from a window
                      client cordinate to a device cordinate

    ddmm.cpp        - generic directdraw multimonitor helper routines.

                      DirectDrawCreateFromDevice
                      DirectDrawCreateFromWindow
                      DirectDrawDeviceFromWindow

    multimon.h      - stub multimon functions that use GetProcAddress
                      used by ddmm.cpp, so it can still run on
                      Win95 or NT4
