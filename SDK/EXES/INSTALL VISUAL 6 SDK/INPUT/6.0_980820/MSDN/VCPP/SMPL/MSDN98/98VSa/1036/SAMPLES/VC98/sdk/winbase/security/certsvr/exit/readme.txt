The source code in this directory can be used to build a sample Exit Module
for the Microsoft Certificate Server.  It is meant to run on Windows NT 4.0
with SP3 or later or on Windows NT 5.0 only.  The Certificate Server must
already be installed.

The Certificate Server calls the Exit Module through the ICertExit interface,
and the Exit Module can call back to the Certificate Server through the
ICertServerExit interface.

Each time the Certificate Server issues a certificate, it passes control to
the CCertExit::Notify method in exit.cpp, specifying that a certificate
has been issued.  The passed Context parameter is used with the ICertServerExit
interface to retrieve properties from the newly issued certificate.

Once the certexit.dll DLL is built, its COM interface must be registered
via the following command:
    regsvr32 certexit.dll
and the Certificate Server service must be stopped and restarted to load
the newly registered Exit Module.  Use the Control Panel's Services applet,
and stop and restart the "Certificate Authority" service.

If you wish to see the printf output from the sample Exit Module, register
the Exit Module and stop the Certificate Server service as above, then start
the Certificate Server as a console application via the following
command:
    certsrv -z

Files:
------
atl.cpp      -- ActiveX Template Library COM support code

certexit.cpp -- Implements COM and initialization entry points:
			DllMain
			DllCanUnloadNow
			DllGetClassObject
			DllRegisterServer
			DllUnregisterServer

certexit.def -- Exports COM entry points

certexit.rc  -- Version Resource

exit.cpp     -- Implements ICertExit

exit.h       -- Implements ICertExit

pch.cpp      -- Precompiled Header file

resource.h   -- Resource ID definitions
