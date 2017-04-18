/*
 *  Shinobi Library
 *  Copyright (c) 1998 SEGA
 *
 *       Keyboard
 *
 *  Module  : Library Header File
 *  File    : sg_pdkbd.h
 *  Create  : 1998-03-25
 *  Modify  : 1999-05-27
 *  Version : 1.50
 *  Note    :
 */

#ifndef _SG_PDKBD_H_
#define _SG_PDKBD_H_

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

#include <sg_xpt.h>
#include <sg_pad.h>


/*
 *  DEFINES / MACROS
 */

/******** 特殊キービットアサイン ********************************************/
/******** Special keys bit assign *******************************************/
#define PDD_KEY_CTRL_RGUI     (1 << 7)     /* S2                            */
#define PDD_KEY_CTRL_RALT     (1 << 6)     /* R-ALT                         */
#define PDD_KEY_CTRL_RSHIFT   (1 << 5)     /* R-SHIFT                       */
#define PDD_KEY_CTRL_RCTRL    (1 << 4)     /* R-CTRL                        */
#define PDD_KEY_CTRL_LGUI     (1 << 3)     /* S1                            */
#define PDD_KEY_CTRL_LALT     (1 << 2)     /* L-ALT                         */
#define PDD_KEY_CTRL_LSHIFT   (1 << 1)     /* L-SHIFT                       */
#define PDD_KEY_CTRL_LCTRL    (1 << 0)     /* L-CTRL                        */
#define PDD_KEY_CTRL_S2       (1 << 7)     /* S2                            */
#define PDD_KEY_CTRL_S1       (1 << 3)     /* S1                            */

/******** LED点灯状態 *******************************************************/
/******** LED lighting state ************************************************/
#define PDD_LED_SHIFT         (1 << 7)     /* Shift                         */
#define PDD_LED_POWER         (1 << 6)     /* Power                         */
#define PDD_LED_KANA          (1 << 5)     /* Kana                          */
#define PDD_LED_SCRLOCK       (1 << 2)     /* Scroll Lock                   */
#define PDD_LED_CAPLOCK       (1 << 1)     /* Caps Lock                     */
#define PDD_LED_NUMLOCK       (1 << 0)     /* Num Lock                      */

/******** キーボード言語 ****************************************************/
/******** Keyboard language *************************************************/
#define PDD_KBDLANG_JP        0x01         /* Japan                         */
#define PDD_KBDLANG_US        0x02         /* America                       */
#define PDD_KBDLANG_UK        0x03         /* England                       */
#define PDD_KBDLANG_GERMANY   0x04         /* Germany                       */
#define PDD_KBDLANG_FRANCE    0x05         /* France                        */
#define PDD_KBDLANG_ITALY     0x06         /* Italy                         */
#define PDD_KBDLANG_SPAIN     0x07         /* Spain                         */
#define PDD_KBDLANG_SWEDEN    0x08         /* Sweden                        */
#define PDD_KBDLANG_SWITZER   0x09         /* Switzerland                   */
#define PDD_KBDLANG_NETHER    0x0a         /* The Netherlands               */
#define PDD_KBDLANG_PORTUGAL  0x0b         /* Portugal                      */
#define PDD_KBDLANG_LATIN     0x0c         /* Latin America                 */
#define PDD_KBDLANG_CANFRENCH 0x0d         /* Canadian French               */
#define PDD_KBDLANG_RUSSIA    0x0e         /* Russia                        */
#define PDD_KBDLANG_CHINA     0x0f         /* China                         */
#define PDD_KBDLANG_KOREA     0x10         /* Korea                         */
                                           /* 0x11 - 0xff are reserved      */

/******** キーボードタイプ***************************************************/
/******** Keyboard type *****************************************************/
#define PDD_KBDTYPE_89        0x01         /*  89 keys                      */
#define PDD_KBDTYPE_92        0x02         /*  92 keys                      */
#define PDD_KBDTYPE_101       0x03         /* 101 keys                      */
#define PDD_KBDTYPE_102       0x04         /* 102 keys                      */
#define PDD_KBDTYPE_104       0x05         /* 104 keys                      */
#define PDD_KBDTYPE_105       0x06         /* 105 keys                      */
#define PDD_KBDTYPE_106       0x07         /* 106 keys                      */
#define PDD_KBDTYPE_109       0x08         /* 109 keys                      */
#define PDD_KBDTYPE_87        0x09         /*  87 keys                      */
#define PDD_KBDTYPE_88        0x0a         /*  88 keys                      */
                                           /* 0x0b - 0xff are reserved      */

/******** LEDの制御 *********************************************************/
/******** LED Control *******************************************************/
#define PDD_LEDCTRL_HOST      0x00         /* ホスト(DC)が制御する          */
                                           /* Dreamcast controls LCD.       */
#define PDD_LEDCTRL_KEYBOARD  0x80         /* キーボードが制御する          */
                                           /* Keyboard controler LCD.       */


/*
 *  TYPEDEFS
 */

/******** キーボード情報構造体 *********************************************/
/******** Keyboard info structure ******************************************/
typedef struct {
	Uint8 lang;                           /* キーボード言語                */
	                                      /* Language                      */
	Uint8 type;                           /* キーボードタイプ              */
	                                      /* Type                          */
	Uint8 led;                            /* LEDの種類                     */
	                                      /* LED Type                      */
	Uint8 led_ctrl;                       /* LEDの制御                     */
	                                      /* LED Control                   */
} PDS_KEYBOARDINFO;

/******** キーボードデータ構造体 *******************************************/
/******** Keyboard data structure ******************************************/
typedef struct {
	Uint8 ctrl;                           /* 特殊キーの状態                */
	                                      /* Special keys state            */
	Uint8 led;                            /* LEDの点灯状態                 */
	                                      /* LED lighting state            */
	Uint8 key[6];                         /* 押されているキーコード        */
	                                      /* key codes                     */
	PDS_KEYBOARDINFO* info;               /* キーボード情報へのポインタ    */
	                                      /* Pointer to keyboard info      */
} PDS_KEYBOARD;


/* PDS_KEYBOARD key[] array settings
   key[] stores up to 6 presses */

/* U.S. keyboard (101 keys). */
enum
{
	PDD_KEYUS_NONE = 0x00,		// 0x00 *
	PDD_KEYUS_ROLLOVER,			// 0x01 *
	PDD_KEYUS_FAIL,				// 0x02
	PDD_KEYUS_UNDEFINED,		// 0x03
	PDD_KEYUS_A,				// 0x04 *
	PDD_KEYUS_B,				// 0x05 *
	PDD_KEYUS_C,				// 0x06 *
	PDD_KEYUS_D,				// 0x07 *
	PDD_KEYUS_E,				// 0x08 *
	PDD_KEYUS_F,				// 0x09 *
	PDD_KEYUS_G,				// 0x0A *
	PDD_KEYUS_H,				// 0x0B *
	PDD_KEYUS_I,				// 0x0C *
	PDD_KEYUS_J,				// 0x0D *
	PDD_KEYUS_K,				// 0x0E *
	PDD_KEYUS_L,				// 0x0F *
	PDD_KEYUS_M,				// 0x10 *
	PDD_KEYUS_N,				// 0x11 *
	PDD_KEYUS_O,				// 0x12 *
	PDD_KEYUS_P,				// 0x13 *
	PDD_KEYUS_Q,				// 0x14 *
	PDD_KEYUS_R,				// 0x15 *
	PDD_KEYUS_S,				// 0x16 *
	PDD_KEYUS_T,				// 0x17 *
	PDD_KEYUS_U,				// 0x18 *
	PDD_KEYUS_V,				// 0x19 *
	PDD_KEYUS_W,				// 0x1A *
	PDD_KEYUS_X,				// 0x1B *
	PDD_KEYUS_Y,				// 0x1C *
	PDD_KEYUS_Z,				// 0x1D *

	PDD_KEYUS_1,				// 0x1E *
	PDD_KEYUS_2,				// 0x1F *
	PDD_KEYUS_3,				// 0x20 *
	PDD_KEYUS_4,				// 0x21 *
	PDD_KEYUS_5,				// 0x22 *
	PDD_KEYUS_6,				// 0x23 *
	PDD_KEYUS_7,				// 0x24 *
	PDD_KEYUS_8,				// 0x25 *
	PDD_KEYUS_9,				// 0x26 *
	PDD_KEYUS_0,				// 0x27 *

	PDD_KEYUS_RETURN,			// 0x28 *
	PDD_KEYUS_ESC,				// 0x29 *
	PDD_KEYUS_BACKSPACE,		// 0x2A *
	PDD_KEYUS_TAB,				// 0x2B *
	PDD_KEYUS_SPACE,			// 0x2C *
	PDD_KEYUS_MINUS,			// 0x2D *
	PDD_KEYUS_PLUS,				// 0x2E *
	PDD_KEYUS_LBRACKET,			// 0x2F *
	PDD_KEYUS_RBRACKET,			// 0x30 *
	PDD_KEYUS_BSLASH,			// 0x31 *
	PDD_KEYUS_UNUSED0,			// 0x32
	PDD_KEYUS_SEMICOLON,		// 0x33 *
	PDD_KEYUS_QUOTE,			// 0x34 *
	PDD_KEYUS_TILDA,			// 0x35 *
	PDD_KEYUS_COMMA,			// 0x36 *
	PDD_KEYUS_PERIOD,			// 0x37 *
	PDD_KEYUS_FSLASH,			// 0x38 *
	PDD_KEYUS_CAPSLOCK,			// 0x39 *

	PDD_KEYUS_F1,				// 0x3A *
	PDD_KEYUS_F2,				// 0x3B *
	PDD_KEYUS_F3,				// 0x3C *
	PDD_KEYUS_F4,				// 0x3D *
	PDD_KEYUS_F5,				// 0x3E *
	PDD_KEYUS_F6,				// 0x3F *
	PDD_KEYUS_F7,				// 0x40 *
	PDD_KEYUS_F8,				// 0x41 *
	PDD_KEYUS_F9,				// 0x42 *
	PDD_KEYUS_F10,				// 0x43 *
	PDD_KEYUS_F11,				// 0x44 *
	PDD_KEYUS_F12,				// 0x45 *

	PDD_KEYUS_PRINT,			// 0x46 *
	PDD_KEYUS_SCRLOCK,			// 0x47 *
	PDD_KEYUS_PAUSE,			// 0x48 *

	PDD_KEYUS_INSERT,			// 0x49 *
	PDD_KEYUS_HOME,				// 0x4A *
	PDD_KEYUS_PGUP,				// 0x4B *
	PDD_KEYUS_DEL,				// 0x4C *
	PDD_KEYUS_END,				// 0x4D *
	PDD_KEYUS_PGDN,				// 0x4E *

	PDD_KEYUS_RIGHT,			// 0x4F *
	PDD_KEYUS_LEFT,				// 0x50 *
	PDD_KEYUS_DOWN,				// 0x51 *
	PDD_KEYUS_UP,				// 0x52 *

	PDD_KEYUS_PAD_NUMLOCK,		// 0x53 *
	PDD_KEYUS_PAD_DIVIDE,		// 0x54 *
	PDD_KEYUS_PAD_MULT,			// 0x55 *
	PDD_KEYUS_PAD_MINUS,		// 0x56 *
	PDD_KEYUS_PAD_PLUS,			// 0x57 *
	PDD_KEYUS_PAD_ENTER,		// 0x58 *
	PDD_KEYUS_PAD_END,			// 0x59 *
	PDD_KEYUS_PAD_DOWN,			// 0x5A *
	PDD_KEYUS_PAD_PGDN,			// 0x5B *
	PDD_KEYUS_PAD_LEFT,			// 0x5C *
	PDD_KEYUS_PAD_5,			// 0x5D *
	PDD_KEYUS_PAD_RIGHT,		// 0x5E *
	PDD_KEYUS_PAD_HOME,			// 0x5F *
	PDD_KEYUS_PAD_UP,			// 0x60 *
	PDD_KEYUS_PAD_PGUP,			// 0x61 *
	PDD_KEYUS_PAD_INSERT,		// 0x62 *
	PDD_KEYUS_PAD_DEL,			// 0x63 *

								// Numeric Keypad definitions
	PDD_KEYUS_PAD_1 = 0x59,		// 0x59 *
	PDD_KEYUS_PAD_2,			// 0x5A *
	PDD_KEYUS_PAD_3,			// 0x5B *
	PDD_KEYUS_PAD_4,			// 0x5C *
//	PDD_KEYUS_PAD_5,			// 0x5D * Same as above definition
	PDD_KEYUS_PAD_6 = 0x5E,		// 0x5E *
	PDD_KEYUS_PAD_7,			// 0x5F *
	PDD_KEYUS_PAD_8,			// 0x60 *
	PDD_KEYUS_PAD_9,			// 0x61 *
	PDD_KEYUS_PAD_0,			// 0x62 *
	PDD_KEYUS_PAD_PERIOD,		// 0x63 *

	PDD_KEYUS_UNUSED1,			// 0x64

	PDD_KEYUS_S3				// 0x65 *
};

/* Japanese keyboard (88 keys). */
enum
{
	PDD_KEYJ_NONE = 0x00,
	PDD_KEYJ_ROLLOVER,
	PDD_KEYJ_FAIL,
	PDD_KEYJ_UNDEFINED,
	PDD_KEYJ_A,
	PDD_KEYJ_B,
	PDD_KEYJ_C,
	PDD_KEYJ_D,
	PDD_KEYJ_E,
	PDD_KEYJ_F,
	PDD_KEYJ_G,
	PDD_KEYJ_H,
	PDD_KEYJ_I,
	PDD_KEYJ_J,
	PDD_KEYJ_K,
	PDD_KEYJ_L,
	PDD_KEYJ_M,
	PDD_KEYJ_N,
	PDD_KEYJ_O,
	PDD_KEYJ_P,
	PDD_KEYJ_Q,
	PDD_KEYJ_R,
	PDD_KEYJ_S,
	PDD_KEYJ_T,
	PDD_KEYJ_U,
	PDD_KEYJ_V,
	PDD_KEYJ_W,
	PDD_KEYJ_X,
	PDD_KEYJ_Y,
	PDD_KEYJ_Z,

	PDD_KEYJ_1,
	PDD_KEYJ_2,
	PDD_KEYJ_3,
	PDD_KEYJ_4,
	PDD_KEYJ_5,
	PDD_KEYJ_6,
	PDD_KEYJ_7,
	PDD_KEYJ_8,
	PDD_KEYJ_9,
	PDD_KEYJ_0,

	PDD_KEYJ_RETURN,
	PDD_KEYJ_ESC,
	PDD_KEYJ_BACKSPACE,
	PDD_KEYJ_TAB,
	PDD_KEYJ_SPACE,
	PDD_KEYJ_MINUS,
	PDD_KEYJ_POWER,
	PDD_KEYJ_AT,
	PDD_KEYJ_LBRACKET,
	PDD_UNUSED0,
	PDD_KEYJ_RBRACKET,
	PDD_KEYJ_SEMICOLON,
	PDD_KEYJ_COLON,
	PDD_KEYJ_KAKU,
	PDD_KEYJ_COMMA,
	PDD_KEYJ_PERIOD,
	PDD_KEYJ_FSLASH,
	PDD_KEYJ_CAPSLOCK,

	PDD_KEYJ_F1,
	PDD_KEYJ_F2,
	PDD_KEYJ_F3,
	PDD_KEYJ_F4,
	PDD_KEYJ_F5,
	PDD_KEYJ_F6,
	PDD_KEYJ_F7,
	PDD_KEYJ_F8,
	PDD_KEYJ_F9,
	PDD_KEYJ_F10,
	PDD_KEYJ_F11,
	PDD_KEYJ_F12,

	PDD_KEYJ_PRINT,
	PDD_KEYJ_SCRLOCK,
	PDD_KEYJ_PAUSE,

	PDD_KEYJ_INSERT,
	PDD_KEYJ_HOME,
	PDD_KEYJ_PGUP,
	PDD_KEYJ_DEL,
	PDD_KEYJ_END,
	PDD_KEYJ_PGDN,

	PDD_KEYJ_RIGHT,
	PDD_KEYJ_LEFT,
	PDD_KEYJ_DOWN,
	PDD_KEYJ_UP,

	PDD_KEYJ_APP	= 0x65,
	PDD_KEYJ_BSLASH = 0x87,
	PDD_KEYJ_KANA,
	PDD_KEYJ_OR,
	PDD_KEYJ_HENKAN,
	PDD_KEYJ_MUHENKAN
};


/*
 *  PROTOTYPES
 */

/******** 低レベルキーボード関数 *******************************************/
/******** Low level keyboard functions *************************************/
void pdKbdInit(void);
void pdKbdExit(void);
const PDS_KEYBOARD* pdKbdGetData(Uint32 port);
const PDS_KEYBOARDINFO* pdKbdGetInfo(Uint32 port);
void pdKbdExecServer(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _SG_PDKBD_H_ */
