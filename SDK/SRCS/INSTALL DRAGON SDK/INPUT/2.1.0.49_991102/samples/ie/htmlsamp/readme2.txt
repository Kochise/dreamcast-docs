Macromedia Flash Player for Windows CE / Dreamcast
==================================================

Gary Grossman
October 25, 1999


Contents
--------

CEFLASH.DLL: The Flash 4 Player for Windows CE / Dreamcast

HTMLSAMP: A modified version of the HTML Sample Application included in
the Dreamcast SDK.  HTMLSAMP has been modified to support embedded
Flash animations.


Testing
-------

To test the Flash Player for Dreamcast, launch the provided version of
HTMLSAMP.EXE.  HTMLSAMP will automatically register the Flash Player
ActiveX Control.  Then, visit a Web page that contains Flash content,
such as
   http://www.turbonium.com/flash/index.html


Usage
-----

The Flash Player is an ActiveX Control and can be hosted in an ActiveX
Container.  Typically, the Flash Player will be embedded in the
Dreamcast HTML Control using the HTML OBJECT tag.  It is also possible
to directly embed the Flash Player ActiveX Control in any program
that is an ActiveX Control Container.

Interface
---------

The Flash Player is an ActiveX Control; however, because of the
differences between Windows CE/Dreamcast and traditional Windows
platforms, some additional API methods are provided for controlling
the Flash ActiveX Control.  These methods reside in the DCFlashPlayer
COM object.  Before creating instances of the Flash Player control in
your application, create a DCFlashPlayer COM object and query for the
IDCFlashPlayer interface.

The DCFlashPlayer COM object's CLSID is
   3526D8A6-6FAF-11D3-B31A00105A29E72B
The IID of the IDCFlashPlayer interface is
   3526D8A5-6FAF-11D3-B31A00105A29E72B

In the modified HTMLSAMP project provided, these COM objects and interfaces
are defined in the files CEFlash.h and CEFlash_i.c.

The available methods are:

HRESULT SetDirectSound([in] LPUNKNOWN pDirectSound);

  Sets the DirectSound interface for the Flash Player ActiveX
  Control.  To avoid conflict with DirectSound objects created
  by your application, the Flash Player does not create its own
  DirectSound object using DirectSoundCreate.  Instead, pass
  your DirectSound object to Flash using this method.

HRESULT MouseDown([in] int x, [in] int y);
HRESULT MouseMove([in] int x, [in] int y);
HRESULT MouseUp([in] int x, [in] int y);

  Flash's button model is designed to be used with a mouse.
  However, the Dreamcast may be using a joystick or some other device
  instead of a mouse.  Call these methods to interface your input
  device with Flash.

HRESULT Idle();

  The Idle method should be called periodically by your application's
  main message loop to run Flash animations.


Open Issues
-----------

* The HTML Control sometimes does not in-place activate the Flash
  ActiveX Control immediately when it is encountered on an HTML page.
  Often, it is necessary to move over the Flash movie with the arrow keys
  to force the HTML Control to in-place activate it.  This appears to be
  an HTML Control issue and not a Flash Player issue.
