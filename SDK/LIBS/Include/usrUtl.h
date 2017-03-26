#ifndef _USRUTLH
#define	_USRUTLH
/********************************************************************************************/
/* CONFIDENTIAL AND PROPRIETARY:                                                            */
/*      Copyright 2000, Sega of America.  All rights reserved.                              */
/*      This sample source code is provided for demonstration purposes only.                */
/*      Use and distribution of Sega proprietary material is governed by                    */
/*      developer licensing agreement.                                                      */
/********************************************************************************************/
//
//
//	Title:		usrUtl.h
//	Author:		David J. Rudolph
//	Date:		1/28/2000
//	Purpose:	Utils to fetch ISP info. back from FlashRAM.
//
//

#include <sg_xpt.h>

// Destination output format
// additional support for other stacks could be added
#define		UU_PWEB			1
#define		UU_ACCESS		2
#define		UU_ANY			3
#define		UU_NONE			0

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

//Sint8	UUInitISPInfo(Uint8	dstFormat);

Uint8 UUInitISPInfo(Uint8 stackusing);
//char	UUISPAreaUsed(void);
//
//	Boolean Information
//
void	UUSetPW(Uint8 pwOnFlag);
Uint8	UUGetPW(void);
Uint8   UUGetPWVer(void);
Sint8	UUGetDialAreaCode(void);
Uint16	UUGetConnectFlags(void);

//
//	Modem Information
//
Sint8	*UUGetModemInit(void);

//
//	Dialing Information
//
Uint8	*UUGetPrimaryNumber(void);
Uint8	*UUGetSecondaryNumber(void);
Sint8	*UUGetAreaCode(void);
Sint8	*UUGetOutsideLine(void);
Sint8	*UUGetLongDst(void);
Sint8	*UUGetCallWaiting(void);

//
//	User Information
//
Uint8	*UUGetLoginID(void);
Uint8	*UUGetPassword(void);
Sint8	*UUGetRealName(void);

//
//	DNS Services
//
unsigned long	UUGetPrimaryDNS(void);
unsigned long	UUGetSecondaryDNS(void);

//
//	Mail Services
//
Uint8	*UUGetMailAddress(void);
Uint8	*UUGetMailServer(void);

//
//	Point of Presence Services
//
Uint8	*UUGetPopServer(void);
Uint8	*UUGetPopId(void);
Uint8	*UUGetPopPasswd(void);

//
//	Proxy Services
//
Uint8	*UUGetProxyServer(void);
Uint16	UUGetProxyPortNum(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif