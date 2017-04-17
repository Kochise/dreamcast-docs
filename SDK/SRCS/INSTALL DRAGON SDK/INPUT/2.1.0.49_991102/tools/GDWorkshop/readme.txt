-------------------------------------------------------------------------------
  OS Loader ReadMe file
  Version 0.90  1998-09-06
  SEGA ENTERPRISES, LTD
-------------------------------------------------------------------------------

1. Contents
    readme.txt    : This file
    1ST_READ.BIN  : a dummy Dragon OS file
    ip_drago.bin  : a sample IP file

2. How to use
   2-1. Please extract the archive.
   2-2. Please update the KABUTO (BootRom) to ver.081 and the
        GD WorkShop to ver 2.4.11a (F/W 2.4.2b) [required]
   2-3. Please turn on the SET5 and execute the GD Workshop and make
        a new project, put the file (1ST_READ.BIN)
        to root directory of the High density area of GD-WS.
   2-4. Please choose the "Disc" tub of the GD-WS, and set the ip_drago.bin file to
        the two "System Area File", using Browse button.
        Press the "Apply" button, which at the bottom of the "Disc" tub.
   2-4. Boot the CodeScape with CPU debug mode, and reset SET5.
        Close the CD-tray, and Run by the CodeScape.
        (F9 or [Debug]->[Execution]->[Run])
        KABUTO will execute OS loader and it will load the
        1ST_READ.BIN
        You can see by some debugger that loaded sample program
        (just looping at 0xAc400000) is working with SET5.
   2-5. Please change 1ST_READ.BIN to real Dragon Image file,
        after you confirm the sample.

  ****  Note: IMPORTANT *********************************************************

     [1] Some rules
         There are some rules for 1st read file, like file name, location, etc.
         Dragon Image file also required this rules, as following.

       1. File should be locate at root directory.
       2. Name of the file should begin with numeral. (e.x. 1DRAGON.BIN)
       3. Size of the file name should be equal or less than 12 characters
          including the period.

     [2] How to distinguish Dragon GD from other GD's
         Dragon GD needs this OS loader for boot-up, so it needs some mark
         to distinguish by KABUTO, Dragon GD or not.
         
         It required that all Dragon GDs has same ID in the [System ID]
         in the System area of the GD.

         The ID is 1 Byte in System ID,

         +===================+
         | ASCII code |  1   |
         +------------+------+
         | Hex code   | 31 H |
         +------------+------+
         | Location   | 3E H |
         +===================+

         [System ID]
          0123456789ABCDEF 
         +----------------+
     00H |SEGA SEGAKATANA |     H/W identifer
     10H |                |     Maker identifer
     20H |                |     Media information
     30H |              1 |     Compatible area symbols / Compatible peripherals [DragonOS ID]
     40H |                |     Product number / Version
     50H |                |     Release date
         :                :
      
  *******************************************************************************

3. Address issue
      Please make Dragon files which should load
      from 0x0C010000 until 0x0CCFFFFF in physical address.
      Remaing area from 0x0CE00000 until 0x0CFFFFFF can be used by
      Dragon OS (or game application) after boot up.

4. DMA reading
   4-1) The pLoadAddress of each sections should be H'20 Bytes boundary.
   4-2) The sectionSize of each sections should be multiple of H'20.
   4-3) The offsetInFile of each sections should be a sum of size of
        the above sections.

   i.e.  for (i=0;i<numSections)
    1]   (0x0000001F & sections[i].pLoadAddress) == 0x00000000;   // True
    2]   (0x0000001F & sections[i].sectionSize) == 0x00000000;   // True
    3]   sections[i+1].offsetInFile
               == sections[i].offsetInFile + sections[i].sectionSize; // True

5. About the sample (1ST_READ.BIN)
   The Dragon Image header file of this sample contains following information.
   
           numSections = 4L;
           pStartAddress = (void*)0xAC400000;

           sections[0].offsetInFile = 0x0800L;
           sections[0].sectionSize = 0x0800L;
           sections[0].pLoadAddress = (void*)0x0C100000;

           sections[1].offsetInFile = 0x1000L;
           sections[1].sectionSize = 0x0800L;
           sections[1].pLoadAddress = (void*)0x0C200000;

           sections[2].offsetInFile = 0x1800L;
           sections[2].sectionSize = 0x0400L;
           sections[2].pLoadAddress = (void*)0x0C300000;

           sections[3].offsetInFile = 0x1C00L;
           sections[3].sectionSize = 0x0020L;
           sections[3].pLoadAddress = (void*)0xAC400000;

        Here,
           Section[0]: "SEGA" filled as byte data.
           Section[1]: "SEGA" filled as word data.
           Section[2]: "SEGA" filled as long data.
           Section[3]: a sample program.
            (This sample program is just loop at 0xAc400000)

[EOF]