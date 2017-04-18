/*
 *  S M H I N P X P . C
 *
 *  Sample mail handling hook filter importing and exporting.
 *  Copyright 1992-95 Microsoft Corporation.  All Rights Reserved.
 */

#include "_pch.h"
#include <commdlg.h>

extern SPropTagArray sptRule;

#define Align(_cb,_pad)         (((_cb)+((_pad)-1)) & ~((_pad)-1))
#define Align8(_cb)             Align((_cb),8)

#ifdef WIN16
#define SEG(_fp)                HIWORD((DWORD)_fp)
#define OFF(_fp)                LOWORD((DWORD)_fp)
#define PvRelocPv(_p,_bo,_bn)   ((LPVOID)MAKELONG(OFF(_p)-OFF(_bo)+OFF(_bn),SEG(_bn)))
#else
#define PvRelocPv(_p,_bo,_bn)   ((LPVOID)((LPBYTE)(_p)-(LPBYTE)(_bo)+(LPBYTE)(_bn)))
#endif

static const BYTE rgbExportKey[] = { 0x4F, 0x6C, 0x61, 0x66, 0xDE, 0xAD };

/*
 *  Property Flattening -------------------------------------------------------
 */

/*
 *  ScSizeFlattenedProps()
 *  ScFlattenProps()
 *  ScNormalizeFlattenedProps()
 *  
 *  These three functions are similar to the MAPI utility functions
 *  ScCountProps(), ScCopyProps() and ScRelocProps().  SMH uses these
 *  implementations because they are platform independant.  Additionally,
 *  the SMH rule property sets are very simple and do not require support
 *  for complex property types.
 *  
 *  To be platform independent, SMH pads all variable length properties
 *  out to 8 byte aligment.  This ensures that all RISC platforms (MIPS,
 *  ALPHA and PowerPC) will not suffer aligment problems when using the
 *  normalized flattened property values.
 *  
 *  ScSizeFlattenedProps() calculates the size of a buffer required to
 *  flatten the properties in the SPropValue array.
 *  
 *  ScFlattenProps() copies the properties from the source array to the
 *  destination buffer.
 *  
 *  ScNormalizeFlattenedProps() goes through a flattened a property array
 *  and bases all the pointers to a specific value.
 */
SCODE
ScSizeFlattenedProps (UINT cv, LPSPropValue rgval, ULONG FAR * lpcb)
{
    SCODE sc = S_OK;
    ULONG cb = 0;

    for (; cv--; rgval++)
    {
        cb += sizeof(SPropValue);
        switch (PROP_TYPE (rgval->ulPropTag))
        {
          default:
          case PT_UNSPECIFIED:
          case PT_I2:
          case PT_R4:
          case PT_APPTIME:
          case PT_DOUBLE:
          case PT_BOOLEAN:
          case PT_CURRENCY:
          case PT_SYSTIME:
          case PT_I8:
          case PT_OBJECT:
          case PT_CLSID:
          case PT_MV_I2:
          case PT_MV_LONG:
          case PT_MV_R4:
          case PT_MV_APPTIME:
          case PT_MV_DOUBLE:
          case PT_MV_CURRENCY:
          case PT_MV_SYSTIME:
          case PT_MV_CLSID:
          case PT_MV_I8:
          case PT_MV_BINARY:
          case PT_MV_STRING8:
          case PT_MV_UNICODE:

            sc = MAPI_E_UNEXPECTED_TYPE;
            break;
            
          case PT_LONG:
          case PT_ERROR:
          case PT_NULL:

            /*  There is no additional data to include in
             *  the size of the flattened props.
             */
            continue;

          case PT_BINARY:
                
            cb += Align8 (rgval->Value.bin.cb);
            break;

          case PT_STRING8:
                
            cb += Align8 ((lstrlenA (rgval->Value.lpszA ) + 1) * sizeof(CHAR));
            break;

          case PT_UNICODE:
                
            cb += Align8 ((lstrlenW (rgval->Value.lpszW ) + 1) * sizeof(WCHAR));
            break;

        }
        
        if (FAILED (sc))
            break;
    }

    *lpcb = cb;
    DebugTraceSc (ScSizeFlattenedProps(), sc);
    return sc;
}


SCODE
ScFlattenProps (UINT cv, LPSPropValue rgval, LPBYTE lpb)
{
    SCODE sc = S_OK;
    LPSPropValue rgvalDst = (LPSPropValue)lpb;
    ULONG cb;

    /*  Copy over the base properties and setup
     *  a pointer to the block of memory following
     *  the property value array
     */
    memcpy (rgvalDst, rgval, cv * sizeof(SPropValue));
    lpb += cv * sizeof(SPropValue);

    for (; cv--; rgval++, rgvalDst++)
    {
        switch (PROP_TYPE (rgval->ulPropTag))
        {
          default:
          case PT_UNSPECIFIED:
          case PT_I2:
          case PT_R4:
          case PT_APPTIME:
          case PT_DOUBLE:
          case PT_BOOLEAN:
          case PT_CURRENCY:
          case PT_SYSTIME:
          case PT_I8:
          case PT_OBJECT:
          case PT_CLSID:
          case PT_MV_I2:
          case PT_MV_LONG:
          case PT_MV_R4:
          case PT_MV_APPTIME:
          case PT_MV_DOUBLE:
          case PT_MV_CURRENCY:
          case PT_MV_SYSTIME:
          case PT_MV_CLSID:
          case PT_MV_I8:
          case PT_MV_BINARY:
          case PT_MV_STRING8:
          case PT_MV_UNICODE:

            sc = MAPI_E_UNEXPECTED_TYPE;
            break;

          case PT_LONG:
          case PT_ERROR:
          case PT_NULL:

            /*  There is no additional data to flatten for
             *  these types of properties.  All the data is
             *  contained in the SPropValue struct.
             */
            continue;
            
          case PT_BINARY:

            cb = rgval->Value.bin.cb;
            rgvalDst->Value.bin.lpb = lpb;
            memcpy (lpb, rgval->Value.bin.lpb, (UINT)cb);
            break;

          case PT_STRING8:

            cb = lstrlenA (rgval->Value.lpszA) + 1;
            rgvalDst->Value.lpszA = (LPSTR)lpb;
            memcpy (lpb, rgval->Value.lpszA, cb);
            break;

          case PT_UNICODE:
              
            cb = (lstrlenW (rgval->Value.lpszW) + 1) * sizeof(WCHAR);
            rgvalDst->Value.lpszW = (LPWSTR)lpb;
            memcpy (lpb, rgval->Value.lpszW, cb);
            break;
        }

        if (FAILED (sc))
            break;

        /*  Align the size and adjust the data pointer */

        lpb += Align8 (cb);
    }

    DebugTraceSc (ScFlattenProps(), sc);
    return sc;
}


SCODE
ScNormalizeFlattenedProps (UINT cv, LPSPropValue rgval, LPVOID lpvOld, LPVOID lpvNew)
{
    SCODE sc = S_OK;

    for (; cv--; rgval++)
    {
        switch (PROP_TYPE (rgval->ulPropTag))
        {
          default:
          case PT_UNSPECIFIED:
          case PT_I2:
          case PT_R4:
          case PT_APPTIME:
          case PT_DOUBLE:
          case PT_BOOLEAN:
          case PT_CURRENCY:
          case PT_SYSTIME:
          case PT_I8:
          case PT_OBJECT:
          case PT_CLSID:
          case PT_MV_I2:
          case PT_MV_LONG:
          case PT_MV_R4:
          case PT_MV_APPTIME:
          case PT_MV_DOUBLE:
          case PT_MV_CURRENCY:
          case PT_MV_SYSTIME:
          case PT_MV_CLSID:
          case PT_MV_I8:
          case PT_MV_BINARY:
          case PT_MV_STRING8:
          case PT_MV_UNICODE:

            sc = MAPI_E_UNEXPECTED_TYPE;
            break;

          case PT_LONG:
          case PT_ERROR:
          case PT_NULL:

            /*  Nothing to relocate */
              
            continue;

          case PT_BINARY:
              
            rgval->Value.bin.lpb = PvRelocPv (rgval->Value.bin.lpb, lpvOld, lpvNew);
            break;

          case PT_STRING8:

            rgval->Value.lpszA = PvRelocPv (rgval->Value.lpszA, lpvOld, lpvNew);
            break;

          case PT_UNICODE:

            rgval->Value.lpszW = PvRelocPv (rgval->Value.lpszW, lpvOld, lpvNew);
            break;
        }
        
        if (FAILED (sc))
            break;
    }

    DebugTraceSc (ScNormalizeFlattenedProps(), sc);
    return sc;
}


/*
 *  Common Dialog Helper Functions --------------------------------------------
 */

#ifdef  WIN16
#define COMMDLG             "commdlg.dll"
#define GETOPENFILENAME     "GetOpenFileName"
#define GETSAVEFILENAME     "GetSaveFileName"
#else
#define COMMDLG             "comdlg32"
#define GETOPENFILENAME     "GetOpenFileNameA"
#define GETSAVEFILENAME     "GetSaveFileNameA"
#endif
typedef BOOL  (WINAPI COMMDLG_GETOPENFILENAME)(LPOPENFILENAME);
typedef COMMDLG_GETOPENFILENAME FAR * LPCOMMDLG_GETOPENFILENAME;
typedef BOOL  (WINAPI COMMDLG_GETSAVEFILENAME)(LPOPENFILENAME);
typedef COMMDLG_GETSAVEFILENAME FAR * LPCOMMDLG_GETSAVEFILENAME;
   
SCODE
ScSetupCommdlg (HINSTANCE FAR * lplib,
    LPCOMMDLG_GETOPENFILENAME FAR * lppfnOpen,
    LPCOMMDLG_GETSAVEFILENAME FAR * lppfnSave)
{
    HINSTANCE hlib = LoadLibrary (COMMDLG);
    
#ifdef WIN16
    if (hlib < HINSTANCE_ERROR)
        hlib = NULL;
#endif

    if (hlib)
    {       
        *lppfnOpen = (LPCOMMDLG_GETOPENFILENAME)GetProcAddress (hlib, GETOPENFILENAME);
        *lppfnSave = (LPCOMMDLG_GETSAVEFILENAME)GetProcAddress (hlib, GETSAVEFILENAME);
    }

    *lplib = hlib;

    return hlib ? S_OK : MAPI_E_CALL_FAILED;
}


UINT CALLBACK
CommdlgHook (HWND hdlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (msg == WM_INITDIALOG)
    {
        CTL3D_Subclass (lpCtl3D, hdlg, CTL3D_ALL);
        return TRUE;
    }
    
    return FALSE;   
}


/*
 *  Filter Exporting ----------------------------------------------------------
 *  
 *  SMH allows the importing and exporting of its filters.  This is
 *  useful when the user has multiple machines available for use.  Or for
 *  when the user needs to re-create their profile.
 *
 *  ScWriteRule() take the muid of a profile section that contains a
 *  filter and writes the rule out to the passed in file handle.
 *  
 *  ScExportFilters() opens the export file and iterates through the
 *  rules and calls ScWriteRule() for each filter.
 */
SCODE
ScWriteRule (LPSCD lpscd, HFILE hf, LPMAPIUID lpmuid)
{
    SCODE sc = S_OK;
    HRESULT hr;
    LPPROFSECT lpsec = NULL;
    LPSPropValue lpval = NULL;
    LPSPropValue lpvalT = NULL;
    ULONG cb;
    ULONG cval;

    /*  Open the profile section for the rule */

    hr = lpscd->lpadmin->lpVtbl->OpenProfileSection (lpscd->lpadmin,
                                        lpmuid,
                                        NULL,
                                        0,
                                        &lpsec);
    if (!HR_FAILED (hr))
    {
        /*  Get the set of properties describing the rule */

        hr = lpsec->lpVtbl->GetProps (lpsec,
                                (LPSPropTagArray)&sptRule,
                                0,
                                &cval,
                                &lpval);
        if (!HR_FAILED (hr))
        {
            /*  When exporting, we do not want to
             *  export the values for store-based
             *  entryid's.  These can be profile
             *  specific.
             */
            lpval[ipRLEid].ulPropTag = PR_NULL;
            lpval[ipRLSEid].ulPropTag = PR_NULL;

            /*  Flatten the remaining property set and
             *  write them out to the export file
             */
            sc = ScSizeFlattenedProps (cval, lpval, &cb);
            if (!FAILED (sc))
            {
                sc = (*lpscd->lpfnAlloc) (cb, &lpvalT);
                if (!FAILED (sc))
                {
                    sc = ScFlattenProps (cval, lpval, (LPBYTE)lpvalT);
                    if (!FAILED (sc))
                    {
                        sc = ScNormalizeFlattenedProps (cval, lpvalT, lpvalT, 0);
                        if (!FAILED (sc))
                        {
                            /*  We have the flattened props, so
                             *  write them out.
                             */
                            _lwrite (hf, (LPBYTE)&cb, sizeof(ULONG));
                            _lwrite (hf, (LPBYTE)lpvalT, (UINT)cb);
                        }
                    }
                }
            }
        }
    }
    if (HR_FAILED (hr))
        sc = GetScode (sc);
    
    (*lpscd->lpfnFree) (lpvalT);
    (*lpscd->lpfnFree) (lpval);
    UlRelease (lpsec);
    
    DebugTraceSc (ScWriteRule(), sc);
    return sc;
}


SCODE
ScExportFilters (LPSCD lpscd, HWND hwnd)
{
    SCODE sc = S_OK;
    CHAR rgch[MAX_PATH];
    HFILE hf;
    HINSTANCE hlib = NULL;
    LPCOMMDLG_GETOPENFILENAME lpfnOpen;
    LPCOMMDLG_GETSAVEFILENAME lpfnSave;
    OFSTRUCT ob;
    OPENFILENAME ofn = {sizeof(OPENFILENAME)};
    UINT irl;
    UINT ofFlags = OF_READWRITE | OF_SHARE_EXCLUSIVE | OF_CREATE;

    /*  Setup the commdlg structures */
    
    lstrcpy (rgch, "smh.mrl");
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Filter Export Files (*.mrl)\0*.mrl\0";
    ofn.lpstrFile = rgch;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = "Create Filter Export File";
    ofn.lpstrDefExt = "MRL";
    ofn.hInstance = lpscd->hinst;
    ofn.lCustData = 0;
    ofn.lpfnHook = (LPOFNHOOKPROC)CommdlgHook;
    ofn.Flags = OFN_PATHMUSTEXIST       |
                OFN_HIDEREADONLY        |
                OFN_NOCHANGEDIR         |
                OFN_ENABLEHOOK          |
                OFN_OVERWRITEPROMPT;

    if (FWin4Shell ())
        ofn.Flags |= OFN_EXPLORER;

    /*  Get commdlg loaded and ready to serve */

    if (!FAILED (ScSetupCommdlg (&hlib, &lpfnOpen, &lpfnSave)))
    {
        /*  Prompt the user for the file to use */
        
        if ((*lpfnSave) (&ofn))
        {
            /*  Open the file and iterate through the rules;
             *  Writing each one out as we go.
             */
            hf = OpenFile (rgch, &ob, ofFlags);
            if (hf != HFILE_ERROR)
            {
                _lwrite (hf, (LPBYTE)rgbExportKey, sizeof(rgbExportKey));
                _lwrite (hf, (LPBYTE)&lpscd->crl, sizeof(ULONG));
                for (irl = 0; irl < lpscd->crl; irl++)
                {
                    sc = ScWriteRule (lpscd, hf, (LPMAPIUID)lpscd->lpbin[irl].lpb);
                    if (FAILED (sc))
                        break;
                }

                _lclose (hf);
            }
        }
        FreeLibrary (hlib);
    }

    DebugTraceSc (ScExportFilters(), sc);
    return sc;
}


/*
 *  Filter Importing ----------------------------------------------------------
 *  
 *  SMH allows the importing and exporting of its filters.  This is
 *  useful when the user has multiple machines available for use.  Or for
 *  when the user needs to re-create their profile.
 *  
 *  ScInsertImportedRule() takes a SPropValue array and sets those values
 *  into a profile section.  It will replace rules by name -- maybe some
 *  sort of a conflict message would be good here, but... -- otherwise,
 *  it will create a new profile section for each rule.  The filter is
 *  then added to the filters page of the SMH config.
 *  
 *  ScReadRule() reads in the components of a flattened rule from the
 *  passed in file handle.  It then tries to insert the rule into the
 *  profile via ScInsertImportedRule().
 *  
 *  ScImportFilters() opens the imported rule file and iterates through
 *  the file calling ScReadRule() for each contained filter.
 */
SCODE
ScInsertImportedRule (LPSCD lpscd, HWND hctrl, LPSPropValue lpval)
{
    SCODE sc;
    HRESULT hr = hrSuccess;
    LPSBinary lpbin;
    LPTSTR FAR * lppsz;
    LPPROFSECT lpsec = NULL;
    MAPIUID muid;
    UINT irl;
    UINT cb;

    /*  See if the filter alread exists -- if so, we wil replace it */
    
    for (irl = 0; irl < lpscd->crl; irl++)
        if (!lstrcmpi (lpscd->lppsz[irl], lpval[ipRLDisp].Value.lpszA))
            break;

    if (irl == lpscd->crl)
        hr = lpscd->lpsup->lpVtbl->NewUID (lpscd->lpsup, &muid);
    else
        memcpy (&muid, lpscd->lpbin[irl].lpb, sizeof(MAPIUID));

    if (!HR_FAILED (hr))
    {
        hr = lpscd->lpadmin->lpVtbl->OpenProfileSection (lpscd->lpadmin,
                                        &muid,
                                        NULL,
                                        MAPI_MODIFY,
                                        &lpsec);
        if (!HR_FAILED (hr))
        {
            hr = lpsec->lpVtbl->SetProps (lpsec, cpRLMax, lpval, NULL);
            if (!HR_FAILED (hr))
                hr = lpsec->lpVtbl->SaveChanges (lpsec, 0);
        }
    }

    /*  Add the filter to the list of active filters */
    
    if (!HR_FAILED (hr))
    {
        if (irl == lpscd->crlMax)
        {
            /*  We need to make room for new entries */

            cb = (irl + GROW_SIZE) * sizeof(LPVOID);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, (LPVOID FAR *)&lppsz)))
                goto ret;
            memcpy (lppsz, lpscd->lppsz, lpscd->crl * sizeof(LPTSTR));
                
            cb = (irl + GROW_SIZE) * sizeof(SBinary);
            if (FAILED (sc = (*lpscd->lpfnAlloc) (cb, &lpbin)))
                goto ret;
            memcpy (lpbin, lpscd->lpbin, lpscd->crl * sizeof(SBinary));

            /*  Swap out the old for the new */

            (*lpscd->lpfnFree) (lpscd->lppsz);
            (*lpscd->lpfnFree) (lpscd->lpbin);
            lpscd->crlMax += GROW_SIZE;
            lpscd->lppsz = lppsz;
            lpscd->lpbin = lpbin;
        }

        sc = (*lpscd->lpfnAlloc) (lstrlen (lpval[ipRLDisp].Value.LPSZ) + 1, &lpscd->lppsz[irl]);
        if (!FAILED (sc) &&
            !FAILED (sc = (*lpscd->lpfnAlloc) (sizeof(MAPIUID), &lpscd->lpbin[irl].lpb)))
        {
            if ((ListBox_AddString (hctrl, lpval[ipRLDisp].Value.LPSZ) != LB_ERR) &&
                (ListBox_SetItemData (hctrl, irl, irl) != LB_ERR))
            {
                /*  Copy the identifiers across */
                    
                lstrcpy (lpscd->lppsz[irl], lpval[ipRLDisp].Value.LPSZ);
                memcpy (lpscd->lpbin[irl].lpb, &muid, sizeof(MAPIUID));
                lpscd->lpbin[irl].cb = sizeof(MAPIUID);
                lpscd->crl++;
            }
        }
        else
            hr = ResultFromScode (sc);
    }

ret:
    
    UlRelease (lpsec);
    DebugTraceResult (ScInsertImportedRule(), hr);
    return GetScode (hr);
}


SCODE
ScReadRule (LPSCD lpscd, HWND hctrl, HFILE hf)
{
    SCODE sc = S_OK;
    LPSPropValue lpval = NULL;
    ULONG cb;
    
    if (_lread (hf, (LPBYTE)&cb, sizeof(ULONG)) == sizeof(ULONG))
    {
        sc = (*lpscd->lpfnAlloc) (cb, &lpval);
        if (!FAILED (sc))
        {
            if (_lread (hf, (LPBYTE)lpval, (UINT)cb) == cb)
            {
                sc = ScNormalizeFlattenedProps (cpRLMax, lpval, 0, lpval);
                if (!FAILED (sc))
                    sc = ScInsertImportedRule (lpscd, hctrl, lpval);
            }
        }
    }
    
    (*lpscd->lpfnFree) (lpval);
    DebugTraceSc (ScWriteRule(), sc);
    return sc;
}


SCODE
ScImportFilters (LPSCD lpscd, HWND hwnd, HWND hctrl)
{
    SCODE sc = S_OK;
    BOOL fCtl3d = FALSE;
    CHAR rgch[MAX_PATH];
    CHAR rgchT[MAX_PATH + 60];
    CHAR rgb[sizeof(rgbExportKey)];
    HFILE hf;
    OFSTRUCT ob;
    UINT ofFlags = OF_READ | OF_SHARE_EXCLUSIVE;
    UINT irl;
    ULONG crlNew;
    HINSTANCE hlib = NULL;
    LPCOMMDLG_GETOPENFILENAME lpfnOpen;
    LPCOMMDLG_GETSAVEFILENAME lpfnSave;
    OPENFILENAME ofn = {sizeof(OPENFILENAME)};

    lstrcpy (rgch, "*.mrl");
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "Filter Export Files (*.mrl)\0*.mrl\0";
    ofn.lpstrFile = rgch;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrInitialDir = NULL;
    ofn.lpstrTitle = "Open Filter Export File";
    ofn.lpstrDefExt = "MRL";
    ofn.hInstance = lpscd->hinst;
    ofn.lCustData = 0;
    ofn.lpfnHook = (LPOFNHOOKPROC)CommdlgHook;
    ofn.Flags = OFN_PATHMUSTEXIST       |
                OFN_HIDEREADONLY        |
                OFN_ENABLEHOOK          |
                OFN_NOCHANGEDIR;

    if (FWin4Shell ())
        ofn.Flags |= OFN_EXPLORER;

    if (!FAILED (ScSetupCommdlg (&hlib, &lpfnOpen, &lpfnSave)))
    {
        if ((*lpfnOpen) (&ofn))
        {
            hf = OpenFile (rgch, &ob, ofFlags);
            if (hf != HFILE_ERROR)
            {
                _lread (hf, (LPBYTE)rgb, sizeof(rgbExportKey));
                if (!memcmp (rgb, rgbExportKey, sizeof(rgbExportKey)))
                {
                    _lread (hf, (LPBYTE)&crlNew, sizeof(ULONG));
                    for (irl = 0; irl < crlNew; irl++)
                    {
                        sc = ScReadRule (lpscd, hctrl, hf);
                        if (FAILED (sc))
                            break;
                    }
                }
                else
                {
                    wsprintf (rgchT,
                        "'%s' is an invalid or corrupt exported filter file.",
                        rgch);

                    if (CTL3D_GetVer(lpCtl3D) >= 0x220 && !CTL3D_IsAutoSubclass(lpCtl3D))
                        CTL3D_AutoSubclass (lpCtl3D, lpscd->hinst, &fCtl3d);
                    MessageBox (hwnd,
                        rgchT,
                        "Import filters",
                        MB_TASKMODAL | MB_OK | MB_ICONINFORMATION);
                    CTL3D_CeaseAutoSubclass(lpCtl3D, fCtl3d);
                }

                _lclose (hf);
            }
        }
        else
            sc = MAPI_E_USER_CANCEL;
        
        FreeLibrary (hlib);
    }
    
    DebugTraceSc (ScImportFilters(), sc);
    return sc;
}


