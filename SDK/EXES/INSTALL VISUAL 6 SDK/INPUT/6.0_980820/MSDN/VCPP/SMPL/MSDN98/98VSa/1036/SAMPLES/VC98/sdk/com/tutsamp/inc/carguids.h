/*+==========================================================================
  File:      CARGUIDS.H

  Summary:   This is the common include file for the Car-related COM
             Interfaces and COM Objects. GUIDs are defined for the
             Interfaces and CLSIDs are defined for the COM objects made
             using those interfaces.

             This file is global to all the Tutorial Code Samples (kept
             in the ..\INC directory).  It is a good practice to
             factor out Interface and GUID specifications to reduce the
             possibility of GUID or interface conflicts.

  Classes:   .

  Functions: .

  Origin:    10-7-95: atrent - Factored out of COMOBJ and DLLSERVE.

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

#if !defined(CARGUIDS_H)
#define CARGUIDS_H

#if !defined(RC_INCLUDE)

/*---------------------------------------------------------------------------
  Here are the IIDs for the interfaces of the Car-related
  COM components in the DLLSERVE, DLLCLIEN, and later code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(IID_ICar,
  0x0002da00, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_IUtility,
  0x0002da01, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_ICruise,
  0x0002da02, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(IID_ISample,
  0x0002da03, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the CLSIDs for the Class Factories of the Car-related
  COM components in the DLLSERVE and DLLCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(CLSID_DllCar,
  0x0002da04, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllUtilityCar,
  0x0002da05, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllCruiseCar,
  0x0002da06, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_DllCarSample,
  0x0002da07, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the CLSIDs for the Class Factories of the Car-related
  COM components in the LICSERVE and LICCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(CLSID_LicCruiseCar,
  0x0002da08, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_LicCarSample,
  0x0002da09, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the CLSIDs for the Class Factories of the Car-related
  COM components in the LOCSERVE and LOCCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(CLSID_LocCar,
  0x0002da0a, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_LocUtilityCar,
  0x0002da0b, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_LocCruiseCar,
  0x0002da0c, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


/*---------------------------------------------------------------------------
  Here are the CLSIDs for the Class Factories of the Car-related
  COM components in the APTSERVE and APTCLIEN code samples.
---------------------------------------------------------------------------*/
DEFINE_GUID(CLSID_AptCar,
  0x0002da0d, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_AptUtilityCar,
  0x0002da0e, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);

DEFINE_GUID(CLSID_AptCruiseCar,
  0x0002da0f, 0x0000, 0x0000, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46);


#endif // RC_INCLUDE

#endif // CARGUIDS_H
