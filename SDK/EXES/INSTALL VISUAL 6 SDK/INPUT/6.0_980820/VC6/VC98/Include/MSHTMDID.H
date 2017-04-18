//*********************************************************************
//*                  Microsoft Windows                               **
//*            Copyright(c) Microsoft Corp., 1996-1998               **
//*********************************************************************


#ifndef __MSHTMDID_H__
#define __MSHTMDID_H__

#define DISPID_XOBJ_MIN                 0x80010000
#define DISPID_XOBJ_MAX                 0x8001FFFF
#define DISPID_XOBJ_BASE                DISPID_XOBJ_MIN
#define DISPID_HTMLOBJECT               (DISPID_XOBJ_BASE   + 500)
#define DISPID_ELEMENT                  (DISPID_HTMLOBJECT  + 500)
#define DISPID_SITE                     (DISPID_ELEMENT     + 1000)
#define DISPID_OBJECT                   (DISPID_SITE        + 1000)
#define DISPID_STYLE                    (DISPID_OBJECT      + 1000)
#define DISPID_ATTRS                    (DISPID_STYLE       + 1000)
#define DISPID_EVENTS                   (DISPID_ATTRS       + 1000)
#define DISPID_XOBJ_EXPANDO             (DISPID_EVENTS      + 1000)
#define DISPID_XOBJ_ORDINAL             (DISPID_XOBJ_EXPANDO+ 1000)

//
// Standard control properties
//

#define DISPID_CommonCtrl_FONTNAME        1
#define DISPID_CommonCtrl_FONTSIZE        2
#define DISPID_CommonCtrl_FONTBOLD        3
#define DISPID_CommonCtrl_FONTITAL        4
#define DISPID_CommonCtrl_FONTUNDER       5
#define DISPID_CommonCtrl_FONTSTRIKE      6
#define DISPID_CommonCtrl_FONTWEIGHT      7
#define DISPID_CommonCtrl_FONTCHARSET     8
#define DISPID_CommonCtrl_FONTSUPERSCRIPT 9
#define DISPID_CommonCtrl_FONTSUBSCRIPT   10

// Data Binding DISPID's
#define DISPID_MSDATASRCINTERFACE       (-3900)
#define DISPID_ADVISEDATASRCCHANGEEVENT (-3901)


// DISPID values for HTML Dialogs files per interface

#define DISPID_HTMLDLG                          25000
#define DISPID_HTMLDLGMODEL                     26000

//----------------------------------------------------------------------------
//
//  Semi-standard x-object properties.
//
//  These values match those used by VB and are for the benefit of controls
//  with hard coded knowledge of VB.
//
//----------------------------------------------------------------------------

#define STDPROPID_XOBJ_NAME                 (DISPID_XOBJ_BASE + 0x0)
#define STDPROPID_XOBJ_INDEX                (DISPID_XOBJ_BASE + 0x1)
#define STDPROPID_XOBJ_BASEHREF             (DISPID_XOBJ_BASE + 0x2)
#define STDPROPID_XOBJ_LEFT                 (DISPID_XOBJ_BASE + 0x3)
#define STDPROPID_XOBJ_TOP                  (DISPID_XOBJ_BASE + 0x4)
#define STDPROPID_XOBJ_WIDTH                (DISPID_XOBJ_BASE + 0x5)
#define STDPROPID_XOBJ_HEIGHT               (DISPID_XOBJ_BASE + 0x6)
#define STDPROPID_XOBJ_VISIBLE              (DISPID_XOBJ_BASE + 0x7)
#define STDPROPID_XOBJ_PARENT               (DISPID_XOBJ_BASE + 0x8)
#define STDPROPID_XOBJ_DRAGMODE             (DISPID_XOBJ_BASE + 0x9)
#define STDPROPID_XOBJ_DRAGICON             (DISPID_XOBJ_BASE + 0xA)
#define STDPROPID_XOBJ_TAG                  (DISPID_XOBJ_BASE + 0xB)
#define STDPROPID_XOBJ_TABSTOP              (DISPID_XOBJ_BASE + 0xE)
#define STDPROPID_XOBJ_TABINDEX             (DISPID_XOBJ_BASE + 0xF)
#define STDPROPID_XOBJ_HELPCONTEXTID        (DISPID_XOBJ_BASE + 0x32)
#define STDPROPID_XOBJ_DEFAULT              (DISPID_XOBJ_BASE + 0x37)
#define STDPROPID_XOBJ_CANCEL               (DISPID_XOBJ_BASE + 0x38)
#define STDPROPID_XOBJ_LEFTNORUN            (DISPID_XOBJ_BASE + 0x39)
#define STDPROPID_XOBJ_TOPNORUN             (DISPID_XOBJ_BASE + 0x3A)
#define STDPROPID_XOBJ_ALIGNPERSIST         (DISPID_XOBJ_BASE + 0x3C)
#define STDPROPID_XOBJ_LINKTIMEOUT          (DISPID_XOBJ_BASE + 0x3D)
#define STDPROPID_XOBJ_LINKTOPIC            (DISPID_XOBJ_BASE + 0x3E)
#define STDPROPID_XOBJ_LINKITEM             (DISPID_XOBJ_BASE + 0x3F)
#define STDPROPID_XOBJ_LINKMODE             (DISPID_XOBJ_BASE + 0x40)
#define STDPROPID_XOBJ_DATACHANGED          (DISPID_XOBJ_BASE + 0x41)
#define STDPROPID_XOBJ_DATAFIELD            (DISPID_XOBJ_BASE + 0x42)
#define STDPROPID_XOBJ_DATASOURCE           (DISPID_XOBJ_BASE + 0x43)
#define STDPROPID_XOBJ_WHATSTHISHELPID      (DISPID_XOBJ_BASE + 0x44)
#define STDPROPID_XOBJ_CONTROLTIPTEXT       (DISPID_XOBJ_BASE + 0x45)
#define STDPROPID_XOBJ_STATUSBARTEXT        (DISPID_XOBJ_BASE + 0x46)
#define STDPROPID_XOBJ_APPLICATION          (DISPID_XOBJ_BASE + 0x47)
#define STDPROPID_XOBJ_BLOCKALIGN           (DISPID_XOBJ_BASE + 0x48)
#define STDPROPID_XOBJ_CONTROLALIGN         (DISPID_XOBJ_BASE + 0x49)
#define STDPROPID_XOBJ_STYLE                (DISPID_XOBJ_BASE + 0x4A)
#define STDPROPID_XOBJ_COUNT                (DISPID_XOBJ_BASE + 0x4B)
#define STDPROPID_XOBJ_DISABLED             (DISPID_XOBJ_BASE + 0x4C)

//----------------------------------------------------------------------------
//
//  Semi-standard x-object properties.
//
//  These are events that are fired for all sites
//----------------------------------------------------------------------------

#define STDDISPID_XOBJ_ONBLUR                           (DISPID_XOBJ_BASE)
#define STDDISPID_XOBJ_ONFOCUS                          (DISPID_XOBJ_BASE + 1)
#define STDDISPID_XOBJ_BEFOREUPDATE                     (DISPID_XOBJ_BASE + 4)
#define STDDISPID_XOBJ_AFTERUPDATE                      (DISPID_XOBJ_BASE + 5)
#define STDDISPID_XOBJ_ONROWEXIT                        (DISPID_XOBJ_BASE + 6)
#define STDDISPID_XOBJ_ONROWENTER                       (DISPID_XOBJ_BASE + 7)
#define STDDISPID_XOBJ_ONMOUSEOVER                      (DISPID_XOBJ_BASE + 8)
#define STDDISPID_XOBJ_ONMOUSEOUT                       (DISPID_XOBJ_BASE + 9)
#define STDDISPID_XOBJ_ONHELP                           (DISPID_XOBJ_BASE + 10)
#define STDDISPID_XOBJ_ONDRAGSTART                      (DISPID_XOBJ_BASE + 11)
#define STDDISPID_XOBJ_ONSELECTSTART                    (DISPID_XOBJ_BASE + 12)
#define STDDISPID_XOBJ_ERRORUPDATE                      (DISPID_XOBJ_BASE + 13)
#define STDDISPID_XOBJ_ONDATASETCHANGED                 (DISPID_XOBJ_BASE + 14)
#define STDDISPID_XOBJ_ONDATAAVAILABLE                  (DISPID_XOBJ_BASE + 15)
#define STDDISPID_XOBJ_ONDATASETCOMPLETE                (DISPID_XOBJ_BASE + 16)
#define STDDISPID_XOBJ_ONFILTER                         (DISPID_XOBJ_BASE + 17)

//----------------------------------------------------------------------------
//
//  Base DISPIDs for each class.
//
//  Object and its base classes must use ids in the reserved x-object range.
//
//----------------------------------------------------------------------------

#define DISPID_NORMAL_FIRST                     1000
#define DISPID_ANCHOR                           DISPID_NORMAL_FIRST
#define DISPID_BLOCK                            DISPID_NORMAL_FIRST
#define DISPID_BODY                             (DISPID_TEXTSITE + 1000)
#define DISPID_BR                               DISPID_NORMAL_FIRST
#define DISPID_BGSOUND                          DISPID_NORMAL_FIRST
#define DISPID_DD                               DISPID_NORMAL_FIRST
#define DISPID_DIR                              DISPID_NORMAL_FIRST
#define DISPID_DIV                              DISPID_NORMAL_FIRST
#define DISPID_DL                               DISPID_NORMAL_FIRST
#define DISPID_DT                               DISPID_NORMAL_FIRST
#define DISPID_EFONT                            DISPID_NORMAL_FIRST
#define DISPID_FORM                             DISPID_NORMAL_FIRST
#define DISPID_HEADER                           DISPID_NORMAL_FIRST
#define DISPID_HEDELEMS                         DISPID_NORMAL_FIRST
#define DISPID_HR                               DISPID_NORMAL_FIRST
#define DISPID_LABEL                            DISPID_NORMAL_FIRST
#define DISPID_LI                               DISPID_NORMAL_FIRST
#define DISPID_IMGBASE                          DISPID_NORMAL_FIRST
#define DISPID_IMG                              (DISPID_IMGBASE + 1000)
#define DISPID_INPUTIMAGE                       (DISPID_IMGBASE + 1000)
#define DISPID_INPUT                            (DISPID_TEXTSITE + 1000)
#define DISPID_INPUTTEXTBASE                    (DISPID_INPUT+1000)
#define DISPID_INPUTTEXT                        (DISPID_INPUTTEXTBASE+1000)
#define DISPID_MENU                             DISPID_NORMAL_FIRST
#define DISPID_OL                               DISPID_NORMAL_FIRST
#define DISPID_PARA                             DISPID_NORMAL_FIRST
#define DISPID_SELECT                           DISPID_NORMAL_FIRST
#define DISPID_SELECTOBJ                        DISPID_NORMAL_FIRST
#define DISPID_TABLE                            DISPID_NORMAL_FIRST
#define DISPID_TEXTSITE                         DISPID_NORMAL_FIRST
#define DISPID_TEXTAREA                         (DISPID_INPUTTEXT + 1000)
#define DISPID_MARQUEE                          (DISPID_TEXTAREA + 1000)
#define DISPID_UL                               DISPID_NORMAL_FIRST
#define DISPID_PHRASE                           DISPID_NORMAL_FIRST
#define DISPID_UNKNOWNPDL                       DISPID_NORMAL_FIRST
#define DISPID_COMMENTPDL                       DISPID_NORMAL_FIRST
#define DISPID_TABLECELL                        (DISPID_TEXTSITE + 1000)
#define DISPID_RANGE                            DISPID_NORMAL_FIRST
#define DISPID_SELECTION                        DISPID_NORMAL_FIRST
#define DISPID_OPTION                           DISPID_NORMAL_FIRST
#define DISPID_1D                               (DISPID_TEXTSITE + 1000)
#define DISPID_MAP                              DISPID_NORMAL_FIRST
#define DISPID_AREA                             DISPID_NORMAL_FIRST
#define DISPID_PARAM                            DISPID_NORMAL_FIRST
#define DISPID_TABLESECTION                     DISPID_NORMAL_FIRST
#define DISPID_TABLEROW                         DISPID_NORMAL_FIRST
#define DISPID_TABLECOL                         DISPID_NORMAL_FIRST
#define DISPID_SCRIPT                           DISPID_NORMAL_FIRST
#define DISPID_STYLESHEET                       DISPID_NORMAL_FIRST
#define DISPID_STYLERULE                        DISPID_NORMAL_FIRST
#define DISPID_STYLESHEETS_COL                  DISPID_NORMAL_FIRST
#define DISPID_STYLERULES_COL                   DISPID_NORMAL_FIRST
#define DISPID_MIMETYPES_COL                    DISPID_NORMAL_FIRST
#define DISPID_PLUGINS_COL                      DISPID_NORMAL_FIRST
#define DISPID_2D                               DISPID_NORMAL_FIRST
#define DISPID_OMWINDOW                         DISPID_NORMAL_FIRST
#define DISPID_EVENTOBJ                         DISPID_NORMAL_FIRST
#define DISPID_OLESITE                          DISPID_NORMAL_FIRST
#define DISPID_FRAMESET                         DISPID_NORMAL_FIRST
#define DISPID_LINK                             DISPID_NORMAL_FIRST
#define DISPID_STYLEELEMENT                     DISPID_NORMAL_FIRST
#define DISPID_FILTERS                          DISPID_NORMAL_FIRST
#define DISPID_TABLESECTION                     DISPID_NORMAL_FIRST

#define DISPID_HTMLDOCUMENT                     DISPID_NORMAL_FIRST
#define DISPID_OMDOCUMENT                       DISPID_NORMAL_FIRST
#define DISPID_WINDOW                           1
#define DISPID_SCREEN                           DISPID_NORMAL_FIRST
#define DISPID_HISTORY                          1
#define DISPID_LOCATION                         1
#define DISPID_NAVIGATOR                        1
#define DISPID_COLLECTION                       (DISPID_NORMAL_FIRST+500)
#define DISPID_OPTIONS_COL                      (DISPID_NORMAL_FIRST+500)

#define DISPID_CHECKBOX                         DISPID_NORMAL_FIRST
#define DISPID_RADIO                            (DISPID_CHECKBOX + 1000)

#define DISPID_FRAMESITE                        (DISPID_SITE        + 1000)
#define DISPID_FRAME                            (DISPID_FRAMESITE   + 1000)
#define DISPID_IFRAME                           (DISPID_FRAMESITE   + 1000)


//----------------------------------------------------------------------------
//
//  Reserved negative DISPIDs
//
//----------------------------------------------------------------------------

#define DISPID_WINDOWOBJECT                     (-5500)
#define DISPID_LOCATIONOBJECT                   (-5506)
#define DISPID_HISTORYOBJECT                    (-5507)
#define DISPID_NAVIGATOROBJECT                  (-5508)
#define DISPID_SECURITYCTX                      (-5511)
#define DISPID_AMBIENT_DLCONTROL                (-5512)
#define DISPID_AMBIENT_USERAGENT                (-5513)
#define DISPID_SECURITYDOMAIN                   (-5514)
#define DLCTL_DLIMAGES                          0x00000010
#define DLCTL_VIDEOS                            0x00000020
#define DLCTL_BGSOUNDS                          0x00000040
#define DLCTL_NO_SCRIPTS                        0x00000080
#define DLCTL_NO_JAVA                           0x00000100
#define DLCTL_NO_RUNACTIVEXCTLS                 0x00000200
#define DLCTL_NO_DLACTIVEXCTLS                  0x00000400
#define DLCTL_DOWNLOADONLY                      0x00000800
#define DLCTL_NO_FRAMEDOWNLOAD                  0x00001000
#define DLCTL_RESYNCHRONIZE                     0x00002000
#define DLCTL_PRAGMA_NO_CACHE                   0x00004000
#define DLCTL_FORCEOFFLINE                      0x10000000
#define DLCTL_NO_CLIENTPULL                     0x20000000
#define DLCTL_SILENT                            0x40000000
#define DLCTL_OFFLINEIFNOTCONNECTED             0x80000000
#define DLCTL_OFFLINE                           DLCTL_OFFLINEIFNOTCONNECTED

//----------------------------------------------------------------------------
//
//  DISPID for each non xobject event
//
//----------------------------------------------------------------------------

#define DISPID_ONABORT                          (DISPID_NORMAL_FIRST)
#define DISPID_ONCHANGE                         (DISPID_NORMAL_FIRST + 1)
#define DISPID_ONERROR                          (DISPID_NORMAL_FIRST + 2)
#define DISPID_ONLOAD                           (DISPID_NORMAL_FIRST + 3)
#define DISPID_ONSELECT                         (DISPID_NORMAL_FIRST + 6)
#define DISPID_ONSUBMIT                         (DISPID_NORMAL_FIRST + 7)
#define DISPID_ONUNLOAD                         (DISPID_NORMAL_FIRST + 8)
#define DISPID_ONBOUNCE                         (DISPID_NORMAL_FIRST + 9)
#define DISPID_ONFINISH                         (DISPID_NORMAL_FIRST + 10)
#define DISPID_ONSTART                          (DISPID_NORMAL_FIRST + 11)
#define DISPID_ONLAYOUT                         (DISPID_NORMAL_FIRST + 13)
#define DISPID_ONSCROLL                         (DISPID_NORMAL_FIRST + 14)
#define DISPID_ONRESET                          (DISPID_NORMAL_FIRST + 15)
#define DISPID_ONRESIZE                         (DISPID_NORMAL_FIRST + 16)
#define DISPID_ONBEFOREUNLOAD                   (DISPID_NORMAL_FIRST + 17)
#define DISPID_ONCHANGEFOCUS                    (DISPID_NORMAL_FIRST + 18)
#define DISPID_ONCHANGEBLUR                     (DISPID_NORMAL_FIRST + 19)

//----------------------------------------------------------------------------
//
//  DISPID for each unique HtmlAttribute/CssAttribute
//
//----------------------------------------------------------------------------

#define DISPID_A_FIRST                          DISPID_ATTRS
#define DISPID_A_BACKGROUNDIMAGE                (DISPID_A_FIRST+1)
#define DISPID_A_COLOR                          (DISPID_A_FIRST+2)
#define DISPID_A_TEXTTRANSFORM                  (DISPID_A_FIRST+4)
#define DISPID_A_NOWRAP                         (DISPID_A_FIRST+5)
#define DISPID_A_LINEHEIGHT                     (DISPID_A_FIRST+6)
#define DISPID_A_TEXTINDENT                     (DISPID_A_FIRST+7)
#define DISPID_A_LETTERSPACING                  (DISPID_A_FIRST+8)
#define DISPID_A_LANG                           (DISPID_A_FIRST+9)
#define DISPID_A_OVERFLOW                       (DISPID_A_FIRST+10)

#define DISPID_A_PADDING                        (DISPID_A_FIRST+11)
#define DISPID_A_PADDINGTOP                     (DISPID_A_FIRST+12)
#define DISPID_A_PADDINGRIGHT                   (DISPID_A_FIRST+13)
#define DISPID_A_PADDINGBOTTOM                  (DISPID_A_FIRST+14)
#define DISPID_A_PADDINGLEFT                    (DISPID_A_FIRST+15)

#define DISPID_A_CLEAR                          (DISPID_A_FIRST+16)
#define DISPID_A_LISTTYPE                       (DISPID_A_FIRST+17)
#define DISPID_A_FONTFACE                       (DISPID_A_FIRST+18)
#define DISPID_A_FONTSIZE                       (DISPID_A_FIRST+19)

#define DISPID_A_TEXTDECORATIONLINETHROUGH      (DISPID_A_FIRST+20)
#define DISPID_A_TEXTDECORATIONUNDERLINE        (DISPID_A_FIRST+21)
#define DISPID_A_TEXTDECORATIONBLINK            (DISPID_A_FIRST+22)
#define DISPID_A_TEXTDECORATIONNONE             (DISPID_A_FIRST+23)


#define DISPID_A_FONTSTYLE                      (DISPID_A_FIRST+24)
#define DISPID_A_FONTVARIANT                    (DISPID_A_FIRST+25)
#define DISPID_A_BASEFONT                       (DISPID_A_FIRST+26)
#define DISPID_A_FONTWEIGHT                     (DISPID_A_FIRST+27)

#define DISPID_A_TABLEBORDERCOLOR               (DISPID_A_FIRST+28)
#define DISPID_A_TABLEBORDERCOLORLIGHT          (DISPID_A_FIRST+29)
#define DISPID_A_TABLEBORDERCOLORDARK           (DISPID_A_FIRST+30)
#define DISPID_A_TABLEVALIGN                    (DISPID_A_FIRST+31)

#define DISPID_A_BACKGROUND                     (DISPID_A_FIRST+32)
#define DISPID_A_BACKGROUNDPOSX                 (DISPID_A_FIRST+33)
#define DISPID_A_BACKGROUNDPOSY                 (DISPID_A_FIRST+34)

#define DISPID_A_TEXTDECORATION                 (DISPID_A_FIRST+35)

#define DISPID_A_MARGIN                         (DISPID_A_FIRST+36)
#define DISPID_A_MARGINTOP                      (DISPID_A_FIRST+37)
#define DISPID_A_MARGINRIGHT                    (DISPID_A_FIRST+38)
#define DISPID_A_MARGINBOTTOM                   (DISPID_A_FIRST+39)
#define DISPID_A_MARGINLEFT                     (DISPID_A_FIRST+40)

#define DISPID_A_FONT                           (DISPID_A_FIRST+41)
#define DISPID_A_FONTSIZEKEYWORD                (DISPID_A_FIRST+42)
#define DISPID_A_FONTSIZECOMBINE                (DISPID_A_FIRST+43)

#define DISPID_A_BACKGROUNDREPEAT               (DISPID_A_FIRST+44)
#define DISPID_A_BACKGROUNDATTACHMENT           (DISPID_A_FIRST+45)
#define DISPID_A_BACKGROUNDPOSITION             (DISPID_A_FIRST+46)
#define DISPID_A_WORDSPACING                    (DISPID_A_FIRST+47)
#define DISPID_A_VERTICALALIGN                  (DISPID_A_FIRST+48)
#define DISPID_A_BORDER                         (DISPID_A_FIRST+49)
#define DISPID_A_BORDERTOP                      (DISPID_A_FIRST+50)
#define DISPID_A_BORDERRIGHT                    (DISPID_A_FIRST+51)
#define DISPID_A_BORDERBOTTOM                   (DISPID_A_FIRST+52)
#define DISPID_A_BORDERLEFT                     (DISPID_A_FIRST+53)
#define DISPID_A_BORDERCOLOR                    (DISPID_A_FIRST+54)
#define DISPID_A_BORDERTOPCOLOR                 (DISPID_A_FIRST+55)
#define DISPID_A_BORDERRIGHTCOLOR               (DISPID_A_FIRST+56)
#define DISPID_A_BORDERBOTTOMCOLOR              (DISPID_A_FIRST+57)
#define DISPID_A_BORDERLEFTCOLOR                (DISPID_A_FIRST+58)
#define DISPID_A_BORDERWIDTH                    (DISPID_A_FIRST+59)
#define DISPID_A_BORDERTOPWIDTH                 (DISPID_A_FIRST+60)
#define DISPID_A_BORDERRIGHTWIDTH               (DISPID_A_FIRST+61)
#define DISPID_A_BORDERBOTTOMWIDTH              (DISPID_A_FIRST+62)
#define DISPID_A_BORDERLEFTWIDTH                (DISPID_A_FIRST+63)
#define DISPID_A_BORDERSTYLE                    (DISPID_A_FIRST+64)
#define DISPID_A_BORDERTOPSTYLE                 (DISPID_A_FIRST+65)
#define DISPID_A_BORDERRIGHTSTYLE               (DISPID_A_FIRST+66)
#define DISPID_A_BORDERBOTTOMSTYLE              (DISPID_A_FIRST+67)
#define DISPID_A_BORDERLEFTSTYLE                (DISPID_A_FIRST+68)
#define DISPID_A_TEXTDECORATIONOVERLINE         (DISPID_A_FIRST+69)
#define DISPID_A_FLOAT                          (DISPID_A_FIRST+70)
#define DISPID_A_DISPLAY                        (DISPID_A_FIRST+71)
#define DISPID_A_LISTSTYLETYPE                  (DISPID_A_FIRST+72)
#define DISPID_A_LISTSTYLEPOSITION              (DISPID_A_FIRST+73)
#define DISPID_A_LISTSTYLEIMAGE                 (DISPID_A_FIRST+74)
#define DISPID_A_LISTSTYLE                      (DISPID_A_FIRST+75)
#define DISPID_A_WHITESPACE                     (DISPID_A_FIRST+76)
#define DISPID_A_PAGEBREAKBEFORE                (DISPID_A_FIRST+77)
#define DISPID_A_PAGEBREAKAFTER                 (DISPID_A_FIRST+78)
#define DISPID_A_SCROLL                         (DISPID_A_FIRST+79)
#define DISPID_A_VISIBILITY                     (DISPID_A_FIRST+80)
#define DISPID_A_HIDDEN                         (DISPID_A_FIRST+81)
#define DISPID_A_FILTER                         (DISPID_A_FIRST+82)

#define DISPID_DEFAULTVALUE                     (DISPID_A_FIRST+83)

#define DISPID_A_POSITION                       (DISPID_A_FIRST+90)
#define DISPID_A_ZINDEX                         (DISPID_A_FIRST+91)
#define DISPID_A_CLIP                           (DISPID_A_FIRST+92)
#define DISPID_A_CLIPRECTTOP                    (DISPID_A_FIRST+93)
#define DISPID_A_CLIPRECTRIGHT                  (DISPID_A_FIRST+94)
#define DISPID_A_CLIPRECTBOTTOM                 (DISPID_A_FIRST+95)
#define DISPID_A_CLIPRECTLEFT                   (DISPID_A_FIRST+96)

#define DISPID_A_FONTFACESRC                    (DISPID_A_FIRST+97)

// The style as a text string
#define DISPID_A_STYLETEXT                      (DISPID_A_FIRST+99)

// Known attributes that have special meaning
#define DISPID_A_LANGUAGE                       (DISPID_A_FIRST+100)

#define DISPID_A_VALUE                          (DISPID_A_FIRST+101)
#define DISPID_A_CURSOR                         (DISPID_A_FIRST+102)

//------------------------------------------------------------------------
//
//  Event property and method dispids
//
//------------------------------------------------------------------------

#define DISPID_EVPROP_ONMOUSEOVER           (DISPID_EVENTS +  0)
#define DISPID_EVMETH_ONMOUSEOVER            STDDISPID_XOBJ_ONMOUSEOVER
#define DISPID_EVPROP_ONMOUSEOUT            (DISPID_EVENTS +  1)
#define DISPID_EVMETH_ONMOUSEOUT             STDDISPID_XOBJ_ONMOUSEOUT
#define DISPID_EVPROP_ONMOUSEDOWN           (DISPID_EVENTS +  2)
#define DISPID_EVMETH_ONMOUSEDOWN            DISPID_MOUSEDOWN
#define DISPID_EVPROP_ONMOUSEUP             (DISPID_EVENTS +  3)
#define DISPID_EVMETH_ONMOUSEUP              DISPID_MOUSEUP
#define DISPID_EVPROP_ONMOUSEMOVE           (DISPID_EVENTS +  4)
#define DISPID_EVMETH_ONMOUSEMOVE            DISPID_MOUSEMOVE
#define DISPID_EVPROP_ONKEYDOWN             (DISPID_EVENTS +  5)
#define DISPID_EVMETH_ONKEYDOWN              DISPID_KEYDOWN
#define DISPID_EVPROP_ONKEYUP               (DISPID_EVENTS +  6)
#define DISPID_EVMETH_ONKEYUP                DISPID_KEYUP
#define DISPID_EVPROP_ONKEYPRESS            (DISPID_EVENTS +  7)
#define DISPID_EVMETH_ONKEYPRESS             DISPID_KEYPRESS
#define DISPID_EVPROP_ONCLICK               (DISPID_EVENTS +  8)
#define DISPID_EVMETH_ONCLICK                DISPID_CLICK
#define DISPID_EVPROP_ONDBLCLICK            (DISPID_EVENTS +  9)
#define DISPID_EVMETH_ONDBLCLICK             DISPID_DBLCLICK
#define DISPID_EVPROP_ONSELECT              (DISPID_EVENTS + 10)
#define DISPID_EVMETH_ONSELECT               DISPID_ONSELECT
#define DISPID_EVPROP_ONSUBMIT              (DISPID_EVENTS + 11)
#define DISPID_EVMETH_ONSUBMIT               DISPID_ONSUBMIT
#define DISPID_EVPROP_ONRESET               (DISPID_EVENTS + 12)
#define DISPID_EVMETH_ONRESET                DISPID_ONRESET
#define DISPID_EVPROP_ONHELP                (DISPID_EVENTS + 13)
#define DISPID_EVMETH_ONHELP                 STDDISPID_XOBJ_ONHELP
#define DISPID_EVPROP_ONFOCUS               (DISPID_EVENTS + 14)
#define DISPID_EVMETH_ONFOCUS                STDDISPID_XOBJ_ONFOCUS
#define DISPID_EVPROP_ONBLUR                (DISPID_EVENTS + 15)
#define DISPID_EVMETH_ONBLUR                 STDDISPID_XOBJ_ONBLUR
#define DISPID_EVPROP_ONROWEXIT             (DISPID_EVENTS + 18)
#define DISPID_EVMETH_ONROWEXIT              STDDISPID_XOBJ_ONROWEXIT
#define DISPID_EVPROP_ONROWENTER            (DISPID_EVENTS + 19)
#define DISPID_EVMETH_ONROWENTER             STDDISPID_XOBJ_ONROWENTER
#define DISPID_EVPROP_ONBOUNCE              (DISPID_EVENTS + 20)
#define DISPID_EVMETH_ONBOUNCE               DISPID_ONBOUNCE
#define DISPID_EVPROP_ONBEFOREUPDATE        (DISPID_EVENTS + 21)
#define DISPID_EVMETH_ONBEFOREUPDATE         STDDISPID_XOBJ_BEFOREUPDATE
#define DISPID_EVPROP_ONAFTERUPDATE         (DISPID_EVENTS + 22)
#define DISPID_EVMETH_ONAFTERUPDATE          STDDISPID_XOBJ_AFTERUPDATE
#define DISPID_EVPROP_ONBEFOREDRAGOVER      (DISPID_EVENTS + 23)
#define DISPID_EVMETH_ONBEFOREDRAGOVER       EVENTID_CommonCtrlEvent_BeforeDragOver
#define DISPID_EVPROP_ONBEFOREDROPORPASTE   (DISPID_EVENTS + 24)
#define DISPID_EVMETH_ONBEFOREDROPORPASTE    EVENTID_CommonCtrlEvent_BeforeDropOrPaste
#define DISPID_EVPROP_ONREADYSTATECHANGE    (DISPID_EVENTS + 25)
#define DISPID_EVMETH_ONREADYSTATECHANGE     DISPID_READYSTATECHANGE
#define DISPID_EVPROP_ONFINISH              (DISPID_EVENTS + 26)
#define DISPID_EVMETH_ONFINISH               DISPID_ONFINISH
#define DISPID_EVPROP_ONSTART               (DISPID_EVENTS + 27)
#define DISPID_EVMETH_ONSTART                DISPID_ONSTART
#define DISPID_EVPROP_ONABORT               (DISPID_EVENTS + 28)
#define DISPID_EVMETH_ONABORT                DISPID_ONABORT
#define DISPID_EVPROP_ONERROR               (DISPID_EVENTS + 29)
#define DISPID_EVMETH_ONERROR                DISPID_ONERROR
#define DISPID_EVPROP_ONCHANGE              (DISPID_EVENTS + 30)
#define DISPID_EVMETH_ONCHANGE               DISPID_ONCHANGE
#define DISPID_EVPROP_ONSCROLL              (DISPID_EVENTS + 31)
#define DISPID_EVMETH_ONSCROLL               DISPID_ONSCROLL
#define DISPID_EVPROP_ONLOAD                (DISPID_EVENTS + 32)
#define DISPID_EVMETH_ONLOAD                 DISPID_ONLOAD
#define DISPID_EVPROP_ONUNLOAD              (DISPID_EVENTS + 33)
#define DISPID_EVMETH_ONUNLOAD               DISPID_ONUNLOAD
#define DISPID_EVPROP_ONLAYOUT              (DISPID_EVENTS + 34)
#define DISPID_EVMETH_ONLAYOUT               DISPID_ONLAYOUT
#define DISPID_EVPROP_ONDRAGSTART           (DISPID_EVENTS + 35)
#define DISPID_EVMETH_ONDRAGSTART            STDDISPID_XOBJ_ONDRAGSTART
#define DISPID_EVPROP_ONRESIZE              (DISPID_EVENTS + 36)
#define DISPID_EVMETH_ONRESIZE               DISPID_ONRESIZE
#define DISPID_EVPROP_ONSELECTSTART         (DISPID_EVENTS + 37)
#define DISPID_EVMETH_ONSELECTSTART          STDDISPID_XOBJ_ONSELECTSTART
#define DISPID_EVPROP_ONERRORUPDATE         (DISPID_EVENTS + 38)
#define DISPID_EVMETH_ONERRORUPDATE          STDDISPID_XOBJ_ERRORUPDATE
#define DISPID_EVPROP_ONBEFOREUNLOAD        (DISPID_EVENTS + 39)
#define DISPID_EVMETH_ONBEFOREUNLOAD         DISPID_ONBEFOREUNLOAD
#define DISPID_EVPROP_ONDATASETCHANGED      (DISPID_EVENTS + 40)
#define DISPID_EVMETH_ONDATASETCHANGED       STDDISPID_XOBJ_ONDATASETCHANGED
#define DISPID_EVPROP_ONDATAAVAILABLE       (DISPID_EVENTS + 41)
#define DISPID_EVMETH_ONDATAAVAILABLE         STDDISPID_XOBJ_ONDATAAVAILABLE
#define DISPID_EVPROP_ONDATASETCOMPLETE     (DISPID_EVENTS + 42)
#define DISPID_EVMETH_ONDATASETCOMPLETE      STDDISPID_XOBJ_ONDATASETCOMPLETE
#define DISPID_EVPROP_ONFILTER              (DISPID_EVENTS + 43)
#define DISPID_EVMETH_ONFILTER               STDDISPID_XOBJ_ONFILTER
#define DISPID_EVMETH_ONCHANGEFOCUS          DISPID_ONCHANGEFOCUS
#define DISPID_EVPROP_ONCHANGEFOCUS         (DISPID_EVENTS + 44)
#define DISPID_EVMETH_ONCHANGEBLUR           DISPID_ONCHANGEBLUR
#define DISPID_EVPROP_ONCHANGEBLUR          (DISPID_EVENTS + 45)
#define DISPID_EVPROPS_COUNT                (                45)

//  DISPIDs for interface IDispatchEx

#define DISPID_IDISPATCHEX_GETDISPID                              
#define DISPID_IDISPATCHEX_INVOKEEX                               
#define DISPID_IDISPATCHEX_DELETEMEMBERBYNAME                     
#define DISPID_IDISPATCHEX_DELETEMEMBERBYDISPID                   
#define DISPID_IDISPATCHEX_GETMEMBERPROPERTIES                    
#define DISPID_IDISPATCHEX_GETMEMBERNAME                          
#define DISPID_IDISPATCHEX_GETNEXTDISPID                          
#define DISPID_IDISPATCHEX_GETNAMESPACEPARENT                     

//  DISPIDs for interface IObjectIdentity

#define DISPID_IOBJECTIDENTITY_ISEQUALOBJECT                      

//  DISPIDs for interface IHTMLStyle

#define DISPID_IHTMLSTYLE_FONTFAMILY                              DISPID_A_FONTFACE
#define DISPID_IHTMLSTYLE_FONTSTYLE                               DISPID_A_FONTSTYLE
#define DISPID_IHTMLSTYLE_FONTVARIANT                             DISPID_A_FONTVARIANT
#define DISPID_IHTMLSTYLE_FONTWEIGHT                              DISPID_A_FONTWEIGHT
#define DISPID_IHTMLSTYLE_FONTSIZE                                DISPID_A_FONTSIZE
#define DISPID_IHTMLSTYLE_FONT                                    DISPID_A_FONT
#define DISPID_IHTMLSTYLE_COLOR                                   DISPID_A_COLOR
#define DISPID_IHTMLSTYLE_BACKGROUND                              DISPID_A_BACKGROUND
#define DISPID_IHTMLSTYLE_BACKGROUNDCOLOR                         DISPID_BACKCOLOR
#define DISPID_IHTMLSTYLE_BACKGROUNDIMAGE                         DISPID_A_BACKGROUNDIMAGE
#define DISPID_IHTMLSTYLE_BACKGROUNDREPEAT                        DISPID_A_BACKGROUNDREPEAT
#define DISPID_IHTMLSTYLE_BACKGROUNDATTACHMENT                    DISPID_A_BACKGROUNDATTACHMENT
#define DISPID_IHTMLSTYLE_BACKGROUNDPOSITION                      DISPID_A_BACKGROUNDPOSITION
#define DISPID_IHTMLSTYLE_BACKGROUNDPOSITIONX                     DISPID_A_BACKGROUNDPOSX
#define DISPID_IHTMLSTYLE_BACKGROUNDPOSITIONY                     DISPID_A_BACKGROUNDPOSY
#define DISPID_IHTMLSTYLE_WORDSPACING                             DISPID_A_WORDSPACING
#define DISPID_IHTMLSTYLE_LETTERSPACING                           DISPID_A_LETTERSPACING
#define DISPID_IHTMLSTYLE_TEXTDECORATION                          DISPID_A_TEXTDECORATION
#define DISPID_IHTMLSTYLE_TEXTDECORATIONNONE                      DISPID_A_TEXTDECORATIONNONE
#define DISPID_IHTMLSTYLE_TEXTDECORATIONUNDERLINE                 DISPID_A_TEXTDECORATIONUNDERLINE
#define DISPID_IHTMLSTYLE_TEXTDECORATIONOVERLINE                  DISPID_A_TEXTDECORATIONOVERLINE
#define DISPID_IHTMLSTYLE_TEXTDECORATIONLINETHROUGH               DISPID_A_TEXTDECORATIONLINETHROUGH
#define DISPID_IHTMLSTYLE_TEXTDECORATIONBLINK                     DISPID_A_TEXTDECORATIONBLINK
#define DISPID_IHTMLSTYLE_VERTICALALIGN                           DISPID_A_VERTICALALIGN
#define DISPID_IHTMLSTYLE_TEXTTRANSFORM                           DISPID_A_TEXTTRANSFORM
#define DISPID_IHTMLSTYLE_TEXTALIGN                               STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLSTYLE_TEXTINDENT                              DISPID_A_TEXTINDENT
#define DISPID_IHTMLSTYLE_LINEHEIGHT                              DISPID_A_LINEHEIGHT
#define DISPID_IHTMLSTYLE_MARGINTOP                               DISPID_A_MARGINTOP
#define DISPID_IHTMLSTYLE_MARGINRIGHT                             DISPID_A_MARGINRIGHT
#define DISPID_IHTMLSTYLE_MARGINBOTTOM                            DISPID_A_MARGINBOTTOM
#define DISPID_IHTMLSTYLE_MARGINLEFT                              DISPID_A_MARGINLEFT
#define DISPID_IHTMLSTYLE_MARGIN                                  DISPID_A_MARGIN
#define DISPID_IHTMLSTYLE_PADDINGTOP                              DISPID_A_PADDINGTOP
#define DISPID_IHTMLSTYLE_PADDINGRIGHT                            DISPID_A_PADDINGRIGHT
#define DISPID_IHTMLSTYLE_PADDINGBOTTOM                           DISPID_A_PADDINGBOTTOM
#define DISPID_IHTMLSTYLE_PADDINGLEFT                             DISPID_A_PADDINGLEFT
#define DISPID_IHTMLSTYLE_PADDING                                 DISPID_A_PADDING
#define DISPID_IHTMLSTYLE_BORDER                                  DISPID_A_BORDER
#define DISPID_IHTMLSTYLE_BORDERTOP                               DISPID_A_BORDERTOP
#define DISPID_IHTMLSTYLE_BORDERRIGHT                             DISPID_A_BORDERRIGHT
#define DISPID_IHTMLSTYLE_BORDERBOTTOM                            DISPID_A_BORDERBOTTOM
#define DISPID_IHTMLSTYLE_BORDERLEFT                              DISPID_A_BORDERLEFT
#define DISPID_IHTMLSTYLE_BORDERCOLOR                             DISPID_A_BORDERCOLOR
#define DISPID_IHTMLSTYLE_BORDERTOPCOLOR                          DISPID_A_BORDERTOPCOLOR
#define DISPID_IHTMLSTYLE_BORDERRIGHTCOLOR                        DISPID_A_BORDERRIGHTCOLOR
#define DISPID_IHTMLSTYLE_BORDERBOTTOMCOLOR                       DISPID_A_BORDERBOTTOMCOLOR
#define DISPID_IHTMLSTYLE_BORDERLEFTCOLOR                         DISPID_A_BORDERLEFTCOLOR
#define DISPID_IHTMLSTYLE_BORDERWIDTH                             DISPID_A_BORDERWIDTH
#define DISPID_IHTMLSTYLE_BORDERTOPWIDTH                          DISPID_A_BORDERTOPWIDTH
#define DISPID_IHTMLSTYLE_BORDERRIGHTWIDTH                        DISPID_A_BORDERRIGHTWIDTH
#define DISPID_IHTMLSTYLE_BORDERBOTTOMWIDTH                       DISPID_A_BORDERBOTTOMWIDTH
#define DISPID_IHTMLSTYLE_BORDERLEFTWIDTH                         DISPID_A_BORDERLEFTWIDTH
#define DISPID_IHTMLSTYLE_BORDERSTYLE                             DISPID_A_BORDERSTYLE
#define DISPID_IHTMLSTYLE_BORDERTOPSTYLE                          DISPID_A_BORDERTOPSTYLE
#define DISPID_IHTMLSTYLE_BORDERRIGHTSTYLE                        DISPID_A_BORDERRIGHTSTYLE
#define DISPID_IHTMLSTYLE_BORDERBOTTOMSTYLE                       DISPID_A_BORDERBOTTOMSTYLE
#define DISPID_IHTMLSTYLE_BORDERLEFTSTYLE                         DISPID_A_BORDERLEFTSTYLE
#define DISPID_IHTMLSTYLE_WIDTH                                   STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLSTYLE_HEIGHT                                  STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLSTYLE_STYLEFLOAT                              DISPID_A_FLOAT
#define DISPID_IHTMLSTYLE_CLEAR                                   DISPID_A_CLEAR
#define DISPID_IHTMLSTYLE_DISPLAY                                 DISPID_A_DISPLAY
#define DISPID_IHTMLSTYLE_VISIBILITY                              DISPID_A_VISIBILITY
#define DISPID_IHTMLSTYLE_LISTSTYLETYPE                           DISPID_A_LISTSTYLETYPE
#define DISPID_IHTMLSTYLE_LISTSTYLEPOSITION                       DISPID_A_LISTSTYLEPOSITION
#define DISPID_IHTMLSTYLE_LISTSTYLEIMAGE                          DISPID_A_LISTSTYLEIMAGE
#define DISPID_IHTMLSTYLE_LISTSTYLE                               DISPID_A_LISTSTYLE
#define DISPID_IHTMLSTYLE_WHITESPACE                              DISPID_A_WHITESPACE
#define DISPID_IHTMLSTYLE_TOP                                     STDPROPID_XOBJ_TOP
#define DISPID_IHTMLSTYLE_LEFT                                    STDPROPID_XOBJ_LEFT
#define DISPID_IHTMLSTYLE_POSITION                                DISPID_A_POSITION
#define DISPID_IHTMLSTYLE_ZINDEX                                  DISPID_A_ZINDEX
#define DISPID_IHTMLSTYLE_OVERFLOW                                DISPID_A_OVERFLOW
#define DISPID_IHTMLSTYLE_PAGEBREAKBEFORE                         DISPID_A_PAGEBREAKBEFORE
#define DISPID_IHTMLSTYLE_PAGEBREAKAFTER                          DISPID_A_PAGEBREAKAFTER
#define DISPID_IHTMLSTYLE_CSSTEXT                                 DISPID_A_STYLETEXT
#define DISPID_IHTMLSTYLE_PIXELTOP                                DISPID_STYLE+0
#define DISPID_IHTMLSTYLE_PIXELLEFT                               DISPID_STYLE+1
#define DISPID_IHTMLSTYLE_PIXELWIDTH                              DISPID_STYLE+2
#define DISPID_IHTMLSTYLE_PIXELHEIGHT                             DISPID_STYLE+3
#define DISPID_IHTMLSTYLE_POSTOP                                  DISPID_STYLE+4
#define DISPID_IHTMLSTYLE_POSLEFT                                 DISPID_STYLE+5
#define DISPID_IHTMLSTYLE_POSWIDTH                                DISPID_STYLE+6
#define DISPID_IHTMLSTYLE_POSHEIGHT                               DISPID_STYLE+7
#define DISPID_IHTMLSTYLE_CURSOR                                  DISPID_A_CURSOR
#define DISPID_IHTMLSTYLE_CLIP                                    DISPID_A_CLIP
#define DISPID_IHTMLSTYLE_FILTER                                  DISPID_A_FILTER
#define DISPID_IHTMLSTYLE_SETATTRIBUTE                            DISPID_HTMLOBJECT+1
#define DISPID_IHTMLSTYLE_GETATTRIBUTE                            DISPID_HTMLOBJECT+2
#define DISPID_IHTMLSTYLE_REMOVEATTRIBUTE                         DISPID_HTMLOBJECT+3
#define DISPID_IHTMLSTYLE_TOSTRING                                DISPID_STYLE+8

//  DISPIDs for interface IHTMLRuleStyle

#define DISPID_IHTMLRULESTYLE_FONTFAMILY                          DISPID_A_FONTFACE
#define DISPID_IHTMLRULESTYLE_FONTSTYLE                           DISPID_A_FONTSTYLE
#define DISPID_IHTMLRULESTYLE_FONTVARIANT                         DISPID_A_FONTVARIANT
#define DISPID_IHTMLRULESTYLE_FONTWEIGHT                          DISPID_A_FONTWEIGHT
#define DISPID_IHTMLRULESTYLE_FONTSIZE                            DISPID_A_FONTSIZE
#define DISPID_IHTMLRULESTYLE_FONT                                DISPID_A_FONT
#define DISPID_IHTMLRULESTYLE_COLOR                               DISPID_A_COLOR
#define DISPID_IHTMLRULESTYLE_BACKGROUND                          DISPID_A_BACKGROUND
#define DISPID_IHTMLRULESTYLE_BACKGROUNDCOLOR                     DISPID_BACKCOLOR
#define DISPID_IHTMLRULESTYLE_BACKGROUNDIMAGE                     DISPID_A_BACKGROUNDIMAGE
#define DISPID_IHTMLRULESTYLE_BACKGROUNDREPEAT                    DISPID_A_BACKGROUNDREPEAT
#define DISPID_IHTMLRULESTYLE_BACKGROUNDATTACHMENT                DISPID_A_BACKGROUNDATTACHMENT
#define DISPID_IHTMLRULESTYLE_BACKGROUNDPOSITION                  DISPID_A_BACKGROUNDPOSITION
#define DISPID_IHTMLRULESTYLE_BACKGROUNDPOSITIONX                 DISPID_A_BACKGROUNDPOSX
#define DISPID_IHTMLRULESTYLE_BACKGROUNDPOSITIONY                 DISPID_A_BACKGROUNDPOSY
#define DISPID_IHTMLRULESTYLE_WORDSPACING                         DISPID_A_WORDSPACING
#define DISPID_IHTMLRULESTYLE_LETTERSPACING                       DISPID_A_LETTERSPACING
#define DISPID_IHTMLRULESTYLE_TEXTDECORATION                      DISPID_A_TEXTDECORATION
#define DISPID_IHTMLRULESTYLE_TEXTDECORATIONNONE                  DISPID_A_TEXTDECORATIONNONE
#define DISPID_IHTMLRULESTYLE_TEXTDECORATIONUNDERLINE             DISPID_A_TEXTDECORATIONUNDERLINE
#define DISPID_IHTMLRULESTYLE_TEXTDECORATIONOVERLINE              DISPID_A_TEXTDECORATIONOVERLINE
#define DISPID_IHTMLRULESTYLE_TEXTDECORATIONLINETHROUGH           DISPID_A_TEXTDECORATIONLINETHROUGH
#define DISPID_IHTMLRULESTYLE_TEXTDECORATIONBLINK                 DISPID_A_TEXTDECORATIONBLINK
#define DISPID_IHTMLRULESTYLE_VERTICALALIGN                       DISPID_A_VERTICALALIGN
#define DISPID_IHTMLRULESTYLE_TEXTTRANSFORM                       DISPID_A_TEXTTRANSFORM
#define DISPID_IHTMLRULESTYLE_TEXTALIGN                           STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLRULESTYLE_TEXTINDENT                          DISPID_A_TEXTINDENT
#define DISPID_IHTMLRULESTYLE_LINEHEIGHT                          DISPID_A_LINEHEIGHT
#define DISPID_IHTMLRULESTYLE_MARGINTOP                           DISPID_A_MARGINTOP
#define DISPID_IHTMLRULESTYLE_MARGINRIGHT                         DISPID_A_MARGINRIGHT
#define DISPID_IHTMLRULESTYLE_MARGINBOTTOM                        DISPID_A_MARGINBOTTOM
#define DISPID_IHTMLRULESTYLE_MARGINLEFT                          DISPID_A_MARGINLEFT
#define DISPID_IHTMLRULESTYLE_MARGIN                              DISPID_A_MARGIN
#define DISPID_IHTMLRULESTYLE_PADDINGTOP                          DISPID_A_PADDINGTOP
#define DISPID_IHTMLRULESTYLE_PADDINGRIGHT                        DISPID_A_PADDINGRIGHT
#define DISPID_IHTMLRULESTYLE_PADDINGBOTTOM                       DISPID_A_PADDINGBOTTOM
#define DISPID_IHTMLRULESTYLE_PADDINGLEFT                         DISPID_A_PADDINGLEFT
#define DISPID_IHTMLRULESTYLE_PADDING                             DISPID_A_PADDING
#define DISPID_IHTMLRULESTYLE_BORDER                              DISPID_A_BORDER
#define DISPID_IHTMLRULESTYLE_BORDERTOP                           DISPID_A_BORDERTOP
#define DISPID_IHTMLRULESTYLE_BORDERRIGHT                         DISPID_A_BORDERRIGHT
#define DISPID_IHTMLRULESTYLE_BORDERBOTTOM                        DISPID_A_BORDERBOTTOM
#define DISPID_IHTMLRULESTYLE_BORDERLEFT                          DISPID_A_BORDERLEFT
#define DISPID_IHTMLRULESTYLE_BORDERCOLOR                         DISPID_A_BORDERCOLOR
#define DISPID_IHTMLRULESTYLE_BORDERTOPCOLOR                      DISPID_A_BORDERTOPCOLOR
#define DISPID_IHTMLRULESTYLE_BORDERRIGHTCOLOR                    DISPID_A_BORDERRIGHTCOLOR
#define DISPID_IHTMLRULESTYLE_BORDERBOTTOMCOLOR                   DISPID_A_BORDERBOTTOMCOLOR
#define DISPID_IHTMLRULESTYLE_BORDERLEFTCOLOR                     DISPID_A_BORDERLEFTCOLOR
#define DISPID_IHTMLRULESTYLE_BORDERWIDTH                         DISPID_A_BORDERWIDTH
#define DISPID_IHTMLRULESTYLE_BORDERTOPWIDTH                      DISPID_A_BORDERTOPWIDTH
#define DISPID_IHTMLRULESTYLE_BORDERRIGHTWIDTH                    DISPID_A_BORDERRIGHTWIDTH
#define DISPID_IHTMLRULESTYLE_BORDERBOTTOMWIDTH                   DISPID_A_BORDERBOTTOMWIDTH
#define DISPID_IHTMLRULESTYLE_BORDERLEFTWIDTH                     DISPID_A_BORDERLEFTWIDTH
#define DISPID_IHTMLRULESTYLE_BORDERSTYLE                         DISPID_A_BORDERSTYLE
#define DISPID_IHTMLRULESTYLE_BORDERTOPSTYLE                      DISPID_A_BORDERTOPSTYLE
#define DISPID_IHTMLRULESTYLE_BORDERRIGHTSTYLE                    DISPID_A_BORDERRIGHTSTYLE
#define DISPID_IHTMLRULESTYLE_BORDERBOTTOMSTYLE                   DISPID_A_BORDERBOTTOMSTYLE
#define DISPID_IHTMLRULESTYLE_BORDERLEFTSTYLE                     DISPID_A_BORDERLEFTSTYLE
#define DISPID_IHTMLRULESTYLE_WIDTH                               STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLRULESTYLE_HEIGHT                              STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLRULESTYLE_STYLEFLOAT                          DISPID_A_FLOAT
#define DISPID_IHTMLRULESTYLE_CLEAR                               DISPID_A_CLEAR
#define DISPID_IHTMLRULESTYLE_DISPLAY                             DISPID_A_DISPLAY
#define DISPID_IHTMLRULESTYLE_VISIBILITY                          DISPID_A_VISIBILITY
#define DISPID_IHTMLRULESTYLE_LISTSTYLETYPE                       DISPID_A_LISTSTYLETYPE
#define DISPID_IHTMLRULESTYLE_LISTSTYLEPOSITION                   DISPID_A_LISTSTYLEPOSITION
#define DISPID_IHTMLRULESTYLE_LISTSTYLEIMAGE                      DISPID_A_LISTSTYLEIMAGE
#define DISPID_IHTMLRULESTYLE_LISTSTYLE                           DISPID_A_LISTSTYLE
#define DISPID_IHTMLRULESTYLE_WHITESPACE                          DISPID_A_WHITESPACE
#define DISPID_IHTMLRULESTYLE_TOP                                 STDPROPID_XOBJ_TOP
#define DISPID_IHTMLRULESTYLE_LEFT                                STDPROPID_XOBJ_LEFT
#define DISPID_IHTMLRULESTYLE_POSITION                            DISPID_A_POSITION
#define DISPID_IHTMLRULESTYLE_ZINDEX                              DISPID_A_ZINDEX
#define DISPID_IHTMLRULESTYLE_OVERFLOW                            DISPID_A_OVERFLOW
#define DISPID_IHTMLRULESTYLE_PAGEBREAKBEFORE                     DISPID_A_PAGEBREAKBEFORE
#define DISPID_IHTMLRULESTYLE_PAGEBREAKAFTER                      DISPID_A_PAGEBREAKAFTER
#define DISPID_IHTMLRULESTYLE_CSSTEXT                             DISPID_A_STYLETEXT
#define DISPID_IHTMLRULESTYLE_CURSOR                              DISPID_A_CURSOR
#define DISPID_IHTMLRULESTYLE_CLIP                                DISPID_A_CLIP
#define DISPID_IHTMLRULESTYLE_FILTER                              DISPID_A_FILTER
#define DISPID_IHTMLRULESTYLE_SETATTRIBUTE                        DISPID_HTMLOBJECT+1
#define DISPID_IHTMLRULESTYLE_GETATTRIBUTE                        DISPID_HTMLOBJECT+2
#define DISPID_IHTMLRULESTYLE_REMOVEATTRIBUTE                     DISPID_HTMLOBJECT+3

//  DISPIDs for interface IHTMLFiltersCollection

#define DISPID_IHTMLFILTERSCOLLECTION_LENGTH                      DISPID_FILTERS+1
#define DISPID_IHTMLFILTERSCOLLECTION__NEWENUM                    DISPID_NEWENUM
#define DISPID_IHTMLFILTERSCOLLECTION_ITEM                        DISPID_VALUE

//  DISPIDs for interface ICSSFilterSite

#define DISPID_ICSSFILTERSITE_GETELEMENT                          
#define DISPID_ICSSFILTERSITE_FIREONFILTERCHANGEEVENT             

//  DISPIDs for interface ICSSFilter

#define DISPID_ICSSFILTER_SETSITE                                 
#define DISPID_ICSSFILTER_ONAMBIENTPROPERTYCHANGE                 

//  DISPIDs for interface IHTMLElement

#define DISPID_IHTMLELEMENT_SETATTRIBUTE                          DISPID_HTMLOBJECT+1
#define DISPID_IHTMLELEMENT_GETATTRIBUTE                          DISPID_HTMLOBJECT+2
#define DISPID_IHTMLELEMENT_REMOVEATTRIBUTE                       DISPID_HTMLOBJECT+3
#define DISPID_IHTMLELEMENT_CLASSNAME                             DISPID_ELEMENT+1
#define DISPID_IHTMLELEMENT_ID                                    DISPID_ELEMENT+2
#define DISPID_IHTMLELEMENT_TAGNAME                               DISPID_ELEMENT+4
#define DISPID_IHTMLELEMENT_PARENTELEMENT                         STDPROPID_XOBJ_PARENT
#define DISPID_IHTMLELEMENT_STYLE                                 STDPROPID_XOBJ_STYLE
#define DISPID_IHTMLELEMENT_ONHELP                                DISPID_EVPROP_ONHELP
#define DISPID_IHTMLELEMENT_ONCLICK                               DISPID_EVPROP_ONCLICK
#define DISPID_IHTMLELEMENT_ONDBLCLICK                            DISPID_EVPROP_ONDBLCLICK
#define DISPID_IHTMLELEMENT_ONKEYDOWN                             DISPID_EVPROP_ONKEYDOWN
#define DISPID_IHTMLELEMENT_ONKEYUP                               DISPID_EVPROP_ONKEYUP
#define DISPID_IHTMLELEMENT_ONKEYPRESS                            DISPID_EVPROP_ONKEYPRESS
#define DISPID_IHTMLELEMENT_ONMOUSEOUT                            DISPID_EVPROP_ONMOUSEOUT
#define DISPID_IHTMLELEMENT_ONMOUSEOVER                           DISPID_EVPROP_ONMOUSEOVER
#define DISPID_IHTMLELEMENT_ONMOUSEMOVE                           DISPID_EVPROP_ONMOUSEMOVE
#define DISPID_IHTMLELEMENT_ONMOUSEDOWN                           DISPID_EVPROP_ONMOUSEDOWN
#define DISPID_IHTMLELEMENT_ONMOUSEUP                             DISPID_EVPROP_ONMOUSEUP
#define DISPID_IHTMLELEMENT_DOCUMENT                              DISPID_ELEMENT+18
#define DISPID_IHTMLELEMENT_TITLE                                 STDPROPID_XOBJ_CONTROLTIPTEXT
#define DISPID_IHTMLELEMENT_LANGUAGE                              DISPID_A_LANGUAGE
#define DISPID_IHTMLELEMENT_ONSELECTSTART                         DISPID_EVPROP_ONSELECTSTART
#define DISPID_IHTMLELEMENT_SCROLLINTOVIEW                        DISPID_ELEMENT+19
#define DISPID_IHTMLELEMENT_CONTAINS                              DISPID_ELEMENT+20
#define DISPID_IHTMLELEMENT_SOURCEINDEX                           DISPID_ELEMENT+24
#define DISPID_IHTMLELEMENT_RECORDNUMBER                          DISPID_ELEMENT+25
#define DISPID_IHTMLELEMENT_LANG                                  DISPID_A_LANG
#define DISPID_IHTMLELEMENT_OFFSETLEFT                            DISPID_ELEMENT+8
#define DISPID_IHTMLELEMENT_OFFSETTOP                             DISPID_ELEMENT+9
#define DISPID_IHTMLELEMENT_OFFSETWIDTH                           DISPID_ELEMENT+10
#define DISPID_IHTMLELEMENT_OFFSETHEIGHT                          DISPID_ELEMENT+11
#define DISPID_IHTMLELEMENT_OFFSETPARENT                          DISPID_ELEMENT+12
#define DISPID_IHTMLELEMENT_INNERHTML                             DISPID_ELEMENT+26
#define DISPID_IHTMLELEMENT_INNERTEXT                             DISPID_ELEMENT+27
#define DISPID_IHTMLELEMENT_OUTERHTML                             DISPID_ELEMENT+28
#define DISPID_IHTMLELEMENT_OUTERTEXT                             DISPID_ELEMENT+29
#define DISPID_IHTMLELEMENT_INSERTADJACENTHTML                    DISPID_ELEMENT+30
#define DISPID_IHTMLELEMENT_INSERTADJACENTTEXT                    DISPID_ELEMENT+31
#define DISPID_IHTMLELEMENT_PARENTTEXTEDIT                        DISPID_ELEMENT+32
#define DISPID_IHTMLELEMENT_ISTEXTEDIT                            DISPID_ELEMENT+34
#define DISPID_IHTMLELEMENT_CLICK                                 DISPID_ELEMENT+33
#define DISPID_IHTMLELEMENT_FILTERS                               DISPID_ELEMENT+35
#define DISPID_IHTMLELEMENT_ONDRAGSTART                           DISPID_EVPROP_ONDRAGSTART
#define DISPID_IHTMLELEMENT_TOSTRING                              DISPID_ELEMENT+36
#define DISPID_IHTMLELEMENT_ONBEFOREUPDATE                        DISPID_EVPROP_ONBEFOREUPDATE
#define DISPID_IHTMLELEMENT_ONAFTERUPDATE                         DISPID_EVPROP_ONAFTERUPDATE
#define DISPID_IHTMLELEMENT_ONERRORUPDATE                         DISPID_EVPROP_ONERRORUPDATE
#define DISPID_IHTMLELEMENT_ONROWEXIT                             DISPID_EVPROP_ONROWEXIT
#define DISPID_IHTMLELEMENT_ONROWENTER                            DISPID_EVPROP_ONROWENTER
#define DISPID_IHTMLELEMENT_ONDATASETCHANGED                      DISPID_EVPROP_ONDATASETCHANGED
#define DISPID_IHTMLELEMENT_ONDATAAVAILABLE                       DISPID_EVPROP_ONDATAAVAILABLE
#define DISPID_IHTMLELEMENT_ONDATASETCOMPLETE                     DISPID_EVPROP_ONDATASETCOMPLETE
#define DISPID_IHTMLELEMENT_ONFILTERCHANGE                        DISPID_EVPROP_ONFILTER
#define DISPID_IHTMLELEMENT_CHILDREN                              DISPID_ELEMENT+37
#define DISPID_IHTMLELEMENT_ALL                                   DISPID_ELEMENT+38

//  DISPIDs for interface IHTMLDatabinding

#define DISPID_IHTMLDATABINDING_DATAFLD                           DISPID_ELEMENT+21
#define DISPID_IHTMLDATABINDING_DATASRC                           DISPID_ELEMENT+22
#define DISPID_IHTMLDATABINDING_DATAFORMATAS                      DISPID_ELEMENT+23

//  DISPIDs for event set HTMLElementEvents

#define DISPID_HTMLELEMENTEVENTS_ONHELP                           DISPID_EVMETH_ONHELP
#define DISPID_HTMLELEMENTEVENTS_ONCLICK                          DISPID_EVMETH_ONCLICK
#define DISPID_HTMLELEMENTEVENTS_ONDBLCLICK                       DISPID_EVMETH_ONDBLCLICK
#define DISPID_HTMLELEMENTEVENTS_ONKEYPRESS                       DISPID_EVMETH_ONKEYPRESS
#define DISPID_HTMLELEMENTEVENTS_ONKEYDOWN                        DISPID_EVMETH_ONKEYDOWN
#define DISPID_HTMLELEMENTEVENTS_ONKEYUP                          DISPID_EVMETH_ONKEYUP
#define DISPID_HTMLELEMENTEVENTS_ONMOUSEOUT                       DISPID_EVMETH_ONMOUSEOUT
#define DISPID_HTMLELEMENTEVENTS_ONMOUSEOVER                      DISPID_EVMETH_ONMOUSEOVER
#define DISPID_HTMLELEMENTEVENTS_ONMOUSEMOVE                      DISPID_EVMETH_ONMOUSEMOVE
#define DISPID_HTMLELEMENTEVENTS_ONMOUSEDOWN                      DISPID_EVMETH_ONMOUSEDOWN
#define DISPID_HTMLELEMENTEVENTS_ONMOUSEUP                        DISPID_EVMETH_ONMOUSEUP
#define DISPID_HTMLELEMENTEVENTS_ONSELECTSTART                    DISPID_EVMETH_ONSELECTSTART
#define DISPID_HTMLELEMENTEVENTS_ONFILTERCHANGE                   DISPID_EVMETH_ONFILTER
#define DISPID_HTMLELEMENTEVENTS_ONDRAGSTART                      DISPID_EVMETH_ONDRAGSTART
#define DISPID_HTMLELEMENTEVENTS_ONBEFOREUPDATE                   DISPID_EVMETH_ONBEFOREUPDATE
#define DISPID_HTMLELEMENTEVENTS_ONAFTERUPDATE                    DISPID_EVMETH_ONAFTERUPDATE
#define DISPID_HTMLELEMENTEVENTS_ONERRORUPDATE                    DISPID_EVMETH_ONERRORUPDATE
#define DISPID_HTMLELEMENTEVENTS_ONROWEXIT                        DISPID_EVMETH_ONROWEXIT
#define DISPID_HTMLELEMENTEVENTS_ONROWENTER                       DISPID_EVMETH_ONROWENTER
#define DISPID_HTMLELEMENTEVENTS_ONDATASETCHANGED                 DISPID_EVMETH_ONDATASETCHANGED
#define DISPID_HTMLELEMENTEVENTS_ONDATAAVAILABLE                  DISPID_EVMETH_ONDATAAVAILABLE
#define DISPID_HTMLELEMENTEVENTS_ONDATASETCOMPLETE                DISPID_EVMETH_ONDATASETCOMPLETE

//  DISPIDs for interface IHTMLStyleSheetRule

#define DISPID_IHTMLSTYLESHEETRULE_SELECTORTEXT                   DISPID_STYLERULE+1
#define DISPID_IHTMLSTYLESHEETRULE_STYLE                          STDPROPID_XOBJ_STYLE
#define DISPID_IHTMLSTYLESHEETRULE_READONLY                       DISPID_STYLERULE+2

//  DISPIDs for interface IHTMLStyleSheetRulesCollection

#define DISPID_IHTMLSTYLESHEETRULESCOLLECTION_LENGTH              DISPID_STYLERULES_COL+1
#define DISPID_IHTMLSTYLESHEETRULESCOLLECTION_ITEM                DISPID_VALUE

//  DISPIDs for interface IHTMLStyleSheet

#define DISPID_IHTMLSTYLESHEET_TITLE                              DISPID_STYLESHEET+1
#define DISPID_IHTMLSTYLESHEET_PARENTSTYLESHEET                   DISPID_STYLESHEET+2
#define DISPID_IHTMLSTYLESHEET_OWNINGELEMENT                      DISPID_STYLESHEET+3
#define DISPID_IHTMLSTYLESHEET_DISABLED                           STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLSTYLESHEET_READONLY                           DISPID_STYLESHEET+4
#define DISPID_IHTMLSTYLESHEET_IMPORTS                            DISPID_STYLESHEET+5
#define DISPID_IHTMLSTYLESHEET_HREF                               DISPID_STYLESHEET+6
#define DISPID_IHTMLSTYLESHEET_TYPE                               DISPID_STYLESHEET+7
#define DISPID_IHTMLSTYLESHEET_ID                                 DISPID_STYLESHEET+8
#define DISPID_IHTMLSTYLESHEET_ADDIMPORT                          DISPID_STYLESHEET+9
#define DISPID_IHTMLSTYLESHEET_ADDRULE                            DISPID_STYLESHEET+10
#define DISPID_IHTMLSTYLESHEET_REMOVEIMPORT                       DISPID_STYLESHEET+11
#define DISPID_IHTMLSTYLESHEET_REMOVERULE                         DISPID_STYLESHEET+12
#define DISPID_IHTMLSTYLESHEET_MEDIA                              DISPID_STYLESHEET+13
#define DISPID_IHTMLSTYLESHEET_CSSTEXT                            DISPID_STYLESHEET+14
#define DISPID_IHTMLSTYLESHEET_RULES                              DISPID_STYLESHEET+15

//  DISPIDs for interface IHTMLStyleSheetsCollection

#define DISPID_IHTMLSTYLESHEETSCOLLECTION_LENGTH                  DISPID_STYLESHEETS_COL+1
#define DISPID_IHTMLSTYLESHEETSCOLLECTION__NEWENUM                DISPID_NEWENUM
#define DISPID_IHTMLSTYLESHEETSCOLLECTION_ITEM                    DISPID_VALUE

//  DISPIDs for interface IHTMLLinkElement

#define DISPID_IHTMLLINKELEMENT_HREF                              DISPID_HEDELEMS+5
#define DISPID_IHTMLLINKELEMENT_REL                               DISPID_HEDELEMS+6
#define DISPID_IHTMLLINKELEMENT_REV                               DISPID_HEDELEMS+7
#define DISPID_IHTMLLINKELEMENT_TYPE                              DISPID_HEDELEMS+8
#define DISPID_IHTMLLINKELEMENT_READYSTATE                        DISPID_HEDELEMS+9
#define DISPID_IHTMLLINKELEMENT_ONREADYSTATECHANGE                DISPID_EVPROP_ONREADYSTATECHANGE
#define DISPID_IHTMLLINKELEMENT_ONLOAD                            DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLLINKELEMENT_ONERROR                           DISPID_EVPROP_ONERROR
#define DISPID_IHTMLLINKELEMENT_STYLESHEET                        DISPID_HEDELEMS+14
#define DISPID_IHTMLLINKELEMENT_DISABLED                          DISPID_HEDELEMS+15
#define DISPID_IHTMLLINKELEMENT_MEDIA                             DISPID_HEDELEMS+16

//  DISPIDs for event set HTMLLinkElementEvents

#define DISPID_HTMLLINKELEMENTEVENTS_ONREADYSTATECHANGE           DISPID_EVMETH_ONREADYSTATECHANGE
#define DISPID_HTMLLINKELEMENTEVENTS_ONLOAD                       DISPID_EVMETH_ONLOAD
#define DISPID_HTMLLINKELEMENTEVENTS_ONERROR                      DISPID_EVMETH_ONERROR

//  DISPIDs for interface IHTMLTxtRange

#define DISPID_IHTMLTXTRANGE_HTMLTEXT                             DISPID_RANGE+3
#define DISPID_IHTMLTXTRANGE_TEXT                                 DISPID_RANGE+4
#define DISPID_IHTMLTXTRANGE_PARENTELEMENT                        DISPID_RANGE+6
#define DISPID_IHTMLTXTRANGE_DUPLICATE                            DISPID_RANGE+8
#define DISPID_IHTMLTXTRANGE_INRANGE                              DISPID_RANGE+10
#define DISPID_IHTMLTXTRANGE_ISEQUAL                              DISPID_RANGE+11
#define DISPID_IHTMLTXTRANGE_SCROLLINTOVIEW                       DISPID_RANGE+12
#define DISPID_IHTMLTXTRANGE_COLLAPSE                             DISPID_RANGE+13
#define DISPID_IHTMLTXTRANGE_EXPAND                               DISPID_RANGE+14
#define DISPID_IHTMLTXTRANGE_MOVE                                 DISPID_RANGE+15
#define DISPID_IHTMLTXTRANGE_MOVESTART                            DISPID_RANGE+16
#define DISPID_IHTMLTXTRANGE_MOVEEND                              DISPID_RANGE+17
#define DISPID_IHTMLTXTRANGE_SELECT                               DISPID_RANGE+24
#define DISPID_IHTMLTXTRANGE_PASTEHTML                            DISPID_RANGE+26
#define DISPID_IHTMLTXTRANGE_MOVETOELEMENTTEXT                    DISPID_RANGE+1
#define DISPID_IHTMLTXTRANGE_SETENDPOINT                          DISPID_RANGE+25
#define DISPID_IHTMLTXTRANGE_COMPAREENDPOINTS                     DISPID_RANGE+18
#define DISPID_IHTMLTXTRANGE_FINDTEXT                             DISPID_RANGE+19
#define DISPID_IHTMLTXTRANGE_MOVETOPOINT                          DISPID_RANGE+20
#define DISPID_IHTMLTXTRANGE_GETBOOKMARK                          DISPID_RANGE+21
#define DISPID_IHTMLTXTRANGE_MOVETOBOOKMARK                       DISPID_RANGE+9
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDSUPPORTED                DISPID_RANGE+27
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDENABLED                  DISPID_RANGE+28
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDSTATE                    DISPID_RANGE+29
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDINDETERM                 DISPID_RANGE+30
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDTEXT                     DISPID_RANGE+31
#define DISPID_IHTMLTXTRANGE_QUERYCOMMANDVALUE                    DISPID_RANGE+32
#define DISPID_IHTMLTXTRANGE_EXECCOMMAND                          DISPID_RANGE+33
#define DISPID_IHTMLTXTRANGE_EXECCOMMANDSHOWHELP                  DISPID_RANGE+34

//  DISPIDs for interface IHTMLTextRangeMetrics

#define DISPID_IHTMLTEXTRANGEMETRICS_OFFSETTOP                    DISPID_RANGE+35
#define DISPID_IHTMLTEXTRANGEMETRICS_OFFSETLEFT                   DISPID_RANGE+36
#define DISPID_IHTMLTEXTRANGEMETRICS_BOUNDINGTOP                  DISPID_RANGE+37
#define DISPID_IHTMLTEXTRANGEMETRICS_BOUNDINGLEFT                 DISPID_RANGE+38
#define DISPID_IHTMLTEXTRANGEMETRICS_BOUNDINGWIDTH                DISPID_RANGE+39
#define DISPID_IHTMLTEXTRANGEMETRICS_BOUNDINGHEIGHT               DISPID_RANGE+40

//  DISPIDs for interface IHTMLFormElement

#define DISPID_IHTMLFORMELEMENT_ACTION                            DISPID_FORM+1
#define DISPID_IHTMLFORMELEMENT_DIR                               DISPID_FORM+2
#define DISPID_IHTMLFORMELEMENT_ENCODING                          DISPID_FORM+3
#define DISPID_IHTMLFORMELEMENT_METHOD                            DISPID_FORM+4
#define DISPID_IHTMLFORMELEMENT_ELEMENTS                          DISPID_FORM+5
#define DISPID_IHTMLFORMELEMENT_TARGET                            DISPID_FORM+6
#define DISPID_IHTMLFORMELEMENT_NAME                              STDPROPID_XOBJ_NAME
#define DISPID_IHTMLFORMELEMENT_ONSUBMIT                          DISPID_EVPROP_ONSUBMIT
#define DISPID_IHTMLFORMELEMENT_ONRESET                           DISPID_EVPROP_ONRESET
#define DISPID_IHTMLFORMELEMENT_SUBMIT                            DISPID_FORM+9
#define DISPID_IHTMLFORMELEMENT_RESET                             DISPID_FORM+10
#define DISPID_IHTMLFORMELEMENT_LENGTH                            DISPID_COLLECTION
#define DISPID_IHTMLFORMELEMENT__NEWENUM                          DISPID_NEWENUM
#define DISPID_IHTMLFORMELEMENT_ITEM                              DISPID_VALUE
#define DISPID_IHTMLFORMELEMENT_TAGS                              DISPID_COLLECTION+2

//  DISPIDs for event set HTMLFormElementEvents

#define DISPID_HTMLFORMELEMENTEVENTS_ONSUBMIT                     DISPID_EVMETH_ONSUBMIT
#define DISPID_HTMLFORMELEMENTEVENTS_ONRESET                      DISPID_EVMETH_ONRESET

//  DISPIDs for interface IHTMLControlElement

#define DISPID_IHTMLCONTROLELEMENT_TABINDEX                       STDPROPID_XOBJ_TABINDEX
#define DISPID_IHTMLCONTROLELEMENT_FOCUS                          DISPID_SITE+0
#define DISPID_IHTMLCONTROLELEMENT_ACCESSKEY                      DISPID_SITE+5
#define DISPID_IHTMLCONTROLELEMENT_ONBLUR                         DISPID_EVPROP_ONBLUR
#define DISPID_IHTMLCONTROLELEMENT_ONFOCUS                        DISPID_EVPROP_ONFOCUS
#define DISPID_IHTMLCONTROLELEMENT_ONRESIZE                       DISPID_EVPROP_ONRESIZE
#define DISPID_IHTMLCONTROLELEMENT_BLUR                           DISPID_SITE+2
#define DISPID_IHTMLCONTROLELEMENT_ADDFILTER                      DISPID_SITE+17
#define DISPID_IHTMLCONTROLELEMENT_REMOVEFILTER                   DISPID_SITE+18
#define DISPID_IHTMLCONTROLELEMENT_CLIENTHEIGHT                   DISPID_SITE+19
#define DISPID_IHTMLCONTROLELEMENT_CLIENTWIDTH                    DISPID_SITE+20
#define DISPID_IHTMLCONTROLELEMENT_CLIENTTOP                      DISPID_SITE+21
#define DISPID_IHTMLCONTROLELEMENT_CLIENTLEFT                     DISPID_SITE+22

//  DISPIDs for event set HTMLControlElementEvents

#define DISPID_HTMLCONTROLELEMENTEVENTS_ONFOCUS                   DISPID_EVMETH_ONFOCUS
#define DISPID_HTMLCONTROLELEMENTEVENTS_ONBLUR                    DISPID_EVMETH_ONBLUR
#define DISPID_HTMLCONTROLELEMENTEVENTS_ONRESIZE                  DISPID_EVMETH_ONRESIZE

//  DISPIDs for interface IHTMLTextContainer

#define DISPID_IHTMLTEXTCONTAINER_CREATECONTROLRANGE              DISPID_TEXTSITE+1
#define DISPID_IHTMLTEXTCONTAINER_SCROLLHEIGHT                    DISPID_TEXTSITE+2
#define DISPID_IHTMLTEXTCONTAINER_SCROLLWIDTH                     DISPID_TEXTSITE+3
#define DISPID_IHTMLTEXTCONTAINER_SCROLLTOP                       DISPID_TEXTSITE+4
#define DISPID_IHTMLTEXTCONTAINER_SCROLLLEFT                      DISPID_TEXTSITE+5
#define DISPID_IHTMLTEXTCONTAINER_ONSCROLL                        DISPID_EVPROP_ONSCROLL

//	DISPIDs for event set HTMLTextContainerEvents

#define DISPID_HTMLTEXTCONTAINEREVENTS_ONCHANGE                   DISPID_EVMETH_ONCHANGE
#define DISPID_HTMLTEXTCONTAINEREVENTS_ONSCROLL                   DISPID_EVMETH_ONSCROLL
#define DISPID_HTMLTEXTCONTAINEREVENTS_ONSELECT                   DISPID_EVMETH_ONSELECT

//  DISPIDs for interface IHTMLControlRange

#define DISPID_IHTMLCONTROLRANGE_SELECT                           DISPID_RANGE+2
#define DISPID_IHTMLCONTROLRANGE_ADD                              DISPID_RANGE+3
#define DISPID_IHTMLCONTROLRANGE_REMOVE                           DISPID_RANGE+4
#define DISPID_IHTMLCONTROLRANGE_ITEM                             DISPID_VALUE
#define DISPID_IHTMLCONTROLRANGE_SCROLLINTOVIEW                   DISPID_RANGE+6
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDSUPPORTED            DISPID_RANGE+7
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDENABLED              DISPID_RANGE+8
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDSTATE                DISPID_RANGE+9
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDINDETERM             DISPID_RANGE+10
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDTEXT                 DISPID_RANGE+11
#define DISPID_IHTMLCONTROLRANGE_QUERYCOMMANDVALUE                DISPID_RANGE+12
#define DISPID_IHTMLCONTROLRANGE_EXECCOMMAND                      DISPID_RANGE+13
#define DISPID_IHTMLCONTROLRANGE_EXECCOMMANDSHOWHELP              DISPID_RANGE+14
#define DISPID_IHTMLCONTROLRANGE_COMMONPARENTELEMENT              DISPID_RANGE+15
#define DISPID_IHTMLCONTROLRANGE_LENGTH                           DISPID_RANGE+5

//  DISPIDs for event set HTMLImgBaseEvents

#define DISPID_HTMLIMGBASEEVENTS_ONREADYSTATECHANGE               DISPID_EVMETH_ONREADYSTATECHANGE
#define DISPID_HTMLIMGBASEEVENTS_ONLOAD                           DISPID_EVMETH_ONLOAD
#define DISPID_HTMLIMGBASEEVENTS_ONERROR                          DISPID_EVMETH_ONERROR
#define DISPID_HTMLIMGBASEEVENTS_ONABORT                          DISPID_EVMETH_ONABORT

//  DISPIDs for interface IHTMLImgElement

#define DISPID_IHTMLIMGELEMENT_ISMAP                              DISPID_IMG+2
#define DISPID_IHTMLIMGELEMENT_USEMAP                             DISPID_IMG+8
#define DISPID_IHTMLIMGELEMENT_MIMETYPE                           DISPID_IMG+10
#define DISPID_IHTMLIMGELEMENT_FILESIZE                           DISPID_IMG+11
#define DISPID_IHTMLIMGELEMENT_FILECREATEDDATE                    DISPID_IMG+12
#define DISPID_IHTMLIMGELEMENT_FILEMODIFIEDDATE                   DISPID_IMG+13
#define DISPID_IHTMLIMGELEMENT_FILEUPDATEDDATE                    DISPID_IMG+14
#define DISPID_IHTMLIMGELEMENT_PROTOCOL                           DISPID_IMG+15
#define DISPID_IHTMLIMGELEMENT_HREF                               DISPID_IMG+16
#define DISPID_IHTMLIMGELEMENT_NAMEPROP                           DISPID_IMG+17
#define DISPID_IHTMLIMGELEMENT_BORDER                             DISPID_IMGBASE+4
#define DISPID_IHTMLIMGELEMENT_VSPACE                             DISPID_IMGBASE+5
#define DISPID_IHTMLIMGELEMENT_HSPACE                             DISPID_IMGBASE+6
#define DISPID_IHTMLIMGELEMENT_ALT                                DISPID_IMGBASE+2
#define DISPID_IHTMLIMGELEMENT_SRC                                DISPID_IMGBASE+3
#define DISPID_IHTMLIMGELEMENT_LOWSRC                             DISPID_IMGBASE+7
#define DISPID_IHTMLIMGELEMENT_VRML                               DISPID_IMGBASE+8
#define DISPID_IHTMLIMGELEMENT_DYNSRC                             DISPID_IMGBASE+9
#define DISPID_IHTMLIMGELEMENT_READYSTATE                         DISPID_IMGBASE+12
#define DISPID_IHTMLIMGELEMENT_COMPLETE                           DISPID_IMGBASE+10
#define DISPID_IHTMLIMGELEMENT_LOOP                               DISPID_IMGBASE+11
#define DISPID_IHTMLIMGELEMENT_ALIGN                              STDPROPID_XOBJ_CONTROLALIGN
#define DISPID_IHTMLIMGELEMENT_ONLOAD                             DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLIMGELEMENT_ONERROR                            DISPID_EVPROP_ONERROR
#define DISPID_IHTMLIMGELEMENT_ONABORT                            DISPID_EVPROP_ONABORT
#define DISPID_IHTMLIMGELEMENT_NAME                               STDPROPID_XOBJ_NAME
#define DISPID_IHTMLIMGELEMENT_WIDTH                              STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLIMGELEMENT_HEIGHT                             STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLIMGELEMENT_START                              DISPID_IMGBASE+13

//  DISPIDs for interface IHTMLInputImage

#define DISPID_IHTMLINPUTIMAGE_TYPE                               DISPID_INPUTIMAGE
#define DISPID_IHTMLINPUTIMAGE_DISABLED                           STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLINPUTIMAGE_BORDER                             DISPID_IMGBASE+4
#define DISPID_IHTMLINPUTIMAGE_VSPACE                             DISPID_IMGBASE+5
#define DISPID_IHTMLINPUTIMAGE_HSPACE                             DISPID_IMGBASE+6
#define DISPID_IHTMLINPUTIMAGE_ALT                                DISPID_IMGBASE+2
#define DISPID_IHTMLINPUTIMAGE_SRC                                DISPID_IMGBASE+3
#define DISPID_IHTMLINPUTIMAGE_LOWSRC                             DISPID_IMGBASE+7
#define DISPID_IHTMLINPUTIMAGE_VRML                               DISPID_IMGBASE+8
#define DISPID_IHTMLINPUTIMAGE_DYNSRC                             DISPID_IMGBASE+9
#define DISPID_IHTMLINPUTIMAGE_READYSTATE                         DISPID_IMGBASE+12
#define DISPID_IHTMLINPUTIMAGE_COMPLETE                           DISPID_IMGBASE+10
#define DISPID_IHTMLINPUTIMAGE_LOOP                               DISPID_IMGBASE+11
#define DISPID_IHTMLINPUTIMAGE_ALIGN                              STDPROPID_XOBJ_CONTROLALIGN
#define DISPID_IHTMLINPUTIMAGE_ONLOAD                             DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLINPUTIMAGE_ONERROR                            DISPID_EVPROP_ONERROR
#define DISPID_IHTMLINPUTIMAGE_ONABORT                            DISPID_EVPROP_ONABORT
#define DISPID_IHTMLINPUTIMAGE_NAME                               STDPROPID_XOBJ_NAME
#define DISPID_IHTMLINPUTIMAGE_WIDTH                              STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLINPUTIMAGE_HEIGHT                             STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLINPUTIMAGE_START                              DISPID_IMGBASE+13

//  DISPIDs for interface IHTMLImageElementFactory

#define DISPID_IHTMLIMAGEELEMENTFACTORY_CREATE                    DISPID_VALUE

//  DISPIDs for interface IHTMLBodyElement

#define DISPID_IHTMLBODYELEMENT_BACKGROUND                        DISPID_A_BACKGROUNDIMAGE
#define DISPID_IHTMLBODYELEMENT_BGPROPERTIES                      DISPID_A_BACKGROUNDATTACHMENT
#define DISPID_IHTMLBODYELEMENT_LEFTMARGIN                        DISPID_A_MARGINLEFT
#define DISPID_IHTMLBODYELEMENT_TOPMARGIN                         DISPID_A_MARGINTOP
#define DISPID_IHTMLBODYELEMENT_RIGHTMARGIN                       DISPID_A_MARGINRIGHT
#define DISPID_IHTMLBODYELEMENT_BOTTOMMARGIN                      DISPID_A_MARGINBOTTOM
#define DISPID_IHTMLBODYELEMENT_NOWRAP                            DISPID_A_NOWRAP
#define DISPID_IHTMLBODYELEMENT_BGCOLOR                           DISPID_BACKCOLOR
#define DISPID_IHTMLBODYELEMENT_TEXT                              DISPID_A_COLOR
#define DISPID_IHTMLBODYELEMENT_LINK                              DISPID_BODY+10
#define DISPID_IHTMLBODYELEMENT_VLINK                             DISPID_BODY+12
#define DISPID_IHTMLBODYELEMENT_ALINK                             DISPID_BODY+11
#define DISPID_IHTMLBODYELEMENT_ONLOAD                            DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLBODYELEMENT_ONUNLOAD                          DISPID_EVPROP_ONUNLOAD
#define DISPID_IHTMLBODYELEMENT_SCROLL                            DISPID_A_SCROLL
#define DISPID_IHTMLBODYELEMENT_ONSELECT                          DISPID_EVPROP_ONSELECT
#define DISPID_IHTMLBODYELEMENT_ONBEFOREUNLOAD                    DISPID_EVPROP_ONBEFOREUNLOAD
#define DISPID_IHTMLBODYELEMENT_CREATETEXTRANGE                   DISPID_BODY+13

//  DISPIDs for interface IHTMLFontElement

#define DISPID_IHTMLFONTELEMENT_COLOR                             DISPID_A_COLOR
#define DISPID_IHTMLFONTELEMENT_FACE                              DISPID_A_FONTFACE
#define DISPID_IHTMLFONTELEMENT_SIZE                              DISPID_A_FONTSIZE

//  DISPIDs for interface IHTMLAnchorElement

#define DISPID_IHTMLANCHORELEMENT_HREF                            DISPID_VALUE
#define DISPID_IHTMLANCHORELEMENT_TARGET                          DISPID_ANCHOR+3
#define DISPID_IHTMLANCHORELEMENT_REL                             DISPID_ANCHOR+5
#define DISPID_IHTMLANCHORELEMENT_REV                             DISPID_ANCHOR+6
#define DISPID_IHTMLANCHORELEMENT_URN                             DISPID_ANCHOR+7
#define DISPID_IHTMLANCHORELEMENT_METHODS                         DISPID_ANCHOR+8
#define DISPID_IHTMLANCHORELEMENT_NAME                            STDPROPID_XOBJ_NAME
#define DISPID_IHTMLANCHORELEMENT_HOST                            DISPID_ANCHOR+12
#define DISPID_IHTMLANCHORELEMENT_HOSTNAME                        DISPID_ANCHOR+13
#define DISPID_IHTMLANCHORELEMENT_PATHNAME                        DISPID_ANCHOR+14
#define DISPID_IHTMLANCHORELEMENT_PORT                            DISPID_ANCHOR+15
#define DISPID_IHTMLANCHORELEMENT_PROTOCOL                        DISPID_ANCHOR+16
#define DISPID_IHTMLANCHORELEMENT_SEARCH                          DISPID_ANCHOR+17
#define DISPID_IHTMLANCHORELEMENT_HASH                            DISPID_ANCHOR+18
#define DISPID_IHTMLANCHORELEMENT_ONBLUR                          DISPID_EVPROP_ONBLUR
#define DISPID_IHTMLANCHORELEMENT_ONFOCUS                         DISPID_EVPROP_ONFOCUS
#define DISPID_IHTMLANCHORELEMENT_ACCESSKEY                       DISPID_ANCHOR+22
#define DISPID_IHTMLANCHORELEMENT_PROTOCOLLONG                    DISPID_ANCHOR+31
#define DISPID_IHTMLANCHORELEMENT_MIMETYPE                        DISPID_ANCHOR+30
#define DISPID_IHTMLANCHORELEMENT_NAMEPROP                        DISPID_ANCHOR+32
#define DISPID_IHTMLANCHORELEMENT_TABINDEX                        STDPROPID_XOBJ_TABINDEX
#define DISPID_IHTMLANCHORELEMENT_FOCUS                           DISPID_ANCHOR+33
#define DISPID_IHTMLANCHORELEMENT_BLUR                            DISPID_ANCHOR+34

//  DISPIDs for event set HTMLAnchorEvents

#define DISPID_HTMLANCHOREVENTS_ONFOCUS                           DISPID_EVMETH_ONFOCUS
#define DISPID_HTMLANCHOREVENTS_ONBLUR                            DISPID_EVMETH_ONBLUR

//  DISPIDs for interface IHTMLLabelElement

#define DISPID_IHTMLLABELELEMENT_HTMLFOR                          DISPID_LABEL
#define DISPID_IHTMLLABELELEMENT_ACCESSKEY                        DISPID_LABEL+1

//  DISPIDs for interface IHTMLUListElement

#define DISPID_IHTMLULISTELEMENT_COMPACT                          DISPID_UL+2
#define DISPID_IHTMLULISTELEMENT_TYPE                             DISPID_A_LISTTYPE

//  DISPIDs for interface IHTMLOListElement

#define DISPID_IHTMLOLISTELEMENT_COMPACT                          DISPID_OL+2
#define DISPID_IHTMLOLISTELEMENT_START                            DISPID_OL+3
#define DISPID_IHTMLOLISTELEMENT_TYPE                             DISPID_A_LISTTYPE

//  DISPIDs for interface IHTMLLIElement

#define DISPID_IHTMLLIELEMENT_TYPE                                DISPID_A_LISTTYPE
#define DISPID_IHTMLLIELEMENT_VALUE                               DISPID_LI+1

//  DISPIDs for interface IHTMLBlockElement

#define DISPID_IHTMLBLOCKELEMENT_CLEAR                            DISPID_A_CLEAR

//  DISPIDs for interface IHTMLDivElement

#define DISPID_IHTMLDIVELEMENT_ALIGN                              STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLDIVELEMENT_NOWRAP                             DISPID_A_NOWRAP

//  DISPIDs for interface IHTMLDDElement

#define DISPID_IHTMLDDELEMENT_NOWRAP                              DISPID_A_NOWRAP

//  DISPIDs for interface IHTMLDTElement

#define DISPID_IHTMLDTELEMENT_NOWRAP                              DISPID_A_NOWRAP

//  DISPIDs for interface IHTMLBRElement

#define DISPID_IHTMLBRELEMENT_CLEAR                               DISPID_A_CLEAR

//	DISPIDs for interface IHTMLDListElement

#define DISPID_IHTMLDLISTELEMENT_COMPACT                          DISPID_DL+1

//	DISPIDs for interface IHTMLHRElement

#define DISPID_IHTMLHRELEMENT_ALIGN                               STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLHRELEMENT_COLOR                               DISPID_A_COLOR
#define DISPID_IHTMLHRELEMENT_NOSHADE                             DISPID_HR+1
#define DISPID_IHTMLHRELEMENT_WIDTH                               STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLHRELEMENT_SIZE                                STDPROPID_XOBJ_HEIGHT

//	DISPIDs for interface IHTMLParaElement

#define DISPID_IHTMLPARAELEMENT_ALIGN                             STDPROPID_XOBJ_BLOCKALIGN

//	DISPIDs for interface IHTMLElementCollection

#define DISPID_IHTMLELEMENTCOLLECTION_TOSTRING                    DISPID_COLLECTION+1
#define DISPID_IHTMLELEMENTCOLLECTION_LENGTH                      DISPID_COLLECTION
#define DISPID_IHTMLELEMENTCOLLECTION__NEWENUM                    DISPID_NEWENUM
#define DISPID_IHTMLELEMENTCOLLECTION_ITEM                        DISPID_VALUE
#define DISPID_IHTMLELEMENTCOLLECTION_TAGS                        DISPID_COLLECTION+2

//	DISPIDs for interface IHTMLHeaderElement

#define DISPID_IHTMLHEADERELEMENT_ALIGN                           STDPROPID_XOBJ_BLOCKALIGN

//	DISPIDs for interface IHTMLSelectElement

#define DISPID_IHTMLSELECTELEMENT_SIZE                            DISPID_SELECT+2
#define DISPID_IHTMLSELECTELEMENT_MULTIPLE                        DISPID_SELECT+3
#define DISPID_IHTMLSELECTELEMENT_NAME                            STDPROPID_XOBJ_NAME
#define DISPID_IHTMLSELECTELEMENT_OPTIONS                         DISPID_SELECT+5
#define DISPID_IHTMLSELECTELEMENT_ONCHANGE                        DISPID_EVPROP_ONCHANGE
#define DISPID_IHTMLSELECTELEMENT_SELECTEDINDEX                   DISPID_SELECT+10
#define DISPID_IHTMLSELECTELEMENT_TYPE                            DISPID_SELECT+12
#define DISPID_IHTMLSELECTELEMENT_VALUE                           DISPID_SELECT+11
#define DISPID_IHTMLSELECTELEMENT_DISABLED                        STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLSELECTELEMENT_FORM                            DISPID_SITE+4
#define DISPID_IHTMLSELECTELEMENT_ADD                             DISPID_COLLECTION+3
#define DISPID_IHTMLSELECTELEMENT_REMOVE                          DISPID_COLLECTION+4
#define DISPID_IHTMLSELECTELEMENT_LENGTH                          DISPID_COLLECTION
#define DISPID_IHTMLSELECTELEMENT__NEWENUM                        DISPID_NEWENUM
#define DISPID_IHTMLSELECTELEMENT_ITEM                            DISPID_VALUE
#define DISPID_IHTMLSELECTELEMENT_TAGS                            DISPID_COLLECTION+2

//	DISPIDs for event set HTMLSelectElementEvents

#define DISPID_HTMLSELECTELEMENTEVENTS_ONCHANGE                   DISPID_EVMETH_ONCHANGE

//	DISPIDs for interface IHTMLSelectionObject

#define DISPID_IHTMLSELECTIONOBJECT_CREATERANGE                   DISPID_SELECTOBJ+1
#define DISPID_IHTMLSELECTIONOBJECT_EMPTY                         DISPID_SELECTOBJ+2
#define DISPID_IHTMLSELECTIONOBJECT_CLEAR                         DISPID_SELECTOBJ+3
#define DISPID_IHTMLSELECTIONOBJECT_TYPE                          DISPID_SELECTOBJ+4

//	DISPIDs for interface IHTMLOptionElement

#define DISPID_IHTMLOPTIONELEMENT_SELECTED                        DISPID_OPTION+1
#define DISPID_IHTMLOPTIONELEMENT_VALUE                           DISPID_OPTION+2
#define DISPID_IHTMLOPTIONELEMENT_DEFAULTSELECTED                 DISPID_OPTION+3
#define DISPID_IHTMLOPTIONELEMENT_INDEX                           DISPID_OPTION+5
#define DISPID_IHTMLOPTIONELEMENT_TEXT                            DISPID_OPTION+4
#define DISPID_IHTMLOPTIONELEMENT_FORM                            DISPID_OPTION+6

//	DISPIDs for interface IHTMLOptionElementFactory

#define DISPID_IHTMLOPTIONELEMENTFACTORY_CREATE                   DISPID_VALUE

//	DISPIDs for interface IHTMLInputHiddenElement

#define DISPID_IHTMLINPUTHIDDENELEMENT_TYPE                       DISPID_INPUT
#define DISPID_IHTMLINPUTHIDDENELEMENT_VALUE                      DISPID_A_VALUE
#define DISPID_IHTMLINPUTHIDDENELEMENT_NAME                       STDPROPID_XOBJ_NAME
#define DISPID_IHTMLINPUTHIDDENELEMENT_STATUS                     DISPID_INPUT+1
#define DISPID_IHTMLINPUTHIDDENELEMENT_DISABLED                   STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLINPUTHIDDENELEMENT_FORM                       DISPID_SITE+4
#define DISPID_IHTMLINPUTHIDDENELEMENT_CREATETEXTRANGE            DISPID_INPUTTEXTBASE+5

//	DISPIDs for interface IHTMLInputTextElement

#define DISPID_IHTMLINPUTTEXTELEMENT_TYPE                         DISPID_INPUT
#define DISPID_IHTMLINPUTTEXTELEMENT_VALUE                        DISPID_A_VALUE
#define DISPID_IHTMLINPUTTEXTELEMENT_NAME                         STDPROPID_XOBJ_NAME
#define DISPID_IHTMLINPUTTEXTELEMENT_STATUS                       DISPID_INPUT+1
#define DISPID_IHTMLINPUTTEXTELEMENT_DISABLED                     STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLINPUTTEXTELEMENT_FORM                         DISPID_SITE+4
#define DISPID_IHTMLINPUTTEXTELEMENT_DEFAULTVALUE                 DISPID_DEFAULTVALUE
#define DISPID_IHTMLINPUTTEXTELEMENT_SIZE                         DISPID_INPUTTEXT+1
#define DISPID_IHTMLINPUTTEXTELEMENT_MAXLENGTH                    DISPID_INPUTTEXT+2
#define DISPID_IHTMLINPUTTEXTELEMENT_SELECT                       DISPID_INPUTTEXTBASE+3
#define DISPID_IHTMLINPUTTEXTELEMENT_ONCHANGE                     DISPID_EVPROP_ONCHANGE
#define DISPID_IHTMLINPUTTEXTELEMENT_ONSELECT                     DISPID_EVPROP_ONSELECT
#define DISPID_IHTMLINPUTTEXTELEMENT_READONLY                     DISPID_INPUTTEXTBASE+1
#define DISPID_IHTMLINPUTTEXTELEMENT_CREATETEXTRANGE              DISPID_INPUTTEXTBASE+5

//	DISPIDs for interface IHTMLTextAreaElement

#define DISPID_IHTMLTEXTAREAELEMENT_TYPE                          DISPID_INPUT
#define DISPID_IHTMLTEXTAREAELEMENT_VALUE                         DISPID_A_VALUE
#define DISPID_IHTMLTEXTAREAELEMENT_NAME                          STDPROPID_XOBJ_NAME
#define DISPID_IHTMLTEXTAREAELEMENT_STATUS                        DISPID_INPUT+1
#define DISPID_IHTMLTEXTAREAELEMENT_DISABLED                      STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLTEXTAREAELEMENT_FORM                          DISPID_SITE+4
#define DISPID_IHTMLTEXTAREAELEMENT_DEFAULTVALUE                  DISPID_DEFAULTVALUE
#define DISPID_IHTMLTEXTAREAELEMENT_SELECT                        DISPID_INPUTTEXTBASE+3
#define DISPID_IHTMLTEXTAREAELEMENT_ONCHANGE                      DISPID_EVPROP_ONCHANGE
#define DISPID_IHTMLTEXTAREAELEMENT_ONSELECT                      DISPID_EVPROP_ONSELECT
#define DISPID_IHTMLTEXTAREAELEMENT_READONLY                      DISPID_INPUTTEXTBASE+1
#define DISPID_IHTMLTEXTAREAELEMENT_ROWS                          DISPID_TEXTAREA+1
#define DISPID_IHTMLTEXTAREAELEMENT_COLS                          DISPID_TEXTAREA+2
#define DISPID_IHTMLTEXTAREAELEMENT_WRAP                          DISPID_TEXTAREA+3
#define DISPID_IHTMLTEXTAREAELEMENT_CREATETEXTRANGE               DISPID_INPUTTEXTBASE+5

//	DISPIDs for event set HTMLInputTextElementEvents

#define DISPID_HTMLINPUTTEXTELEMENTEVENTS_ONCHANGE                DISPID_EVMETH_ONCHANGE
#define DISPID_HTMLINPUTTEXTELEMENTEVENTS_ONSELECT                DISPID_EVMETH_ONSELECT

//	DISPIDs for interface IHTMLInputButtonElement

#define DISPID_IHTMLINPUTBUTTONELEMENT_TYPE                       DISPID_INPUT
#define DISPID_IHTMLINPUTBUTTONELEMENT_VALUE                      DISPID_A_VALUE
#define DISPID_IHTMLINPUTBUTTONELEMENT_NAME                       STDPROPID_XOBJ_NAME
#define DISPID_IHTMLINPUTBUTTONELEMENT_STATUS                     DISPID_INPUT+1
#define DISPID_IHTMLINPUTBUTTONELEMENT_DISABLED                   STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLINPUTBUTTONELEMENT_FORM                       DISPID_SITE+4
#define DISPID_IHTMLINPUTBUTTONELEMENT_CREATETEXTRANGE            DISPID_INPUT+4

//	DISPIDs for interface IHTMLButtonElement

#define DISPID_IHTMLBUTTONELEMENT_TYPE                            DISPID_INPUT
#define DISPID_IHTMLBUTTONELEMENT_VALUE                           DISPID_A_VALUE
#define DISPID_IHTMLBUTTONELEMENT_NAME                            STDPROPID_XOBJ_NAME
#define DISPID_IHTMLBUTTONELEMENT_STATUS                          DISPID_INPUT+1
#define DISPID_IHTMLBUTTONELEMENT_DISABLED                        STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLBUTTONELEMENT_FORM                            DISPID_SITE+4
#define DISPID_IHTMLBUTTONELEMENT_CREATETEXTRANGE                 DISPID_INPUT+4

//	DISPIDs for interface IHTMLInputFileElement

#define DISPID_IHTMLINPUTFILEELEMENT_TYPE                         DISPID_INPUT
#define DISPID_IHTMLINPUTFILEELEMENT_NAME                         STDPROPID_XOBJ_NAME
#define DISPID_IHTMLINPUTFILEELEMENT_STATUS                       DISPID_INPUT+1
#define DISPID_IHTMLINPUTFILEELEMENT_DISABLED                     STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLINPUTFILEELEMENT_FORM                         DISPID_SITE+4
#define DISPID_IHTMLINPUTFILEELEMENT_SIZE                         DISPID_INPUTTEXT+1
#define DISPID_IHTMLINPUTFILEELEMENT_MAXLENGTH                    DISPID_INPUTTEXT+2
#define DISPID_IHTMLINPUTFILEELEMENT_SELECT                       DISPID_INPUTTEXTBASE+3
#define DISPID_IHTMLINPUTFILEELEMENT_ONCHANGE                     DISPID_EVPROP_ONCHANGE
#define DISPID_IHTMLINPUTFILEELEMENT_ONSELECT                     DISPID_EVPROP_ONSELECT
#define DISPID_IHTMLINPUTFILEELEMENT_VALUE                        DISPID_A_VALUE

//	DISPIDs for interface IHTMLMarqueeElement

#define DISPID_IHTMLMARQUEEELEMENT_BGCOLOR                        DISPID_BACKCOLOR
#define DISPID_IHTMLMARQUEEELEMENT_SCROLLDELAY                    DISPID_MARQUEE
#define DISPID_IHTMLMARQUEEELEMENT_DIRECTION                      DISPID_MARQUEE+1
#define DISPID_IHTMLMARQUEEELEMENT_BEHAVIOR                       DISPID_MARQUEE+2
#define DISPID_IHTMLMARQUEEELEMENT_SCROLLAMOUNT                   DISPID_MARQUEE+3
#define DISPID_IHTMLMARQUEEELEMENT_LOOP                           DISPID_MARQUEE+4
#define DISPID_IHTMLMARQUEEELEMENT_VSPACE                         DISPID_MARQUEE+5
#define DISPID_IHTMLMARQUEEELEMENT_HSPACE                         DISPID_MARQUEE+6
#define DISPID_IHTMLMARQUEEELEMENT_ONFINISH                       DISPID_EVPROP_ONFINISH
#define DISPID_IHTMLMARQUEEELEMENT_ONSTART                        DISPID_EVPROP_ONSTART
#define DISPID_IHTMLMARQUEEELEMENT_ONBOUNCE                       DISPID_EVPROP_ONBOUNCE
#define DISPID_IHTMLMARQUEEELEMENT_WIDTH                          STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLMARQUEEELEMENT_HEIGHT                         STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLMARQUEEELEMENT_TRUESPEED                      DISPID_MARQUEE+7
#define DISPID_IHTMLMARQUEEELEMENT_START                          DISPID_MARQUEE+10
#define DISPID_IHTMLMARQUEEELEMENT_STOP                           DISPID_MARQUEE+11

//	DISPIDs for event set HTMLMarqueeElementEvents

#define DISPID_HTMLMARQUEEELEMENTEVENTS_ONBOUNCE                  DISPID_EVMETH_ONBOUNCE
#define DISPID_HTMLMARQUEEELEMENTEVENTS_ONFINISH                  DISPID_EVMETH_ONFINISH
#define DISPID_HTMLMARQUEEELEMENTEVENTS_ONSTART                   DISPID_EVMETH_ONSTART

//	DISPIDs for interface IHTMLOptionButtonElement

#define DISPID_IHTMLOPTIONBUTTONELEMENT_VALUE                     DISPID_A_VALUE
#define DISPID_IHTMLOPTIONBUTTONELEMENT_TYPE                      DISPID_CHECKBOX
#define DISPID_IHTMLOPTIONBUTTONELEMENT_NAME                      STDPROPID_XOBJ_NAME
#define DISPID_IHTMLOPTIONBUTTONELEMENT_CHECKED                   DISPID_CHECKBOX+1
#define DISPID_IHTMLOPTIONBUTTONELEMENT_DEFAULTCHECKED            DISPID_CHECKBOX+2
#define DISPID_IHTMLOPTIONBUTTONELEMENT_ONCHANGE                  DISPID_EVPROP_ONCHANGE
#define DISPID_IHTMLOPTIONBUTTONELEMENT_DISABLED                  STDPROPID_XOBJ_DISABLED
#define DISPID_IHTMLOPTIONBUTTONELEMENT_STATUS                    DISPID_CHECKBOX+3
#define DISPID_IHTMLOPTIONBUTTONELEMENT_INDETERMINATE             DISPID_CHECKBOX+4
#define DISPID_IHTMLOPTIONBUTTONELEMENT_FORM                      DISPID_SITE+4

//	DISPIDs for event set HTMLOptionButtonElementEvents

#define DISPID_HTMLOPTIONBUTTONELEMENTEVENTS_ONCHANGE             DISPID_EVMETH_ONCHANGE

//	DISPIDs for interface IHTMLTitleElement

#define DISPID_IHTMLTITLEELEMENT_TEXT                             DISPID_A_VALUE

//	DISPIDs for interface IHTMLMetaElement

#define DISPID_IHTMLMETAELEMENT_HTTPEQUIV                         DISPID_HEDELEMS+1
#define DISPID_IHTMLMETAELEMENT_CONTENT                           DISPID_HEDELEMS+2
#define DISPID_IHTMLMETAELEMENT_NAME                              STDPROPID_XOBJ_NAME
#define DISPID_IHTMLMETAELEMENT_URL                               DISPID_HEDELEMS+3
#define DISPID_IHTMLMETAELEMENT_CHARSET                           DISPID_HEDELEMS+13

//	DISPIDs for interface IHTMLBaseElement

#define DISPID_IHTMLBASEELEMENT_HREF                              DISPID_HEDELEMS+3
#define DISPID_IHTMLBASEELEMENT_TARGET                            DISPID_HEDELEMS+4

//	DISPIDs for interface IHTMLIsIndexElement

#define DISPID_IHTMLISINDEXELEMENT_PROMPT                         DISPID_HEDELEMS+10
#define DISPID_IHTMLISINDEXELEMENT_ACTION                         DISPID_HEDELEMS+11

//	DISPIDs for interface IHTMLNextIdElement

#define DISPID_IHTMLNEXTIDELEMENT_N                               DISPID_HEDELEMS+12

//	DISPIDs for interface IHTMLBaseFontElement

#define DISPID_IHTMLBASEFONTELEMENT_COLOR                         DISPID_A_COLOR
#define DISPID_IHTMLBASEFONTELEMENT_FACE                          DISPID_A_FONTFACE
#define DISPID_IHTMLBASEFONTELEMENT_SIZE                          DISPID_A_BASEFONT

//	DISPIDs for interface IOmHistory

#define DISPID_IOMHISTORY_LENGTH                                  DISPID_HISTORY
#define DISPID_IOMHISTORY_BACK                                    DISPID_HISTORY+1
#define DISPID_IOMHISTORY_FORWARD                                 DISPID_HISTORY+2
#define DISPID_IOMHISTORY_GO                                      DISPID_HISTORY+3

//	DISPIDs for interface IHTMLMimeTypesCollection

#define DISPID_IHTMLMIMETYPESCOLLECTION_LENGTH                    1

//	DISPIDs for interface IHTMLPluginsCollection

#define DISPID_IHTMLPLUGINSCOLLECTION_LENGTH                      1
#define DISPID_IHTMLPLUGINSCOLLECTION_REFRESH                     2

//	DISPIDs for interface IHTMLOpsProfile

#define DISPID_IHTMLOPSPROFILE_ADDREQUEST                         1
#define DISPID_IHTMLOPSPROFILE_CLEARREQUEST                       2
#define DISPID_IHTMLOPSPROFILE_DOREQUEST                          3
#define DISPID_IHTMLOPSPROFILE_GETATTRIBUTE                       4
#define DISPID_IHTMLOPSPROFILE_SETATTRIBUTE                       5
#define DISPID_IHTMLOPSPROFILE_COMMITCHANGES                      6
#define DISPID_IHTMLOPSPROFILE_ADDREADREQUEST                     7
#define DISPID_IHTMLOPSPROFILE_DOREADREQUEST                      8
#define DISPID_IHTMLOPSPROFILE_DOWRITEREQUEST                     9

//	DISPIDs for interface IOmNavigator

#define DISPID_IOMNAVIGATOR_APPCODENAME                           DISPID_NAVIGATOR
#define DISPID_IOMNAVIGATOR_APPNAME                               DISPID_NAVIGATOR+1
#define DISPID_IOMNAVIGATOR_APPVERSION                            DISPID_NAVIGATOR+2
#define DISPID_IOMNAVIGATOR_USERAGENT                             DISPID_NAVIGATOR+3
#define DISPID_IOMNAVIGATOR_JAVAENABLED                           DISPID_NAVIGATOR+4
#define DISPID_IOMNAVIGATOR_TAINTENABLED                          DISPID_NAVIGATOR+5
#define DISPID_IOMNAVIGATOR_MIMETYPES                             DISPID_NAVIGATOR+6
#define DISPID_IOMNAVIGATOR_PLUGINS                               DISPID_NAVIGATOR+7
#define DISPID_IOMNAVIGATOR_COOKIEENABLED                         DISPID_NAVIGATOR+8
#define DISPID_IOMNAVIGATOR_OPSPROFILE                            DISPID_NAVIGATOR+9
#define DISPID_IOMNAVIGATOR_TOSTRING                              DISPID_NAVIGATOR+10
#define DISPID_IOMNAVIGATOR_CPUCLASS                              DISPID_NAVIGATOR+11
#define DISPID_IOMNAVIGATOR_SYSTEMLANGUAGE                        DISPID_NAVIGATOR+12
#define DISPID_IOMNAVIGATOR_BROWSERLANGUAGE                       DISPID_NAVIGATOR+13
#define DISPID_IOMNAVIGATOR_USERLANGUAGE                          DISPID_NAVIGATOR+14
#define DISPID_IOMNAVIGATOR_PLATFORM                              DISPID_NAVIGATOR+15
#define DISPID_IOMNAVIGATOR_APPMINORVERSION                       DISPID_NAVIGATOR+16
#define DISPID_IOMNAVIGATOR_CONNECTIONSPEED                       DISPID_NAVIGATOR+17
#define DISPID_IOMNAVIGATOR_ONLINE                                DISPID_NAVIGATOR+18
#define DISPID_IOMNAVIGATOR_USERPROFILE                           DISPID_NAVIGATOR+19

//	DISPIDs for interface IHTMLLocation

#define DISPID_IHTMLLOCATION_HREF                                 DISPID_VALUE
#define DISPID_IHTMLLOCATION_PROTOCOL                             DISPID_LOCATION
#define DISPID_IHTMLLOCATION_HOST                                 DISPID_LOCATION+1
#define DISPID_IHTMLLOCATION_HOSTNAME                             DISPID_LOCATION+2
#define DISPID_IHTMLLOCATION_PORT                                 DISPID_LOCATION+3
#define DISPID_IHTMLLOCATION_PATHNAME                             DISPID_LOCATION+4
#define DISPID_IHTMLLOCATION_SEARCH                               DISPID_LOCATION+5
#define DISPID_IHTMLLOCATION_HASH                                 DISPID_LOCATION+6
#define DISPID_IHTMLLOCATION_RELOAD                               DISPID_LOCATION+7
#define DISPID_IHTMLLOCATION_REPLACE                              DISPID_LOCATION+8
#define DISPID_IHTMLLOCATION_ASSIGN                               DISPID_LOCATION+9
#define DISPID_IHTMLLOCATION_TOSTRING                             DISPID_LOCATION+10

//	DISPIDs for interface IHTMLEventObj

#define DISPID_IHTMLEVENTOBJ_SRCELEMENT                           DISPID_EVENTOBJ+1
#define DISPID_IHTMLEVENTOBJ_ALTKEY                               DISPID_EVENTOBJ+2
#define DISPID_IHTMLEVENTOBJ_CTRLKEY                              DISPID_EVENTOBJ+3
#define DISPID_IHTMLEVENTOBJ_SHIFTKEY                             DISPID_EVENTOBJ+4
#define DISPID_IHTMLEVENTOBJ_RETURNVALUE                          DISPID_EVENTOBJ+7
#define DISPID_IHTMLEVENTOBJ_CANCELBUBBLE                         DISPID_EVENTOBJ+8
#define DISPID_IHTMLEVENTOBJ_FROMELEMENT                          DISPID_EVENTOBJ+9
#define DISPID_IHTMLEVENTOBJ_TOELEMENT                            DISPID_EVENTOBJ+10
#define DISPID_IHTMLEVENTOBJ_KEYCODE                              DISPID_EVENTOBJ+11
#define DISPID_IHTMLEVENTOBJ_BUTTON                               DISPID_EVENTOBJ+12
#define DISPID_IHTMLEVENTOBJ_TYPE                                 DISPID_EVENTOBJ+13
#define DISPID_IHTMLEVENTOBJ_QUALIFIER                            DISPID_EVENTOBJ+14
#define DISPID_IHTMLEVENTOBJ_REASON                               DISPID_EVENTOBJ+15
#define DISPID_IHTMLEVENTOBJ_X                                    DISPID_EVENTOBJ+5
#define DISPID_IHTMLEVENTOBJ_Y                                    DISPID_EVENTOBJ+6
#define DISPID_IHTMLEVENTOBJ_CLIENTX                              DISPID_EVENTOBJ+20
#define DISPID_IHTMLEVENTOBJ_CLIENTY                              DISPID_EVENTOBJ+21
#define DISPID_IHTMLEVENTOBJ_OFFSETX                              DISPID_EVENTOBJ+22
#define DISPID_IHTMLEVENTOBJ_OFFSETY                              DISPID_EVENTOBJ+23
#define DISPID_IHTMLEVENTOBJ_SCREENX                              DISPID_EVENTOBJ+24
#define DISPID_IHTMLEVENTOBJ_SCREENY                              DISPID_EVENTOBJ+25
#define DISPID_IHTMLEVENTOBJ_SRCFILTER                            DISPID_EVENTOBJ+26

//	DISPIDs for interface IHTMLFramesCollection2

#define DISPID_IHTMLFRAMESCOLLECTION2_ITEM                        0
#define DISPID_IHTMLFRAMESCOLLECTION2_LENGTH                      1001

//	DISPIDs for interface IHTMLScreen

#define DISPID_IHTMLSCREEN_COLORDEPTH                             DISPID_SCREEN+1
#define DISPID_IHTMLSCREEN_BUFFERDEPTH                            DISPID_SCREEN+2
#define DISPID_IHTMLSCREEN_WIDTH                                  DISPID_SCREEN+3
#define DISPID_IHTMLSCREEN_HEIGHT                                 DISPID_SCREEN+4
#define DISPID_IHTMLSCREEN_UPDATEINTERVAL                         DISPID_SCREEN+5
#define DISPID_IHTMLSCREEN_AVAILHEIGHT                            DISPID_SCREEN+6
#define DISPID_IHTMLSCREEN_AVAILWIDTH                             DISPID_SCREEN+7
#define DISPID_IHTMLSCREEN_FONTSMOOTHINGENABLED                   DISPID_SCREEN+8

//	DISPIDs for interface IHTMLWindow2

#define DISPID_IHTMLWINDOW2_FRAMES                                1100
#define DISPID_IHTMLWINDOW2_DEFAULTSTATUS                         1101
#define DISPID_IHTMLWINDOW2_STATUS                                1102
#define DISPID_IHTMLWINDOW2_SETTIMEOUT                            1103
#define DISPID_IHTMLWINDOW2_CLEARTIMEOUT                          1104
#define DISPID_IHTMLWINDOW2_ALERT                                 1105
#define DISPID_IHTMLWINDOW2_CONFIRM                               1110
#define DISPID_IHTMLWINDOW2_PROMPT                                1111
#define DISPID_IHTMLWINDOW2_IMAGE                                 1125
#define DISPID_IHTMLWINDOW2_LOCATION                              14
#define DISPID_IHTMLWINDOW2_HISTORY                               2
#define DISPID_IHTMLWINDOW2_CLOSE                                 3
#define DISPID_IHTMLWINDOW2_OPENER                                4
#define DISPID_IHTMLWINDOW2_NAVIGATOR                             5
#define DISPID_IHTMLWINDOW2_NAME                                  11
#define DISPID_IHTMLWINDOW2_PARENT                                12
#define DISPID_IHTMLWINDOW2_OPEN                                  13
#define DISPID_IHTMLWINDOW2_SELF                                  20
#define DISPID_IHTMLWINDOW2_TOP                                   21
#define DISPID_IHTMLWINDOW2_WINDOW                                22
#define DISPID_IHTMLWINDOW2_NAVIGATE                              25
#define DISPID_IHTMLWINDOW2_ONFOCUS                               DISPID_EVPROP_ONFOCUS
#define DISPID_IHTMLWINDOW2_ONBLUR                                DISPID_EVPROP_ONBLUR
#define DISPID_IHTMLWINDOW2_ONLOAD                                DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLWINDOW2_ONBEFOREUNLOAD                        DISPID_EVPROP_ONBEFOREUNLOAD
#define DISPID_IHTMLWINDOW2_ONUNLOAD                              DISPID_EVPROP_ONUNLOAD
#define DISPID_IHTMLWINDOW2_ONHELP                                DISPID_EVPROP_ONHELP
#define DISPID_IHTMLWINDOW2_ONERROR                               DISPID_EVPROP_ONERROR
#define DISPID_IHTMLWINDOW2_ONRESIZE                              DISPID_EVPROP_ONRESIZE
#define DISPID_IHTMLWINDOW2_ONSCROLL                              DISPID_EVPROP_ONSCROLL
#define DISPID_IHTMLWINDOW2_DOCUMENT                              1151
#define DISPID_IHTMLWINDOW2_EVENT                                 1152
#define DISPID_IHTMLWINDOW2__NEWENUM                              1153
#define DISPID_IHTMLWINDOW2_SHOWMODALDIALOG                       1154
#define DISPID_IHTMLWINDOW2_SHOWHELP                              1155
#define DISPID_IHTMLWINDOW2_SCREEN                                1156
#define DISPID_IHTMLWINDOW2_OPTION                                1157
#define DISPID_IHTMLWINDOW2_FOCUS                                 1158
#define DISPID_IHTMLWINDOW2_CLOSED                                23
#define DISPID_IHTMLWINDOW2_BLUR                                  1159
#define DISPID_IHTMLWINDOW2_SCROLL                                1160
#define DISPID_IHTMLWINDOW2_CLIENTINFORMATION                     1161
#define DISPID_IHTMLWINDOW2_SETINTERVAL                           1162
#define DISPID_IHTMLWINDOW2_CLEARINTERVAL                         1163
#define DISPID_IHTMLWINDOW2_OFFSCREENBUFFERING                    1164
#define DISPID_IHTMLWINDOW2_EXECSCRIPT                            1165
#define DISPID_IHTMLWINDOW2_TOSTRING                              1166
#define DISPID_IHTMLWINDOW2_SCROLLBY                              1167
#define DISPID_IHTMLWINDOW2_SCROLLTO                              1168
#define DISPID_IHTMLWINDOW2_MOVETO                                6
#define DISPID_IHTMLWINDOW2_MOVEBY                                7
#define DISPID_IHTMLWINDOW2_RESIZETO                              9
#define DISPID_IHTMLWINDOW2_RESIZEBY                              8
#define DISPID_IHTMLWINDOW2_EXTERNAL                              1169

//	DISPIDs for event set HTMLWindowEvents

#define DISPID_HTMLWINDOWEVENTS_ONLOAD                            DISPID_EVMETH_ONLOAD
#define DISPID_HTMLWINDOWEVENTS_ONUNLOAD                          DISPID_EVMETH_ONUNLOAD
#define DISPID_HTMLWINDOWEVENTS_ONHELP                            DISPID_EVMETH_ONHELP
#define DISPID_HTMLWINDOWEVENTS_ONFOCUS                           DISPID_EVMETH_ONFOCUS
#define DISPID_HTMLWINDOWEVENTS_ONBLUR                            DISPID_EVMETH_ONBLUR
#define DISPID_HTMLWINDOWEVENTS_ONERROR                           DISPID_EVMETH_ONERROR
#define DISPID_HTMLWINDOWEVENTS_ONRESIZE                          DISPID_EVMETH_ONRESIZE
#define DISPID_HTMLWINDOWEVENTS_ONSCROLL                          DISPID_EVMETH_ONSCROLL
#define DISPID_HTMLWINDOWEVENTS_ONBEFOREUNLOAD                    DISPID_EVMETH_ONBEFOREUNLOAD

//	DISPIDs for interface IHTMLDocument

#define DISPID_IHTMLDOCUMENT_SCRIPT                               DISPID_OMDOCUMENT+1

//	DISPIDs for interface IHTMLDocument2

#define DISPID_IHTMLDOCUMENT2_ALL                                 DISPID_OMDOCUMENT+3
#define DISPID_IHTMLDOCUMENT2_BODY                                DISPID_OMDOCUMENT+4
#define DISPID_IHTMLDOCUMENT2_ACTIVEELEMENT                       DISPID_OMDOCUMENT+5
#define DISPID_IHTMLDOCUMENT2_IMAGES                              DISPID_OMDOCUMENT+11
#define DISPID_IHTMLDOCUMENT2_APPLETS                             DISPID_OMDOCUMENT+8
#define DISPID_IHTMLDOCUMENT2_LINKS                               DISPID_OMDOCUMENT+9
#define DISPID_IHTMLDOCUMENT2_FORMS                               DISPID_OMDOCUMENT+10
#define DISPID_IHTMLDOCUMENT2_ANCHORS                             DISPID_OMDOCUMENT+7
#define DISPID_IHTMLDOCUMENT2_TITLE                               DISPID_OMDOCUMENT+12
#define DISPID_IHTMLDOCUMENT2_SCRIPTS                             DISPID_OMDOCUMENT+13
#define DISPID_IHTMLDOCUMENT2_DESIGNMODE                          DISPID_OMDOCUMENT+14
#define DISPID_IHTMLDOCUMENT2_SELECTION                           DISPID_OMDOCUMENT+17
#define DISPID_IHTMLDOCUMENT2_READYSTATE                          DISPID_OMDOCUMENT+18
#define DISPID_IHTMLDOCUMENT2_FRAMES                              DISPID_OMDOCUMENT+19
#define DISPID_IHTMLDOCUMENT2_EMBEDS                              DISPID_OMDOCUMENT+15
#define DISPID_IHTMLDOCUMENT2_PLUGINS                             DISPID_OMDOCUMENT+21
#define DISPID_IHTMLDOCUMENT2_ALINKCOLOR                          DISPID_OMDOCUMENT+22
#define DISPID_IHTMLDOCUMENT2_BGCOLOR                             DISPID_BACKCOLOR
#define DISPID_IHTMLDOCUMENT2_FGCOLOR                             DISPID_A_COLOR
#define DISPID_IHTMLDOCUMENT2_LINKCOLOR                           DISPID_OMDOCUMENT+24
#define DISPID_IHTMLDOCUMENT2_VLINKCOLOR                          DISPID_OMDOCUMENT+23
#define DISPID_IHTMLDOCUMENT2_REFERRER                            DISPID_OMDOCUMENT+27
#define DISPID_IHTMLDOCUMENT2_LOCATION                            DISPID_OMDOCUMENT+26
#define DISPID_IHTMLDOCUMENT2_LASTMODIFIED                        DISPID_OMDOCUMENT+28
#define DISPID_IHTMLDOCUMENT2_URL                                 DISPID_OMDOCUMENT+25
#define DISPID_IHTMLDOCUMENT2_DOMAIN                              DISPID_OMDOCUMENT+29
#define DISPID_IHTMLDOCUMENT2_COOKIE                              DISPID_OMDOCUMENT+30
#define DISPID_IHTMLDOCUMENT2_EXPANDO                             DISPID_OMDOCUMENT+31
#define DISPID_IHTMLDOCUMENT2_CHARSET                             DISPID_OMDOCUMENT+32
#define DISPID_IHTMLDOCUMENT2_DEFAULTCHARSET                      DISPID_OMDOCUMENT+33
#define DISPID_IHTMLDOCUMENT2_MIMETYPE                            DISPID_OMDOCUMENT+41
#define DISPID_IHTMLDOCUMENT2_FILESIZE                            DISPID_OMDOCUMENT+42
#define DISPID_IHTMLDOCUMENT2_FILECREATEDDATE                     DISPID_OMDOCUMENT+43
#define DISPID_IHTMLDOCUMENT2_FILEMODIFIEDDATE                    DISPID_OMDOCUMENT+44
#define DISPID_IHTMLDOCUMENT2_FILEUPDATEDDATE                     DISPID_OMDOCUMENT+45
#define DISPID_IHTMLDOCUMENT2_SECURITY                            DISPID_OMDOCUMENT+46
#define DISPID_IHTMLDOCUMENT2_PROTOCOL                            DISPID_OMDOCUMENT+47
#define DISPID_IHTMLDOCUMENT2_NAMEPROP                            DISPID_OMDOCUMENT+48
#define DISPID_IHTMLDOCUMENT2_WRITE                               DISPID_OMDOCUMENT+54
#define DISPID_IHTMLDOCUMENT2_WRITELN                             DISPID_OMDOCUMENT+55
#define DISPID_IHTMLDOCUMENT2_OPEN                                DISPID_OMDOCUMENT+56
#define DISPID_IHTMLDOCUMENT2_CLOSE                               DISPID_OMDOCUMENT+57
#define DISPID_IHTMLDOCUMENT2_CLEAR                               DISPID_OMDOCUMENT+58
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDSUPPORTED               DISPID_OMDOCUMENT+59
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDENABLED                 DISPID_OMDOCUMENT+60
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDSTATE                   DISPID_OMDOCUMENT+61
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDINDETERM                DISPID_OMDOCUMENT+62
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDTEXT                    DISPID_OMDOCUMENT+63
#define DISPID_IHTMLDOCUMENT2_QUERYCOMMANDVALUE                   DISPID_OMDOCUMENT+64
#define DISPID_IHTMLDOCUMENT2_EXECCOMMAND                         DISPID_OMDOCUMENT+65
#define DISPID_IHTMLDOCUMENT2_EXECCOMMANDSHOWHELP                 DISPID_OMDOCUMENT+66
#define DISPID_IHTMLDOCUMENT2_CREATEELEMENT                       DISPID_OMDOCUMENT+67
#define DISPID_IHTMLDOCUMENT2_ONHELP                              DISPID_EVPROP_ONHELP
#define DISPID_IHTMLDOCUMENT2_ONCLICK                             DISPID_EVPROP_ONCLICK
#define DISPID_IHTMLDOCUMENT2_ONDBLCLICK                          DISPID_EVPROP_ONDBLCLICK
#define DISPID_IHTMLDOCUMENT2_ONKEYUP                             DISPID_EVPROP_ONKEYUP
#define DISPID_IHTMLDOCUMENT2_ONKEYDOWN                           DISPID_EVPROP_ONKEYDOWN
#define DISPID_IHTMLDOCUMENT2_ONKEYPRESS                          DISPID_EVPROP_ONKEYPRESS
#define DISPID_IHTMLDOCUMENT2_ONMOUSEUP                           DISPID_EVPROP_ONMOUSEUP
#define DISPID_IHTMLDOCUMENT2_ONMOUSEDOWN                         DISPID_EVPROP_ONMOUSEDOWN
#define DISPID_IHTMLDOCUMENT2_ONMOUSEMOVE                         DISPID_EVPROP_ONMOUSEMOVE
#define DISPID_IHTMLDOCUMENT2_ONMOUSEOUT                          DISPID_EVPROP_ONMOUSEOUT
#define DISPID_IHTMLDOCUMENT2_ONMOUSEOVER                         DISPID_EVPROP_ONMOUSEOVER
#define DISPID_IHTMLDOCUMENT2_ONREADYSTATECHANGE                  DISPID_EVPROP_ONREADYSTATECHANGE
#define DISPID_IHTMLDOCUMENT2_ONAFTERUPDATE                       DISPID_EVPROP_ONAFTERUPDATE
#define DISPID_IHTMLDOCUMENT2_ONROWEXIT                           DISPID_EVPROP_ONROWEXIT
#define DISPID_IHTMLDOCUMENT2_ONROWENTER                          DISPID_EVPROP_ONROWENTER
#define DISPID_IHTMLDOCUMENT2_ONDRAGSTART                         DISPID_EVPROP_ONDRAGSTART
#define DISPID_IHTMLDOCUMENT2_ONSELECTSTART                       DISPID_EVPROP_ONSELECTSTART
#define DISPID_IHTMLDOCUMENT2_ELEMENTFROMPOINT                    DISPID_OMDOCUMENT+68
#define DISPID_IHTMLDOCUMENT2_PARENTWINDOW                        DISPID_OMDOCUMENT+34
#define DISPID_IHTMLDOCUMENT2_STYLESHEETS                         DISPID_OMDOCUMENT+69
#define DISPID_IHTMLDOCUMENT2_ONBEFOREUPDATE                      DISPID_EVPROP_ONBEFOREUPDATE
#define DISPID_IHTMLDOCUMENT2_ONERRORUPDATE                       DISPID_EVPROP_ONERRORUPDATE
#define DISPID_IHTMLDOCUMENT2_TOSTRING                            DISPID_OMDOCUMENT+70
#define DISPID_IHTMLDOCUMENT2_CREATESTYLESHEET                    DISPID_OMDOCUMENT+71

//	DISPIDs for event set HTMLDocumentEvents

#define DISPID_HTMLDOCUMENTEVENTS_ONHELP                          DISPID_EVMETH_ONHELP
#define DISPID_HTMLDOCUMENTEVENTS_ONCLICK                         DISPID_EVMETH_ONCLICK
#define DISPID_HTMLDOCUMENTEVENTS_ONDBLCLICK                      DISPID_EVMETH_ONDBLCLICK
#define DISPID_HTMLDOCUMENTEVENTS_ONKEYDOWN                       DISPID_EVMETH_ONKEYDOWN
#define DISPID_HTMLDOCUMENTEVENTS_ONKEYUP                         DISPID_EVMETH_ONKEYUP
#define DISPID_HTMLDOCUMENTEVENTS_ONKEYPRESS                      DISPID_EVMETH_ONKEYPRESS
#define DISPID_HTMLDOCUMENTEVENTS_ONMOUSEDOWN                     DISPID_EVMETH_ONMOUSEDOWN
#define DISPID_HTMLDOCUMENTEVENTS_ONMOUSEMOVE                     DISPID_EVMETH_ONMOUSEMOVE
#define DISPID_HTMLDOCUMENTEVENTS_ONMOUSEUP                       DISPID_EVMETH_ONMOUSEUP
#define DISPID_HTMLDOCUMENTEVENTS_ONMOUSEOUT                      DISPID_EVMETH_ONMOUSEOUT
#define DISPID_HTMLDOCUMENTEVENTS_ONMOUSEOVER                     DISPID_EVMETH_ONMOUSEOVER
#define DISPID_HTMLDOCUMENTEVENTS_ONREADYSTATECHANGE              DISPID_EVMETH_ONREADYSTATECHANGE
#define DISPID_HTMLDOCUMENTEVENTS_ONBEFOREUPDATE                  DISPID_EVMETH_ONBEFOREUPDATE
#define DISPID_HTMLDOCUMENTEVENTS_ONAFTERUPDATE                   DISPID_EVMETH_ONAFTERUPDATE
#define DISPID_HTMLDOCUMENTEVENTS_ONROWEXIT                       DISPID_EVMETH_ONROWEXIT
#define DISPID_HTMLDOCUMENTEVENTS_ONROWENTER                      DISPID_EVMETH_ONROWENTER
#define DISPID_HTMLDOCUMENTEVENTS_ONDRAGSTART                     DISPID_EVMETH_ONDRAGSTART
#define DISPID_HTMLDOCUMENTEVENTS_ONSELECTSTART                   DISPID_EVMETH_ONSELECTSTART
#define DISPID_HTMLDOCUMENTEVENTS_ONERRORUPDATE                   DISPID_EVMETH_ONERRORUPDATE

//	DISPIDs for interface IHTMLEmbedElement

#define DISPID_IHTMLEMBEDELEMENT_HIDDEN                           DISPID_A_HIDDEN
#define DISPID_IHTMLEMBEDELEMENT_PALETTE                          DISPID_OBJECT+4
#define DISPID_IHTMLEMBEDELEMENT_PLUGINSPAGE                      DISPID_OBJECT+5
#define DISPID_IHTMLEMBEDELEMENT_SRC                              DISPID_OBJECT+6
#define DISPID_IHTMLEMBEDELEMENT_UNITS                            DISPID_OBJECT+8
#define DISPID_IHTMLEMBEDELEMENT_NAME                             STDPROPID_XOBJ_NAME
#define DISPID_IHTMLEMBEDELEMENT_WIDTH                            STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLEMBEDELEMENT_HEIGHT                           STDPROPID_XOBJ_HEIGHT

//	DISPIDs for interface IHTMLAreasCollection

#define DISPID_IHTMLAREASCOLLECTION_LENGTH                        DISPID_COLLECTION
#define DISPID_IHTMLAREASCOLLECTION__NEWENUM                      DISPID_NEWENUM
#define DISPID_IHTMLAREASCOLLECTION_ITEM                          DISPID_VALUE
#define DISPID_IHTMLAREASCOLLECTION_TAGS                          DISPID_COLLECTION+2
#define DISPID_IHTMLAREASCOLLECTION_ADD                           DISPID_COLLECTION+3
#define DISPID_IHTMLAREASCOLLECTION_REMOVE                        DISPID_COLLECTION+4

//	DISPIDs for interface IHTMLMapElement

#define DISPID_IHTMLMAPELEMENT_AREAS                              DISPID_MAP+2
#define DISPID_IHTMLMAPELEMENT_NAME                               STDPROPID_XOBJ_NAME

//	DISPIDs for interface IHTMLAreaElement

#define DISPID_IHTMLAREAELEMENT_SHAPE                             DISPID_AREA+1
#define DISPID_IHTMLAREAELEMENT_COORDS                            DISPID_AREA+2
#define DISPID_IHTMLAREAELEMENT_HREF                              DISPID_VALUE
#define DISPID_IHTMLAREAELEMENT_TARGET                            DISPID_AREA+4
#define DISPID_IHTMLAREAELEMENT_ALT                               DISPID_AREA+5
#define DISPID_IHTMLAREAELEMENT_NOHREF                            DISPID_AREA+6
#define DISPID_IHTMLAREAELEMENT_HOST                              DISPID_AREA+7
#define DISPID_IHTMLAREAELEMENT_HOSTNAME                          DISPID_AREA+8
#define DISPID_IHTMLAREAELEMENT_PATHNAME                          DISPID_AREA+9
#define DISPID_IHTMLAREAELEMENT_PORT                              DISPID_AREA+10
#define DISPID_IHTMLAREAELEMENT_PROTOCOL                          DISPID_AREA+11
#define DISPID_IHTMLAREAELEMENT_SEARCH                            DISPID_AREA+12
#define DISPID_IHTMLAREAELEMENT_HASH                              DISPID_AREA+13
#define DISPID_IHTMLAREAELEMENT_ONBLUR                            DISPID_EVPROP_ONBLUR
#define DISPID_IHTMLAREAELEMENT_ONFOCUS                           DISPID_EVPROP_ONFOCUS
#define DISPID_IHTMLAREAELEMENT_TABINDEX                          STDPROPID_XOBJ_TABINDEX
#define DISPID_IHTMLAREAELEMENT_FOCUS                             DISPID_AREA+14
#define DISPID_IHTMLAREAELEMENT_BLUR                              DISPID_AREA+15

//	DISPIDs for event set HTMLAreaEvents

#define DISPID_HTMLAREAEVENTS_ONFOCUS                             DISPID_EVMETH_ONFOCUS
#define DISPID_HTMLAREAEVENTS_ONBLUR                              DISPID_EVMETH_ONBLUR

//	DISPIDs for interface IHTMLTableCaption

#define DISPID_IHTMLTABLECAPTION_ALIGN                            STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLTABLECAPTION_VALIGN                           DISPID_A_TABLEVALIGN

//	DISPIDs for interface IHTMLCommentElement

#define DISPID_IHTMLCOMMENTELEMENT_TEXT                           DISPID_COMMENTPDL+1
#define DISPID_IHTMLCOMMENTELEMENT_ATOMIC                         DISPID_COMMENTPDL+2

//	DISPIDs for interface IHTMLTable

#define DISPID_IHTMLTABLE_COLS                                    DISPID_TABLE+1
#define DISPID_IHTMLTABLE_BORDER                                  DISPID_TABLE+2
#define DISPID_IHTMLTABLE_FRAME                                   DISPID_TABLE+4
#define DISPID_IHTMLTABLE_RULES                                   DISPID_TABLE+3
#define DISPID_IHTMLTABLE_CELLSPACING                             DISPID_TABLE+5
#define DISPID_IHTMLTABLE_CELLPADDING                             DISPID_TABLE+6
#define DISPID_IHTMLTABLE_BACKGROUND                              DISPID_A_BACKGROUNDIMAGE
#define DISPID_IHTMLTABLE_BGCOLOR                                 DISPID_BACKCOLOR
#define DISPID_IHTMLTABLE_BORDERCOLOR                             DISPID_A_TABLEBORDERCOLOR
#define DISPID_IHTMLTABLE_BORDERCOLORLIGHT                        DISPID_A_TABLEBORDERCOLORLIGHT
#define DISPID_IHTMLTABLE_BORDERCOLORDARK                         DISPID_A_TABLEBORDERCOLORDARK
#define DISPID_IHTMLTABLE_ALIGN                                   STDPROPID_XOBJ_CONTROLALIGN
#define DISPID_IHTMLTABLE_REFRESH                                 DISPID_TABLE+15
#define DISPID_IHTMLTABLE_ROWS                                    DISPID_TABLE+16
#define DISPID_IHTMLTABLE_WIDTH                                   STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLTABLE_HEIGHT                                  STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLTABLE_DATAPAGESIZE                            DISPID_TABLE+17
#define DISPID_IHTMLTABLE_NEXTPAGE                                DISPID_TABLE+18
#define DISPID_IHTMLTABLE_PREVIOUSPAGE                            DISPID_TABLE+19
#define DISPID_IHTMLTABLE_THEAD                                   DISPID_TABLE+20
#define DISPID_IHTMLTABLE_TFOOT                                   DISPID_TABLE+21
#define DISPID_IHTMLTABLE_TBODIES                                 DISPID_TABLE+24
#define DISPID_IHTMLTABLE_CAPTION                                 DISPID_TABLE+25
#define DISPID_IHTMLTABLE_CREATETHEAD                             DISPID_TABLE+26
#define DISPID_IHTMLTABLE_DELETETHEAD                             DISPID_TABLE+27
#define DISPID_IHTMLTABLE_CREATETFOOT                             DISPID_TABLE+28
#define DISPID_IHTMLTABLE_DELETETFOOT                             DISPID_TABLE+29
#define DISPID_IHTMLTABLE_CREATECAPTION                           DISPID_TABLE+30
#define DISPID_IHTMLTABLE_DELETECAPTION                           DISPID_TABLE+31
#define DISPID_IHTMLTABLE_INSERTROW                               DISPID_TABLE+32
#define DISPID_IHTMLTABLE_DELETEROW                               DISPID_TABLE+33
#define DISPID_IHTMLTABLE_READYSTATE                              DISPID_TABLE+34
#define DISPID_IHTMLTABLE_ONREADYSTATECHANGE                      DISPID_EVPROP_ONREADYSTATECHANGE

//	DISPIDs for interface IHTMLTableCol

#define DISPID_IHTMLTABLECOL_SPAN                                 DISPID_TABLECOL+1
#define DISPID_IHTMLTABLECOL_WIDTH                                STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLTABLECOL_ALIGN                                STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLTABLECOL_VALIGN                               DISPID_A_TABLEVALIGN

//	DISPIDs for interface IHTMLTableSection

#define DISPID_IHTMLTABLESECTION_ALIGN                            STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLTABLESECTION_VALIGN                           DISPID_A_TABLEVALIGN
#define DISPID_IHTMLTABLESECTION_BGCOLOR                          DISPID_BACKCOLOR
#define DISPID_IHTMLTABLESECTION_ROWS                             DISPID_TABLESECTION
#define DISPID_IHTMLTABLESECTION_INSERTROW                        DISPID_TABLESECTION+1
#define DISPID_IHTMLTABLESECTION_DELETEROW                        DISPID_TABLESECTION+2

//	DISPIDs for interface IHTMLTableRow

#define DISPID_IHTMLTABLEROW_ALIGN                                STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLTABLEROW_VALIGN                               DISPID_A_TABLEVALIGN
#define DISPID_IHTMLTABLEROW_BGCOLOR                              DISPID_BACKCOLOR
#define DISPID_IHTMLTABLEROW_BORDERCOLOR                          DISPID_A_TABLEBORDERCOLOR
#define DISPID_IHTMLTABLEROW_BORDERCOLORLIGHT                     DISPID_A_TABLEBORDERCOLORLIGHT
#define DISPID_IHTMLTABLEROW_BORDERCOLORDARK                      DISPID_A_TABLEBORDERCOLORDARK
#define DISPID_IHTMLTABLEROW_ROWINDEX                             DISPID_TABLEROW
#define DISPID_IHTMLTABLEROW_SECTIONROWINDEX                      DISPID_TABLEROW+1
#define DISPID_IHTMLTABLEROW_CELLS                                DISPID_TABLEROW+2
#define DISPID_IHTMLTABLEROW_INSERTCELL                           DISPID_TABLEROW+3
#define DISPID_IHTMLTABLEROW_DELETECELL                           DISPID_TABLEROW+4

//	DISPIDs for interface IHTMLTableRowMetrics

#define DISPID_IHTMLTABLEROWMETRICS_CLIENTHEIGHT                  DISPID_TABLEROW+5
#define DISPID_IHTMLTABLEROWMETRICS_CLIENTWIDTH                   DISPID_TABLEROW+6
#define DISPID_IHTMLTABLEROWMETRICS_CLIENTTOP                     DISPID_TABLEROW+7
#define DISPID_IHTMLTABLEROWMETRICS_CLIENTLEFT                    DISPID_TABLEROW+8

//	DISPIDs for interface IHTMLTableCell

#define DISPID_IHTMLTABLECELL_ROWSPAN                             DISPID_TABLECELL+1
#define DISPID_IHTMLTABLECELL_COLSPAN                             DISPID_TABLECELL+2
#define DISPID_IHTMLTABLECELL_ALIGN                               STDPROPID_XOBJ_BLOCKALIGN
#define DISPID_IHTMLTABLECELL_VALIGN                              DISPID_A_TABLEVALIGN
#define DISPID_IHTMLTABLECELL_BGCOLOR                             DISPID_BACKCOLOR
#define DISPID_IHTMLTABLECELL_NOWRAP                              DISPID_A_NOWRAP
#define DISPID_IHTMLTABLECELL_BACKGROUND                          DISPID_A_BACKGROUNDIMAGE
#define DISPID_IHTMLTABLECELL_BORDERCOLOR                         DISPID_A_TABLEBORDERCOLOR
#define DISPID_IHTMLTABLECELL_BORDERCOLORLIGHT                    DISPID_A_TABLEBORDERCOLORLIGHT
#define DISPID_IHTMLTABLECELL_BORDERCOLORDARK                     DISPID_A_TABLEBORDERCOLORDARK
#define DISPID_IHTMLTABLECELL_WIDTH                               STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLTABLECELL_HEIGHT                              STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLTABLECELL_CELLINDEX                           DISPID_TABLECELL+3

//	DISPIDs for event set HTMLTableEvents

#define DISPID_HTMLTABLEEVENTS_ONREADYSTATECHANGE                 DISPID_EVMETH_ONREADYSTATECHANGE

//	DISPIDs for interface IHTMLScriptElement

#define DISPID_IHTMLSCRIPTELEMENT_SRC                             DISPID_SCRIPT+1
#define DISPID_IHTMLSCRIPTELEMENT_HTMLFOR                         DISPID_SCRIPT+4
#define DISPID_IHTMLSCRIPTELEMENT_EVENT                           DISPID_SCRIPT+5
#define DISPID_IHTMLSCRIPTELEMENT_TEXT                            DISPID_SCRIPT+6
#define DISPID_IHTMLSCRIPTELEMENT_DEFER                           DISPID_SCRIPT+7
#define DISPID_IHTMLSCRIPTELEMENT_READYSTATE                      DISPID_SCRIPT+8
#define DISPID_IHTMLSCRIPTELEMENT_ONERROR                         DISPID_EVPROP_ONERROR
#define DISPID_IHTMLSCRIPTELEMENT_TYPE                            DISPID_SCRIPT+9

//	DISPIDs for event set HTMLScriptEvents

#define DISPID_HTMLSCRIPTEVENTS_ONREADYSTATECHANGE                DISPID_EVMETH_ONREADYSTATECHANGE
#define DISPID_HTMLSCRIPTEVENTS_ONERROR                           DISPID_EVMETH_ONERROR

//	DISPIDs for interface IHTMLObjectElement

#define DISPID_IHTMLOBJECTELEMENT_OBJECT                          DISPID_OBJECT+1
#define DISPID_IHTMLOBJECTELEMENT_CLASSID                         DISPID_OBJECT+2
#define DISPID_IHTMLOBJECTELEMENT_DATA                            DISPID_OBJECT+3
#define DISPID_IHTMLOBJECTELEMENT_RECORDSET                       DISPID_OBJECT+5
#define DISPID_IHTMLOBJECTELEMENT_ALIGN                           STDPROPID_XOBJ_CONTROLALIGN
#define DISPID_IHTMLOBJECTELEMENT_NAME                            STDPROPID_XOBJ_NAME
#define DISPID_IHTMLOBJECTELEMENT_CODEBASE                        DISPID_OBJECT+6
#define DISPID_IHTMLOBJECTELEMENT_CODETYPE                        DISPID_OBJECT+7
#define DISPID_IHTMLOBJECTELEMENT_CODE                            DISPID_OBJECT+8
#define DISPID_IHTMLOBJECTELEMENT_BASEHREF                        STDPROPID_XOBJ_BASEHREF
#define DISPID_IHTMLOBJECTELEMENT_TYPE                            DISPID_OBJECT+9
#define DISPID_IHTMLOBJECTELEMENT_FORM                            DISPID_SITE+4
#define DISPID_IHTMLOBJECTELEMENT_WIDTH                           STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLOBJECTELEMENT_HEIGHT                          STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLOBJECTELEMENT_READYSTATE                      DISPID_OBJECT+10
#define DISPID_IHTMLOBJECTELEMENT_ONREADYSTATECHANGE              DISPID_EVPROP_ONREADYSTATECHANGE
#define DISPID_IHTMLOBJECTELEMENT_ONERROR                         DISPID_EVPROP_ONERROR
#define DISPID_IHTMLOBJECTELEMENT_ALTHTML                         DISPID_OBJECT+11
#define DISPID_IHTMLOBJECTELEMENT_VSPACE                          DISPID_OBJECT+12
#define DISPID_IHTMLOBJECTELEMENT_HSPACE                          DISPID_OBJECT+13

//	DISPIDs for event set HTMLObjectElementEvents

#define DISPID_HTMLOBJECTELEMENTEVENTS_ONBEFOREUPDATE             DISPID_EVMETH_ONBEFOREUPDATE
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONAFTERUPDATE              DISPID_EVMETH_ONAFTERUPDATE
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONERRORUPDATE              DISPID_EVMETH_ONERRORUPDATE
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONROWEXIT                  DISPID_EVMETH_ONROWEXIT
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONROWENTER                 DISPID_EVMETH_ONROWENTER
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONDATASETCHANGED           DISPID_EVMETH_ONDATASETCHANGED
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONDATAAVAILABLE            DISPID_EVMETH_ONDATAAVAILABLE
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONDATASETCOMPLETE          DISPID_EVMETH_ONDATASETCOMPLETE
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONREADYSTATECHANGE         DISPID_XOBJ_BASE+18
#define DISPID_HTMLOBJECTELEMENTEVENTS_ONERROR                    DISPID_XOBJ_BASE+19

//	DISPIDs for interface IHTMLFrameBase

#define DISPID_IHTMLFRAMEBASE_SRC                                 DISPID_FRAMESITE+0
#define DISPID_IHTMLFRAMEBASE_NAME                                STDPROPID_XOBJ_NAME
#define DISPID_IHTMLFRAMEBASE_BORDER                              DISPID_FRAMESITE+2
#define DISPID_IHTMLFRAMEBASE_FRAMEBORDER                         DISPID_FRAMESITE+3
#define DISPID_IHTMLFRAMEBASE_FRAMESPACING                        DISPID_FRAMESITE+4
#define DISPID_IHTMLFRAMEBASE_MARGINWIDTH                         DISPID_FRAMESITE+5
#define DISPID_IHTMLFRAMEBASE_MARGINHEIGHT                        DISPID_FRAMESITE+6
#define DISPID_IHTMLFRAMEBASE_NORESIZE                            DISPID_FRAMESITE+7
#define DISPID_IHTMLFRAMEBASE_SCROLLING                           DISPID_FRAMESITE+8

//	DISPIDs for interface IHTMLFrameElement

#define DISPID_IHTMLFRAMEELEMENT_BORDERCOLOR                      DISPID_FRAME+1

//	DISPIDs for interface IHTMLIFrameElement

#define DISPID_IHTMLIFRAMEELEMENT_HEIGHT                          STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLIFRAMEELEMENT_WIDTH                           STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLIFRAMEELEMENT_VSPACE                          DISPID_IFRAME+1
#define DISPID_IHTMLIFRAMEELEMENT_HSPACE                          DISPID_IFRAME+2
#define DISPID_IHTMLIFRAMEELEMENT_ALIGN                           STDPROPID_XOBJ_CONTROLALIGN

//	DISPIDs for interface IHTMLDivPosition

#define DISPID_IHTMLDIVPOSITION_ALIGN                             STDPROPID_XOBJ_CONTROLALIGN

//	DISPIDs for interface IHTMLFieldSetElement

#define DISPID_IHTMLFIELDSETELEMENT_ALIGN                         STDPROPID_XOBJ_CONTROLALIGN

//	DISPIDs for interface IHTMLLegendElement

#define DISPID_IHTMLLEGENDELEMENT_ALIGN                           STDPROPID_XOBJ_CONTROLALIGN

//	DISPIDs for interface IHTMLSpanFlow

#define DISPID_IHTMLSPANFLOW_ALIGN                                STDPROPID_XOBJ_CONTROLALIGN

//	DISPIDs for interface IHTMLFrameSetElement

#define DISPID_IHTMLFRAMESETELEMENT_ROWS                          DISPID_FRAMESET
#define DISPID_IHTMLFRAMESETELEMENT_COLS                          DISPID_FRAMESET+1
#define DISPID_IHTMLFRAMESETELEMENT_BORDER                        DISPID_FRAMESET+2
#define DISPID_IHTMLFRAMESETELEMENT_BORDERCOLOR                   DISPID_FRAMESET+3
#define DISPID_IHTMLFRAMESETELEMENT_FRAMEBORDER                   DISPID_FRAMESET+4
#define DISPID_IHTMLFRAMESETELEMENT_FRAMESPACING                  DISPID_FRAMESET+5
#define DISPID_IHTMLFRAMESETELEMENT_NAME                          STDPROPID_XOBJ_NAME
#define DISPID_IHTMLFRAMESETELEMENT_ONLOAD                        DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLFRAMESETELEMENT_ONUNLOAD                      DISPID_EVPROP_ONUNLOAD
#define DISPID_IHTMLFRAMESETELEMENT_ONBEFOREUNLOAD                DISPID_EVPROP_ONBEFOREUNLOAD

//	DISPIDs for interface IHTMLBGsound

#define DISPID_IHTMLBGSOUND_SRC                                   DISPID_BGSOUND+1
#define DISPID_IHTMLBGSOUND_LOOP                                  DISPID_BGSOUND+2
#define DISPID_IHTMLBGSOUND_VOLUME                                DISPID_BGSOUND+3
#define DISPID_IHTMLBGSOUND_BALANCE                               DISPID_BGSOUND+4

//	DISPIDs for interface IHTMLFontNamesCollection

#define DISPID_IHTMLFONTNAMESCOLLECTION_LENGTH                    DISPID_OPTIONS_COL+1
#define DISPID_IHTMLFONTNAMESCOLLECTION__NEWENUM                  DISPID_NEWENUM
#define DISPID_IHTMLFONTNAMESCOLLECTION_ITEM                      DISPID_VALUE

//	DISPIDs for interface IHTMLFontSizesCollection

#define DISPID_IHTMLFONTSIZESCOLLECTION_LENGTH                    DISPID_OPTIONS_COL+2
#define DISPID_IHTMLFONTSIZESCOLLECTION__NEWENUM                  DISPID_NEWENUM
#define DISPID_IHTMLFONTSIZESCOLLECTION_FORFONT                   DISPID_OPTIONS_COL+3
#define DISPID_IHTMLFONTSIZESCOLLECTION_ITEM                      DISPID_VALUE

//	DISPIDs for interface IHTMLOptionsHolder

#define DISPID_IHTMLOPTIONSHOLDER_DOCUMENT                        DISPID_OPTIONS_COL+3
#define DISPID_IHTMLOPTIONSHOLDER_FONTS                           DISPID_OPTIONS_COL+4
#define DISPID_IHTMLOPTIONSHOLDER_EXECARG                         DISPID_OPTIONS_COL+5
#define DISPID_IHTMLOPTIONSHOLDER_ERRORLINE                       DISPID_OPTIONS_COL+6
#define DISPID_IHTMLOPTIONSHOLDER_ERRORCHARACTER                  DISPID_OPTIONS_COL+7
#define DISPID_IHTMLOPTIONSHOLDER_ERRORCODE                       DISPID_OPTIONS_COL+8
#define DISPID_IHTMLOPTIONSHOLDER_ERRORMESSAGE                    DISPID_OPTIONS_COL+9
#define DISPID_IHTMLOPTIONSHOLDER_ERRORDEBUG                      DISPID_OPTIONS_COL+10
#define DISPID_IHTMLOPTIONSHOLDER_UNSECUREDWINDOWOFDOCUMENT       DISPID_OPTIONS_COL+11
#define DISPID_IHTMLOPTIONSHOLDER_FINDTEXT                        DISPID_OPTIONS_COL+12
#define DISPID_IHTMLOPTIONSHOLDER_ANYTHINGAFTERFRAMESET           DISPID_OPTIONS_COL+13
#define DISPID_IHTMLOPTIONSHOLDER_SIZES                           DISPID_OPTIONS_COL+14
#define DISPID_IHTMLOPTIONSHOLDER_OPENFILEDLG                     DISPID_OPTIONS_COL+15
#define DISPID_IHTMLOPTIONSHOLDER_SAVEFILEDLG                     DISPID_OPTIONS_COL+16
#define DISPID_IHTMLOPTIONSHOLDER_CHOOSECOLORDLG                  DISPID_OPTIONS_COL+17
#define DISPID_IHTMLOPTIONSHOLDER_SHOWSECURITYINFO                DISPID_OPTIONS_COL+18
#define DISPID_IHTMLOPTIONSHOLDER_ISAPARTMENTMODEL                DISPID_OPTIONS_COL+19
#define DISPID_IHTMLOPTIONSHOLDER_GETCHARSET                      DISPID_OPTIONS_COL+20

//	DISPIDs for interface IHTMLStyleElement

#define DISPID_IHTMLSTYLEELEMENT_TYPE                             DISPID_STYLEELEMENT+2
#define DISPID_IHTMLSTYLEELEMENT_READYSTATE                       DISPID_STYLEELEMENT+3
#define DISPID_IHTMLSTYLEELEMENT_ONREADYSTATECHANGE               DISPID_EVPROP_ONREADYSTATECHANGE
#define DISPID_IHTMLSTYLEELEMENT_ONLOAD                           DISPID_EVPROP_ONLOAD
#define DISPID_IHTMLSTYLEELEMENT_ONERROR                          DISPID_EVPROP_ONERROR
#define DISPID_IHTMLSTYLEELEMENT_STYLESHEET                       DISPID_STYLEELEMENT+4
#define DISPID_IHTMLSTYLEELEMENT_DISABLED                         DISPID_STYLEELEMENT+5
#define DISPID_IHTMLSTYLEELEMENT_MEDIA                            DISPID_STYLEELEMENT+6

//	DISPIDs for event set HTMLStyleElementEvents

#define DISPID_HTMLSTYLEELEMENTEVENTS_ONREADYSTATECHANGE          DISPID_EVMETH_ONREADYSTATECHANGE
#define DISPID_HTMLSTYLEELEMENTEVENTS_ONLOAD                      DISPID_EVMETH_ONLOAD
#define DISPID_HTMLSTYLEELEMENTEVENTS_ONERROR                     DISPID_EVMETH_ONERROR

//	DISPIDs for interface IHTMLStyleFontFace

#define DISPID_IHTMLSTYLEFONTFACE_FONTSRC                         DISPID_A_FONTFACESRC

//	DISPIDs for interface IHTMLDialog

#define DISPID_IHTMLDIALOG_DIALOGTOP                              STDPROPID_XOBJ_TOP
#define DISPID_IHTMLDIALOG_DIALOGLEFT                             STDPROPID_XOBJ_LEFT
#define DISPID_IHTMLDIALOG_DIALOGWIDTH                            STDPROPID_XOBJ_WIDTH
#define DISPID_IHTMLDIALOG_DIALOGHEIGHT                           STDPROPID_XOBJ_HEIGHT
#define DISPID_IHTMLDIALOG_DIALOGARGUMENTS                        DISPID_HTMLDLG+0
#define DISPID_IHTMLDIALOG_MENUARGUMENTS                          DISPID_HTMLDLG+13
#define DISPID_IHTMLDIALOG_RETURNVALUE                            DISPID_HTMLDLG+1
#define DISPID_IHTMLDIALOG_CLOSE                                  DISPID_HTMLDLG+11
#define DISPID_IHTMLDIALOG_TOSTRING                               DISPID_HTMLDLG+12


#endif // __MSHTMDID_H__
