/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


#ifndef __HELPIDS_H
#define __HELPIDS_H

// from WINUSER.H
#define IDOK                1
#define IDCANCEL            2
#define IDABORT             3
#define IDRETRY             4
#define IDIGNORE            5
#define IDYES               6
#define IDNO                7
#define IDCLOSE             8
#define IDHELP              9

// from AFXRES.H
#define ID_EDIT_COPY        0xE122


// Constants < 0x20000000 are for popup text
#define IDH_COPYINFO            0x10000000
#define IDH_SELECT_LIMIT_CHAR   0x10000001

/** constants for extension module **/
#define IDH_EXT_WWW             1117            // same as IDC_WWW
#define IDH_EXT_NAME            0x12000000
#define IDH_EXT_CODE            0x12000001
#define IDH_EXT_REGISTER        0x12000002
#define IDH_EXT_ENOUGH          0x12000003
#define IDH_EXT_PERIOD          0x12000004
#define IDH_EXT_USE_AUTO_KEY    0x12000005
#define IDH_EXT_USE_WEB_KEY     0x12000006

// Constants 0x20000000...0x2FFFFFFF use window type 'PopupTopicWnd'
#define IDH_SNAP                0x20000001
#define IDH_USE_WWHIZ           0x20000002
#define IDH_DISP_DELIM          0x20000003
#define IDH_REASON              0x20000004
#define IDH_USE_GROUP_OPS       0x20000005
#define IDH_DISCLAMER           0x20000006
#define IDH_PIPELINE            0x20000007

#define IDH_OPTPAGE_TABS_LAYOUT     0x20000100
#define IDH_OPTPAGE_TABS_CONTENT    0x20000101
#define IDH_OPTPAGE_TABS_ORDERING   0x20000102
#define IDH_OPTPAGE_TABS_TRIMMING   0x20000103
#define IDH_OPTPAGE_TABS_ADVANCED   0x20000104
#define IDH_OPTPAGE_WINFILEMAN      0x20000105
#define IDH_OPTPAGE_CUST_MENUS      0x20000106
#define IDH_OPTPAGE_CUST_KBD        0x20000107
#define IDH_OPTPAGE_CUST_MOUSE      0x20000108
#define IDH_OPTPAGE_GENERAL         0x20000109
#define IDH_OPTPAGE_INTERNET        0x20000110
#define IDH_OPTPAGE_LANGUAGES       0x20000111
#define IDH_OPTPAGE_REGISTRATION    0x20000112

// Constants 0x30000000...0x3000FFFF use window types registered with the
// RegisterHTMLHelpWindowType() function.
// The type number is designated in the lower byte of the high word, i.e.
// the number format is 0x30NN0000 where NN denotes the type number.
// When NN = 0, the default window type is used.
#define IDH_WELCOME             0x30000000
#define IDH_REGISTER            0x30000001
#define IDH_CUSTOMIZE_COMMANDS  0x30000002
#define IDH_CUSTOMIZE_KEYBOARD  0x30000003
#define IDH_CUSTOMIZE_OPTIONS   0x30000004
#define IDH_WNDTABSEXT          0x30000005
#define IDH_CONTACT_INFO        0x30000006


#include "..\Resource.h"

#endif // __HELPIDS_H

