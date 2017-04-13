/*+==========================================================================
  File:      PAPGUIDS.H

  Summary:   This is the common include file for the GUIDs of drawing
             paper-related COM Interfaces and COM Objects. GUIDs are
             defined for the Interfaces and CLSIDs for the COM objects
             constructed using those interfaces.

             This file is global to all the Tutorial Code Samples (kept
             in the ..\INC directory).  It is a good practice to
             factor out Interface and GUID specifications to reduce the
             possibility of GUID or interface conflicts.

  Classes:   .

  Functions: .

  Origin:    8-24-97: atrent - Editor inheritance from BALLGUID.H.
               [Revised]

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

#if !defined(PAPGUIDS_H)
#define PAPGUIDS_H

#if !defined(RC_INCLUDE)


/*---------------------------------------------------------------------------
  Here are the IIDs for interfaces and the CLSIDs for the Class Factories
  of the drawing paper-related COM components in the STOSERVE, and
  STOCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_IPaper,
  0x0002da30, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_IPaperSink,
  0x0002da34, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllPaper,
  0x0002da38, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the IIDs for interfaces and the CLSIDs for the Class Factories
  of the drawing paper-related COM components in the DCDSERVE, and
  DCOMDRAW code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_ISharePaper,
  0x0002da31, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_SharePaper,
  0x0002da32, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


#endif // RC_INCLUDE

#endif // PAPGUIDS_H
