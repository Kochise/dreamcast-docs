//OLE Control Container Verification Application, Version 1.00
//
//Copyright (c) 1995-6 Microsoft Corp, All Rights Reserved
//
//	This is a part of the Microsoft Source Code Samples.
//	This source code is only intended as a supplement to
//	the Microsoft Development Tools and/or WinHelp implementation.
//	See these sources for detailed information regarding the
//	Microsoft sample programs.
//
//Revisions:
//	November 30, 1995	mtm		First Implementation
//
//Purpose:
//	Class used for each control that is tested.

#include "stdafx.h"
#include "verify.h"

/////////////////////////////////////////////////////////////////////////////
// CVerify

IMPLEMENT_DYNCREATE(CVerify, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CVerify properties

/////////////////////////////////////////////////////////////////////////////
// CVerify operations

void CVerify::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}
