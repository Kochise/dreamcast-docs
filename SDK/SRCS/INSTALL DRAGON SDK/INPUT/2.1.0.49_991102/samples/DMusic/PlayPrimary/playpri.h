//-----------------------------------------------------------------------------
// File: PlayPri.h
//
// Desc: Header file for for DirectMusic sample
//
//
// Copyright (c) 1998 Microsoft Corporation. All rights reserved.
//-----------------------------------------------------------------------------

#ifndef PLAY_PRI_H
#define PLAY_PRI_H

//-----------------------------------------------------------------------------
// External function-prototypes
//-----------------------------------------------------------------------------
HRESULT InitDirectMusic(LPTSTR pszPath);
HRESULT FreeDirectMusic();
HRESULT PlaySegment(LPTSTR pszSegment, int nRepeats);
void RetailOutput(TCHAR *tszErr, ...);

#endif // !defined(PLAY_PRI_H)
