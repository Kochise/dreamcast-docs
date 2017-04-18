OLE 2.0 Outline Sample Code


SUMMARY
=======

The OUTLINE sample application set demonstrates taking a 'base' application
(in this case OUTLINE.EXE) and extending it into an OLE 2 server and
container (SVROUTL and CNTROUTL respectively) and into an OLE 2 in-place
(aka visual editing) container and server (ICNTROTL and ISVROTL).

These applications attempt to implement the complete OLE 2 functionality
and recommended user model. For example, these applications implement all
of the OLE 2 User Interface dialog boxes. As such, this is not a trivial
sample application set.

All OUTLINE sample applications support loading and saving files; they all 
use docfiles for storage.


MORE INFORMATION
================

The OUTLINE sample uses the following directory structure:

                        OUTLINE
                           |
       +---------+---------+--------+--------+
       |         |         |        |        |
    OUTLINE   SVROUTL   CNTROUTL ISVROTL  ICNTROTL

All five variations of the OUTLINE applications are built from common
sources. All of the common source code (*.C and *.H files) is in the
OUTLINE directory. Each variant of the application builds under its own
subdirectory for this release.

Files that begin with OUTL comprise the base version of the application. 
They are also used by OLE versions of the applicaton. Files that begin with 
CNTR are specific to the container version and files that begin with SVR are 
specific to the server version. Files that begin with OLE are common to both 
the container and server versions. This series of sample applications 
highlights the changes necessary to implement OLE into an existing 
application. The container version has the same functionality as the base 
(OUTLINE) and also allows you to embed objects.

Some of the major OLE features are organized into special
files in order to group related code across the application variants:

File         Description

DRAGDROP.C   Drag/Drop implementation.
CLIPBRD.C    OLE 2 style copy/paste implementation (data transfer).
LINKING.C    Linking and Moniker support implementation.
CNTRINPL.C   In-place container implementation.
SVRINPL.C    In-place server implementation.
CLASSFAC.C   IClassFactory implementation.

Conditional compilation is used to control what code is used with which
version. The following defines are used to control the compilation:

Define       Description

OLE_VERSION  Code common to all OLE versions.
OLE_SERVER   Code used by both SVROUTL and ISVROTL.
OLE_CNTR     Code used by both CNTROUTL and ICNTROTL.
INPLACE_CNTR Code used by ICNTROTL only.

The following defines are used to identify code specific for a particular
feature. NOTE: It is not really intended that these symbols should be
turned off.

Define          Description

USE_DRAGDROP    Drag/drop code.
USE_FRAMETOOLS  Formula bar and tool bar.
USE_HEADING     Row/column headings code.
USE_STATUSBAR   Status bar code.
USE_CTL3D       Use CTL3D.DLL to have 3D effect for dialogs.
USE_MSGFILTER   IMessageFilter code.
_DEBUG          Debug code.

HOW TO BUILD
------------

To build, simply run "nmake" from the root of the outline directory.

You must first have built SDKUTIL.LIB, OLESTD.LIB, BTTNCUR.LIB,
BTTNCUR.DLL, GIZMOBAR.LIB and GIZMOBAR.DLL. To build these files, run
"nmake" in each of the COMMON, BTTNCUR, GIZMOBAR and OLESTD directories
under the OLE sample directory (in that order).

All the outline samples are copied into the OLE\BIN subdirectory after
compilation.

You will want to load the OUTLINE.REG file into the system registry before
attempting to embed any of the outline objects.
