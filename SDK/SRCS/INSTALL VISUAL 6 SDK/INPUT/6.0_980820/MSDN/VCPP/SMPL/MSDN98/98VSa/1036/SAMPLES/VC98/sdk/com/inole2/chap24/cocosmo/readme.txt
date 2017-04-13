To build a version of Component Cosmo that uses POLY24.DLL, copy
the sources from CHAP13\COCOSMO and modify the function
CCosmoDoc::FInit in DOCUMENT.CPP to use CLSID_Polyline24 instead
of CLSID_Polyline10 in the CoCreateInstance call:

Nothing else in CoCosmo needs to change to use the revised Polyline.
Note that CoCosmo still uses the IPolyline10 interface on the Polyline
object.  For all intents and purposes, nothing should change at all
in the execution of CoCosmo, demonstrating how interfaces do not
interfere with each other:  CoCosmo ignores the compound document
interfaces.



Just note how all the in-place activation and OLE Control support
in Polyline does not preclude Component Cosmo from using like a
non-compound document embedded object or a non-control object!
