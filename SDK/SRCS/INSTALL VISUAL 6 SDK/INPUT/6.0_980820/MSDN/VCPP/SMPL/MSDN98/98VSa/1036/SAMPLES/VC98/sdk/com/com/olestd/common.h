/*
 * COMMON.H
 *
 * Structures and definitions applicable to all OLE 2.0 UI dialogs.
 *
 * Copyright (c)1992-1996 Microsoft Corporation, All Right Reserved
 */


#ifndef _COMMON_H_
#define _COMMON_H_

#include "ansiapi.h"

//Structure for label and source extraction from a metafile
typedef struct tagLABELEXTRACT
   {
   LPOLESTR    lpsz;
   UINT        Index;      // index in lpsz (so we can retrieve 2+ lines)
   DWORD       PrevIndex;  // index of last line (so we can mimic word wrap)

   union
      {
      UINT    cch;        //Length of label for label extraction
      UINT    iIcon;      //Index of icon in source extraction.
      } u;

   //For internal use in enum procs
   BOOL        fFoundIconOnly;
   BOOL        fFoundSource;
   BOOL        fFoundIndex;
   } LABELEXTRACT, FAR * LPLABELEXTRACT;


//Structure for extracting icons from a metafile (CreateIcon parameters)
typedef struct tagICONEXTRACT
   {
   HICON       hIcon;          //Icon created in the enumeration proc.

   /*
    * Since we want to handle multitasking well we have the caller
    * of the enumeration proc instantiate these variables instead of
    * using statics in the enum proc (which would be bad).
    */
   BOOL        fAND;
   HGLOBAL     hMemAND;        //Enumeration proc allocates and copies
   } ICONEXTRACT, FAR * LPICONEXTRACT;


//Structure to use to pass info to EnumMetafileDraw
typedef struct tagDRAWINFO
   {
   RECT     Rect;
   BOOL     fIconOnly;
   } DRAWINFO, FAR * LPDRAWINFO;

int CALLBACK EXPORT EnumMetafileIconDraw(HDC, HANDLETABLE FAR *, METARECORD FAR *, int, LPARAM);
int CALLBACK EXPORT EnumMetafileExtractLabel(HDC, HANDLETABLE FAR *, METARECORD FAR *, int, LPLABELEXTRACT);
int CALLBACK EXPORT EnumMetafileExtractIcon(HDC, HANDLETABLE FAR *, METARECORD FAR *, int, LPICONEXTRACT);
int CALLBACK EXPORT EnumMetafileExtractIconSource(HDC, HANDLETABLE FAR *, METARECORD FAR *, int, LPLABELEXTRACT);

//Shared globals:  our instance and clipboard formats used by the PasteSpecial dialog

extern HINSTANCE  ghInst;

extern UINT       cfObjectDescriptor;
extern UINT       cfLinkSrcDescriptor;
extern UINT       cfEmbedSource;
extern UINT       cfEmbeddedObject;
extern UINT       cfLinkSource;
extern UINT       cfOwnerLink;
extern UINT       cfFileName;

#endif //_COMMON_H_
