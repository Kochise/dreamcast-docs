/*+==========================================================================
  File:      README.TXT

  Summary:   This directory and those in the branch below contain the COM
             Tutorial Samples. These code samples include an integrated
             tutorial narrative that covers the foundations of COM
             technology. All source for these samples is in C++. MFC is
             not used. The series is for advanced programmers using their
             proficiency in C++ Win32 programming to code COM and ActiveX
             applications.

             You can start the tutorial by executing TUTORIAL.EXE in this
             directory (ie, the main directory of the installed COM
             Tutorial Samples). Within the tutorial you can jump to Web
             pages containing the individual lessons associated with each
             sample. You can also jump to view pages covering how to set
             up your computer environment to build and run the code
             samples,

             You must have a Web browser installed for TUTORIAL.EXE to
             work. The Web browser must have a file association with the
             .HTM file extension. The tutorial starts in the TUTORIAL.HTM
             file.

  Origin:    9-9-97: atrent - Revised for COM Tutorial Sample series.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997. All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or online documentation. See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/


COM Tutorial Programming Samples
================================

The COM (Component Object Model) technology is the primary foundation for
Microsoft's component software technology. OLE technology is built upon COM
and all ActiveX controls are COM Component Objects.

This tutorial sample series is directed to serve advanced programmers who
are using their proficiency in C++ Win32 programming to develop or modify
systems-level software using COM (Component Object Model) technology.
These advanced samples show how to program components at the foundation
level of COM. Neither MFC nor ATL is used in the samples.

If you are developing internet Web applications with ActiveX controls and
an integrated development environment like Microsoft Developer Studio,
then you have the benefit of tools and abstractions that hide most of the
technical detail covered in this series. The series exposes much of the
infastructure that is now being increasingly hidden by MFC (Microsoft
Foundation Classes) and ATL (Active Template Library). This series can
help when you need to drop below the convenient abstractions in MFC or ATL
to perform COM-compliant modifications. Of course, it can also help if you
are working directly at this foundation level of COM programming to
develop the highest performance professional applications.

These source code samples are the same as those currently found as branch
\MSSDK\SAMPLES\COM\TUTSAMP of the installed Microsoft Win32 Platform SDK.
All source for these code samples is in C++. MFC is not used.

Each code sample has an associated description of the sample's external
operation and a narrative code tour of the internal construction (based on
the specific goal of the tutorial lesson). This tutorial narrative resides
in a <lesson>.HTM Web page file--where <lesson> is the name of the
lesson/code sample. There is one of these narrative HTML files for each
tutorial code sample. All of these HTML files are located in the main
directory of the tutorial samples branch. The complete tutorial is thus
made up of many HTML files located in the parent directory of all the
sample directories. This single parent directory is the main tutorial
directory. Additional details on the internal mechanisms of each sample
can be found in code comments in each source file located in the sample's
directory.

The tutorial HTML files for the tutorial samples are linked together into
a Web that can be viewed with a Web browser. You can start browsing this
tutorial by executing the TUTORIAL.EXE command in the main directory. You
must have a Web browser installed for TUTORIAL.EXE to work.

The COM tutorial samples reside in the following directory tree, organized
in a graduated sequence of tutorial lessons. The numbered order of lessons
is the sequence we recommend that you follow in the tutorial. Each lesson
illustrates a major feature of COM technology. Most lessons build on the
ones that came earlier in the sequence.

  TUTSAMP    - This file, TUTORIAL.EXE, MAKEALL.BAT, *.HTM, etc.
    INC      - Common include directory used by the code samples
    LIB      - Common library directory used by the code samples
    APPUTIL  - Lesson  0: Win32 Basics: Application Utility Library
    READTUT  - Lesson  1: Win32 Basics: Tutorial Reader and Linking to APPUTIL
    EXESKEL  - Lesson  2: Win32 Basics: Win32 EXE Skeleton Application
    DLLSKEL  - Lesson  3: Win32 Basics: Win32 DLL Skeleton
    DLLUSER  - Lesson  4: Win32 Basics: EXE User of a DLL
    COMOBJ   - Lesson  5: COM Objects: Containment and Aggregation in a DLL
    COMUSER  - Lesson  6: COM Objects: Nested Aggregation in EXE User
    REGISTER - Lesson  7: COM Components: Component Registration
    DLLSERVE - Lesson  8: COM Components: Component DLL Server
    DLLCLIEN - Lesson  9: COM Components: Client Application of DLL Server
    LICSERVE - Lesson 10: COM Components: DLL Licensed Server
    LICCLIEN - Lesson 11: COM Components: Client App of Licensed Server
    MARSHAL  - Lesson 12: COM Components: Custom Interface Standard Marshaling
    MARSHAL2 - Lesson 13: COM Components: Marshaling DLL Self-Registration
    LOCSERVE - Lesson 14: COM Components: Local Server
    LOCCLIEN - Lesson 15: COM Components: Client App of Local Server
    APTSERVE - Lesson 16: COM Components: Local Server with Multiple Apartments
    APTCLIEN - Lesson 17: COM Components: Client of Multiple Apartment Server
    REMCLIEN - Lesson 18: COM Components: DCOM Remote Client
    FRESERVE - Lesson 19: COM Components: Free-threaded Server
    FRECLIEN - Lesson 20: COM Components: Client of Free-threaded Server
    CONSERVE - Lesson 21: COM Components: Connectable Object Server
    CONCLIEN - Lesson 22: COM Components: Client of Connectable Object Server
    STOSERVE - Lesson 23: COM Components: Structured Storage Server
    STOCLIEN - Lesson 24: COM Components: Client of Structored Storage Server
    PERSERVE - Lesson 25: COM Components: IPersistStream Persistence Server
    PERTEXT  - Lesson 26: COM Components: IPersistStreamInit Persistence Server
    PERDRAW  - Lesson 27: COM Components: IPersistStorage Persistence Server
    PERCLIEN - Lesson 28: COM Components: Client of Persistent Components
    DCDMARSH - Lesson 29: COM Components: Standard Marshaling for DCOM
    DCDSERVE - Lesson 30: COM Components: DCOM Server Using Security
    DCOMDRAW - Lesson 31: COM Components: DCOM Client Using Security.

Throughout the sample sequence a clear differentiation is maintained
between client and server, with a separate lesson sample for each.
Usually, each client/server pair covers an area of COM technology. Here is
an overview of the technologies covered by the lessons.

Basic Win32 application programming is covered in the APPUTIL, READTUT,
EXESKEL, DLLSKEL, and DLLUSER lessons. APPUTIL provides a utility
framework for building Win32 applications. It also contains some tools
needed for tutorial purposes. READTUT is a very simple EXE application
that shows how to link to the APPUTIL static library and call utility
functions in it. READTUT also shows how to invoke the COM tutorial Web
page reader that is used throughout the sample series. EXESKEL shows a
basic Win32 skeleton EXE application built using APPUTIL. DLLSKEL and
DLLUSER simularly show a basic Win32 DLL (Dynamic Link Library) skeleton
and how to access it from an EXE user application.

Basic COM object construction, custom interfaces, and techniques for
coding their reuse using aggregation and containment are covered in COMOBJ
and COMUSER. The implementation and use of the standard IUnknown interface
is covered. The implementation and use of the custom ICar, IUtility, and
ICruise interfaces is covered.

Basic COM component construction, class factories, component object
registration, and techniques for housing COM objects in COM component
servers are covered in REGISTER, DLLSERVE, and DLLCLIEN. The
implementation and use of the standard IClassFactory interface is covered.

COM component Licensing is covered in LICSERVE and LICCLIEN. The
implementation and use of the standard IClassFactory2 interface is
covered.

Out-of-Process local servers and the standard marshaling of custom
interfaces are covered in MARSHAL, LOCSERVE, and LOCCLIEN. Explicit
self-registration in the standard marshaling DLL is covered in MARSHAL2.
The use of the MIDL language to specify custom interfaces is covered. The
use of the MIDL compiler to produce proxy/stub marshaling servers is also
covered.

Apartment model server and client construction are covered in APTSERVE and
APTCLIEN. Construction of multiple single-threaded apartments (STA) in the
same process is covered.

DCOM (Distributed COM) with custom interfaces operating between client and
server across machine boundaries is covered in REMCLIEN. Specifying the
remote machine name in the COSERVERINFO structure is covered. Detailed
DCOM security issues are not covered.

Free-threaded COM components and their access by free-threaded clients are
covered in FRESERVE and FRECLIEN. The use several client worker threads in
the multi-threaded apartment (MTA) is covered. The implementation and use
of a custom IBall interface is covered.

Connectable COM object technology is covered in CONSERVE and CONCLIEN.
Event source and sink construction is covered. Implementation and use of
the IConnectionPointContainer, IConnectionPoint, IEnumConnectionPoints,
and IEnumConnections standard interfaces are covered. The implementation
and use of the custom IBall and IBallSink interfaces is covered.

Structured storage using COM's compound file technology is covered in
STOSERVE and STOCLIEN. A COM-based scribble drawing application is used.
Use of the IStorage and IStream standard interfaces is covered. The
implementation and use of the custom IPaper and IPaperSink interfaces is
covered.

Persistent COM objects are covered in PERSERVE, PERTEXT, PERDRAW, and
PERCLIEN. IPersistStream is covered in the PERSERVE components.
IPersistStreamInit is covered in the PERTEXT components. IPersistStorage
is covered in the PERDRAW components. The PERCLIEN client functions these
various persistent objects and manages storage for all of them in various
substorages and streams within one structured storage compound file. The
implementation and use of the custom IPageList, ITextPage, IDrawPage,
IPageListSink, ITextPageSink, and IDrawPageSink interfaces is covered.

DCOM (Distributed COM) Security is covered in DCDMARSH, DCDSERVE, and
DCOMDRAW. The use of CoInitializeSecurity is shown in the DCDSERVE and
DCOMDRAW samples. Multiple clients accessing a shared single COM object
across machine boundaries is shown in a simple network shared-drawing
application. Process and activation security within NT network domains is
discussed. Registry AppIDs and their LaunchPermission, AccessPermission,
and RunAs named values are discussed. The use of the DCOMCNFG utility is
covered.


FILES in the Main TUTSAMP Tutorial Directory
============================================

File          Description
----          -----------
README.TXT    This file. Short introduction to the COM Tutorial Samples.
MAKEALL.BAT   Main batch file for building the entire samples branch
                regardless of branch's location. Use this one.
LOGMALL.BAT   Same as MAKEALL.BAT except that all build output is logged
                to file ERRORLOG.TXT and viewed in NOTEPAD.
REGALL.BAT    Batch file for registering all sample COM servers.
UNREGALL.BAT  Batch file for unregistering all sample COM servers.
CLEANALL.BAT  Batch file for performing CLEANALL on all the samples.
MAKEFILE      Makefile for all samples. Use ONLY if building the entire
                samples branch WITHIN an installed Win32 Platform SDK.
TUTORIAL.EXE  The main executable entry to the Web-based tutorial.
TUTORIAL.HTM  Tutorial Web page. Main overview of COM Tutorial Samples.
LESSONS.HTM   Tutorial Web page. Main Tutorial lesson list (with links).
USING.HTM     Tutorial Web page. Details about using the code samples.
APPUTIL.HTM   Tutorial Web page covering the APPUTIL sample.
READTUT.HTM   Tutorial Web page covering the READTUT sample.
EXESKEL.HTM   Tutorial Web page covering the EXESKEL sample.
DLLSKEL.HTM   Tutorial Web page covering the DLLSKEL sample.
DLLUSER.HTM   Tutorial Web page covering the DLLUSER sample.
COMOBJ.HTM    Tutorial Web page covering the COMOBJ sample.
COMUSER.HTM   Tutorial Web page covering the COMUSER sample.
REGISTER.HTM  Tutorial Web page covering the REGISTER sample.
DLLSERVE.HTM  Tutorial Web page covering the DLLSERVE sample.
DLLCLIEN.HTM  Tutorial Web page covering the DLLCLIEN sample.
LICSERVE.HTM  Tutorial Web page covering the LICSERVE sample.
LICCLIEN.HTM  Tutorial Web page covering the LICCLIEN sample.
MARSHAL.HTM   Tutorial Web page covering the MARSHAL sample.
MARSHAL2.HTM  Tutorial Web page covering the MARSHAL2 sample.
LOCSERVE.HTM  Tutorial Web page covering the LOCSERVE sample.
LOCCLIEN.HTM  Tutorial Web page covering the LOCCLIEN sample.
APTSERVE.HTM  Tutorial Web page covering the APTSERVE sample.
APTCLIEN.HTM  Tutorial Web page covering the APTCLIEN sample.
REMCLIEN.HTM  Tutorial Web page covering the REMCLIEN sample.
CONSERVE.HTM  Tutorial Web page covering the CONSERVE sample.
CONCLIEN.HTM  Tutorial Web page covering the CONCLIEN sample.
FRESERVE.HTM  Tutorial Web page covering the FRESERVE sample.
FRECLIEN.HTM  Tutorial Web page covering the FRECLIEN sample.
STOSERVE.HTM  Tutorial Web page covering the STOSERVE sample.
STOCLIEN.HTM  Tutorial Web page covering the STOCLIEN sample.
PERSERVE.HTM  Tutorial Web page covering the PERSERVE sample.
PERTEXT.HTM   Tutorial Web page covering the PERTEXT sample.
PERDRAW.HTM   Tutorial Web page covering the PERDRAW sample.
PERCLIEN.HTM  Tutorial Web page covering the PERCLIEN sample.
DCDMARSH.HTM  Tutorial Web page covering the DCDMARSH sample.
DCDSERVE.HTM  Tutorial Web page covering the DCDSERVE sample.
DCOMDRAW.HTM  Tutorial Web page covering the DCOMDRAW sample.
LOGO.GIF      Logo graphic used by the Tutorial. COM Logo.
BULLET.GIF    Small graphic used by the Tutorial. General Bullet.
PAGETOP.GIF   Small graphic used by the Tutorial. Top-of-page button.
NAVBTN.GIF    Small graphic used by the Tutorial. General Button.
NEXT.GIF      Small graphic used by the Tutorial. Next Arrow Button.
PREV.GIF      Small graphic used by the Tutorial. Previous Arrow Button.
