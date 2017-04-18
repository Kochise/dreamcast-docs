DirectMusic sample program -- PlayMotif
-----------------------------------------

* Purpose:
This sample application shows how motifs can be played over a primary segment.
Press the buttons on the joystick to play the various secondary segments (motifs)
on top of the main playing primary segment.

* Required Files\Parameters:
Usage for playmotif:
        playmotif [-p searchpath] [-?] [segment]

        If the "-p" parameter is not set, PlayMotif sets the search directory 
        to \Windows, which means that the data files which you are playing
        must be in your BIN image.  To put these files in the BIN image,
        use the Image Configuration Tool, and add a User Defined component
        with the appropriate files (i.e., sample.sgt and amadeus.sty).

        You may use the "-p" parameter to change the search directory to
        "\cd-rom" in order to load the data files from the GDROM (emulator).
        To use this method, copy all required data files to the GDROM
        (emulator) -- (i.e., sample.sgt and amadeus.sty).

        You may also use the "-p" parameter to change the search directory to
        "\pc\samples" in order to load the data files directly from the PC 
        release directory -- <WCEDreamcast\release\(debug,retail)\samples.  
        However, this method results in a very slow load time, and is not 
        recommended.

        If the "segment" parameter is not provided, PlayMotif will play the 
        "sample.sgt" segment by default.  Playing this segment also requires 
        the "amadeus.sty" file.

        In addition, DirectMusic will look for the the GM.DCS and GMDRUMS.DCS 
        files in the default location (\CD-ROM\WINCE) as specified by the 
        following registry key, which is in the platform.reg file:

            [HKEY_LOCAL_MACHINE\Software\Microsoft\DirectMusic]
                "GMFilePath"="\\CD-ROM\\WINCE\\GM.DCS"
                "GMDrumsFilePath"="\\CD-ROM\\WINCE\\GMDRUMS.DCS"

        These files contain the downloadable sounds (tonebank data) necessary 
        to play quality music.  To load these files from a different location 
        (such as \Windows), you may modify the registry key in platform.reg, 
        and rebuild your image.  If DirectMusic cannot find the DCS files 
        in the location specified by the registry key, then the music will 
        still be played, but the audio hardware of the Dreamcast will default 
        to FM synthesis, which results in much poorer quality of music than 
        with the wavetable synthesis provided by using the DCS files.


* To exit this sample, press the 'Send ESC' button in DCTool or
press <Esc> on the keyboard.
