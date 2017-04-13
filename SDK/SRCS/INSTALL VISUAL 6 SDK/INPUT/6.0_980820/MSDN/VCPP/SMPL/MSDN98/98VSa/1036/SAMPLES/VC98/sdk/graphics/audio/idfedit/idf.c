//************************************************************************
//**
//**  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
//**  ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED
//**  TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR
//**  A PARTICULAR PURPOSE.
//**
//**  Copyright (C) 1993 - 1997 Microsoft Corporation. All Rights Reserved.
//**
//**  idf.c
//**
//**  DESCRIPTION:
//**    main worker code for IDF editing
//**
//************************************************************************

#include <windows.h>
#include <windowsx.h>
#include <mmsystem.h>

#include "idfedit.h"

#include <commdlg.h>
#include "drawstr.h"

VOID FreeIDFFile (LPIDFHEAD);


/*+ PromptForIDFName();
 *
 *
 *  DESCRIPTION:
 *     This function is a wrapper for the Get[Open/Save]FileName commdlg
 *     chooser dialogs. Based on the fuFlags argument, this function
 *     will display the appropriate chooser dialog and return the result.
 *
 *  ARGUMENTS:
 *     HWND    hwnd          - Handle to parent window.
 *     LPSTR   lpszPath      - Pointer to the buffer to receive the
 *                             the file path.
 *     LPSTR   lpszTitle     - Pointer to the buffer to receive the
 *                             file the file title, NULL if no title
 *                             is wanted.
 *     BOOL     fSave        - TRUE if we are to save a file,
 *                             FALSE if we are to open the file.
 *
 *  RETURNS:
 *     BOOL  -  TRUE if a file was chosen. FALSE if the user canceled
 *              the operation.
 *
 *-=======================================================================*/

BOOL WINAPI PromptForIDFName (
    HWND    hwnd,
    LPTSTR  lpszPath,
    LPTSTR  lpszTitle,
    BOOL    fSave)
{
   OPENFILENAME   ofn;
   TCHAR          szExtDefault[4];
   TCHAR          szExtFilter[256];
   LPTSTR         pstr;
   BOOL           bRet;

   //  Get the extension filter and default extension.
   //
   LoadString (hInst, IDS_OFN_EXT_DEF, szExtDefault, NUMELMS(szExtDefault));
   LoadString (hInst, IDS_OFN_EXT_FILTER, szExtFilter, NUMELMS(szExtFilter));

   // Parse the bang out of the filter string, replace with a NULL.
   //
   for (pstr = szExtFilter; *pstr; pstr = AnsiNext(pstr))
      if (TEXT('!') == *pstr)
         *pstr = 0;

   // set the default path to *.ext
   //
   lpszPath[0] = TEXT('*');
   if (szExtDefault[0])
      {
      lpszPath[1] = TEXT('.');
      lstrcpy (lpszPath+2, szExtDefault);
      }


   // If there is a title then reset it also.
   //
   if (lpszTitle)
      lpszTitle[0] = 0;

   //  Initialize the OPENFILENAME structure elements.
   //
   ZeroMemory(&ofn, sizeof(ofn));
   ofn.lStructSize    = sizeof(OPENFILENAME);
   ofn.hwndOwner      = hwnd;
   ofn.lpstrFilter    = szExtFilter;
   ofn.nFilterIndex   = 1;
   ofn.lpstrFile      = lpszPath;
   ofn.nMaxFile       = MAX_PATH;
   ofn.lpstrFileTitle = lpszTitle;
   ofn.nMaxFileTitle  = lpszTitle ? MAX_PATH : 0;
   ofn.lpstrDefExt    = szExtDefault;

   //  If the fSave is TRUE, then call GetSaveFileName()
   //  otherwise call GetOpenFileName().
   //
   if (fSave)
      {
      // Set the OPENFILENAME flags to save and prompt if we
      // will overwrite an existing file.
      //
      ofn.Flags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;
      bRet = GetSaveFileName(&ofn);
      }
   else
      {
      // Set the OPENFILENAME flags to open and the file 
      // must exist if we are opening.
      //
      ofn.Flags = OFN_HIDEREADONLY | OFN_FILEMUSTEXIST;
      bRet = GetOpenFileName(&ofn);
      }

   return bRet;
}

STATICFN UINT fnMapLabel (
   LPTSTR    psz,
   UINT      cch,
   UINT      uDummy,
   UINT      uIndex,
   UINT      uMsgID)
{
   UINT   lRet = 0;

   switch (uMsgID)
   {
      case WM_GETTEXT:
         lstrcpy (psz, "  0   1   2   3   4   5   6   7   8   9");
         lRet = lstrlen (psz);
         break;
   }

   return lRet;
}

#define BLANK_LINE "", 0,0,AS_HEX,0,0

// 0
//
#undef STDFLD
#define STDFLD(fld) FLD(INSTRUMENT,fld)
static DSFIELD aINSTRUMENTfields[] = {
    "IDF Version", STDFLD(dwVersion),            AS_HEX | IS_EDIT, 0, 0,
    "IDF Creator", STDFLD(dwCreator),            AS_HEX | IS_EDIT, 0, 0,
//  "Instrument Identifier",  STDFLD(szInstID),             AS_SZ | IS_EDIT,  0, 0,

    BLANK_LINE,
    "Manufacturer ID",      STDFLD(dwManufactID),         AS_INT | IS_EDIT, 0, 0,
    "Product ID",           STDFLD(dwProductID),          AS_INT | IS_EDIT, 0, 0,
    "Product Rev.",         STDFLD(dwRevision),           AS_INT | IS_EDIT, 0, 0,
    "Manufacturer",         STDFLD(szManufact),           AS_SZ | IS_EDIT, 0, 0,
    "Product Name",         STDFLD(szProduct),            AS_SZ | IS_EDIT, 0, 0,

    BLANK_LINE,
    "Supports General MIDI",   STDFLD(dwFlags), AS_BITFIELD | IS_EDIT, 0, 0,
    "Supports SysEx Messages", STDFLD(dwFlags), AS_BITFIELD | IS_EDIT, 1, 0,
    "Basic Channel",           STDFLD(dwBasicChannel),       AS_INT | IS_EDIT, 0, 0,
    "Number of Channels",      STDFLD(nChannels),            AS_INT | IS_EDIT, 0, 0,
    "Instrument Polyphony",    STDFLD(nInstrumentPolyphony), AS_INT | IS_EDIT, 0, 0,
    "Channel Polyphony",       STDFLD(nChannelPolyphony),    AS_INT | IS_EDIT, 0, 0,

    // pmap fields
    //
    BLANK_LINE,
    "Patch Map",       0, 0, AS_XMODE, (DWORD)fnMapLabel, 0,
    " %02d",           FIELDOFF(INSTRUMENT,aPatch), 10, AS_BYTES | IS_EDIT | AS_ARRAY, 0, 12,
    " 12",             FIELDOFF(INSTRUMENT,aPatch) + 120, 8, AS_BYTES | IS_EDIT, 0, 0,

    // key fields
    //
    BLANK_LINE,
    "General Key Map", 0, 0,  AS_XMODE, (DWORD)fnMapLabel, 0,
    " %02d",           FIELDOFF(INSTRUMENT,aGenKeymap), 10, AS_BYTES | IS_EDIT | AS_ARRAY, 0, 12,
    " 12",             FIELDOFF(INSTRUMENT,aGenKeymap) + 120, 8, AS_BYTES | IS_EDIT, 0, 0,

    BLANK_LINE,
    "Drum Key Map",    0, 0,  AS_XMODE, (DWORD)fnMapLabel, 0,
    " %02d",           FIELDOFF(INSTRUMENT,aDrumKeymap), 10, AS_BYTES | IS_EDIT | AS_ARRAY, 0, 12,
    " 12",             FIELDOFF(INSTRUMENT,aDrumKeymap) + 120, 8, AS_BYTES | IS_EDIT, 0, 0,

    // chnl fields
    //
    BLANK_LINE,
    "Channel %2d",     FIELDOFF(INSTRUMENT,aChannel), 0, AS_ARRAY | AS_STRUCT, 1, 16,
    // CHANNEL aChannel[MAX_CHANNEL];

    NULL, (UINT)-1, 0, AS_NONE, 0, 0,
    };

#include <stdlib.h>

STATICFN UINT AsciiToBytes (
   LPDWORD lpv,
   UINT    cb,
   LPTSTR  psz)
   {
   UINT   jj;

   for (jj = 0; ; ++jj)
      {
      ULONG uu;
      LPTSTR pszStop;
      while (*psz == '\t' || *psz == ' ')
         ++psz;

      pszStop = psz;
      uu = strtoul (psz, &pszStop, 16);
      if (pszStop == psz)
         break;

      if (jj < cb/sizeof(*lpv))
         lpv[jj] = uu;

      psz = pszStop;
      }

   return jj * sizeof(*lpv);
   }

STATICFN VOID BytesToAscii (
   LPTSTR  psz,
   UINT    cch,
   LPDWORD lpv,
   UINT    cbData)
{
   UINT jj;
   UINT cb;

   for (jj = 0; jj < (cbData+sizeof(*lpv)-1)/sizeof(*lpv); ++jj)
      {
      wsprintf (psz, "%08lX ", lpv[jj]);
      cch -= (cb = lstrlen(psz));
      psz += cb;
      *psz = 0;
      if (cch < cb + 4)
         {
         *psz++ = '.';
         *psz++ = '.';
         *psz++ = '.';
         *psz++ = 0;
         break;
         } 
      }
}   

const TCHAR cszNone[] = "<none>";

STATICFN UINT fnChanData (
   LPTSTR    psz,
   UINT      cch,
   LPCHANNEL pChan,
   UINT      uIndex,
   UINT      uMsgID)
{
   LPDWORD lpvData = pChan->lpInit;
   UINT    cbData  = pChan->cbInit;
   UINT    lRet = 0;

   switch (uMsgID)
   {
      case WM_GETTEXT:
         if (!lpvData || !cbData)
            lstrcpy (psz, cszNone);
         else
            BytesToAscii (psz, cch, lpvData, cbData);
         lRet = lstrlen (psz);
         break;

      case WM_SETTEXT:
         {
         UINT uu;

         // if we dont have a writable pointer to sysex data,
         // we must allocate an editable one before we go further.
         //
         if (IsBadWritePtr (lpvData,1))
            cbData = 0;

         // if the data is not the string <none>
         // parse it as HEX data and use that to set the sysex
         // data.  if it is <none> remove the sysex data.
         //
         if (!psz || ! lstrcmpi(psz, cszNone))
            uu = 0;
         else
            uu = AsciiToBytes (lpvData, cbData, psz);

         // if there was more data than would fit in the current
         // sysex buffer. allocate a new buffer and try again
         //
         if (uu > cbData)
            {
            if (cbData && lpvData)
               HeapFree (gs.idf.hEditHeap, 0, lpvData);

            lpvData = HeapAlloc (gs.idf.hEditHeap, 0, uu);
            AsciiToBytes (lpvData, uu, psz);
            }

         // update pChan pointers to reflect the new sysex data
         //
         pChan->lpInit = lpvData;
         pChan->cbInit = uu;
         }
         break;

      case WM_COPY:
         {
         HGLOBAL hMem = GlobalAlloc (GHND, 4 + cbData * 3);
         if (!(psz = GlobalLock (hMem)))
            break;

         // put the sysex data on the clipboard as ASCII
         //
         BytesToAscii (psz, 4 + cbData * 3, lpvData, cbData);
         GlobalUnlock (hMem);
         if (!OpenClipboard (hWndMain))
            GlobalFree (hMem);
         else
            {
            EmptyClipboard ();
            SetClipboardData (CF_TEXT, hMem);
            CloseClipboard ();
            lRet = 1;
            }
         }
         break;

      case WM_PASTE:
         {
         HGLOBAL hMem;

         // grap text from the clipboard and use it as the sysex data
         // however, ignore the data if it's not valid hex data
         //
         if (!OpenClipboard (hWndMain))
            break;
         if (hMem = GetClipboardData (CF_TEXT))
            {
            if (psz = GlobalLock (hMem))
               {
               fnChanData (psz, GlobalSize(hMem), pChan, uIndex, WM_SETTEXT);
               GlobalUnlock (hMem);
               lRet = 1;
               }
            }
         CloseClipboard ();
         }
         break;
   }

   return lRet;
}

// 0
//
#undef STDFLD
#define STDFLD(fld) #fld, FLD(CHANNEL,fld)
static DSFIELD aCHANNELfields[] = {
    "Mute This Channel", FLD(CHANNEL,iFlags), AS_BITFIELD | IS_EDIT, 1, 0,
    "Is Drum Channel",   FLD(CHANNEL,iFlags), AS_BITFIELD | IS_EDIT, 0, 0,
    //"Init Data",  0, sizeof(CHANNEL), AS_XMODE | IS_EDIT, (DWORD)fnChanData, 0,
    NULL, (UINT)-1, 0, AS_NONE, 0, 0,
    };

static DSFIELDTBL aStructs[] = {
    aINSTRUMENTfields,   "INSTRUMENT", sizeof(INSTRUMENT),
    aCHANNELfields,      "CHANNEL",    sizeof(CHANNEL),
    };


/*+ FindListChunk
 *
 *-======================================================================*/

LPRIFF FindListChunk (
   LPRIFFLIST pList,
   DWORD      fccToFind)
{
   UINT   cbRemain;
   LPRIFF pRiff;

   // in this code, we expect to have only MMAP lists
   //
   assert (pList);
   assert (pList->cbList > sizeof(RIFF) + sizeof(DWORD));
   assert (pList->fccType == FCC_MMAP);

   cbRemain = pList->cbList - sizeof(DWORD);
   assert (cbRemain < 0x10000); // reasonableness check

   // scan for the requested chunk
   //
   pRiff = (LPRIFF)(pList+1);
   for (;;)
      {
      UINT cbAdvance = pRiff->cb + (pRiff->cb & 1) + sizeof(RIFF);
      if (pRiff->fcc == fccToFind)
         return pRiff;
      if (cbRemain <= cbAdvance)
         break;

      cbRemain -= cbAdvance;
      pRiff = NEXTRIFF(pRiff);
      }

   return NULL;
}

/*+ 
 *
 *-======================================================================*/

LPVOID CopyForEditing (
   LPVOID pData, 
   UINT   cbData)
{
   LPVOID pDataT;

   pDataT = HeapAlloc (gs.idf.hEditHeap, 0, cbData);
   if (pDataT)
      CopyMemory (pDataT, pData, cbData);
   return pDataT;
}   

/*+ 
 *
 *-======================================================================*/

void FreeInstrumEdits (
   LPINSTRUMENT pInstrum)
{
   UINT      ii;

   // free anything that has been dynamically allocated for editing
   // purposes.  (currently only sysex channel init data)
   //
   for (ii = 0; ii < NUMELMS(pInstrum->aChannel); ++ii)
      {
      LPCHANNEL pChan = &pInstrum->aChannel[ii];

      // if the pointer is a valid writeable pointer, assume it
      // cam from the edit heap.
      //
      if (pChan->lpInit && !IsBadWritePtr(pChan->lpInit, 1))
         HeapFree (gs.idf.hEditHeap, 0, pChan->lpInit);

      ZeroMemory (pChan, sizeof(*pChan));
      }
}

/*+ IdentityMap
 *
 *-======================================================================*/

STATICFN void _inline IdentityMap (
   LPBYTE abData)
{
   BYTE ii;

   assert (MAX_PATCH == MAX_KEYMAP);

   for (ii = 0; ii < MAX_KEYMAP; ++ii)
      abData[ii] = ii;
}

/*+ IsIdentityMap
 *
 *-======================================================================*/

STATICFN BOOL IsIdentityMap (
   LPBYTE abData)
{
   BYTE ii;

   assert (MAX_PATCH == MAX_KEYMAP);

   for (ii = 0; ii < MAX_KEYMAP; ++ii)
      if (abData[ii] != ii)
         return FALSE;
   return TRUE;
}

/*+ 
 *
 *-======================================================================*/

void CopyInstrumData (
   LPINSTRUMENT pInstrum, 
   LPRIFFLIST   pList)
{
   LPRIFF pRiff;
   UINT   ii;

   #pragma message (SQUAWK "free channel data first?")

   // initialize to defaults for optional fields in the IDF file
   //
   FreeInstrumEdits (pInstrum);
   ZeroMemory (pInstrum, sizeof(*pInstrum));
   IdentityMap (pInstrum->aPatch);
   IdentityMap (pInstrum->aGenKeymap);
   IdentityMap (pInstrum->aDrumKeymap);
   pInstrum->aChannel[9].iFlags = CHANNEL_IS_DRUM;

   assert (pList);
   if (!pList)
      return;

   // is there a header chunk? if so, then
   // copy it's data into the instrum structure
   //
   pRiff = FindListChunk (pList, FCC_hdr);
   if (pRiff && pRiff->cb >= sizeof(IDFHEADER))
      {
      LPIDFHEADER phdr = (LPVOID)(pRiff+1);

      pInstrum->dwVersion = phdr->dwVersion;
      pInstrum->dwCreator = phdr->dwCreator;

      // copy instrument id, and force a NULL terminator
      //
      CopyMemory (pInstrum->szInstID, 
                  phdr->abInstID,
                  max(phdr->cbInstID, NUMELMS(pInstrum->szInstID)));
      pInstrum->szInstID[NUMELMS(pInstrum->szInstID)-1] = 0;
      }


   // manufacturer info
   //
   pRiff = FindListChunk (pList, FCC_inst);
   if (pRiff && pRiff->cb >= sizeof(IDFINSTINFO))
      {
      LPIDFINSTINFO pinst = (LPVOID)(pRiff+1);

      #pragma message (SQUAWK "get tables of manufactures & products")

      pInstrum->dwManufactID = pinst->dwManufactID;
      pInstrum->dwProductID = pinst->dwProductID;
      pInstrum->dwRevision = pinst->dwRevision;

     #ifdef UNICODE
      CopyMemory (pInstrum->szManufact, pinst->abData,
                  max(pinst->cbManufactUNICODE, sizeof(pInstrum->szManufact)));
     #else
      CopyMemory (pInstrum->szManufact, pinst->abData,
                  max(pinst->cbManufactASCII, sizeof(pInstrum->szManufact)));
     #endif
      pInstrum->szManufact[NUMELMS(pInstrum->szManufact)-1] = 0;

     #ifdef UNICODE
      CopyMemory (pInstrum->szProduct, 
                  pinst->abData + pinst->cbManufactASCII + pinst->cbManufactUNICODE, 
                  max(pinst->cbProductUNICODE, sizeof(pInstrum->szProduct)));
     #else
      CopyMemory (pInstrum->szProduct,
                  pinst->abData + pinst->cbManufactASCII + pinst->cbManufactUNICODE, 
                  max(pinst->cbProductASCII, sizeof(pInstrum->szProduct)));
     #endif
      pInstrum->szProduct[NUMELMS(pInstrum->szProduct)-1] = 0;
      }

   // capabilities
   //
   pRiff = FindListChunk (pList, FCC_caps);
   if (pRiff && pRiff->cb >= sizeof(IDFINSTCAPS))
      {
      LPIDFINSTCAPS pcaps = (LPVOID)(pRiff+1);

      pInstrum->dwFlags = pcaps->fdwFlags;
      pInstrum->dwBasicChannel = pcaps->dwBasicChannel;
      pInstrum->nChannels      = pcaps->cNumChannels;
      pInstrum->nInstrumentPolyphony = pcaps->cInstrumentPolyphony;
      pInstrum->nChannelPolyphony = pcaps->cChannelPolyphony;
      }


   // per channel init data
   //
   pRiff = FindListChunk (pList, FCC_chan);
   if (pRiff && pRiff->cb >= sizeof(IDFCHANNELHDR))
      {
      LPIDFCHANNELHDR  pchan = (LPVOID)(pRiff+1);
      LPIDFCHANNELINFO pinfo = (LPVOID)(pchan+1);
      UINT cbRemain = pRiff->cb - sizeof(IDFCHANNELHDR);

      for (ii = 0; ii < NUMELMS(pInstrum->aChannel); ++ii)
      {
         pInstrum->aChannel[ii].iFlags &= ~CHANNEL_IS_MUTE;
         if (pchan->dwDrumMask & (1 << ii))
            pInstrum->aChannel[ii].iFlags |= CHANNEL_IS_DRUM;
         else
         {
            pInstrum->aChannel[ii].iFlags &= ~CHANNEL_IS_DRUM;
            if (!(pchan->dwGeneralMask & (1 << ii)))
               pInstrum->aChannel[ii].iFlags |= CHANNEL_IS_MUTE;
         }
      }


      for (ii = 0; /*ii < pchan->cNumChannels*/ ;++ii)
         {
         if (cbRemain < sizeof(IDFCHANNELINFO) ||
             cbRemain < pinfo->cbStruct)
            break;

         if (pinfo->dwChannel < NUMELMS(pInstrum->aChannel))
            {
            LPCHANNEL pChan = &pInstrum->aChannel[pinfo->dwChannel];
            pChan->cbInit = pinfo->cbInitData;
            pChan->lpInit = (LPVOID)pinfo->abData;
            }

         cbRemain -= pinfo->cbStruct;
         if (cbRemain < sizeof(IDFCHANNELINFO))
            break;

         pinfo = (LPVOID)((LPBYTE)pinfo + pinfo->cbStruct);
         }
      }
   else
      {
      pRiff = FindListChunk (pList, FCC_chnl);
      if (pRiff && pRiff->cb >= sizeof(IDFCHNLHDR))
         {
         LPIDFCHNLHDR pchnl = (LPVOID)(pRiff+1);
         LPIDFCHNLINFO pinfo = (LPVOID)(pchnl+1);
         UINT cbRemain = pRiff->cb;

         if (cbRemain >= sizeof(IDFCHNLHDR) + sizeof(IDFCHNLINFO))
            {
            cbRemain -= sizeof(IDFCHNLHDR);

            for (ii = 0; ii < pchnl->cNumChannels; ++ii)
               {
               if (cbRemain < pinfo->cbStruct)
                  break;

               if (pinfo->dwChannel < NUMELMS(pInstrum->aChannel))
                  {
                  LPCHANNEL pChan = &pInstrum->aChannel[pinfo->dwChannel];

                  // for now, just point channel data at riff data, we'll
                  // copy it when they try to actually edit it.
                  //
                  if (pinfo->fdwChannel & IDFCHNLINFO_F_DRUM_CHANNEL)
                     {
                     pChan->iFlags |= CHANNEL_IS_DRUM;
                     pChan->cbInit = pinfo->cbDrumInitData;
                     pChan->lpInit = (LPVOID)(pinfo->abData + pinfo->cbGeneralInitData);
                     }
                  else
                     {
                     pChan->iFlags &= ~CHANNEL_IS_DRUM;
                     pChan->cbInit = pinfo->cbGeneralInitData;
                     pChan->lpInit = (LPVOID)pinfo->abData;
                     }
                  }

               cbRemain -= pinfo->cbStruct;
               if (cbRemain < sizeof(IDFCHNLINFO))
                  break;

               pinfo = (LPVOID)((LPBYTE)pinfo + pinfo->cbStruct);
               }
            }
         }
      }

   // patch map
   //
   pRiff = FindListChunk (pList, FCC_pmap);
   if (pRiff && pRiff->cb >= sizeof(IDFPATCHMAPHDR))
      {
      LPIDFPATCHMAPHDR ppmap = (LPVOID)(pRiff+1);
      CopyMemory (pInstrum->aPatch, ppmap->abPatchMap, sizeof(pInstrum->aPatch));
      }

   //
   // key map.  we support old style 'key' chunk.  but will override
   // it with the data from a new style 'gkey' & 'dkey' chunk if both
   // are found
   //

   // old style 'key ' chunk
   //
   pRiff = FindListChunk (pList, FCC_key);
   if (pRiff && pRiff->cb >= sizeof(IDFKEYHDR))
      {
      LPIDFKEYHDR pkey = (LPVOID)(pRiff+1);
      LPIDFKEY    pmap = (LPVOID)(pkey+1);
      UINT        nMaps = pkey->cNumKeyMaps;
      UINT        cbRemain = pRiff->cb - sizeof(IDFKEYHDR);

      // copy keymaps as we find them, we only recognize 2 differnent
      // keymap types however.  and we only honor the last instance
      // each type that we find
      //
      while (nMaps > 0 && cbRemain >= sizeof(IDFKEY))
         {
         if (IDFKEY_F_GENERAL_CHANNEL == pmap->fdwKeyMap)
             CopyMemory (pInstrum->aGenKeymap, pmap->abKeyMap, sizeof(pInstrum->aGenKeymap));
         else if (IDFKEY_F_DRUM_CHANNEL == pmap->fdwKeyMap)
             CopyMemory (pInstrum->aDrumKeymap, pmap->abKeyMap, sizeof(pInstrum->aDrumKeymap));
         --nMaps;
         ++pmap;
         cbRemain -= sizeof(IDFKEY);
         }
      }

   // 'gkey' chunk
   //
   pRiff = FindListChunk (pList, FCC_gkey);
   if (pRiff && pRiff->cb >= sizeof(IDFKEYMAP))
      {
      LPIDFKEYMAP pgkey = (LPVOID)(pRiff+1);

      assert (sizeof(pgkey->abKeyMap) == sizeof(pInstrum->aGenKeymap));
      CopyMemory (pInstrum->aGenKeymap, pgkey->abKeyMap, sizeof(pInstrum->aGenKeymap));
      }

   // 'dkey' chunk
   //
   pRiff = FindListChunk (pList, FCC_dkey);
   if (pRiff && pRiff->cb >= sizeof(IDFKEYMAP))
      {
      LPIDFKEYMAP pdkey = (LPVOID)(pRiff+1);

      assert (sizeof(pdkey->abKeyMap) == sizeof(pInstrum->aDrumKeymap));
      CopyMemory (pInstrum->aDrumKeymap, pdkey->abKeyMap, sizeof(pInstrum->aDrumKeymap));
      }
}

/*+ SaveInstrumToRiff
 *
 *-======================================================================*/

VOID SaveInstrumToRiff(
    LPRIFFLIST   pList, 
    LPINSTRUMENT pInstrum)
{
    LPRIFF pRiff = (LPVOID)(pList+1);

    // hdr
    {
    LPIDFHEADER phdr = (LPVOID)(pRiff+1);
    UINT        cb = lstrlen(pInstrum->szInstID) + 1;
    phdr->cbStruct = sizeof(*phdr) + cb;
    phdr->dwVersion = pInstrum->dwVersion;
    phdr->dwCreator = pInstrum->dwCreator;
    phdr->cbInstID = cb;
    lstrcpy (phdr->abInstID, pInstrum->szInstID);
    phdr->abInstID[cb-1] = 0;
    pRiff->fcc = FCC_hdr;
    pRiff->cb = phdr->cbStruct;
    pRiff = NEXTRIFF(pRiff);
    }

    // inst
    //
    {
    LPIDFINSTINFO pinst = (LPVOID)(pRiff+1);
    UINT          cb1 = lstrlen(pInstrum->szManufact)+1;
    UINT          cb2 = lstrlen(pInstrum->szProduct)+1;
    cb1 += (cb1 & 1);
    cb2 += (cb2 & 2);
    pinst->cbStruct = sizeof(*pinst) + (cb1 + cb2) * 3;
    pinst->dwManufactID = pInstrum->dwManufactID;
    pinst->dwProductID = pInstrum->dwProductID;
    pinst->dwRevision = pInstrum->dwRevision;
    pinst->cbManufactASCII = cb1;
    pinst->cbManufactUNICODE = cb1 * 2;
    pinst->cbProductASCII = cb2;
    pinst->cbProductUNICODE = cb2 * 2;
    ZeroMemory (pinst->abData, (cb1 + cb2) * 3);
   #ifdef UNICODE
    #error not yet implemented
   #else
    lstrcpy (pinst->abData, pInstrum->szManufact);
    MultiByteToWideChar(CP_ACP, 0, pInstrum->szManufact, 
                        cb1, (LPWSTR)(pinst->abData + cb1),  cb1);
    lstrcpy (pinst->abData + (cb1 * 3), pInstrum->szProduct);
    MultiByteToWideChar(CP_ACP, 0, pInstrum->szProduct, 
                        cb2, (LPWSTR)(pinst->abData + (cb1 * 3) + cb2), cb2);
   #endif
    pRiff->fcc = FCC_inst;
    pRiff->cb = pinst->cbStruct;
    pRiff = NEXTRIFF(pRiff);
    }

    // caps
    //
    {
    LPIDFINSTCAPS pcaps = (LPVOID)(pRiff+1);
    pcaps->cbStruct = sizeof(*pcaps);
    pcaps->fdwFlags = pInstrum->dwFlags;
    pcaps->dwBasicChannel = pInstrum->dwBasicChannel;
    pcaps->cNumChannels = pInstrum->nChannels;
    pcaps->cInstrumentPolyphony = pInstrum->nInstrumentPolyphony;
    pcaps->cChannelPolyphony = pInstrum->nChannelPolyphony;
    pRiff->fcc = FCC_caps;
    pRiff->cb = pcaps->cbStruct;
    pRiff = NEXTRIFF(pRiff);
    }

    //
    // chan chunk
    //
    {
    LPIDFCHANNELHDR  pchan = (LPVOID)(pRiff+1);
    LPIDFCHANNELINFO pinfo = (LPVOID)(pchan+1);
    UINT cbTotal = 0;
    UINT ii;

    pchan->cbStruct = sizeof(*pchan);
    pchan->dwDrumMask = 0;
    pchan->dwGeneralMask = 0x0000FFFF;
    for (ii = 0; ii < NUMELMS(pInstrum->aChannel); ++ii)
        if (pInstrum->aChannel[ii].iFlags & CHANNEL_IS_MUTE)
            pchan->dwGeneralMask &= ~(1 << ii);
        else if (pInstrum->aChannel[ii].iFlags & CHANNEL_IS_DRUM)
            pchan->dwDrumMask |= (1 << ii);

    pchan->dwGeneralMask &= ~(pchan->dwDrumMask);
    pchan->fdwFlags = 0;

    cbTotal = pchan->cbStruct;

    for (ii = 0; ii < NUMELMS(pInstrum->aChannel); ++ii)
       {
       LPCHANNEL pChan = &pInstrum->aChannel[ii];

       // if we have non-default channel info. append
       // channel info data
       //
       if (pChan->cbInit)
          {
          UINT cbData = (pChan->cbInit + 3) & ~3;

          pinfo->dwChannel = ii;
          pinfo->cbInitData = cbData;
          ZeroMemory (pinfo->abData, cbData);
          CopyMemory (pinfo->abData, pChan->lpInit, pChan->cbInit);

          // advance pinfo to the next channel header
          //
          //++pchan->cNumChannels;
          pinfo->cbStruct = sizeof(*pinfo) + cbData;
          cbTotal += pinfo->cbStruct;
          pinfo = (LPVOID)(((LPBYTE)pinfo) + pinfo->cbStruct);
          }
       }

    // save the chan chunk
    //
    pRiff->fcc = FCC_chan;
    pRiff->cb = cbTotal;
    pRiff = NEXTRIFF(pRiff);
    }

    // pmap
    //
    {
    if (!IsIdentityMap(pInstrum->aPatch))
       {
       LPIDFPATCHMAPHDR ppmap = (LPVOID)(pRiff+1);
       ppmap->cbStruct = sizeof(*ppmap);
       CopyMemory (ppmap->abPatchMap, pInstrum->aPatch, sizeof(ppmap->abPatchMap));
       pRiff->fcc = FCC_pmap;
       pRiff->cb = ppmap->cbStruct;  
       pRiff = NEXTRIFF(pRiff);
       }

    //
    // gkey chunk (general keymap)
    //
    if (!IsIdentityMap(pInstrum->aGenKeymap))
       {
       LPIDFKEYMAP pgkey = (LPVOID)(pRiff+1);
       pgkey->cbStruct = sizeof(*pgkey);
       CopyMemory (pgkey->abKeyMap, pInstrum->aGenKeymap, sizeof(pgkey->abKeyMap));
       pRiff->fcc = FCC_gkey;
       pRiff->cb = sizeof(*pgkey);
       pRiff = NEXTRIFF(pRiff);
       }
    // dkey chunk (drum keymap)
    //
    if (!IsIdentityMap(pInstrum->aDrumKeymap))
       {
       LPIDFKEYMAP pdkey = (LPVOID)(pRiff+1);
       pdkey->cbStruct = sizeof(*pdkey);
       CopyMemory (pdkey->abKeyMap, pInstrum->aDrumKeymap, sizeof(pdkey->abKeyMap));
       pRiff->fcc = FCC_dkey;
       pRiff->cb = sizeof(*pdkey);
       pRiff = NEXTRIFF(pRiff);
       }
    }

    pList->fccList = FCC_LIST;
    pList->cbList = (DWORD)pRiff - (DWORD)pList - sizeof(RIFF);
    pList->fccType = FCC_MMAP;
}

/*+ GetBackupName
 *
 *-======================================================================*/

BOOL GetBackupName (
   LPTSTR pszBak,
   LPTSTR pszName)
{
   LPTSTR psz;
   lstrcpy (pszBak, pszName);
   psz = pszBak + lstrlen(pszBak);
   while (psz > pszBak)
      {
      if (*psz == TEXT(':'))
         break;
      if (*psz == TEXT('\\'))
         break;
      if (*psz == TEXT('.'))
         *psz = 0;

      --psz;
      }
   lstrcat (pszBak, TEXT(".id-"));
   return TRUE;
}

/*+ InstrumMaxRiffDataSize
 *
 *-======================================================================*/

STATICFN UINT InstrumMaxRiffDataSize (
   LPINSTRUMENT pInstrum)
{
   UINT cbData;
   UINT ii;

   cbData = (sizeof(RIFF) * 6)
            + sizeof(IDFHEADER) + MAX_NAME 
            + sizeof(IDFINSTINFO) + (MAX_NAME * 6)
            + sizeof(IDFINSTCAPS)
            + sizeof(IDFCHNLHDR)
            + sizeof(IDFPATCHMAPHDR)
            + sizeof(IDFKEYHDR) + (sizeof(IDFKEY) * 2);

   for (ii = 0; ii < NUMELMS(pInstrum->aChannel); ++ii)
       {
       LPCHANNEL pChan = &pInstrum->aChannel[ii];
       cbData += pChan->cbInit + sizeof(IDFCHNLINFO);
       }
   return cbData;
}

/*+ SaveIDFToFile 
 *
 *-======================================================================*/

BOOL SaveIDFToFile (
   LPIDFHEAD pIDF,
   LPTSTR    pszFileIn)
{
   HANDLE hFile = NULL;
   HANDLE hSection = NULL;
   LPBYTE pBase = NULL;
   TCHAR  szBakName[MAX_PATH];
   LPTSTR pszFile = pszFileIn;
   DWORD  cbFile;
   UINT   ii;
   LPRIFFLIST pList;

   // are we saving to the same name? if so
   // rename the old file to a backup name
   //
   szBakName[0] = 0;
   if (!lstrcmpi(pszFile, pIDF->szFile))
   {
      if (pIDF->bReadOnly)
         return FALSE;

      GetBackupName (szBakName, pszFile);
      pszFile = szBakName;
   }

   // determine necessary file size
   //
   cbFile = sizeof(RIFFLIST) * 2;
   for (ii = 0; ii < pIDF->nInstrum; ++ii)
      {
      cbFile += sizeof(RIFFLIST);
      if (pIDF->ai[ii].pInstrum)
         {
         cbFile += InstrumMaxRiffDataSize (pIDF->ai[ii].pInstrum);
         }
      else if (pIDF->ai[ii].pList)
         {
         cbFile += pIDF->ai[ii].pList->cbList;
         }
      else
         {
         assert (0); // should never get here
         }
      }

   // open a writable mapped file of the size
   // necessary to write the IDF data
   //
   hFile = CreateFile (pszFile,
                       GENERIC_READ | GENERIC_WRITE,
                       FILE_SHARE_READ,
                       NULL, // security
                       OPEN_ALWAYS,
                       FILE_ATTRIBUTE_NORMAL,
                       NULL);
   if (INVALID_HANDLE_VALUE == hFile)
      goto error_exit;

   SetFilePointer (hFile, cbFile, NULL, FILE_BEGIN);
   SetEndOfFile (hFile);

   hSection = CreateFileMapping (hFile, NULL,
                                 PAGE_READWRITE, 0, 0, NULL);
   if (INVALID_HANDLE_VALUE == hSection)
      goto error_exit;

   pBase = MapViewOfFile (hSection, FILE_MAP_ALL_ACCESS, 0, 0, 0);
   if (NULL == pBase)
      goto error_exit;

   // Create RIFF data into the memory mapped file
   //   
   pList = (LPVOID)pBase;
   pList->fccList = FCC_RIFF;
   pList->cbList = 0;
   pList->fccType = FCC_IDF;
   ++pList;
   for (ii = 0; ii < pIDF->nInstrum; ++ii)
      {
      struct _instrum_info * pi = &pIDF->ai[ii];

      pList->cbList = 0;

      if (pi->pInstrum)
         {
         SaveInstrumToRiff(pList, pi->pInstrum);
         }
      else if (pi->pList)
         {   
         CopyMemory (pList, pi->pList, 
                     pi->pList->cbList + sizeof(RIFF));
         }
      else
         {
         assert(0);
         }

      if (pList->cbList > 0)
         pList = (LPVOID) NEXTRIFF(pList);
      }
   cbFile = (DWORD)pList - (DWORD)pBase;
   ((LPRIFF)pBase)->cb = cbFile - sizeof(RIFF);

   UnmapViewOfFile (pBase);
   CloseHandle (hSection);

   SetFilePointer (hFile, cbFile, NULL, FILE_BEGIN);
   SetEndOfFile (hFile);
   CloseHandle (hFile);

   // close the existing file, delete the old file, 
   // rename the new file to the previous filename
   // and open the new file & display contents
   //
   FreeIDFFile (pIDF);
   if (pszFile == szBakName)
      {
      pszFile = pszFileIn;
      DeleteFile (pszFile);
      if ( ! MoveFile (szBakName, pszFile))
         {
         // inexplicable failure copy the back over the origonal,
         // int this case we delete the backup and return failure
         //
         DeleteFile (szBakName);
         return FALSE;
         }
      }

   // return success
   //
   return TRUE;

error_exit:
   if (pBase)
      UnmapViewOfFile (pBase);
   if (hSection && INVALID_HANDLE_VALUE != hSection)
      CloseHandle (hSection);
   if (hFile && INVALID_HANDLE_VALUE != hFile)
      CloseHandle (hFile);
   return FALSE;
}

/*+
 *
 *-======================================================================*/

VOID FreeIDFFile (
   LPIDFHEAD pIDF)
{

   if (pIDF->pFileBase)
      UnmapViewOfFile (pIDF->pFileBase), pIDF->pFileBase = NULL;

   if (pIDF->hSection && INVALID_HANDLE_VALUE != pIDF->hSection)
      CloseHandle (pIDF->hSection), pIDF->hSection = NULL;

   if (pIDF->hFile && INVALID_HANDLE_VALUE != pIDF->hFile)
      CloseHandle (pIDF->hFile), pIDF->hFile = NULL;

   if (gs.idf.hEditHeap)
      HeapDestroy (gs.idf.hEditHeap);
   gs.idf.hEditHeap = HeapCreate (0, 0x1000, 0x100000);

   gs.idf.vi.pTable = aStructs;
   gs.idf.vi.lpData = &gs.idf.instrum;

   pIDF->bChanged = FALSE;
   pIDF->nInstrum = 0;
   pIDF->piSelect = NULL;
   pIDF->pInstrumSelect = NULL;
   ZeroMemory (pIDF->ai, sizeof(pIDF->ai));
   ZeroMemory (&pIDF->instrum, sizeof(pIDF->instrum));

   pIDF->szFile[0] = 0;
}

typedef struct _idffile {
    DWORD fccRIFF;
    DWORD cbRIFF;
    DWORD fccIDF;
    } IDFFILE, * LPIDFFILE;

/*+
 *
 *-======================================================================*/

BOOL LoadIDFFromFile (
   LPIDFHEAD pIDF,
   LPTSTR    pszFile)
{
   LPIDFFILE  pIdfFile;
   LPRIFFLIST pList;
   DWORD      cbRemain;
   UINT       ii;

   if (!pszFile)
      pszFile = pIDF->szFile;

   pIDF->bReadOnly = FALSE;
   pIDF->hFile = CreateFile (pszFile,
                             GENERIC_READ | GENERIC_WRITE,
                             FILE_SHARE_READ,
                             NULL, // security
                             OPEN_EXISTING,
                             FILE_ATTRIBUTE_NORMAL,
                             NULL);
   if (INVALID_HANDLE_VALUE == pIDF->hFile)
   {
      pIDF->bReadOnly = TRUE;
      pIDF->hFile = CreateFile (pszFile,
                                GENERIC_READ,
                                FILE_SHARE_READ,
                                NULL, // security
                                OPEN_EXISTING,
                                FILE_ATTRIBUTE_NORMAL,
                                NULL);

      if (INVALID_HANDLE_VALUE == pIDF->hFile)
         goto error_exit;
   }

   pIDF->hSection = CreateFileMapping (pIDF->hFile, NULL,
                                       PAGE_READONLY, //PAGE_READWRITE,
                                       0, 0, NULL);
   if (INVALID_HANDLE_VALUE == pIDF->hSection)
      goto error_exit;

   pIDF->pFileBase = MapViewOfFile (pIDF->hSection, FILE_MAP_READ, 0, 0, 0);
   if (NULL == pIDF->pFileBase)
      goto error_exit;
   pIDF->cbFile = GetFileSize (pIDF->hFile, NULL);

   // verify that this is indeed a valid IDF file
   //
   pIdfFile = (LPVOID)pIDF->pFileBase;
   if (pIdfFile->fccRIFF != FCC_RIFF ||
       pIdfFile->cbRIFF + sizeof(RIFF) > pIDF->cbFile ||
       pIdfFile->fccIDF != FCC_IDF)
       goto error_exit;

   lstrcpy (pIDF->szFile, pszFile);

   // now parse the IDF file and find the instruments therein
   //
   pList = (LPVOID)(pIdfFile + 1);
   cbRemain = pIdfFile->cbRIFF;

   for (ii = 0;
        pList->fccList == FCC_LIST && (ii < NUMELMS(pIDF->ai));
        ++ii, pList = (LPVOID) NEXTRIFF(pList))
      {
      UINT cbAdvance = pList->cbList + (pList->cbList & 1) + sizeof(RIFF); 
      pIDF->ai[ii].pList = pList;
      pIDF->nInstrum = ii+1;
      if (cbAdvance > cbRemain)
         break;
      cbRemain -= cbAdvance;
      }

   if (pIDF->nInstrum)
      pIDF->piSelect = &pIDF->ai[0];

   pIDF->bChanged = FALSE;

   return TRUE;

error_exit:
  #if defined DEBUG || defined _DEBUG
   {
   TCHAR sz[512];
   lstrcpy (sz, "LoadIDFFromFile failed: ");
   FormatMessage (FORMAT_MESSAGE_IGNORE_INSERTS
                  | FORMAT_MESSAGE_FROM_SYSTEM,
                  0,
                  GetLastError(),
                  0,
                  sz + lstrlen(sz),
                  NUMELMS(sz) - lstrlen(sz),
                  NULL);
   lstrcat (sz, "\r\n");
   OutputDebugString (sz);
   }
  #endif
   FreeIDFFile (pIDF);
   return FALSE;
}

/*+ NewIDFInstrum
 *
 *-======================================================================*/

LPINSTRUMENT WINAPI NewIDFInstrum (
   LPIDFHEAD  pIDF,
   LPRIFFLIST pList, // optional RIFF init data for instrument
   LPSTR      pszInstrument)
{
   static VIEWINIT vi;
   LPINSTRUMENT    lpi;

   if (pIDF->nInstrum >= NUMELMS(pIDF->ai))
      return NULL;

   lpi = HeapAlloc (gs.idf.hEditHeap, HEAP_ZERO_MEMORY, sizeof(INSTRUMENT));
   if (lpi)
      {
      static struct {
          RIFFLIST    list;
          RIFF        rhdr;
          IDFHEADER   hdr;
          RIFF        rcaps;
          IDFINSTCAPS caps;
          }  gmMMAP = { 
              FCC_LIST, sizeof(gmMMAP) - sizeof(RIFF), FCC_MMAP, //list
              FCC_hdr, sizeof(IDFHEADER),           // rhdr
              sizeof(IDFHEADER), 0x100, 1, 1, 0,    // hdr
              FCC_caps, sizeof(IDFINSTCAPS), 
              sizeof(IDFINSTCAPS),          // caps size
              IDFINSTCAPS_F_GENERAL_MIDI,   // caps flags
              1,                            // caps basic channel 
              16,                           // caps num channels 
              16,                           // instrument polyphony
              16,                           // channel polyphony
          };

      // set default instrument data
      //
      if (!pList)
         pList = &gmMMAP.list;
      CopyInstrumData (lpi, pList);

      if (pszInstrument)
         lstrcpyA (lpi->szInstID, pszInstrument);

      pIDF->ai[pIDF->nInstrum].pList = pList;
      pIDF->ai[pIDF->nInstrum].pInstrum = lpi;
      pIDF->piSelect = &pIDF->ai[pIDF->nInstrum];
      ++pIDF->nInstrum;

      pIDF->bChanged = TRUE;
      }

   return lpi;
}

/*+ DeleteInstrum
 *
 *-======================================================================*/

VOID DeleteInstrum (
   LPIDFHEAD pIDF)
{
   UINT ii;

   // figure out which slot in the instrument array
   // is the selected one.
   //
   for (ii = 0; ii < pIDF->nInstrum; ++ii)
      {
      if (pIDF->piSelect == &pIDF->ai[ii])
         {
         struct _instrum_info info;
         assert (pIDF->nInstrum > 0);

         // exchange the selected instrument with the one
         // at the end of the list. then decrement the
         // count of valid instruments.
         //
         info = pIDF->ai[ii];
         pIDF->ai[ii] = pIDF->ai[pIDF->nInstrum-1];
         pIDF->ai[pIDF->nInstrum-1] = info;
         --pIDF->nInstrum;

         pIDF->bChanged = TRUE;
         Head_RefreshTree (pIDF->hWndHead);
         break;
         }
      }               
}

/*+ CopyInstrumToClip
 *
 *-======================================================================*/

VOID CopyInstrumToClip (
   LPIDFHEAD pIDF)
{
   UINT ii;

   for (ii = 0; ii < pIDF->nInstrum; ++ii)
      {
      if (pIDF->piSelect == &pIDF->ai[ii])
         {
         HGLOBAL hMem;
         if (pIDF->piSelect->pInstrum)
            {
            LPRIFFLIST pList;
            UINT   cb = InstrumMaxRiffDataSize (pIDF->piSelect->pInstrum);

            hMem = GlobalAlloc (GHND | GMEM_ZEROINIT, cb);
            if (!(pList = GlobalLock (hMem)))
               return;

            SaveInstrumToRiff (pList, pIDF->piSelect->pInstrum);
            GlobalUnlock (hMem);
            GlobalReAlloc (hMem, pList->cbList + sizeof(RIFF), 0);
            }
         else if (pIDF->piSelect->pList)
            {
            LPBYTE lpv;
            UINT   cb = pIDF->piSelect->pList->cbList + sizeof(RIFF);
            hMem = GlobalAlloc (GHND, cb);
            if (!(lpv = GlobalLock (hMem)))
               return;
            CopyMemory (lpv, pIDF->piSelect->pList, cb);
            GlobalUnlock (hMem);
            }

         if (!OpenClipboard (hWndMain))
            GlobalFree (hMem);
         else
            {
            EmptyClipboard ();
            SetClipboardData (CF_RIFF, hMem);
            CloseClipboard ();
            }
         }
      }               
}

/*+ PasteInstrum
 *
 *-======================================================================*/

VOID PasteInstrum (
   LPIDFHEAD pIDF)
{
   HGLOBAL      hMem;
   LPRIFFLIST   pList;

   if (!OpenClipboard(hWndMain))
      return;

   if (hMem = GetClipboardData(CF_RIFF))
      {
      if (pList = GlobalLock (hMem))
         {
         if (pList->fccList == FCC_LIST && pList->fccType == FCC_MMAP)
            {
            NewIDFInstrum (pIDF, pList, NULL);
            Head_RefreshTree (pIDF->hWndHead);
            }
         GlobalUnlock (hMem);
         }
      }

   CloseClipboard ();

   return;
}
