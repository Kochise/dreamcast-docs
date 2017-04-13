Rockem 3D Sample Game
---------------------

This game demonstrates many of the features of Direct X, including DirectDraw,
Direct 3D & DirectSound. It also demonstrates DirectSound3D.
It is important to note that this game is not optimised for raw speed.  It
is meant to give a clear demonstration of how the DirectX technologies can
be used.

When you build this sample, it will create a rockem3d.exe file in either
the retail or debug subdirectories, depending on which version you built.
However, you must then copy the .exe up one directory to the Rockem sample
root (i.e. c:\dxsdk\sdk\samples\rockem).  This is because rockem also needs
to find its .wav files and other resources from that dir.

The commands which this game recognizes are listed on the opening screen.

    ESC	            - Quit
    F1              - Camera side view
    F2              - Camera behind view
    F3              - Camera head view
    F5              - Toggle stats
    F6              - Go up a video mode
    F7              - Go down a video mode
    END             - Highest video mode
    HOME            - Lowest video mode
    Control - M     - Toggle music
    Control - S     - Toggle sound
    Control         - Block
    SpaceBar        - Attack
    Up Arrow        - Move forward
    Down Arrow      - Move backwards
