/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          DOServer.h
   
   Description:   General defintions for the DOServer project

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include <windows.h>
#include <ole2.h>
#include <docobj.h>
#include "OleDoc.h"
#include "OleDocVw.h"
#include "OleObj.h"
#include "DataObj.h"
#include "OIPObj.h"
#include "OIPAObj.h"
#include "PerStor.h"
#include "PerFile.h"
#include "Utils.h"
#include "Resource.h"

/**************************************************************************
   function prototypes
**************************************************************************/

BOOL CALLBACK MainDlgProc(HWND, UINT, WPARAM, LPARAM);

/**************************************************************************
   global variables
**************************************************************************/

extern HINSTANCE  g_hInst;

#define ARRAYSIZE(a)    (sizeof(a)/sizeof(a[0]))

#define DEFAULT_COLOR   (RGB(128, 0, 0))
#define DEFAULT_X       100
#define DEFAULT_Y       100

#define DEFAULT_PROMPT  (L"*.sdo")
#define FILE_EXT        (TEXT(".sdo"))
#define PROG_ID         (TEXT("Simple.DocObject"))
#define DOC_NAME        (TEXT("Simple Doc Object"))

#define RED_COLOR (RGB(128, 0, 0))
#define GREEN_COLOR (RGB(0, 128, 0))
#define BLUE_COLOR (RGB(0, 0, 128))

// {F0FD0C00-65BA-11d0-B66F-00A0C90348D6}
DEFINE_GUID(   CLSID_SimpleDocObject, 
               0xf0fd0c00, 
               0x65ba, 
               0x11d0, 
               0xb6, 
               0x6f, 
               0x0, 
               0xa0, 
               0xc9, 
               0x3, 
               0x48, 
               0xd6);

