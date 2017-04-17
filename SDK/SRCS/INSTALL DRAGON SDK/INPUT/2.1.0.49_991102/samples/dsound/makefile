all: dbg rtl

clean dbg rtl:
	cd DirectSound3D
	nmake $(@B)
	cd ..\Microphone
	nmake $(@B)
	cd ..\Playsound
	nmake $(@B)
	cd ..\CustomDSP
	nmake $(@B)
	cd ..\Reverb
	nmake $(@B)
	cd ..\PlayMultipleSounds
	nmake $(@B)
	cd ..\StreamingSound
	nmake $(@B)
	cd ..
