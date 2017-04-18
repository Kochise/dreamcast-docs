Visual Memory Simulator V1.06
                                                                        1999/10/20
					SEGA Enterprises, Ltd.
					Technical Support Center


<Details of files in each folder>

(1) VmSimulator
	vms.exe		VM Simulator execution file

(2) VmSimulator\Files   VM simulator system files are stored.
	Fbios.sbf	VM System BIOS (Full size BIOS)
	Qbios.sbf	Quick start BIOS for development
	vms.ini		Simulator initializing file
	vms.env		Simulator environment setting file
	Default.env	Application default environment file
	Buz2k.wav	2KHz sign wave audio file
	Buz4k.wav	4KHz sign wave audio file
	Pwm.wav		PWM confirmation audio file
	Game.bin	File for Flash#1
			This file needs to be loaded when executing simulator.

(3) VmSimulator\Help
	Vmshelp.hlp	Japanese version help file
	VmshelpUS.hlp	English version help file


<HELP files>

The language can be specified in the vms.ini file.


<BIOS>

Two types of BIOS, full size BIOS and quick start BIOS, are supported and both files 
are under VmSimulator\Files.

	fbios.sbf	VM System BIOS (Full size BIOS)
	qbios.sbf	Quick start BIOS for development

Full size BIOS is set to be loaded when simulator is started for the first time.

Quick start BIOS is as same as full size BIOS except for the time setting.
Therefore, they have no difference in their functions.


<FLASH#1>

To activate automatic loading, full path to folder with game.bin needs to be specified
in the second line of vms.env file (under VmSimulator\Files)  

	FlashFileName=C:\VM_SDK\VmSimulator\Files\game.bin
		      ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
The setting is automatically loaded from the next execution of the application. 
