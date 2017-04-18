DirectSetup Sample Game

This sample is an example of how to use DirectXSetup API's to install
DirectX subsystem and DirectX drivers.  It also serves as a working template
for ISV's to install a game.
                                                          
Note that this program will not run until the redist directory (on the CD)
is copied into the same directory as setup.exe.  The whole redist directory
and all subdirectories must be copied for setup to work correctly, with
the exception of the driver directories (discussed below).

The driver directories (contained in \redist\directx\drivers) contain 
localized versions of Microsoft-provided display and audio drivers. You may
omit any number of these driver directories from your redistributable to omit
support for driver upgrades for those languages. If you choose to omit
driver support for a particular language, you must omit the entire 
directory and its contents. Likewise, if you choose to include driver
support for a particular language, you must include the entire directory
and its contents. Setup will not function properly otherwise.

For more information on DirectSetup, please refer to the DirectX SDK 
documentation.

IMPORTANT: You must not add, remove, rename or modify any files or 
directories in the redist directory tree (except for omitting language
directories). Setup will not function properly if any of the contents
are altered.
