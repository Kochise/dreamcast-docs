//=--------------------------------------------------------------------------=
// Guids.Cpp
//=--------------------------------------------------------------------------=
// Copyright  1995  Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// contains the guids we will define ourselves.
//


#define INITGUID                   // define all the guids.
#include "IPServer.H"

#include "Guids.H"
#include "olectl.h"
//UNDONE: remove me
//[10/8/96, IvoSa] #include "ObjExt.h"

#include "designer.h"

#include "CircleCoInterfaces.H"

// UNDONE, where should these really be coming from?
DEFINE_OLEGUID(IID_ICreateTypeInfo2,0x0002040EL, 0, 0);
DEFINE_OLEGUID(IID_StdOle,  0x00020430L, 0, 0);
