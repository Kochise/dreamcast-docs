
DEFENSE COMMANDER README - January 24, 2000


INTRODUCTION

Defense Commander is a mini-game / technology demo. There are two versions, 
one for PC and one for Dreamcast. The Dreamcast version runs under Microsoft's
Windows CE operating system.


HARDWARE REQUIREMENTS (PC):

Defense Commander has fairly heavy system requirements. A 350MHz machine with
a 16 meg 3D video card is a rough minimum for running Defense Commander in
high detail mode. Voodoo 1 and 2 video cards are not supported. Various 
configuration options are available during startup to allow you to better tune
the game to your system. The game has been successfully tested on Voodoo 3,
G400 and TNT systems.

SOFTWARE REQUIREMENTS (PC):

DirectX 7 run-time installed.


THE GAME

You, the player, control a gun turret in the center of a small city. You must
defend your turret and the city against waves of attacking craft. The game 
proceeds in stages. Each stage is more difficult than the previous and there
are infinitely many stages. If you can get past stage 10, you are doing well.

Attacking craft are of the following types:

Power Up Drone:  These small red ships fly in formations of 5 or more. They do
                 not attack. If you destroy all ships in a formation a power
                 up will appear. There are five different formations, each of
                 which give a different power up. To receive the power up you
                 must shoot it.

Gunship Fighter: Red ships which attack your turret with guns.

Rocket Fighter:  Yellow ships which attack your turret with rockets. They do
                 more damage than the red gunship fighters but are slower.

Bomber:          Large blue ships which drop bombs on the city. Once all
                 buildings in the city are destroyed they will drop bombs on
                 your turret. Be warned, a single bomb will destroy your
                 turret.

You have the following weapons at your disposal:

Guns:            Your primary form of defense. You have unlimited amunition.
                 Some power ups will give the guns enhanced capabilities
                 for short periods.

Missiles:        Missiles lock onto a target and will seek towards that
                 target until it is destroyed. You have unlimted missiles.
                 You must wait for the missile lock to engage before a
                 missile can be fired. Missiles do more damage than a single
                 gun shot.

Smart Bomb:      Smart bombs instantly destroy all enemy objects including
                 craft, weapons fire and power ups. Smart bombs are limited
                 so are best used sparingly.

The following power ups are available during the game:

Damage Repair:   Repairs up to 50% of the damage to the turret.

Smart Bomb:      Gives you another smart bomb.

Rapid Fire:      Doubles the rate of fire of guns.

Explosive Tip:   The guns do a lot more damage to the enemy ships. This
                 power up will override rapid fire.

Seeker:          The gun fire will seek towards the craft they are fired at.
                 You must fire in the general direction of the craft you
                 wish to hit.  This power up will override rapid fire and
                 explosive tip.

During game play, the following information is displayed to assist you:

Damage Indicators: The bottom right of the screen has two damage indicator
                 bars, one for the city and one for the turret. When a 
                 damage level is becoming critical the bar will turn red.

Smart Bombs:     The number of available smart bombs is displayed in the
                 bottom left of the screen.

Radar:           A radar is located at the left of the screen. Larger objects
                 appear larger on the radar.

Gun Power Up:    The currently active power up (if any) will be indicated on
                 the right of the screen by a small icon. A bar indicates the
                 amount of the power up remaining.


CONTROLS

Mouse (PC only): Moving the mouse controls direction. Left mouse button fires
                 guns, right mouse button fires missiles and center mouse
                 button (if any) triggers smart bomb.

Dreamcast Controller: Analog pad controls direction. Button X fires guns, 
                 button Y fires missiles, button B triggers smart bomb. The
                 Start button can be used to both start and quit a game. Right
                 trigger will pause/unpause time.  Left trigger will toggle in
                 and out of observer mode. While in observer mode you can move
                 around using the directional pad.

Keyboard (on Dreamcast too if you have a keyboard):

                 F1:           Toggle help screen.
                 F2:           Toggle observer mode.
                 F3:           Pause/unpause time.
                 F4:           Toggles frame rate display.
                 F5:           Toggles "show triangles" (PC only).
                 F6:           Toggle god mode. Neither the turret nor the
                               city can be damaged in god mode.
                 F7/F8:        Start/stop demo record. A file NEW.DEM will be
                               created on the Defense Commander folder. To use
                               it, replace the existing DC.DEM with it.
                 F9:           Run the benchmark.
                 F10:          Exit game (to Windows).
                 F11:          Takes a screen shot (PC only). Screen shots are
                               saved in the Defense Commander folder.
                 Ctrl:         Fire guns.
                 Alt:          Fire missile.
                 Space:        Trigger smart bomb.
                 Enter/Return: Start the game.
                 Esc:          End the game being played or quits
                 Arrow keys:   Move while in observer mode.
                 W/A/S/D:      Also move while in observer mode.


HOW TO GET STARTED

Both the PC and Dreamcast versions are included.  A VC6 workspace (DC.DSW) lets you 
built either the Dreamcast or PC version.  Source code (\SRC) and Game 
executables (\) are provided.

To get going on the PC simiply run DCPC.EXE from the root directory.  It in turn 
will load all the necessary resources (\ART\IMAGES, \ART\MESHES, \ART\SOUNDS).  
These resources are shared by both versions of the game.

To look at the Dreamcast version you'll first need to create a GD Workshop project.  The 
sample project below shows you how to create a GD that includes both the PC and Dreamcast 
versions on the same image.  This isn't a lesson on using GD Workshop, you'll need to read 
its documentation as provided by Sega if you have further questions.

Area1:01-Mode1
 (1)	ABSTRACT.TXT
 (1)	BIBLIOGR.TXT
 (1)	COPYRIGH.TXT
 (2)	AUTORUN.INF	
	DCPC.EXE		PC executable
	\ART\DC.DEM		Auto demo played upon starting game
	\ART\IMAGES		Textures
	\ART\IMAGES\TERRAIN	Terrain textures
	\ART\MESHES		Model meshes
	\ART\SOUNDS		Sounds
Area1:02-CDDA
  (3)	WARNING.DA 
Area2:03-MODE1 (4)
  (5)	0WINCEOS.BIN
	DCCE.EXE		Dreamcast CE game executable
	\ART\DC.DEM		Same auto demo file as above
	\ART\IMAGES		Textures (same as above)
	\ART\IMAGES\TERRAIN	Terrain textures (same as above)
	\ART\MESHES		Model meshes (same as above)
	\ART\SOUNDS		Sounds (same as above)

NOTES:
(1) These files are required to build a GD Workshop project.  See the GD
    Workshop documentation on these files.

(2) You can create an autorun.inf file if you wish the PC version to 
    autoexecute.  The file is a text file and contains the following lines.

	[AutoRun]
	open=dcpc.exe	

(3) You need to pad this track with audio. Warning.DA is used in the US. Europe
    and Japan pad with a different file.  See GD Workshop for more information.

(4) Remember to PAD Area2:03-Mode1. See GD Workshop for information

(5) This can either be a debug or retail OS you created with the CE Configuration Tool. When
    creating this file the only addition(s) that are required from the 'DEFAULT CONFIGURATION' 
    is to be sure and include DPLAY. An updated PLATFORM.REG is included in \CEFILES.  You 
    will need to replace your current PLATFORM.REG ( in both release directories ) with this 
    new one and rebuild your image before copying 0WINCEOS.BIN into GD Workshop.  

    By doing this you are replacing 
	"CommandVertexBufferSize"=dword:000E0000
    with
	"CommandVertexBufferSize"=dword:00110000

    This is a speed optimization that will result in filling the video memory.  The performance monitor
    will not work anymore as it requires some small amount of video memory.


    This had modifications to increase the size of the CommandVertexBufferSize, 
    CommandPolygonBufferSize.  SmallestPolygon is set to 1 which will cull polygons less than 1 
    pixel.

    After creating your image you'll find a 0WINCEOS.BIN file either in your 
    \release\debug or \release\retail depending if you built a debug or retail image.  If you wish
    DCCE.EXE to autorun after the OS is loaded you'll need to go under the BOOT tab and say that
    you wish DCCE.EXE to be autorun.  If not then you'll need to 's dcce.exe' from the DCTOOL 
    command line. ...

(*) IPMAKER - as part of creating a GD Workshop file you'll need to create an IP.BIN file using
    IPMaker.  GD Workshop will give you instructions on how to create this and where to place it.

Once you've created this image you'll need to put GD Workshop into EMULATION mode (toolbar switch up),
and click on the 'INSERT DISK' icon on the taskbar.  Now your development system will properly be 
emulating a GD disk.  From DCTOOL tell it to BOOT FROM DISK (located on the toolbar) then REBOOT the 
system from within DCTOOL (CTRL+B).


DIRECTORY STRUCTURE

\			Where DCPC.EXE, DCCE.EXE reside
\Docs			Documentation
\CEFiles		platform.reg used to build your OS image for Dreamcast
\Src			Source Tree
\Src\CE			CE Specific source
\art			Where the demo files reside
\art\Images		Textures
\art\Images\Terrain	Terrain textures
\art\Meshes		Model meshes
\art\Sounds		Sounds


NETWORKING:

The networking implementation is quite simple and limited. Its purpose is to
demonstrate the ability of PC and Dreamcast to network together. Only direct
serial cable connections are supported. The server machine can play the game
as normal. The client machine can only act as an observer to what is
happening on the server machine. On the PC, server or client can be selected
on startup. Dreamcast is fixed to operate as a server and retail Dreamcast
machines require a special adaptor to use a serial cable (not readily
available).


BENCHMARK:

A benchmark feature is included with Defense Commander. To use, start the game
and press the F9 key. The demo sequence will play back as fast as the system
can manage and at the end an average frame rate will be displayed.

PC benchmarking notes: A major issue when benchmarking is vsync. This allows
for a flicker free display but can cause benchmark numbers to be much lower
than they otherwise should be. Two systems which are actually similar in 
performance can give very different benchmark results. To minimize this effect
always run benchmarks with triple buffering enabled and try to ensure all
test platforms are using the same refresh rate. A better solution is to
disable vsync but is only viable when all video cards under test support it.

Defense Commander uses Direct3D's T&L pipeline and while we haven't tested it,
video cards with hardware T&L should perform well. It is recommended that
benchmarks are run in both low resolution modes (to test triangle performance)
as well as high resolution modes (to test fill rate).

Dreamcast benchmarking notes: Dreamcast always uses double buffering (as
opposed to triple buffering) to conserve video memory. This is an appropriate
choice in general since it leaves more room for textures but, as mentioned
above, lowers benchmark figures. While the benchmark figures may not show it,
performance on Dreamcast is similar to a Pentium III 500 system with a good 3D
video card. You can not start the benchmark on Dreamcast without a keyboard.

MISC NOTES
- This sample won't build from command line. You need to rebuild it from within VC
- To use the PC version you need to install DX7 SDK and RunTime.
  ( Don't forget to setup the directories ( both include and lib )  in devstudio 
  to point to DX7 SDK for the desktop version, and make them first in the list 
  ( so they will be looked at first ) )
- Since NT4.0 doesn't support DX7 you can't run the PC version.
- To start networking the Katana box (server by default) needs tos tart up first
- You can not quit the sample from Gamepad.  You'll need to either use a keyboard
  or send an ESC using the DCTOOL keyboard emulator
- The baud rate is set to 115k

