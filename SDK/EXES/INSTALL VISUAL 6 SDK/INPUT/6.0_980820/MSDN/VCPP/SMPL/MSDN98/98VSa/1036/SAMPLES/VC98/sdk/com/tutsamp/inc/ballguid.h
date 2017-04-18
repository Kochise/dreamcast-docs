/*+==========================================================================
  File:      BALLGUID.H

  Summary:   This is the common include file for the ball-related COM
             Interfaces and COM Objects. GUIDs are defined for the
             Interfaces and CLSIDs for the COM objects constructed using
             those interfaces.

             This file is global to all the Tutorial Code Samples (kept
             in the ..\INC directory).  It is a good practice to
             factor out Interface and GUID specifications to reduce the
             possibility of GUID or interface conflicts.

  Classes:   .

  Functions: .

  Origin:    6-3-96: atrent - Revised for the COM Tutorial Code Samples.

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

#if !defined(BALLGUID_H)
#define BALLGUID_H

#if !defined(RC_INCLUDE)


/*---------------------------------------------------------------------------
  Here are the IIDs for interfaces and the CLSIDs for the Class Factories
  of the Ball-related COM components in the FRESERVE, and FRECLIEN code
  samples. IID_IBall is also used in the CONSERVE and CONCLIEN samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_IBall,
  0x0002da22, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllBall,
  0x0002da23, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the IIDs for interfaces and the CLSIDs for the Class Factories
  of the Ball-related COM components in the CONSERVE and CONCLIEN code
  samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_IBallSink,
  0x0002da26, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllSndBall,
  0x0002da27, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


#endif // RC_INCLUDE

#endif // BALLGUID_H
