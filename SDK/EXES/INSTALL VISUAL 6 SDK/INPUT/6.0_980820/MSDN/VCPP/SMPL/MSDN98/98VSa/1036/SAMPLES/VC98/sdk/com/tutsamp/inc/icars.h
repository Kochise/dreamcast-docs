/*+==========================================================================
  File:      ICARS.H

  Summary:   This is the common include file for the Car-related COM
             Interfaces.  The Interface abstract base classes are
             declared.

             This file is global to all the Tutorial Code Samples (kept in
             the ..\INC directory).  It is a good practice to factor out
             Interface and GUID specifications to reduce the possibility
             of GUID or interface conflicts.

  Classes:   ICar, IUtilityCar, ICruiseCar, ISample.

  Functions: none

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

#if !defined(ICARS_H)
#define ICARS_H

#if !defined(RC_INCLUDE)


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: ICar

  Summary:   Basic Interface that can add propulsion, steering, etc, for
             Car-like COM Objects.

  Methods:   Shift
               Shift the main transmission gears.
             Clutch
               Engage/disengage the clutch.
             Speed
               Accelerate/brake the car to a specified speed.
             Steer
               Steer the car.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(ICar, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // ICar methods.
  STDMETHOD(Shift)   (THIS_ short) PURE;
  STDMETHOD(Clutch)  (THIS_ short) PURE;
  STDMETHOD(Speed)   (THIS_ short) PURE;
  STDMETHOD(Steer)   (THIS_ short) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: IUtility

  Summary:   Interface that can add sport-utility offroad systems features
             for Car-like COM Objects.

  Methods:   Offroad
               Shift the transfer case for specified 4-wheel drive mode.
             Winch
               Turn front-mounted Winch on/off.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(IUtility, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // IUtility methods.
  STDMETHOD(Offroad)   (THIS_ short) PURE;
  STDMETHOD(Winch)     (THIS_ short) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: ICruise

  Summary:   Interface that can add cruise control features for
             Car-like COM Objects.

  Methods:   Engage
               Turns the cruise control system on/off.
             Adjust
               Adjusts the cruise speed up or down by 3 Mph increments.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(ICruise, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // ICruise methods.
  STDMETHOD(Engage) (THIS_ BOOL) PURE;
  STDMETHOD(Adjust) (THIS_ BOOL) PURE;
};


/*I+I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I+++I
  Interface: ISample

  Summary:   Utility Interface for Code Sample servers.

  Methods:   Init
               Initializes the Server as a code sample (eg, to log server
               activity to the Client's trace log facility).
             AboutBox
               Commands Server to show it's about box dialog.
I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I---I-I*/
DECLARE_INTERFACE_(ISample, IUnknown)
{
  // IUnknown methods.
  STDMETHOD(QueryInterface) (THIS_ REFIID, PPVOID) PURE;
  STDMETHOD_(ULONG,AddRef)  (THIS) PURE;
  STDMETHOD_(ULONG,Release) (THIS) PURE;

  // ISample methods.
  STDMETHOD(Init)     (THIS_ HWND, PVOID) PURE;
  STDMETHOD(AboutBox) (THIS_ HWND) PURE;
};


#endif // RC_INCLUDE

#endif // ICARS_H
