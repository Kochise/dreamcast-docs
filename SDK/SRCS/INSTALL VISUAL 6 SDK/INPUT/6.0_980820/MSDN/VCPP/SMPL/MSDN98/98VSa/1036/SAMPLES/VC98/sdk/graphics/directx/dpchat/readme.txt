DPCHAT ReadMe

This is a simple chat program to demonstrate usage of the DirectPlay APIs.

Note: MSVC may include older versions of the DirectX header files and
libraries.  This sample requires DirectX 5.  In order to avoid compile errors,
make sure the path to the DirectX 5 header files and libraries are listed
BEFORE the MSVC header files and libraries through the
Tools -> Options -> Directories menu.

Note: The DPLAUNCH or BELLHOP sample that is part of the DirectX 5 SDK can be
used to exercise the lobby functionality of DPCHAT.

dpchat.mak - MSVC workspace to compile DPCHAT.

lobby.cpp - sample code for enabling a DirectPlay application to be launched 
            and connected to a session by a lobby.

dialog.cpp - sample code for establishing a session connection by asking
            the user to supply information and make choices

dpchat.cpp - the core chat application

dpchat.reg - Adds entries to the registry to make DPCHAT visible to lobby
             applications.

