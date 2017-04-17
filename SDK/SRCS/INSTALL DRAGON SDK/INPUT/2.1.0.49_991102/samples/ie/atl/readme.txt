Limited ATL for Dreamcast
---------------------------------------------------------------

* Purpose:
This directory contains ATL support files that have been modified for use on the
Dreamcast platform. They are intended to make creating ActiveX controls easier by
providing much of the common code required by all such controls, but it is not
designed to automatically work with the ATL wizard. You are able to create your
ActiveX control using the wizard and these ATL files, but you will have to make
modifications to the wizard generated files.

* Used by:
Sample ActiveX controls.

* Usage notes:
In either a header file or your project settings, tou need to define the following:
    GAL_VERSION _ATL_NO_SECURITY ATL_USE_URLMON NO_DIALOGS
for ATL to work correctly in the Dreamcast environment.

* MIDL notes:
Make sure you have this line:
    #define MIDL_INTERFACE(x)   struct __declspec(uuid(x)) __declspec(novtable)
in a header file (see stdafx.h) before you include your generated interface header.

