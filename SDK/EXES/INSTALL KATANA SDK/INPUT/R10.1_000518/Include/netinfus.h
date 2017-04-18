
/*
 *  Network Library
 *  Copyright (c) 1999 SEGA
 *
 *  Library : Network Utility Library
 *  File    : ntinfus.h
 *  Date    : 1999.12.14
 *  Version : 1.00
 *
 *  $Log: netinfus.h,v $
 *  Revision 1.3  2000/01/10 07:29:22  taborm
 *  Added check for Planet Web signature
 *
 *  Revision 1.2  2000/01/09 08:11:45  taborm
 *  Fixed incorrect length of parental control field
 *
 *
 */

#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

/*
 * U.S. flash area structure
 */

#define STRING_BUFFER_SIZE              32
#define PCTRL_STRING_BUFFER_SIZE        42
 
typedef struct NetInfUS_ {
        Uint8   signature[10];          // signature
        Uint8   version;                        // current version of this userinfo
        Sint8   dialArea;                       // dial area code always
        Sint8   outLine[STRING_BUFFER_SIZE];    // outside line
        Sint8   callWait[STRING_BUFFER_SIZE];   // disable call waitin
        Sint8   realName[STRING_BUFFER_SIZE];   // used for mail
        Sint8   pcntrl[PCTRL_STRING_BUFFER_SIZE]; // parental control login name
        Sint8   modemInit[STRING_BUFFER_SIZE];  // init the modem with this string
        Sint8   areaCode[STRING_BUFFER_SIZE];   // local area code
        Sint8   longDst[STRING_BUFFER_SIZE];    // long distance (1, and/or credit card)
        Sint8   useProxy;                       // TRUE if we should do HTTP Proxy stuff
        Sint8   mailHdr;                        // show mail headers when retrieving mail
        Sint8   titlebar;                       // show titlebar
        Sint8   toolbar;                        // show tool bar
        Sint8   style;                          // browser theme
        Sint8   qwertykeyb;                     // qwerty/rectangular keyboard
        Sint8   sticky;                         // sticky keyboard
        Sint8   quote;                          // quote orig msg in replys
        Sint8   sndEffects;                     // sound effects
        Sint8   japanese;                       // japanese translation
        Sint8   showTime;                       // show time on screen
        Sint8   timezone;                       // sync time to gmt
        Sint8   daylightSavings;        // are we in daylight savings?
        Sint8   hideKeyb;                       // always hide the keyboard
        Sint8   ssvroff;                        // don't show screen saver
        Sint8   showmodem;                      // modem dialing box?
        Sint8   ccself;                         // Carbon Copy to Self?
        Sint8   anchorDisplay;          // Style of anchors
        Sint8   urlbar;                         // sometimes OFF for some products
} NetInfUS;

/* prototypes */
Sint32 ntInfUSGetNetInfUS(NetInfUS *inf);
Sint32 ntInfUSGetPhoneNumber(char *num1, char *num2, char *num3);

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
