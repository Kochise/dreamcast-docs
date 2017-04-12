//*******************************************************************************
// COPYRIGHT NOTES
// ---------------
// This source code is a part of BCGControlBar library.
// You may use, compile or redistribute it as part of your application 
// for free. You cannot redistribute it as a part of a software development 
// library without the agreement of the author. If the sources are 
// distributed along with the application, you should leave the original 
// copyright notes in the source code without any changes.
// This code can be used WITHOUT ANY WARRANTIES on your own risk.
//
// For the latest updates to this library, check my site:
// http://welcome.to/bcgsoft
// 
// Stas Levin <bcgsoft@yahoo.com>
//*******************************************************************************

#ifndef __BCGCB_H
#define __BCGCB_H

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#ifndef __AFXTEMPL_H__
#include <afxtempl.h>
#endif

#include "bcgcbver.h"	// Library version info.

#ifdef _BCGCB_IN_OTHER_DLL
BCGCONTROLBARDLLEXPORT void BCGControlBarDllInitialize ();	// By Guy Hachlili
#endif // _BCGCB_IN_OTHER_DLL

#if defined _AFXDLL && !defined _BCGCONTROLBAR_STATIC_
	//------------------------------------------
	// MFC shared DLL, BCGControlBar shared DLL
	//------------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474UD.lib") 
			#pragma message("Automatically linking with BCGCB474UD.dll")
		#else
			#pragma comment(lib,"BCGCB474d.lib") 
			#pragma message("Automatically linking with BCGCB474d.dll")
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474U.lib") 
			#pragma message("Automatically linking with BCGCB474U.dll") 
		#else
			#pragma comment(lib,"BCGCB474.lib") 
			#pragma message("Automatically linking with BCGCB474.dll") 
		#endif
	#endif
#elif defined _BCGCONTROLBAR_STATIC_
	//---------------------------------------------
	// MFC shared DLL, BCGControlBar static library
	//---------------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474Staticuds.lib") 
			#pragma message("Automatically linking with BCGCB474Staticuds.lib") 
		#else
			#pragma comment(lib,"BCGCB474Staticds.lib") 
			#pragma message("Automatically linking with BCGCB474Staticds.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474Staticus.lib") 
			#pragma message("Automatically linking with BCGCB474Staticus.lib") 
		#else
			#pragma comment(lib,"BCGCB474Statics.lib") 
			#pragma message("Automatically linking with BCGCB474Statics.lib") 
		#endif
	#endif
#else
	//--------------------------------------------------
	// MFC static library, BCGControlBar static library
	//--------------------------------------------------
	#ifdef _DEBUG
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474Staticud.lib") 
			#pragma message("Automatically linking with BCGCB474Staticud.lib") 
		#else
			#pragma comment(lib,"BCGCB474Staticd.lib") 
			#pragma message("Automatically linking with BCGCB474Staticd.lib") 
		#endif
	#else
		#ifdef _UNICODE
			#pragma comment(lib,"BCGCB474StaticU.lib") 
			#pragma message("Automatically linking with BCGCB474StaticU.lib") 
		#else
			#pragma comment(lib,"BCGCB474Static.lib") 
			#pragma message("Automatically linking with BCGCB474Static.lib") 
		#endif
	#endif
#endif

//------------------
// BCG control bars:
//------------------
#include "BCGToolBar.h"
#include "BCGMenuBar.h"
#include "BCGDialogBar.h"
#include "BCGOutlookBar.h"
#include "BCGColorBar.h"

//-------------------------
// BCG control bar buttons:
//-------------------------
#include "BCGToolbarButton.h"
#include "BCGToolbarComboBoxButton.h"
#include "BCGToolbarDateTimeCtrl.h"
#include "BCGToolbarMenuButton.h"
#include "BCGToolbarRegularMenuButton.h"
#include "BCGToolbarEditBoxButton.h"
#include "BCGDropDown.h"
#include "BCGColorMenuButton.h"

//----------------------------------------------------------------------
// BCG frame windows (replaces CFrameWnd, CMDIFrameWnd, CMDIChildWnd and
// COleIPFrameWnd):
//----------------------------------------------------------------------
#include "BCGFrameWnd.h"
#include "BCGMDIFrameWnd.h"
#include "BCGMDIChildWnd.h"
#include "BCGOleIPFrameWnd.h"

//-------------------------
// BCG customization stuff:
//-------------------------
#include "CBCGToolbarCustomize.h"

#include "BCGContextMenuManager.h"
#include "BCGKeyboardManager.h"
#include "BCGMouseManager.h"

#include "BCGUserTool.h"
#include "KeyHelper.h"

//-----------------------
// BCG workspace manager
//-----------------------
#include "BCGWorkspace.h"
#include "BCGRegistry.h"
#include "RebarState.h"

//-----------------------
// BCG menu replacements:
//-----------------------
#include "BCGPopupMenu.h"
#include "BCGPopupMenuBar.h"
#include "BCGToolBarImages.h"

//------------------
// BCG docking bars:
//------------------
#include "BCGSizingControlBar.h"
#include "BCGTabWnd.h"

//--------------
// BCG controls:
//--------------
#include "BCGButton.h"
#include "BCGColorButton.h"
#include "BCGMenuButton.h"
#include "BCGURLLinkButton.h"
#include "BCGEditListBox.h"
#include "BCGAnimCtrl.h"
#include "PowerColorPicker.h"

//-------------
// BCG dialogs:
//-------------
#include "BCGDialog.h"
#include "BCGFileDialog.h"
#include "BCGWindowsManagerDlg.h"
#include "BCGPrintPreviewView.h"
#include "ImageEditDlg.h"
#include "BCGColorDialog.h"
#include "BCGKeyMapDlg.h"

#endif // __BCGCB_H
