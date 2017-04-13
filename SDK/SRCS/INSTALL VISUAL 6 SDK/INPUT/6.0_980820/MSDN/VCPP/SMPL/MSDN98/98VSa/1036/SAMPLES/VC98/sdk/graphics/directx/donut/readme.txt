This program is useful for testing multiple exclusive mode apps interacting
with multiple non-exclusive mode apps.  The program displays a rotating 
donut in the upper left corner of the screen.  It may be terminated by 
pressing Esc or F12.  

Various command line switches can be specified to modify the characteristics
of this program.  Each switch consists of one character and need not be 
preceeded with a dash or slash.  The switches are as follows:

0   -   Display in far left position
1   -   Display in middle position
2   -   Display in right position
X   -   Use exclusive mode
A   -   Switch mode to 640x480x8 and use exclusive mode
B   -   Switch mode to 800x600x8 and use exclusive mode
C   -   Switch mode to 1024x768x8 and use exclusive mode
D   -   Switch mode to 1280x1024x8 and use exclusive mode

The switches may be combined.  If two switches are used which contradict,
the last switch specified will be in effect.

If this program is running in non-exclusive mode, it attempts to continue to 
run even when it loses focus.  If it is running in exclusive mode, the 
program does not attempt to modify the screen when it doesn't have focus.


