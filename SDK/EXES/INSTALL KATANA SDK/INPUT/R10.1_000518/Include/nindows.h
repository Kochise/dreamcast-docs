/*
	Nindows Library

	COPYRIGHT (C) SEGA ENTERSRISES,LTD.
*/


#ifndef _NINDOWS_H_
#define _NINDOWS_H_

#ifdef __cplusplus
extern "C"{
#endif

#include <Ninja.h>

/*--------------------------------------*/
/*      System Information              */
/*--------------------------------------*/
#define NWD_SM_CXSIZEFRAME  2           /* THICKFRAMEのフレームの幅         */
#define NWD_SM_CYSIZEFRAME  2           /* THICKFRAMEのフレームの高さ       */
#define NWD_SM_CXBORDER     1           /* シングルボーダーの幅             */
#define NWD_SM_CYBORDER     1           /* シングルボーダーの高さ           */
#define NWD_SM_CXMINTRACK   32          /* 最小のウィンドウの幅             */
#define NWD_SM_CYMINTRACK   10          /* 最小のウィンドウの高さ           */
#define NWD_SM_CYCAPTION    20          /* キャプションの高さ               */
#define NWD_SM_SZCAPTION    16          /* キャプションの高さ               */
#define NWD_SM_CXSHADOW     8           /* 影のつきかた                     */
#define NWD_SM_CYSHADOW     8           /* 影のつきかた                     */

/*--------------------------------------*/
/*      Window Style                    */
/*--------------------------------------*/
#define NWD_WS_CAPTION      0x00000001  /* キャプションあり                 */
#define NWD_WS_THICKFRAME   0x00000002  /* フレームつき                     */
#define NWD_WS_BORDER       0x00000004  /* 境界線を持つウィンドウ           */
#define NWD_WS_SHADING      0x00000008  /* シェーディングあり               */
#define NWD_WS_CONTROL      0x00000010  /* クローズボックスあり             */
#define NWD_WS_OFFSET       0x00000020  /* 親ウィンドウとの相対座標を使用   */
#define NWD_WS_SHADOW       0x00000040  /* 影付きウィンドウ                 */
#define NWD_WS_INVISIBLE    0x00000080  /* 描画なしウィンドウ               */
#define NWD_WS_NOMOVE       0x00000100  /* マウスでの移動をしない           */

#define NWD_WS_CLOSEBOX     NWD_WS_CONTROL
#define NWD_WS_MAXIMIZEBOX  0x00000200  /* 最大化ボックスを持つ             */
#define NWD_WS_MINIMIZEBOX  0x00000400  /* 最小化ボックスを持つ             */

#define NWD_WS_SB_HORZ      0x00001000  /* 水平スクロールバー               */
#define NWD_WS_SB_VERT      0x00002000  /* 垂直スクロールバー               */

#define NWD_WS_CLOSE        0x80000000  /* ウィンドウ終了要求               */

/*--------------------------------------*/
/*      Window Class                    */
/*--------------------------------------*/
enum {
	NWD_WC_WIN,                         /* 通常のウィンドウ             */
	NWD_WC_BUTTON,                      /* ボタン                       */
	NWD_WC_SCRBAR,                      /* スクロールバー               */
	NWD_WC_SCRWIN,                      /* スクロールウィンドウ         */
	NWD_WC_EDITWIN,                     /* エディットウィンドウ         */
	NWD_WC_MENUWIN,                     /* メニューウィンドウ           */

	NWD_WC_CTLBOX                       /* コントロールボックス         */
};

/*--------------------------------------*/
/*      Button Status                   */
/*--------------------------------------*/
#define NWD_BS_DOWN         0x00000001      /* ボタンが押されている         */
#define NWD_BS_INVOKED      0x00000100      /* ボタンの機能が選択された     */
#define NWD_BS_GRAYED       0x00000002      /* 選択できない状態             */

/*--------------------------------------*/
/*      Mouse Status                    */
/*--------------------------------------*/
#define NWD_MS_MOVE         0x00010000      /* マウスが移動した             */

#define NWD_MS_BUTTON       0x000f          /* ボタンが押された             */
#define NWD_MS_LBUTTON      0x0001          /* 左ボタンが押されている       */
#define NWD_MS_RBUTTON      0x0002          /* 右ボタンが押されている       */
#define NWD_MS_MBUTTON      0x0004          /* 中ボタンが押されている       */

#define NWD_MS_BUTTONDOWN   0x00f0          /* ボタンが開放された           */
#define NWD_MS_LBUTTONDOWN  0x0010          /* 左ボタンがクリックされた     */
#define NWD_MS_RBUTTONDOWN  0x0020          /* 右ボタンがクリックされた     */
#define NWD_MS_MBUTTONDOWN  0x0040          /* 中ボタンがクリックされた     */
#define NWD_MS_BUTTONUP     0x0f00          /* ボタンが開放された           */
#define NWD_MS_LBUTTONUP    0x0100          /* 左ボタンが開放された         */
#define NWD_MS_RBUTTONUP    0x0200          /* 右ボタンが開放された         */
#define NWD_MS_MBUTTONUP    0x0400          /* 中ボタンが開放された         */

#define NWD_MS_LBUTTONUP    0x0100          /* 左ボタンが開放された         */
#define NWD_MS_RBUTTONUP    0x0200          /* 右ボタンが開放された         */
#define NWD_MS_MBUTTONUP    0x0400          /* 中ボタンが開放された         */

#define NWD_MS_CONTROL      0x1000          /* コントロールキーが押された   */
#define NWD_MS_SHIFT        0x2000          /* シフトキーが押された         */

/* マウスカーソルの形状 */
#define NWD_MCS_DRAG        0x40000000      /* ウィンドウを移動できる       */
#define NWD_MCS_RESIZE      0x20000000      /* ウィンドウをサイズ変更できる */
#define NWD_MCS_AREAMASK    0x0000ffff      /*                              */

#define NWD_MCS_AREAFRAMET      0x0001      /* ウィンドウフレームの上       */
#define NWD_MCS_AREAFRAMELT     0x0002      /* ウィンドウフレームの左上     */
#define NWD_MCS_AREAFRAMEL      0x0003      /* ウィンドウフレームの左       */
#define NWD_MCS_AREAFRAMELB     0x0004      /* ウィンドウフレームの左下     */
#define NWD_MCS_AREAFRAMEB      0x0005      /* ウィンドウフレームの下       */
#define NWD_MCS_AREAFRAMERB     0x0006      /* ウィンドウフレームの右下     */
#define NWD_MCS_AREAFRAMER      0x0007      /* ウィンドウフレームの右       */
#define NWD_MCS_AREAFRAMERT     0x0008      /* ウィンドウフレームの右上     */
#define NWD_MCS_AREACLIENT      0x0009      /* ウィンドウクライアント       */
#define NWD_MCS_AREACAPTION     0x000a      /* ウィンドウキャプション       */

/* スクロールウィンドウのフラグ */
#define NWD_ES_HORIZONTAL       0x00000001  /* 水平方向スクロール可能       */
#define NWD_ES_VERTICAL         0x00000002  /* 垂直方向スクロール可能       */
#define NWD_ES_USECLIP          0x00010000  /* クリッピングする             */


/*--------------------------------------*/
/*      Message Type                    */
/*--------------------------------------*/
enum {
	NWD_MSG_NULL,                           /*                              */
	NWD_MSG_ALL,                            /*                              */
	NWD_MSG_CLICK,                          /*                              */
	NWD_MSG_LBUTTONDOWN,                    /*                              */
	NWD_MSG_FOCUS,                          /*                              */
	NWD_MSG_CLOSE                           /*                              */
};

/*--------------------------------------*/
/*      Data Type                       */
/*--------------------------------------*/
enum {
	NWD_DT_CHAR,                            /* 符号付き１バイト             */
	NWD_DT_SHORT,                           /* 符号付き２バイト             */
	NWD_DT_INT,                             /* 符号付き４バイト             */
	NWD_DT_LONG,                            /* 符号付き４バイト             */
	NWD_DT_FLOAT,                           /* ３２ビット浮動小数点数       */
	NWD_DT_UCHAR,                           /* 符号なし１バイト             */
	NWD_DT_USHORT,                          /* 符号なし２バイト             */
	NWD_DT_UINT,                            /* 符号なし４バイト             */
	NWD_DT_ULONG                            /* 符号なし４バイト             */
};

/*--------------------------------------*/
/*      Menu Type                       */
/*--------------------------------------*/
#define NWD_MF_NULL       0x0000            /* メニューターミネータ         */
#define NWD_MF_NORMAL     0x0001            /* 通常メニュー項目             */
#define NWD_MF_SEPARATOR  0x0002            /* セパレータ                   */
#define NWD_MF_POPUP      0x0004            /* サブメニュー                 */
#define NWD_MF_CHECKED    0x8000            /* チェックマークあり           */
#define NWD_MF_GRAYED     0x0008            /* 選択不可                     */

/*--------------------------------------*/
/*      Font Size                       */
/*--------------------------------------*/
#define NWD_FONTTYPE_SMALL  1               /*                              */
#define NWD_FONTTYPE_NORMAL 2               /*                              */
#define NWD_FONTTYPE_LARGE  3               /*                              */


/*--------------------------------------*/
/*      Nindows Utility Type            */
/*--------------------------------------*/
#define NWD_DEFWIN_SYSMENU     0            /*                          */
#define NWD_DEFWIN_NINJAINFO   1            /*                          */
#define NWD_DEFWIN_WINDOWINFO  2            /*                          */
#define NWD_DEFWIN_TEXCONTROL  3            /*                          */
#define NWD_DEFWIN_TEXVIEWER   4            /*                          */
#define NWD_DEFWIN_PERINFO     5            /*                          */
#define NWD_DEFWIN_DEBUG       6            /*                          */
#define NWD_DEFWIN_PERFORMANCE 7            /*                          */


/*--------------------------------------*/
/*      Basic Structure                 */
/*--------------------------------------*/
typedef struct _NWS_RGBA {
	Uint8 r;                                /* 赤(0-255)                    */
	Uint8 g;                                /* 緑(0-255)                    */
	Uint8 b;                                /* 青(0-255)                    */
	Uint8 a;                                /* 透明度(0-255) 255:不透明     */
} NWS_RGBA;

typedef struct _NWS_RECT {
	Sint32 left;                            /* 左端                         */
	Sint32 top;                             /* 上端                         */
	Sint32 right;                           /* 右端                         */
	Sint32 bottom;                          /* 下端                         */
} NWS_RECT;

typedef struct _NWS_RECTF {
	Float left;                             /* 左端                         */
	Float top;                              /* 上端                         */
	Float right;                            /* 右端                         */
	Float bottom;                           /* 下端                         */
} NWS_RECTF;

typedef struct _NWS_POINT {
	Sint32 x, y;                            /* 座標                         */
} NWS_POINT;

typedef struct _NWS_MOUSE {
	NWS_POINT pt;                           /* 現在の座標                   */
	Sint32    dt;                           /* 現在の状態                   */
	Sint32    cursor;                       /* 現在のカーソル状態           */
	NWS_POINT oldPt;                        /* 昔の座標                     */
	NWS_POINT mv;                           /* 移動量                       */
	NWS_POINT dragPt;                       /* ドラッグ開始地点             */
} NWS_MOUSE;

/*--------------------------------------*/
/*      Basic Macro                     */
/*--------------------------------------*/
#define nwSetRGBA(_d, _r, _g, _b, _a)	\
	((_d)->r = (_r), (_d)->g = (_g), (_d)->b = (_b), (_d)->a = (_a))

#define nwSetRect(a, b , c, d, e)	\
	((a)->left = (b), (a)->top = (c), (a)->right = (d), (a)->bottom = (e))

/*--------------------------------------*/
/*      Message Structure               */
/*--------------------------------------*/
typedef Bool (*NWF_MSGPROC)(Sint32 msg, Sint32 param1, Sint32 param2);

typedef struct _NWS_MSGHANDLE {
	Sint32      msg;                        /*                              */
	NWF_MSGPROC func;                       /*                              */
} NWS_MSGHANDLE;

/*--------------------------------------*/
/*      Data Structure                  */
/*--------------------------------------*/
typedef struct _NWS_DATA {
	void *dt;                               /* データポインタ               */
	Sint32 type;                            /* データタイプ                 */
} NWS_DATA;


/*--------------------------------------*/
/*      Window Structure                */
/*--------------------------------------*/
typedef struct _NWS_WIN {
	Sint32 style;                           /* ウィンドウスタイル           */
	Sint32 wClass;                          /* ウィンドウのクラス           */
	char* caption;                          /* ウィンドウキャプション名     */
	Sint32 font;                            /* フォントタイプ               */

	struct _NWS_WIN* parent;                /* 自分の親ウィンドウのポインタ */
	struct _NWS_WIN* child;                 /* 自分の子(第１子)ウィンドウ   */
	struct _NWS_WIN* before;                /* 兄弟ウィンドウのポインタ     */
	struct _NWS_WIN* next;                  /* 兄弟ウィンドウのポインタ     */

	Sint32 x, y;                            /* クライアントの座標           */
	Sint32 w, h;                            /* クライアントの幅、高さ       */
/*	Sint32 sx,sy;*/                         /* クライアントのオフセット位置 */

	NWS_RGBA col[4];                        /* ウィンドウの色               */
	NWS_MSGHANDLE* msgHandle;               /* メッセージのハンドラ         */
	void* menuTable;                        /* メニューテーブル             */

	void* userBuf;                          /* ユーザー用バッファ           */
	void (*clientDraw)(struct _NWS_WIN *NWFUNC);
	                                        /* クライアント描画コールバック */
	void (*execFunc)(struct _NWS_WIN *NWFUNC);
	                                        /* ウィドウ処理用関数ポインタ   */
	void (*destructor)(struct _NWS_WIN* NWFUNC);
	                                        /* ウィンドウ破棄時コールバック */
	Sint32 param1, param2;                  /* ユーザー用パラメータ         */
	struct _NWS_WIN* hClose;                /* クローズボックスのハンドル   */
	struct _NWS_WIN* hMaximize;             /* 最大化ボタンのハンドル       */
	struct _NWS_WIN* hMinimize;             /* 最小化ボタンのハンドル       */
} NWS_WIN;

typedef NWS_WIN* NWHWND;
typedef void (*NWF_BUTTONFUNC)(NWHWND);




/*--------------------------------------*/
/*      Button Structure                */
/*--------------------------------------*/
typedef struct _NWS_BUTTON {
	NWS_WIN         base;                   /* 基本ウインドウ               */
	NWF_BUTTONFUNC  func;                   /* 押された時に呼び出す関数     */
	Sint32          state;                  /* ボタンの状態                 */
	Sint32          count;                  /* func の実行までのウェイト    */
} NWS_BUTTON;

/*--------------------------------------*/
/*      ScrollBar Structure             */
/*--------------------------------------*/
typedef struct _NWS_SCRBAR {
	NWS_WIN base;                           /* 基本ウインドウ               */
	Float pos;                              /* 現在値                       */
	Float min;                              /* 最小値                       */
	Float max;                              /* 最大値                       */
	Float lineMove;                         /* 移動値                       */
	Float pageMove;                         /* 移動値                       */
	NWS_DATA dt;                            /* データ                       */
} NWS_SCRBAR;

typedef struct {
	char* caption;                          /* キャプション                 */
	NWS_DATA data;                          /* 関連データ                   */
	Float min, max;                         /* データ最大値、最小値         */
	Float line, page;                       /* ライン移動量、ページ移動量   */
	Float pos;                              /* データ初期値                 */
} NWS_SCROLLBARINFO;

typedef struct {
	Sint32 n;                               /* スクロールバー数             */
	Sint32 style;                           /* スクロールバースタイル       */
	Sint16 x, y;                            /* 座標                         */
	Sint16 w, h;                            /* サイズ                       */
	NWS_SCROLLBARINFO* info;                /* スクロールバー情報           */
} NWS_SCROLLBARLIST;


/*--------------------------------------*/
/*      Scroll Window Structure         */
/*--------------------------------------*/
typedef struct _NWS_SCRWIN {
	NWS_WIN base;                           /* 基本ウィンドウ               */
	Sint32 sx, sy;                          /* スクロールポジション         */
	Sint32 flag;                            /* スクロール可能方向フラグ     */
	NWS_RECT clip;                          /* スクロール可能範囲           */
} NWS_SCRWIN;

/*--------------------------------------*/
/*      Edit Window Structure           */
/*--------------------------------------*/
typedef struct _NWS_EDITWIN {
	NWS_SCRWIN base;                        /* 基本ウィンドウ               */
	Sint32 maxColumn;                       /* 最大桁数                     */
	Sint32 maxLine;                         /* 最大行数                     */
	void* textBuf;                          /* テキストバッファ             */
	Sint32 cx, cy;                          /* 文字入力位置                 */
} NWS_EDITWIN;

/*--------------------------------------*/
/*      Menu Handle                     */
/*--------------------------------------*/
typedef void (*NWF_MENUHANDLE)(NWHWND, Sint32 idx, Sint32 param);

/*--------------------------------------*/
/*      Menu Table Structure            */
/*--------------------------------------*/
typedef struct _NWS_MENUTABLE {
	Sint32         type;                    /* メニュータイプ               */
	char*          title;                   /* メニュータイトル             */
	NWF_MENUHANDLE func;                    /* コールバック関数             */
	Sint32         param;                   /* パラメータ                   */
} NWS_MENUTABLE;


/*--------------------------------------*/
/*      Menu Window Structure           */
/*--------------------------------------*/
typedef struct _NWS_MENUWIN {
	NWS_WIN       base;                     /* 基本ウィンドウ               */
	Sint32        check;                    /* 現在チェック中の項目         */
	NWS_MENUTABLE* menuTable;               /* メニューテーブル             */
} NWS_MENUWIN;


/*--------------------------------------*/
/*      Font Structure                  */
/*--------------------------------------*/
typedef struct _NWS_FONT {
	Sint32      baseChar;                   /* 基本文字                     */
	Sint32      w,  h;                      /* 文字の実サイズ               */
	Sint32      u, v;                       /* 文字のuvサイズ               */
	Sint32      gw, gh;                     /* グリッドのサイズ             */
	Sint32      dw;                         /* テクスチャの横文字数         */
	NJS_TEXNAME* texname;                   /* テクスチャ情報               */
	Uint32      globalIndex;                /* グローバルインデックス       */
} NWS_FONT;


/*--------------------------------------*/
/*      Prototypes                      */
/*--------------------------------------*/

/****************************************/
/*      System                          */
/****************************************/

/* #ifdef __SET4__ */
#if 1  /* Modified by H.Hayashi 99/03/04 */

void nwInitSystem(Uint32 numTextures, Uint32 port);
#else
void nwInitSystem(Uint32 numTextures);
#endif
Sint32 nwExecute(void);
void nwExitSystem(void);
void nwInitResource(void);
Uint32 nwVersion(void);
Float nwGetZ(void);
Float nwAddZ(void);

/****************************************/
/*      Menu                            */
/****************************************/
NWHWND nwCreateMenuWindow(NWS_MENUTABLE* menuTbl, const char* caption,
            Sint32 x, Sint32 y, NWHWND parent);

/****************************************/
/*      Font                            */
/****************************************/
void nwTextOut(NWHWND hWnd, Sint32 x, Sint32 y, const char* fmt, ...);
void nwSetTextColor(NWS_RGBA* col);
Sint32 nwGetFontSize(Sint32* width, Sint32* height);
void nwSelectSystemFont(Sint32 fonttype);

/****************************************/
/*      Button                          */
/****************************************/

NWHWND nwCreateButton(NWF_BUTTONFUNC func, const char* title,
	Sint32 x, Sint32 y, Sint32 w, Sint32 h, NWHWND parent);
void nwEnableButton(NWHWND hWnd, Bool flag);

/****************************************/
/*      Scroll Bar                      */
/****************************************/
NWHWND nwCreateScrollBar(Sint32 type, const char* title,
	Sint32 x, Sint32 y, Sint32 w, Sint32 h, NWHWND parent);
void nwSetScrollBarPos(NWHWND hWnd, Float pos);
void nwSetScrollBarRange(NWHWND hWnd, Float min, Float max);
void nwSetScrollBarData(NWHWND hWnd, NWS_DATA *dt);
void nwSetScrollBarLineMove(NWHWND hWnd, Float step);
void nwSetScrollBarPageMove(NWHWND hWnd, Float step);
void nwCreateScrollBarArray(NWS_SCROLLBARLIST* list, NWHWND parent);

/****************************************/
/*      Scroll Window                   */
/****************************************/
Bool nwScrWinEnableScroll(NWHWND hWnd, Sint32 flag);
Bool nwScrWinSetClip(NWHWND hWNd, NWS_RECT* rect);
Bool nwScrWinScroll(NWHWND hWnd, Sint32 x, Sint32 y);
Bool nwScrWinGetScroll(NWHWND hWnd, Sint32* x, Sint32* y);

/****************************************/
/*      Edit Window                     */
/****************************************/
NWHWND nwCreateEditWindow(Sint32 tw, Sint32 th, void* tBuf, Sint32 tBufSize,
	const char* caption, Sint32 style,
	Sint32 x, Sint32 y, Sint32 w, Sint32 h, NWHWND parent);
Bool nwEditWinAddString(NWHWND hWnd, const char* string);
Bool nwEditWinPrintf(NWHWND hWnd, const char* fmt, ...);

/****************************************/
/*      Window Management               */
/****************************************/
NWHWND nwCreateWindow(Sint32 wClass, const char* caption, Sint32 style,
	Sint32 x, Sint32 y, Sint32 w, Sint32 h, NWHWND parent);
void nwDestroyWindow(NWHWND hWnd);

void nwBringWindowToTop(NWHWND hWnd);
NWHWND nwFindWindow(NWHWND hWnd, const char* name);
NWHWND nwFindWindowByPos(Sint16 x, Sint16 y);
NWHWND nwFindWindowEx(NWHWND hWnd, const char* name);

void nwGetClientRect(NWHWND hWnd, NWS_RECT* rc);
Bool nwGetWindowColor(NWHWND hWnd, NWS_RGBA* col);
Bool nwGetWindowPos(NWHWND hWnd, Sint32* x, Sint32* y);
void nwGetWindowRect(NWHWND hWnd, NWS_RECT* rc);
Bool nwGetWindowSize(NWHWND hWnd, Sint32* w, Sint32* h);
Bool nwGetWindowStyle(NWHWND hWnd, Sint32* style);
Sint32 nwGetWindowText(NWHWND hWnd, char *buf, Sint32 size);

Bool nwSetWindowColor(NWHWND hWnd, NWS_RGBA* col);
Bool nwSetWindowStyle(NWHWND hWnd, Sint32 and_style, Sint32 or_style);
Bool nwSetWindowPos(NWHWND hWnd, Sint32 x, Sint32 y);
Bool nwSetWindowSize(NWHWND hWnd, Sint32 w, Sint32 h);
Bool nwSetWindowText(NWHWND hWnd, const char* text);


/****************************************/
/*      Common Dialog                   */
/****************************************/
NWHWND nwCreateColorDialog(Sint32 x, Sint32 y, NWS_RGBA* rgba, NWHWND parent);
NWHWND nwCreatePropertyDialog(NWHWND hWnd, Sint32 x, Sint32 y);

/****************************************/
/*      Nindows Utility                 */
/****************************************/
void nwDebugPrintf(Sint8 *fmt, ...);
void nwSetDefWindowColor(Sint32 win, NWS_RGBA* col);
void nwSetDefWindowStyle(Sint32 win, Sint32 and_style, Sint32 or_style);
void nwSetDefWindowPos(Sint32 win, Sint32 x, Sint32 y);
void nwSetDefWindowSize(Sint32 win, Sint32 w, Sint32 h);
void nwSetUserMenu(NWS_MENUTABLE* menu);

/****************************************/
/*      Mouse                           */
/****************************************/
void nwGetMousePosition(Sint32* x, Sint32* y);
void nwSetMousePosition(Sint32 x, Sint32 y);
void nwGetMouseSpeed(Sint32* x, Sint32* y);
void nwSetMouseSpeed(Sint32 x, Sint32 y);
void nwEnablePeripheral(Bool flag);


#ifdef __cplusplus
}
#endif

#endif /* _NINDOWS_H_ */
