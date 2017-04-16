#include "windows.h"
#include "windowsx.h"
#include "vlist.h"

#ifdef WIN32
#define EXPORT
#else
#define EXPORT _export
#endif
typedef struct tagVLISTBox
   {
      HWND      hwnd;             // hwnd of this VLIST box
      int       nId;              // Id of Control
      HINSTANCE hInstance;        // Instance of parent
      HWND      hwndParent;       // hwnd of parent of VLIST box
      HWND      hwndList;         // hwnd of List box
      WNDPROC   lpfnLBWndProc;    // Window procedure of list box
      int       nchHeight;        // Height of text line
      int       nLines;           // Number of lines in listbox
      LONG      styleSave;        // Save the Style Bits
      WORD      VLBoxStyle;       // List Box Style
      HANDLE    hFont;            // Font for List box
      LONG      lToplIndex;      // Top logical record number;
      int       nCountInBox;      // Number of Items in box.
      LONG      lNumLogicalRecs;  // Number of logical records
      VLBSTRUCT vlbStruct;        // Buffer to communicate to app
      WORD      wFlags;           // Various flags fot the VLB
                                  //
                                  // 0x01 - HasStrings
                                  // 0x02 - Use Data Values
                                  // 0x04 - Multiple Selections
                                  // 0x08 - Ok for parent to have focus
                                  // 0x10 - Control has focus

      LONG      lSelItem;         // List of selected items
      int       nvlbRedrawState;  // Redraw State
      BOOL      bHScrollBar;      // Does it have a H Scroll
} VLBOX;

typedef VLBOX NEAR *PVLBOX;
typedef VLBOX FAR  *LPVLBOX;


#define IDS_VLBOXNAME  1
#define VLBLBOXID      100
#define VLBEDITID      101

#define HASSTRINGS     0x01       // List box stores strings
#define USEDATAVALUES  0x02       // Use Data Values to talk to parent
#define MULTIPLESEL    0x04       // VLB has extended or multiple selection
#define PARENTFOCUS    0x08       // Ok for parent to have focus
#define HASFOCUS       0x10       // 0x10 - Control has focus

LRESULT EXPORT WINAPI VListBoxWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
LRESULT EXPORT WINAPI LBSubclassProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

BOOL WINAPI RegisterVListBox(HINSTANCE hInstance);
LONG VLBMessageItemHandler( PVLBOX pVLBox,  UINT message, LPSTR lpfoo);
LONG VLBParentMessageHandler( PVLBOX pVLBox, UINT message, WPARAM wParam, LPARAM lParam);
LONG VLBNcCreateHandler( HWND hwnd, LPCREATESTRUCT lpcreateStruct);
LONG VLBCreateHandler( PVLBOX pVListBox, HWND hwnd, LPCREATESTRUCT lpcreateStruct);
void VLBNcDestroyHandler(HWND hwnd,  PVLBOX pVListBox, WPARAM wParam, LPARAM lParam);
void VLBSetFontHandler( PVLBOX pVListBox, HANDLE hFont, BOOL fRedraw);
int  VLBScrollDownLine( PVLBOX pVLBox);
int  VLBScrollUpLine( PVLBOX pVLBox);
int  VLBScrollDownPage( PVLBOX pVLBox, int nAdjustment);
int  VLBScrollUpPage( PVLBOX pVLBox, int nAdjustment);
void UpdateVLBWindow( PVLBOX pVLBox, LPRECT lpRect);
int  VLBFindPage( PVLBOX pVLBox, LONG lFindRecNum, BOOL bUpdateTop);
int  VLBFindPos( PVLBOX pVLBox, int nPos);
void VLBFirstPage( PVLBOX pVLBox);
void VLBLastPage( PVLBOX pVLBox);
LONG vlbSetCurSel( PVLBOX pVLBox, int nOption, LONG lParam);
int  vlbFindData( PVLBOX pVLBox, LONG lData);
void VLBSizeHandler( PVLBOX pVLBox, int nItemHeight);
int  vlbInVLB( PVLBOX pVLBox, LONG lData);
void VLBCountLines( PVLBOX pVLBox);

void vlbRedrawOff(PVLBOX pVLBox);
void vlbRedrawOn(PVLBOX pVLBox);

BOOL TestSelectedItem(PVLBOX pVLBox, VLBSTRUCT vlbStruct);
void SetSelectedItem(PVLBOX pVLBox);

void vlbPGDN(PVLBOX pVLBox);
void vlbPGUP(PVLBOX pVLBox);

void vlbLineDn(PVLBOX pVLBox);
void vlbLineUp(PVLBOX pVLBox);

extern HANDLE  hInstance;              // Global instance handle for  DLL
