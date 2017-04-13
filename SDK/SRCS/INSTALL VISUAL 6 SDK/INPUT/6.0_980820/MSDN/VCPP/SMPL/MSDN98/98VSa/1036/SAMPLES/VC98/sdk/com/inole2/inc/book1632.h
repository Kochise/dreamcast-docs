/*
 * BOOK1632.H
 *
 * Macros and other definitions that assist in porting between Win16
 * and Win32 applications.  Defines WIN32 to enable 32-bit versions.
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  INTERNET>kraigb@microsoft.com
 */


#ifndef _BOOK1632_H_
#define _BOOK1632_H_

#ifdef WIN32

#ifndef COMMANDPARAMS
#define COMMANDPARAMS(wID, wCode, hWndMsg)                          \
    WORD        wID     = LOWORD(wParam);                           \
    WORD        wCode   = HIWORD(wParam);                           \
    HWND        hWndMsg = (HWND)(UINT)lParam;
#endif  //COMMANDPARAMS

#ifndef SendCommand
#define SendCommand(hWnd, wID, wCode, hControl)                     \
            SendMessage(hWnd, WM_COMMAND, MAKEWPARAM(wID, wCode)    \
                        , (LPARAM)hControl)
#endif  //SendCommand

#ifndef MENUSELECTPARAMS
#define MENUSELECTPARAMS(wID, wFlags, hMenu)                        \
    WORD        wID     = LOWORD(wParam);                           \
    WORD        wFlags  = HIWORD(wParam);                           \
    HMENU       hMenu   = (HMENU)lParam;
#endif  //MENUSELECTPARAMS


#ifndef SendMenuSelect
#define SendMenuSelect(hWnd, wID, wFlags, hMenu)                    \
            SendMessage(hWnd, WM_MENUSELECT                         \
                , MAKEWPARAM((WORD)wID, (WORD)wFlags), (LPARAM)hMenu)

#endif  //SendMenuSelect

#ifndef SendScrollPosition
#define SendScrollPosition(hWnd, iMsg, iPos)                        \
            SendMessage(hWnd, iMsg, MAKEWPARAM(SB_THUMBPOSITION, iPos), 0)
#endif //SendScrollPosition

#ifndef ScrollThumbPosition
#define ScrollThumbPosition(w, l) HIWORD(w)
#endif //ScrollThumbPosition

#ifndef GETWINDOWINSTANCE
#define GETWINDOWINSTANCE(h) (HINSTANCE)GetWindowLong(h, GWL_HINSTANCE)
#endif  //GETWINDOWINSTANCE

#ifndef GETWINDOWID
#define GETWINDOWID(h) (UINT)GetWindowLong(h, GWW_ID)
#endif  //GETWINDOWID

#ifndef POINTFROMLPARAM
#define POINTFROMLPARAM(p, l) {p.x=(LONG)(SHORT)LOWORD(l); \
                               p.y=(LONG)(SHORT)HIWORD(l);}
#endif  //POINTFROMLPARAM

#ifndef MDISETMENU
#define MDISETMENU(h, hM, hMW)  SendMessage(h, WM_MDISETMENU \
                                    , (WPARAM)hM, (LPARAM)hMW);
#endif  //MDISETMENU


#ifndef MDIREFRESHMENU
#define MDIREFRESHMENU(h) SendMessage(h, WM_MDIREFRESHMENU, 0, 0L)
#endif  //MDIREFRESHMENU


//Activated child window in WM_MDIACTIVATE
#ifndef NEWMDIACTIVE
#define NEWMDIACTIVE lParam
#endif  //NEWMDIACTIVE

#ifndef UNICODETOANSI
#ifdef UNICODE
#define UNICODETOANSI(s, d, cch) WideCharToMultiByte(CP_ACP \
            , 0, s, -1, d, cch, NULL, NULL)
#else  //ANSI
#define UNICODETOANSI(s, d, cch) lstrcpy(d, (LPTSTR)s);
#endif
#endif //UNICODETOANSI


#ifndef ANSITOUNICODE
#ifdef UNICODE
#define ANSITOUNICODE(s, d, cch) MultiByteToWideChar(CP_ACP \
            , 0, s, -1, d, cch)
#else //ANSI
#define ANSITOUNICODE(s, d, cch) lstrcpy(d, (LPTSTR)s);
#endif
#endif  //ANSITOUNICODE



#ifndef SETMESSAGEQUEUE
#define SETMESSAGEQUEUE
#endif

#ifndef CHECKVER_COM
#define CHECKVER_COM
#endif  //CHECKVER_COM

#ifndef CHECKVER_OLE
#define CHECKVER_OLE
#endif  //CHECKVER_OLE

//****END WIN32



#else



//****START !WIN32

#ifndef POINTS
typedef POINT POINTS;
#endif  //POINTS

#ifndef LPPOINTS
typedef POINTS FAR *LPPOINTS;
#endif  //LPPOINTS

#ifndef MAKEPOINTS
#define MAKEPOINTS MAKEPOINT
#endif  //MAKEPOINTS


#ifndef COMMANDPARAMS
#define COMMANDPARAMS(wID, wCode, hWndMsg)                          \
    WORD        wID     = LOWORD(wParam);                           \
    WORD        wCode   = HIWORD(lParam);                           \
    HWND        hWndMsg = (HWND)(UINT)lParam;
#endif  //COMMANDPARAMS

#ifndef SendCommand
#define SendCommand(hWnd, wID, wCode, hControl)                     \
            SendMessage(hWnd, WM_COMMAND, wID                       \
                        , MAKELONG(hControl, wCode))
#endif  //SendCommand

#ifndef MENUSELECTPARAMS
#define MENUSELECTPARAMS(wID, wFlags, hMenu)                        \
    WORD        wID     = LOWORD(wParam);                           \
    WORD        wFlags  = LOWORD(lParam);                           \
    HMENU       hMenu   = (HMENU)HIWORD(lParam);
#endif  //MENUSELECTPARAMS

#ifndef SendMenuSelect
#define SendMenuSelect(hWnd, wID, wFlags, hMenu)                    \
            SendMessage(hWnd, WM_MENUSELECT, wID                    \
                        , MAKELONG((WORD)wFlags, (WORD)hMenu))
#endif  //SendMenuSelect

#ifndef SendScrollPosition
#define SendScrollPosition(hWnd, iMsg, iPos)                        \
            SendMessage(hWnd, iMsg, SB_THUMBPOSITION, MAKELONG(iPos, 0))
#endif //Send ScrollPosition

#ifndef ScrollThumbPosition
#define ScrollThumbPosition(w, l) LOWORD(l)
#endif //ScrollThumbPosition

#ifndef GETWINDOWINSTANCE
#define GETWINDOWINSTANCE(h) (HINSTANCE)GetWindowWord(h, GWW_HINSTANCE)
#endif  //GETWINDOWINSTANCE

#ifndef GETWINDOWID
#define GETWINDOWID(h) (UINT)GetWindowWord(h, GWW_ID)
#endif  //GETWINDOWID

#ifndef POINTFROMLPARAM
#define POINTFROMLPARAM(p, l) {p.x=LOWORD(l); p.y=HIWORD(l);}
#endif  //POINTFROMLPARAM

#ifndef MDISETMENU
#define MDISETMENU(h, hM, hMW)  SendMessage(h, WM_MDISETMENU \
                     , (WPARAM)FALSE, (LPARAM)MAKELPARAM(hM, hMW))
#endif  //MDISETMENU


#ifndef MDIREFRESHMENU
#define MDIREFRESHMENU(h) SendMessage(h, WM_MDISETMENU, TRUE, 0L)
#endif  //MDIREFRESHMENU

//Activated child window in WM_MDIACTIVATE
#ifndef NEWMDIACTIVE
#define NEWMDIACTIVE wParam
#endif  //NEWMDIACTIVE


//Things not present in Win3.1 SDK but present in Win32 SDK.

#ifndef APIENTRY
#define APIENTRY __export FAR PASCAL
#endif  //APIENTRY

#ifndef USHORT
typedef unsigned short USHORT;
#endif  //USHORT

//These are so we can write ANSI/UNICODE portable code.
#ifndef TCHAR
typedef char TCHAR;
#endif  //TCHAR

#ifndef LPTSTR
typedef TCHAR *LPTSTR;
#endif  //LPTSTR

#ifndef LPCTSTR
typedef const TCHAR *LPCTSTR;
#endif  //LPCTSTR

#ifndef _tcsncpy
#define _tcsncpy strncpy
#endif  //_tcsncpy

#ifndef _tcsstr
#define _tcsstr strstr
#endif  //_tcsstr

#ifndef _tcsrchr
#define _tcsrchr strrchr
#endif  //_tcsrchr

#ifndef _tcsncicmp
#define _tcsncicmp  strnicmp
#endif  //_tcsncicmp

#ifndef _ttoi
#define _ttoi   atoi
#endif  //_ttoi

#ifndef lstrcpyA
#define lstrcpyA lstrcpy
#endif  //lstrcpyA

#ifndef lstrcmpiA
#define lstrcmpiA lstrcmpi
#endif  //lstrcmpiA

#ifndef TEXT
#define TEXT(a) a
#endif  //TEXT

#ifndef ReadFile
#define ReadFile(h, b, c, x, y) _lread(h, b, c)
#endif  //ReadFile

#ifndef CloseHandle
#define CloseHandle(h) _lclose(h)
#endif  //CloseHandle

#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE        HFILE_ERROR
#endif  //INVALID_HANDLE_VALUE

#ifndef MAX_PATH
#define MAX_PATH   260
#endif  //MAX_PATH

#ifndef _MAX_PATH
#define _MAX_PATH   MAX_PATH
#endif  //_MAX_PATH

#ifndef RegCreateKeyEx
#define RegCreateKeyEx(h, sz, d, nl1, opt, acc, nl2, ph, nl3)   \
        RegCreateKey(h, sz, ph)
#endif  //RegCreateKeyEx

#ifndef RegSetValueEx
#define RegSetValueEx(h, nl, d, rsz, psz, pch)  \
        RegSetValue(h, nl, rsz, (LPCSTR)psz, 0)
#endif  //RegSetValueEx

#ifndef wsprintfA
#define wsprintfA wsprintf
#endif  //wsprintfA

#ifndef LoadLibraryA
#define LoadLibraryA LoadLibrary
#endif  //LoadLibraryA

#ifndef MessageBoxA
#define MessageBoxA MessageBox
#endif  //MessageBoxA

#ifndef SetForegroundWindow
#define SetForegroundWindow(h) BringWindowToTop(h)
#endif  //SetForegroundWindow

#ifndef DeleteFile
#define DeleteFile(f)                       \
            {                               \
            OFSTRUCT    of;                 \
            OpenFile(f, &of, OF_DELETE);    \
            }
#endif  //DeleteFile

#ifndef UNICODETOANSI
#define UNICODETOANSI(s, d, cch) lstrcpy(d, (LPTSTR)s);
#endif  //UNICODETOANSI

#ifndef ANSITOUNICODE
#define ANSITOUNICODE(s, d, cch) lstrcpy(d, (LPTSTR)s);
#endif  //ANSITOUNICODE


#ifndef SETMESSAGEQUEUE
#define SETMESSAGEQUEUE                                  \
            {                                            \
            int cMsg=96;                                 \
            while (!SetMessageQueue(cMsg) && (cMsg-=8)); \
            }
#endif  //SETMESSAGEQUEUE


#ifdef INC_OLE2
#ifndef CoTaskMemFree
#define CoTaskMemFree(pv)                                       \
            {                                                   \
            IMalloc *pIMalloc;                                  \
            if (SUCCEEDED(CoGetMalloc(MEMCTX_TASK, &pIMalloc))) \
                {                                               \
                pIMalloc->Free(pv);                             \
                pIMalloc->Release();                            \
                }                                               \
            }
#endif  //CoTaskMemFree
#endif

#ifndef CHECKVER_COM
#define CHECKVER_COM                    \
            {                           \
            DWORD       dwVer;          \
                                        \
            dwVer=CoBuildVersion();     \
                                        \
            if (rmm!=HIWORD(dwVer))     \
                return FALSE;           \
            }

#endif  //CHECKVER_COM


#ifndef CHECKVER_OLE
#define CHECKVER_OLE                    \
            {                           \
            DWORD       dwVer;          \
                                        \
            dwVer=OleBuildVersion();    \
                                        \
            if (rmm!=HIWORD(dwVer))     \
                return FALSE;           \
            }

#endif  //CHECKVER_OLE


//Stolen from Win32 so we can do OLE Controls on Win16
#ifndef FVIRTKEY
#define FVIRTKEY  TRUE
#endif
#ifndef FNOINVERT
#define FNOINVERT 0x02
#endif
#ifndef FSHIFT
#define FSHIFT    0x04
#endif
#ifndef FCONTROL
#define FCONTROL  0x08
#endif
#ifndef FALT
#define FALT      0x10
#endif

#ifndef ACCELL
typedef struct tagACCEL
    {
    BYTE   fVirt;
    WORD   key;
    WORD   cmd;
    } ACCEL, *LPACCEL;
#endif


/*
 * Appeared in OLE2.02 on 16-bit, always in Win32 defined as 1.
 * 0 is the only valid flag on OLE 2.01 and 2.00.
 */
#ifndef ROTFLAGS_REGISTRATIONKEEPSALIVE
#define ROTFLAGS_REGISTRATIONKEEPSALIVE     0
#endif  //ROTFLAGS_REGISTRATIONKEEPSALIVE

#endif  //!WIN32


//These definitions we need regardless of Win16 or Win32

/*
 * May not have these in which case they're irrelevant but
 * we want things to still compile.
 */
#ifndef ACTIVEOBJECT_STRONG
#define ACTIVEOBJECT_STRONG     0
#endif  //ACTIVEOBJECT_STRONG

//If this is not defined, it doesn't exist, so make it zero.
#ifndef ACTIVEOBJECT_WEAK
#define ACTIVEOBJECT_WEAK       0
#endif  //ACTIVEOBJECT_WEAK


typedef struct
    {
    short   left;
    short   top;
    short   right;
    short   bottom;
    } RECTS, FAR *LPRECTS;

#define RECTSTORECT(rs, r) {(r).left=(rs).left;(r).top=(rs).top; \
    (r).right=(rs).right;(r).bottom=(rs).bottom;};

#define RECTTORECTS(r, rs) {(rs).left=(short)(r).left;   \
    (rs).top=(short)(r).top;(rs).right=(short)(r).right; \
    (rs).bottom=(short)(r).bottom;};


/*
 * This is for ANSI compiles on Win32, where we HAVE to use
 * a Unicode string literal (so the TEXT macro isn't good enough).
 */

#ifdef WIN32ANSI
#define OLETEXT(x)  L ## x
#else
#define OLETEXT(x)  TEXT(x)
#endif

#endif  //_BOOK1632_H_
