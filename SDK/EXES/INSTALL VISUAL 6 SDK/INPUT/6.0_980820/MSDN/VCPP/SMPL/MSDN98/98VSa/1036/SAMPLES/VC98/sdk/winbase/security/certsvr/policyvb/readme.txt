The source code in this directory can be used to build a sample Policy Module
for the Microsoft Certificate Server.  It is meant to run on Windows NT 4.0
with SP3 or later or on Windows NT 5.0 only.  The Certificate Server must
already be installed.

The Certificate Server calls the Policy Module through the ICertPolicy
interface, and the Policy Module can call back to the Certificate Server
through the ICertServerPolicy interface.

Each time the Certificate Server receives a certificate request, it passes
control to the CCertPolicy::VerifyRequest method in policy.cpp.  The passed
Context parameter is used with the ICertServerPolicy interface to retrieve
properties from the request and potential certificate.  The VerifyRequest
method may add, modify or enable Certificate Extensions, modify the NotBefore
and NotAfter dates and Subject name RDN (Relative Distinguished Name) strings
for the potential certificate.  It must also perform any validation required,
and decide the disposition of the request.  The method should return one of
VR_PENDING, VR_INSTANT_OK or VR_INSTANT_BAD to cause the request to be made
pending, to grant the request and issue the certificate, or to fail the
request.

Once the policyvb.dll DLL is built, its COM interface must be registered
via the following command:
    regsvr32 policyvb.dll
the Certificate Server service must then be stopped and restarted as a console
application to load the newly registered Policy Module.  Use the Control
Panel's Services applet, and stop the "Certificate Authority" service, then
start the Certificate Server as a console application via the following
command:
    certsrv -z

NOTE: Because this VB Policy Module uses an Interactive Form to display
information passed in the certificate request, IT MUST BE STARTED VIA THE
ABOVE COMMAND AS A CONSOLE APPLICATION in order to interact with the desktop
to display the form and accept the user's input.


Files:
------
const.bas    -- Constant definitions

main.bas     -- main definition

mssccprj.scc -- stub source code control file

policy.cls   -- Implements ICertPolicy

policyvb.frm -- Form definition

policyvb.vbp -- VB Project file

policyvb.vbw -- VB Workspace file
