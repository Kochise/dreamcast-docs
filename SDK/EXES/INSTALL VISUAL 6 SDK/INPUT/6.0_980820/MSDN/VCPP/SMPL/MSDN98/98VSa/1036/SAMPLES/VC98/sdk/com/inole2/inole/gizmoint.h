/*
 * GIZMOINT.H
 * Gizmobar Internals
 *
 * Copyright (c)1993-1995 Microsoft Corporation, All Rights Reserved
 *
 * Kraig Brockschmidt, Microsoft
 * Internet  :  kraigb@microsoft.com
 * Compuserve:  >INTERNET:kraigb@microsoft.com
 */


#ifndef _GIZMOINT_H_
#define _GIZMOINT_H_

#ifdef __cplusplus
extern "C"
    {
#endif


typedef struct tagGIZMO
    {
    struct tagGIZMO     *pPrev;
    struct tagGIZMO     *pNext;
    UINT                 iType;
    HWND                 hWnd;       //Texts, edits, lists, combos
    UINT                 uID;
    UINT                 x, y;
    UINT                 dx, dy;
    UINT                 cxImage;    //From UIToolConfigureForDisplay
    UINT                 cyImage;
    HBITMAP              hBmp;       //Buttons only.
    UINT                 iBmp;
    BOOL                 fNotify;    //Send WM_COMMANDs?
    BOOL                 fHidden;    //Independent of state
    BOOL                 fDisabled;
    UINT                 uState;
    UINT                 uStateOrg;
    DWORD                dwData;     //Application-supplied data.
    } GIZMO, * PGIZMO;

typedef PGIZMO *PPGIZMO;
#define CBGIZMO sizeof(GIZMO)

//Property name we attach to controls in a gizmo to identify type
#define SZTYPEPROP      TEXT("iType")

//Number of controls we subclass
#define CSUBGIZMOS       4

//ID of edit controls in comboboxes
#define ID_COMBOEDIT     1001


/*
 * Conversion of iType (a positioned bit) into its position.
 * The BITPOSITION macro does not need to be fast because we only
 * use it once when creating a gizmo.  POSITIONBIT does, however,
 * since we use it in subclass procedures.
 */
#define BITPOSITION(i, j)  {int k=i; for (j=0; k>>=1; j++);}
#define POSITIONBIT(i)     (1 << i)

//Control classifications.  GIZMOBAR.H must be included first.
#define GIZMOTYPE_WINDOWS   (GIZMOTYPE_TEXT | GIZMOTYPE_EDIT \
                            | GIZMOTYPE_LISTBOX              \
                            | GIZMOTYPE_COMBOBOX             \
                            | GIZMOTYPE_BUTTONNORMAL)

#define GIZMOTYPE_BUTTONS   (GIZMOTYPE_BUTTONATTRIBUTEIN     \
                            | GIZMOTYPE_BUTTONATTRIBUTEEX    \
                            | GIZMOTYPE_BUTTONCOMMAND        \
                            | GIZMOTYPE_BUTTONNORMAL)

#define GIZMOTYPE_DRAWN     (GIZMOTYPE_BUTTONATTRIBUTEIN     \
                            | GIZMOTYPE_BUTTONATTRIBUTEEX    \
                            | GIZMOTYPE_BUTTONCOMMAND)


//These must stay in sync with GIZMOBAR.H
#define GIZMOTYPE_MIN               GIZMOTYPE_EDIT
#define GIZMOTYPE_MAX               GIZMOTYPE_BUTTONCOMMAND


//Enumeration callback
typedef BOOL (CALLBACK *PFNGIZMOENUM)(PGIZMO, UINT, DWORD);


//GIZMO.C
PGIZMO   GizmoPAllocate(int *, PPGIZMO, HWND, UINT, UINT, UINT
             , UINT, UINT, LPTSTR, HBITMAP, UINT, UINT);
void     GizmosExpand(PGIZMO);
PGIZMO   GizmoPFree(PPGIZMO, PGIZMO);
void     GizmosCompact(PGIZMO);
PGIZMO   GizmoPFind(PPGIZMO, UINT);
PGIZMO   GizmoPEnum(PPGIZMO, PFNGIZMOENUM, DWORD);
UINT     GizmoPStateSet(HWND, PGIZMO, UINT);
BOOL     GizmoPCheck(HWND, PGIZMO, BOOL);


LRESULT APIENTRY GenericSubProc(HWND, UINT, WPARAM, LPARAM);



/*
 * The main gizmobar structure itself.  There's only one of these,
 * but it references the first GIZMO in the list.
 */

typedef struct tagGIZMOBAR
    {
    PGIZMO      pGizmos;            //List of gizmos we own.
    HWND        hWnd;               //Window handle of ourselves.
    HINSTANCE   hInst;
    HWND        hWndAssociate;      //Associate who gets messages.
    DWORD       dwStyle;            //Copy of GWL_STYLE
    UINT        uState;             //State flags
    UINT        uID;                //Control ID.

    HBRUSH      hBrFace;            //Static control background color
    COLORREF    crFace;             //Color of hBrFace
    HFONT       hFont;              //Font in use
    BOOL        fEnabled;           //Are we enabled?

    PGIZMO      pGizmoTrack;        //Current pressed button.
    BOOL        fTracking;
    BOOL        fMouseOut;
    } GIZMOBAR, * PGIZMOBAR;

#define CBGIZMOBAR sizeof(GIZMOBAR)


//Extra bytes for the window if the size of a local handle.
#define CBEXTRAGIZMOBAR     sizeof(PGIZMOBAR)

#define GBWL_STRUCTURE      0


//Structure for passing paint info to a gizmo enumeration callback.
typedef struct
    {
    PAINTSTRUCT         ps;
    TOOLDISPLAYDATA     tdd;
    } PAINTGIZMO, *PPAINTGIZMO;




//GIZMOBAR.C
PGIZMOBAR         GizmoBarPAllocate(int *, HWND, HINSTANCE, HWND
                      , DWORD, UINT, UINT);
PGIZMOBAR         GizmoBarPFree(PGIZMOBAR);
LRESULT WINAPI    GizmoBarWndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    WINAPI    FEnumChangeFont(PGIZMO, UINT, DWORD);
BOOL    WINAPI    FEnumEnable(PGIZMO, UINT, DWORD);
BOOL    WINAPI    FEnumHitTest(PGIZMO, UINT, DWORD);
void              GizmoBarPaint(HWND, PGIZMOBAR);
BOOL WINAPI       FEnumPaintGizmos(PGIZMO, UINT, DWORD);


//GIZMOAPI.C  See GIZMOBAR.H for others
LRESULT    GBMessageHandler(HWND, UINT, WPARAM, LPARAM, PGIZMOBAR);
PGIZMO     PGizmoFromHwndID(HWND, UINT);

#ifdef __cplusplus
    }
#endif


#endif //_GIZMOINT_H_
