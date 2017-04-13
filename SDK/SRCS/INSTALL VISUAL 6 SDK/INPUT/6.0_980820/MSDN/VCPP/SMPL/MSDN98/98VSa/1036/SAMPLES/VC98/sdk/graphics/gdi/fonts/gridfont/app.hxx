//+--------------------------------------------------------
// File:        App.hxx
//
// Classes:     CController
//
// Functions:   WinMain
//              WndProc
//              MakeWindowClass
//              AboutDlgProc
//
// History:     22-Jan-1993     asmusf  created
//              15-Dec-1993     michelsu
//       - added font content awareness (page and block level)
//       - fix Print All Pages
//				15-Aug-1994		asmusf
//		 - added decomposition, property indication
//----------------------------------------------------------

#include <string.h>
#include "app.h"
#include "view.hxx"
#include "grid.hxx"
#include "box.hxx"

//----------------------------------------------------------
//
// Class Hierarchy for Application   --- inheritance
//           (approximate)           (x) contains x
//
//      CGrid
//        |                          CBlockFrame(CFont)  
//        |                                     (CLineGrid)
//        +--CTextGrid(CFont)                   (CCodeGrid)
//        |     |                               (CCharGrid)
//        |     |
//        |     +CCharGrid           CPage(CFont,CCodeGrid[])
//   CLineGrid  |                         (CBlockFrame[])
//              +CCodeGrid           
//                                   CModel(CPage,CFontRange)
//                                   
//                                   
//
//      CCanvas                       CView
//         |                            |
//         |-- CPaintCanvas             |
//         |                          CScrollableView
//         |-- CScreenCanvas
//         |
//         +-- CPrintCanvas           CPrintRequest
//
//
//     CController(CScrollableView, CModel, CBox)
//
//----------------------------------------------------------

#if 0
#ifndef WPARAM
#define WPARAM WORD
#endif
#ifndef LPARAM
#define LPARAM LONG
#endif
#endif

// procedures called by Windows

extern "C" {

LRESULT CALLBACK WndProc
   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

BOOL CALLBACK AboutDlgProc
   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );

BOOL CALLBACK PropDlgProc
   ( HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam );
}


// Main function and other functions used in App.cxx

int WINAPI WinMain
   ( HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR cmdParam, int cmdShow );

void MakeWindowClass ( WNDPROC WndProc, LPTSTR szAppName, HINSTANCE hInst );


// ==== Class CWindow =============================

class CWindow
{
public:
   CWindow (): _hwnd(0) {}
   CWindow ( LPTSTR caption, LPTSTR lpszClassName, HINSTANCE hInstance,
            int cx = CW_USEDEFAULT, int cy=CW_USEDEFAULT);
   void Show ( int nCmdShow )
   {
      ShowWindow ( _hwnd, nCmdShow );
      UpdateWindow ( _hwnd );
   }
   operator HWND() { return _hwnd; }
protected:
   HWND _hwnd;
};

inline CWindow::CWindow(LPTSTR caption, LPTSTR lpszClassName, HINSTANCE hInstance,
int cx, int cy)
{
   _hwnd = CreateWindow (
      lpszClassName,
      caption,
      WS_OVERLAPPEDWINDOW | WS_VSCROLL | WS_HSCROLL,
      CW_USEDEFAULT,
      CW_USEDEFAULT,
      cx,
      cy,
      NULL,
      NULL,
      hInstance,
      NULL );
}

// ==== Class Controller ==========================

class CController
{
public:
   void Init(HWND hwnd);

   void Create(HWND hwnd, LPARAM lParam);
   void Destroy();
   void Size ( LPARAM lParam );
   void Paint ( HWND hwnd );
   void Command ( HWND hwnd, WPARAM wParam );
   void ButtonDown(HWND hwnd, LPARAM lParam );
   void ButtonUp(HWND hwnd, LPARAM lParam);
   void KeyDown(HWND hwnd, WPARAM wParam, LPARAM lParam);
   void KeyUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
   void VScroll(HWND hwnd, WPARAM wParam, LPARAM lParam);
   void HScroll(HWND hwnd, WPARAM wParam, LPARAM lParam);
   void AlertBox(HWND hwnd, UINT ids, UINT fuStyle);

private:
   void Page(HWND hwnd, WPARAM wParam);

   HINSTANCE  _hInst;
   DLGPROC _funAbout;
   DLGPROC _funProp;

   CScrollableView* _pView;
   CModel* _pModel;
   CBox *  _pBox;
};


inline void CController::Paint ( HWND hwnd )
{
   CPaintCanvas canvas (hwnd);

   _pView->Paint(canvas, _pModel, canvas.GetRect());
}

