/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Tools.h
   
   Description:   

**************************************************************************/

/**************************************************************************
   #include statements
**************************************************************************/

#include "resource.h"

/**************************************************************************
   structure definitions
**************************************************************************/

typedef struct
   {
   int   idCommand;
   int   iImage;
   int   idButtonString;
   int   idMenuString;
   int   nStringOffset;
   BYTE  bState;
   BYTE  bStyle;
   }MYTOOLINFO, *LPMYTOOLINFO;

extern MYTOOLINFO g_Tools[];
