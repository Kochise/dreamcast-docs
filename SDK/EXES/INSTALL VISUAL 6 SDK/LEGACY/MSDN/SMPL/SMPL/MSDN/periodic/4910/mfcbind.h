// mfcbind.h : utility definitions and functions for DocObject
//		Support for MFC
//
// This is a part of the Microsoft Foundation Classes C++ library.
// Copyright (C) 1992-1995 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the
// Microsoft Foundation Classes Reference and related
// electronic documentation provided with the library.
// See these sources for detailed information regarding the
// Microsoft Foundation Classes product.

#ifndef __MFCBIND_H__
   #define __MFCBIND_H__

// Resource Definitions
//#include "resource.h"

// Utility Functions
void MfcBinderUpdateRegistry(const CDocTemplate* pDocTemplate,
                           OLE_APPTYPE nAppType = OAT_INPLACE_SERVER,
                           LPCTSTR* rglpszRegister = NULL,
                           LPCTSTR* rglpszOverwrite = NULL);

HMENU MfcBinderMergeMenus(CMenu* pMenuShared, CMenu* pMenuSource,
                        LONG* lpMenuWidths, int iWidthIndex);
void  MfcBinderUnmergeMenus(CMenu* pMenuShared, CMenu* pMenuSource, 
                          CMenu* pMenuHelpPopup);

#endif // #ifndef __MFCBIND_H__

