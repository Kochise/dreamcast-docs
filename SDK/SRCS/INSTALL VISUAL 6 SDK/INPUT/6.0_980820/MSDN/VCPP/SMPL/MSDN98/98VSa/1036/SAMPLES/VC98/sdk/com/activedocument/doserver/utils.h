/**************************************************************************
   THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
   ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
   PARTICULAR PURPOSE.

   Copyright 1997 Microsoft Corporation.  All Rights Reserved.
**************************************************************************/

/**************************************************************************

   File:          Utils.h
   
   Description:   Utility definitions.

**************************************************************************/

/**************************************************************************
   function prototypes
**************************************************************************/

STDAPI_(void) ParseCommandLine(LPSTR, LPBOOL, LPTSTR);
static LPTSTR GetWord(LPTSTR, LPTSTR);
STDAPI GetOleObjectDataHere(LPPERSISTSTORAGE, LPFORMATETC, LPSTGMEDIUM);

/**************************************************************************
   global variables
**************************************************************************/

#define EMBEDDINGFLAG TEXT("Embedding")

