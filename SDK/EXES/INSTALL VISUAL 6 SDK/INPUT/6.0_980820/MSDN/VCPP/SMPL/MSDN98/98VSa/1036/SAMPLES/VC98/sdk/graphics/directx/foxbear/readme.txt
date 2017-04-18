The Fox & The Bear Sample
-------------------------

You need to run FOXBEAR from the FOXBEAR directory for it to find all of
its files.


Commands for using Foxbear:

    F12      - quit
    NUMPAD 2 - crouch
    NUMPAD 3 - throw an apple
    NUMPAD 4 - move right (hold down to run faster)
    NUMPAD 5 - stop
    NUMPAD 6 - move left (hold down to run faster)
    NUMPAD 7 - jump


Options for running foxbear:

WIN.INI             Command line

use_emulation=0                   Use hardware acceleration
use_emulation=1     -e            Use emulation, not hardware
use_dsound=0        -S            Do not use Direct Sound
use_dsound=1                      Use Direct Sound
buffers=0                         Double or trible buffer vram size dependent
buffers=1           -1            Use no back buffer
buffers=2           -2            Double buffer
                    -d            Double buffer
buffers=4           -4            Use 3 back buffers
                    -s            Use stretch
sysmem=1                          Use system memory when creating surfaces
                    -x            Demo or stress mode (keeps running)

command line dash parameters may be followed by x-resolution y-resolution color-depth
