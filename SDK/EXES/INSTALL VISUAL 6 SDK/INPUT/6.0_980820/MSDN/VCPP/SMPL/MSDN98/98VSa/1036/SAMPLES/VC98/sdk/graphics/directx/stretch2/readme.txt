This is a version of stretch that demonstrates how a windowed DirectDraw
app can/should handle multiple monitors.

files:
    stretch.cpp     - about the same as the original stetch

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

                      used by ddmm.cpp, so stretch can still run on
                      Win95 or NT4
