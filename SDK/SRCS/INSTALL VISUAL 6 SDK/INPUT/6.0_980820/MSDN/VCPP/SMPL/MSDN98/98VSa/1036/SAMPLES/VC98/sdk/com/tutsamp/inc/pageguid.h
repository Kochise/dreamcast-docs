/*+==========================================================================
  File:      PAGEGUID.H

  Summary:   This is the common include file for the GUIDs of page-related
             COM Interfaces and COM Objects. GUIDs are defined for the
             Interfaces and CLSIDs for the COM objects constructed using
             those interfaces.

             This file is global to all the Tutorial Code Samples (kept
             in the ..\INC directory).  It is a good practice to
             factor out Interface and GUID specifications to reduce the
             possibility of GUID or interface conflicts.

  Classes:   .

  Functions: .

  Origin:    5-26-97: atrent - Editor inheritance from PAPGUIDS.H.

----------------------------------------------------------------------------
  This file is part of the Microsoft COM Tutorial Code Samples.

  Copyright (C) Microsoft Corporation, 1997.  All rights reserved.

  This source code is intended only as a supplement to Microsoft
  Development Tools and/or on-line documentation.  See these other
  materials for detailed information regarding Microsoft code samples.

  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
  PARTICULAR PURPOSE.
==========================================================================+*/

#if !defined(PAGEGUID_H)
#define PAGEGUID_H

#if !defined(RC_INCLUDE)


/*---------------------------------------------------------------------------
  Here are the IIDs for interfaces and the CLSIDs for the Class Factories
  of the persistent page-related COM components in the PERSERVE, PERTEXT,
  PERDRAW, and PERCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_IPageList,
  0x0002da10, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_IPageListSink,
  0x0002da11, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_PageList,
  0x0002da12, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_ITextPage,
  0x0002da13, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_ITextPageSink,
  0x0002da14, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_TextPage,
  0x0002da15, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_IDrawPage,
  0x0002da16, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_IDrawPageSink,
  0x0002da17, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DrawPage,
  0x0002da18, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


#endif // RC_INCLUDE

#endif // PAGEGUID_H
