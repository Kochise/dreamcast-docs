#ifndef __VIEW_HXX_
#define __VIEW_HXX_

#include "canvas.hxx"

//--------------------------------------------------------------------
// File: View.hxx
//
// Classes: 
//      CView          - Base class for Views 
//      CScrollaleView - Scrollable View
//
//      CPrintCanvas  - Device context for printing
//      CPrintRequest  - Print Job
//
// History: 22-Jan-1993 Asmusf  Created
//
// Copyright (C) 1993-1997 Microsoft Corp. All Rights reserved
//
//--------------------------------------------------------------------

class CModel;

//======== CView ============================================
class CView
{
public:
        CView(int cx, int cy);
        void SetSize( int cx, int cy);
        BOOL Paint(CCanvas& canvas, CModel * _pModel, RECT rc);
        UINT Hittest(CCanvas& canvas, POINT pt, CModel * _pModel);
        void Invalidate(HWND hwnd, LPRECT lpRect=NULL);
protected:
        void Scroll(CCanvas &canvas);
        SIZE _size;
        UINT _iScale;
        POINT _ptOrg;
        POINT _ptScroll;
        POINT _ptClient;
};

//======== CScrollableView ==================================
class CScrollableView : public CView 
{
public:
        CScrollableView(int cx, int cy):CView(cx,cy){};
        void GetScale(UINT &iScale);
        void SetScale(UINT iScale);
        void SetVScrollPos(HWND hwnd, WPARAM wParam, LPARAM lParam,
                                CModel * pModel);
        void SetHScrollPos(HWND hwnd, WPARAM wParam, LPARAM lParam,
                                CModel * pModel);
protected:
        int _nHScrollPos;
        int _nVScrollPos;
};


inline void CScrollableView::GetScale(UINT &iScale)
{
        iScale=_iScale;
};

inline void CScrollableView::SetScale(UINT iScale)
{
        _iScale=iScale;
};


//======== CPrintRequest =======================================

#define PREQ_SUCCESS   NULL
#define PREQ_CANCEL       1
#define PREQ_USERABORT    2
#define PREQ_ERRENDPAGE   4
#define PREQ_ERRSTARTPAGE 8
#define PREQ_ERRSTARTDOC  16
#define PREQ_ERROR        32


class CPrintRequest
{
friend class CPrintCanvas;
public:
        CPrintRequest(HWND hwnd, UINT minPage=1, UINT maxPage=1);
        ~CPrintRequest();

        UINT Print(HINSTANCE hInst, CCanvas &canvas, CModel *pModel);
        BOOL Cancelled() { return _status == PREQ_CANCEL; };    
        BOOL Error()     { return _status != PREQ_SUCCESS; };   

protected:
        HDC    _hdc;
        HWND   _hwnd;
        UINT   _nFromPage;
        UINT   _nToPage;
        UINT   _status;
        HANDLE _hDevNames;
        CModel* _pModel;
        CView * _pView;
};


//======== CPrintCanvas =======================================

class CPrintCanvas : public CCanvas
{
public:
        CPrintCanvas(CPrintRequest &pr)
        {
            Init(pr._hdc);
            pr._hdc = 0;
        }
        ~CPrintCanvas()
        {            
            DeleteDC(_hdc);     
        }
};


extern "C" {
BOOL CALLBACK PrintDlgProc
   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

BOOL CALLBACK AbortProc
   (HDC hdcPrn, short nCode);
}

class CPrintAux
{
friend class CPrintRequest;
friend BOOL CALLBACK PrintDlgProc
   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
friend BOOL CALLBACK AbortProc (HDC hdcPrn, short nCode);

        BOOL _bUserAbort;
        HWND _hDlgPrint;
};



#endif
