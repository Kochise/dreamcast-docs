///////////////////////////////////////////////////////////////////////////////
// $Workfile: WWhizInterface2Loader.h $
// $Archive: /WorkspaceWhiz/Src/Shared/WWhizInterface2Loader.h $
// $Date: 2001/08/19 21:53:35 $ $Revision: 1.1 $ $Author: osolo $
///////////////////////////////////////////////////////////////////////////////
// This source file is part of the Workspace Whiz! source distribution and
// is Copyright 1997-2001 by Joshua C. Jensen.  (http://workspacewhiz.com/)
//
// The code presented in this file may be freely used and modified for all
// non-commercial and commercial purposes so long as due credit is given and
// this header is left intact.
///////////////////////////////////////////////////////////////////////////////
#pragma once

class WWhizInterface;
struct WWhizReg;
struct IApplication;

/**
	Loads the Workspace Whiz! Interface library.
**/
WWhizInterface* __cdecl WWhizInterface2Create(HINSTANCE hInstance, IApplication* pApplication);

/**
	Destroys a loaded copy of the Workspace Whiz! Interface library.
**/
void __cdecl WWhizInterface2Destroy();
