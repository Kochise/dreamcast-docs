// Copyright 1986 - 1998 Microsoft Corporation.  All Rights Reserved.

#define  CDALREADYUSED   7100
#define  CDBADFILE       7200
#define  CDCONFIRMINFO   7300
#define  CDGETNAME       7400
#define  CDGETNAMEORG    7500
#define  CDGETORG        7600
#define  CDBADNAME       7700
#define  CDBADORG        7800

extern int   FAR PASCAL FInitSystem1(int did, LPSTR sz, int fNet);
extern int   FAR PASCAL FInitSystem3(int did, LPSTR sz, int fAlways);
extern int   FAR PASCAL FCloseSystem(LPSTR szSect, LPSTR szKey, LPSTR szDst,
				int wResType, int wResId);


extern int   FAR PASCAL InitSystemRead(int did, LPSTR sz, int fNet);
extern int   FAR PASCAL InitSystemWrite(int did, LPSTR sz, int fAlways);
extern void  FAR PASCAL CloseSystem(LPSTR szSect, LPSTR szKey, LPSTR szDst,
				int wResType, int wResId);

extern int   FAR PASCAL InitSystem(int did, LPSTR sz, int fNet);
extern int   FAR PASCAL InitSystemDlgs(int fNet);
extern void  FAR PASCAL BadNameOrg(int dlg);
extern int   FAR PASCAL NameOrgOkay(int dlg, LPSTR szName, LPSTR szOrg);
