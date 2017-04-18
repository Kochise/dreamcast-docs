//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  globals.h
//**
//**  DESCRIPTION:
//**
//**
//**  HISTORY:
//**     04/22/93       created.
//**
//************************************************************************

#ifndef GLOBALS_H
#define GLOBALS_H

#include "drawstr.h"

#ifndef NUMELMS
 #define NUMELMS(aa) (sizeof(aa)/sizeof((aa)[0]))
#endif

#define FCC_RIFF MAKEFOURCC('R','I','F','F')
#define FCC_LIST MAKEFOURCC('L','I','S','T')
#define FCC_IDF  MAKEFOURCC('I','D','F',' ')
#define FCC_MMAP MAKEFOURCC('M','M','A','P')

#define FCC_hdr  MAKEFOURCC('h','d','r',' ')
#define FCC_inst MAKEFOURCC('i','n','s','t')
#define FCC_caps MAKEFOURCC('c','a','p','s')
#define FCC_chan MAKEFOURCC('c','h','a','n')
#define FCC_pmap MAKEFOURCC('p','m','a','p')
#define FCC_gkey MAKEFOURCC('g','k','e','y')
#define FCC_dkey MAKEFOURCC('d','k','e','y')

#define FCC_key  MAKEFOURCC('k','e','y',' ')
#define FCC_chnl MAKEFOURCC('c','h','n','l')

typedef struct _riff {
    DWORD fcc;
    DWORD cb;
    } RIFF, * LPRIFF;

typedef struct _rifflist {
    DWORD fccList;
    DWORD cbList;
    DWORD fccType;
    } RIFFLIST, * LPRIFFLIST;

#define NEXTRIFF(pRiff) ((LPRIFF)((LPBYTE)((LPRIFF)pRiff+1) + ((LPRIFF)pRiff)->cb + (((LPRIFF)pRiff)->cb & 1)))

#define MAX_CHANNEL  16
#define MAX_PATCH    128
#define MAX_KEYMAP   128
#define MAX_NAME     128

// iFlags fields
//
#define CHANNEL_IS_DRUM 1
#define CHANNEL_IS_MUTE 2
typedef struct _channel {
    int     iFlags;
    DWORD   cbInit;
    LPDWORD lpInit;
    } CHANNEL, *LPCHANNEL;

typedef struct _instrument {
    BOOL    bChanged;

    // hdr fields
    //
    DWORD   dwVersion;
    DWORD   dwCreator;
    CHAR    szInstID[MAX_NAME];

    // inst fields
    //  
    DWORD   dwManufactID;
    DWORD   dwProductID;
    DWORD   dwRevision;
    TCHAR   szManufact[MAX_NAME];
    TCHAR   szProduct[MAX_NAME];

    // caps fields
    //
    DWORD   dwFlags;
    DWORD   dwBasicChannel;
    DWORD   nChannels;
    DWORD   nInstrumentPolyphony;
    DWORD   nChannelPolyphony;

    // chnl fields
    //
    CHANNEL aChannel[MAX_CHANNEL];

    // pmap fields
    //
    BYTE    aPatch[MAX_PATCH];

    // key fields
    //
    BYTE    aGenKeymap[MAX_KEYMAP];
    BYTE    aDrumKeymap[MAX_KEYMAP];

    } INSTRUMENT, *LPINSTRUMENT;


typedef struct _idf_header {
   TCHAR  szFile[MAX_PATH];
   BOOL   bChanged;

   HANDLE hEditHeap; // heap used for edit'ed copies of IDF data

   HWND   hWndHead;
   HWND   hWndTree;

   POINT  ptClient;
   SIZE   sClient;
   UINT   cxTree; // width of tree in pixels

   HWND   hWndInstrument;

   BOOL   bReadOnly;
   HANDLE hFile;
   HANDLE hSection;
   LPBYTE pFileBase;
   DWORD  cbFile;

   TCHAR  szTreeLabel[32];
   TCHAR  szViewLabel[32];

   INSTRUMENT instrum; // currently displayed instrument
   VIEWINIT   vi;   // instrument view info
   struct _instrum_info * piSelect; // currently selected instrument
   LPINSTRUMENT pInstrumSelect; // currently selecte instrument data

   UINT   nInstrum;
   struct _instrum_info {
      HWND         hWnd;
      LPINSTRUMENT pInstrum;
      LPRIFFLIST   pList;
      } ai[128];

   } IDFHEAD, *LPIDFHEAD;

struct _globalstate {
   TCHAR        szDefFile[MAX_PATH];
   LPIDFHEAD    pIDF;
   IDFHEAD      idf;
   };

#ifdef DECLARE_VARS
 struct _globalstate gs = {0};
#else
 extern struct _globalstate gs;
#endif

#endif // GLOBALS_H
