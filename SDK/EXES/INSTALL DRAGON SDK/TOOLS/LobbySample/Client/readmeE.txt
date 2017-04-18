*******************************************************************************************
*      Lobby Client ReadMe 
*					99.10.25
*******************************************************************************************
This document explains how to build and run the Lobby Client Environment.

Contents

* Build the Lobby Client
* Establish the Lobby Service Provider GUID (for Windows CE)
* Windows CE version and Windows NT version
* Establish the transferring of information to DirectPlay Lobby Provider

1.  Building the Lobby Client

  (1) Install the Lobby Client to an arbitrary folder.

      When you run LobbyClientSetup.exe to set up the Lobby Client, the following three
      folders are created:

      -lobbySP -- Resources, including the DirectPlay Lobby Service Provider DLL
      -test program for Windows CE -- Lobby Client testing program (for Windows CE)
      -test program for Windows NT -- Lobby Client testing program (for Windows NT)

  (2) Confirm the resource of established Lobby Client.

      lobbySP ---  +dll      Lobby Service Provider DLL.
   	           +lib      Lobby Service Provider Library
 	           +include  Include File which an application refers 
      Test program for Windows CE -- This is a testing application which runs on Windows CE.
      Test program for Windows NT -- This is a testing application which runs on Windows NT.
      readme.txt -- This manual
      Dplay.txt -- A list of DirectPlay APIs which this Lobby Server supports.

2.  Establish the Lobby Service Provider GUID (for Windows CE)

    To use DirectPlay Lobby Service Provider, please set the following registry information:

    [HKEY_LOCAL_MACHINE\Software\Microsoft\DirectPlay\Lobby Providers]
    [HKEY_LOCAL_MACHINE\Software\Microsoft\DirectPlay\Lobby Providers\
    Lobby Connection For DirectPlay]
	"Guid"="{17AF6382-87AF-11D3-ADF6-0020AF6849EF}"
	"Path"="LobbySP.dll"
	"dwReserved1"=dword:0
	"dwReserved2"=dword:0

3.  Windows CE version and Windows NT version

    (1) Testing program for Windows NT version is only to confirm if it is connected to the
        Lobby Server.
    (2) Testing program for Windows CE version will connect to Lobby Server using DirectPlay
        API, and complete the User Registration and so on.

    Please refer to the readme files under each folder for instructions on how to use these
    testing programs.

4.  Establish the transferring of information to DirectPlay Lobby Provider.

    If you are going to use the current DirectPlay Lobby Provider, the following two items
    need to be added to the registry:

    (1) Connection server IP address.
    (2) Client name (unique machine ID)

    The methods to register the above items are different between the Windows NT version and
    the Windows CE version. Please read the readme for the appropriate testing program to
    avoid confusion.
