/* fmi.h */
/*
 * (C) Copyright Data Connection Limited 1989-1992.
 * (C) Copyright Microsoft Corporation 1991.
 * All Rights Reserved.
 */

#ifndef FMIH_INCLUDED
#define FMIH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifdef WIN32_SUPPORT
  #pragma pack(1)
#endif

/*****************************************************************************/
/* The following type definitions are in os2def.h so are not needed in OS/2  */
/*****************************************************************************/
#if (defined(DOS_SUPPORT) || defined(MSWIN_SUPPORT))
#define CHAR          char      /* ch  */
typedef unsigned char UCHAR;    /* uch */
typedef unsigned short USHORT;  /* us  */
typedef unsigned long ULONG;    /* ul  */
#endif

/*****************************************************************************/
/* Type definitions for message fields                                       */
/*****************************************************************************/
typedef signed short         INTEGER;

/*****************************************************************************/
/* Macro to convert integer fields other than STARTD and ENDD, SRCI          */
/* and DESTI to In-line format                                               */
/*****************************************************************************/
#ifndef WIN32_SUPPORT
#define DOFLIP(X) ((INTEGER)((((X) & 0xff) << 8) | (((X) >> 8) & 0xff)))
#else
#ifndef ROTL
 #ifndef _CRTAPI1
  unsigned int _rotl(unsigned int, int);
 #else
  unsigned int _CRTAPI1 _rotl(unsigned int, int);
 #endif
  #define ROTL
#endif
#pragma intrinsic(_rotl)
#define DOFLIP(X)   ((INTEGER)_rotl(((unsigned short)(X))*(unsigned long)0x00010001, 8))
#endif
#define DONTFLIP(X) (X)


#ifdef NON_INTEL_BYTE_ORDER
 #define PFLIPI(X)      DONTFLIP(X)
 #define PANTIFLIPI(X)  DOFLIP(X)
#else
 #define PFLIPI(X)      DOFLIP(X)
 #define PANTIFLIPI(X)  DONTFLIP(X)
#endif


/*****************************************************************************/
/* Element offset and length definitions                                     */
/*****************************************************************************/

#define SBCBELT1 1
#define SBCBELT3 13
#define SNANBEDA 268     /* LENGTH OF BUFFER ELEMENT */

/*****************************************************************************/
/* MESSAGE TYPE DECLARATIONS - ELEMENT OPTIONS                               */
/*****************************************************************************/
     typedef
#define RHASENSE     0
#define DATAONLY     1
     signed char ELTDATAT;

     typedef CHAR     SNCHARRU[SNANBEDA];        /* LENGTH OF ELT */

/*****************************************************************************/
/* MAIN DEFINITION OF MESSAGE ELEMENT                                        */
/*****************************************************************************/

/**STRUCT+********************************************************************/
/* Structure: BUFELT                                                         */
/*                                                                           */
/* Description: Main definition of SNAPS Buffer Element                      */
/*****************************************************************************/

#ifdef WIN32_SUPPORT
 #define PTRBFELT struct bufelt *
#else
 #define PTRBFELT struct bufelt far *
#endif

     typedef struct bufelt{
                     PTRBFELT elteptr;   /* Pointer to next element in buffer*/
                     INTEGER  startd;    /* Offset (from 1) of start of data */
                     INTEGER  endd;      /* Offset (from 1) of last data byte*/
                     CHAR     trpad;
                     /*ELTDATAT*/union {
                       /*RHASENSE*/struct {unsigned char rhpad[8];
                                     signed long BBUFF0V;
                                     INTEGER  BBUFF0W;
                                     INTEGER  BBUFF0X;}BBUFF0T;
                       /*DATAONLY*/struct {SNCHARRU BBUFF0Z;
                                                      }BBUFF0Y;
                   }BBUFF0S;}
#define rh       BBUFF0S.BBUFF0T.BBUFF0V /* The RH bytes themselves          */
#define sense1   BBUFF0S.BBUFF0T.BBUFF0W /* Sense data 1 in negative response*/
#define sense2   BBUFF0S.BBUFF0T.BBUFF0X /* Sense data 2 in negative response*/
#define dataru   BBUFF0S.BBUFF0Y.BBUFF0Z /* The data bytes themselves        */
#define lccpad   BBUFF0S.BBUFF0Y.BBUFF1A /* Pad                              */
                   BUFELT;


/*****************************************************************************/
/* OPEN MESSAGE TYPE DECLARATIONS                                            */
/*****************************************************************************/

     typedef struct tpophdr{                          /* OPEN MESSAGE HEADER */
                      CHAR     openqual;
#define REQU     1
#define RSPOK    2
#define RSPERR   3
#define CONFOK   4
#define CONFERR  5
                      CHAR     opentype;
#define SSCPSEC  1
#define LUSEC    2
#define SBPUSEC  3
                      CHAR     appltype;     /* INTERFACE ID - X'02' FOR FMI */
                      CHAR     opluno;              /* INTERFACE USER NUMBER */
                      INTEGER  opresid;             /* INTERFACE USER ID     */
                      union {
                        struct {INTEGER  B03;
                                INTEGER  B04;
                                CHAR     B05;
                                CHAR     B06;}B02;
                        struct {INTEGER  B08;
                                INTEGER  B09;}B07;
                    }B01;}
#define icreditr B01.B02.B03
#define icredits B01.B02.B04
#define opninfo1 B01.B02.B05
#define opnpad1  B01.B02.B06
#define operr1   B01.B07.B08
#define operr2   B01.B07.B09
                    TPOPHDR;

/*****************************************************************************/
/* Open (SSCP) opnpad1 values                                                */
/*****************************************************************************/

#define OPEN_TEST       0               /* DON'T FORCE A CONNECTION ACTIVE   */
#define OPEN_FORCE      1               /* FORCE A CONNECTION ACTIVE         */

/*****************************************************************************/
/* Constants for operr2 field in Open(SSCP) Error Responses                  */
/*****************************************************************************/

#define CSRENOSR 0                      /* NO SERVERS FOUND                  */
#define CSRESERV 1                      /* SERVICE NOT PRESENT AT LOCALITY   */
#define CSRECNFG 2                      /* CONFIGURATION MISMATCH            */
#define CSRECBSH 3                      /* CONTROL BLOCK/RESOURCE SHORTAGE   */
#define CSREFORM 4                      /* FORMAT/PROTOCOL ERROR             */

/*****************************************************************************/
/* LINK TYPE DEFINITIONS FOR OPEN (SSCP) RESPONSE IN DATARU[38]              */
/*****************************************************************************/

#define CESLINK          3              /* SDLC LINK                         */
#define CESX25           4              /* X.25 LINK                         */
#define CESDFT          10              /* DFT LINK                          */
#define CESTR           11              /* TOKEN RING LINK                   */
#define CESTCPIP        30              /* TCP/IP LINK                       */
#define CESRELAY        31              /* FRAME RELAY LINK                  */
#define CESCHANL        32              /* CHANNEL LINK                      */
#define CESISDN         33              /* ISDN LINK                         */
#define CESETHER        34              /* ETHERNET 802.2 LINK               */

/*****************************************************************************/
/* BIND Table Index Values for the Open PLU response (in element)            */
/*****************************************************************************/

#define BIND_TABLE_INDEX_PRT    1
#define BIND_TABLE_INDEX_CRT    2

/*****************************************************************************/
/* CLOSE MESSAGE TYPE DECLARATIONS                                           */
/*****************************************************************************/

     typedef struct tpclhdr{                         /* CLOSE MESSAGE HEADER */
                      CHAR     closqual;    /* Same values as openqual       */
                      CHAR     clstype;     /* Same values as opentype       */
                      CHAR     clsctl;      /* For Close(PLU) only           */
#define CLNORMAL 1
#define CLBIND   2
#define CLCFAERR 3
#define CLPUINAC 4
#define CLLUINAC 5
#define CLLNKERR 6
#define CLBFSHRT 7
#define CLRCVCHK 8
#define CLSLUTRM 9
                      CHAR     clspad1;
                      INTEGER  clspad2;
                      INTEGER  clserr1;
                      INTEGER  clserr2;
                    }TPCLHDR;

/*****************************************************************************/
/* STATUS-ACKNOWLEDGE MESSAGE TYPE DECLARATION                               */
/*****************************************************************************/

     typedef struct tpstahdr{                   /* STATUS ACK MESSAGE HEADER */
                      CHAR     akstat;
#define ACK      1
                      CHAR     akqual;
#define ACKPOS   2
#define ACKNEG1  3
#define ACKNEG2  4
                      INTEGER  akmsgkey;
                      union {
                              INTEGER XXXXX01;
                              struct {
                                 CHAR     XXXXX02;
                                 CHAR     XXXXX03;
                                     } XXXXX04;
                            } XXXXX05;
                      INTEGER  aknumb1;
                      INTEGER  aknumb2;
                      INTEGER  akseqno;

#define akmsgtim XXXXX05.XXXXX01
#define akflags1 XXXXX05.XXXXX04.XXXXX02    /* Same values as fhflags1 below */
                                            /* Reserved for ACKNEG2          */
#define akflags2 XXXXX05.XXXXX04.XXXXX03    /* Same values as fhflags2 below */
                                            /* Crit/Non-Crit fail for ACKNEG2*/

                    }TPSTAHDR;

/*****************************************************************************/
/* STATUS-ERROR MESSAGE TYPE DECLARATION                                     */
/*****************************************************************************/

     typedef struct tpstehdr{                 /* STATUS ERROR MESSAGE HEADER */
                      CHAR     errstat;
#define STERROR  3
                      CHAR     errpad1;
                      INTEGER  errpad2;
                      INTEGER  errpad3;
                      INTEGER  errcode1;
                      INTEGER  errcode2;
                    }TPSTEHDR;

/*****************************************************************************/
/* STATUS-CONTROL MESSAGE TYPE DECLARATION                                   */
/*****************************************************************************/

     typedef struct tpstchdr{               /* STATUS CONTROL MESSAGE HEADER */
                     CHAR     ctlstat;
#define STCNTRL  2
                     CHAR     ctlqual;
#define CTLREQU  1
/* #define ACKPOS   2 */
/* #define ACKNEG1  3 */
/* #define ACKNEG2  4 */
                     CHAR     ctltype;
#define CCLEAR   1
#define CSDT     2
#define CRQR     3
#define CSTSN    4
#define CCANCEL  16
#define CLUSTAT  17
#define CSIGNAL  18
#define CRSHUTD  19
#define CBID     20
#define CCHASE   21
#define CSHUTC   22
#define CSHUTD   23
#define CRTR     24
#define CQC      32
#define CQEC     33
#define CRELQ    34
                     CHAR     ctlack;       /* Same values as fhackrqd below */
                     CHAR     ctlflag1;     /* Same values as fhflags1 below */
                     CHAR     ctlflag2;     /* Same values as fhflags2 below */
                     INTEGER  ctlnumb1;
                     INTEGER  ctlnumb2;
                     INTEGER  ctlmsgk;
                   }TPSTCHDR;

/*****************************************************************************/
/* STATUS-RESOURCE MESSAGE TYPE DECLARATION                                  */
/*****************************************************************************/

     typedef struct tpstrhdr{              /* STATUS RESOURCE MESSAGE HEADER */
                      CHAR     resstat;
#define STRESRCE 4
                      CHAR     respad;
                      INTEGER  rescred;
                    }TPSTRHDR;

/*****************************************************************************/
/* STATUS-SESSION MESSAGE TYPE DECLARATION                                   */
/*****************************************************************************/

     typedef struct tpstshdr{               /* STATUS SESSION MESSAGE HEADER */
                      CHAR     sessstat;
#define STSESSN  5
                      CHAR     sesspad;
                      INTEGER  sesscode;
#define STNOSESS 1                               /* X'01' (NO SESSION)       */
#define STLINERR 2                               /* X'02' (LINK ERROR)       */
#define STPUACT  3                               /* X'03' (PU ACTIVE)        */
#define STPUREAC 4                               /* X'04' (PU RE-ACTIVATED)  */
#define STLUACT  5                               /* X'05' (LU ACTIVE)        */
#define STLUREAC 6                               /* X'06' (LU RE-ACTIVATED)  */
#define STBETB   7                               /* BETB STATUS-SESSION CODE */
                      INTEGER  sessqual;
/* #define STPUACT  3                               X'03' (PU ACTIVE)        */
/* #define STPUREAC 4                               X'04' (PU RE-ACTIVATED)  */
#define STPUINAC 16                              /* X'10' (PU INACTIVE)      */
#define STLUINAC 17                              /* X'11' (LU INACTIVE)      */
                    }TPSTSHDR;

/*****************************************************************************/
/* STATUS-RTM     MESSAGE TYPE DECLARATION                                   */
/*****************************************************************************/

     typedef struct tpstmhdr{               /* STATUS RTM     MESSAGE HEADER */
                      CHAR     rtmstat;
#define STRTM    6
                      CHAR     strbndry;   /* set boundaries flag */
                      CHAR     strcount;   /* set counters flag */
                      CHAR     strtmdef;   /* rtm definition */
                      CHAR     strtmact;   /* rtm active flag */
                      CHAR     strtmdsp;   /* local display active flag */
                    }TPSTMHDR;

/*****************************************************************************/
/* STATUS VARIANT TYPES                                                      */
/*****************************************************************************/

     typedef struct tpashdr{                    /* APPLSTATUS MESSAGE HEADER */
                      union {
                        struct {TPSTAHDR B0G;}B0F; /* Status-Ack variant     */
                        struct {TPSTCHDR B0I;}B0H; /* Status-Control variant */
                        struct {TPSTEHDR B0K;}B0J; /* Status-Error variant   */
                        struct {TPSTRHDR B0M;}B0L; /* Status-Resource variant*/
                        struct {TPSTSHDR B0O;}B0N; /* Status-Session variant */
                        struct {TPSTMHDR X1E;}X1D; /* Status-RTM variant     */
                    }B0E;}
#define stackhdr B0E.B0F.B0G
#define stctlhdr B0E.B0H.B0I
#define sterrhdr B0E.B0J.B0K
#define streshdr B0E.B0L.B0M
#define stseshdr B0E.B0N.B0O
#define strtmhdr B0E.X1D.X1E
                    TPASHDR;

/*****************************************************************************/
/* FMI APPLDATA HERE                                                         */
/*****************************************************************************/

     typedef struct tpfmihdr{                     /* FMI DATA MESSAGE HEADER */
                     CHAR     fhackrqd;
#define NOACKREQ 0
#define ACKREQ   1
                     CHAR     fhpad1;
                     INTEGER  fhmsgkey;
                     CHAR     fhflags1;           /* BIT SIGNIFICANT */
#define AF_FMH  0x80
#define AF_BC   0x40
#define AF_EC   0x20
#define AF_COMM 0x10
#define AF_BB   0x08
#define AF_EB   0x04
#define AF_CD   0x02
#define AF_SD   0x01
                     CHAR     fhflags2;           /* BIT SIGNIFICANT */
#define AF_CODE 0x80
#define AF_ENCR 0x40
#define AF_ENPD 0x20
#define AF_QRI  0x10
#define AF_CEI  0x08
#define AF_BBIU 0x04
#define AF_EBIU 0x02
#define AF_RBI  0x01
                     INTEGER  fhpad2;
                     INTEGER  fhpad3;
                     INTEGER  fhseqno;
                   }TPFMIHDR;

/*****************************************************************************/
/* MAIN DEFINITION OF MESSAGE HEADER                                         */
/*****************************************************************************/

#ifdef WIN32_SUPPORT
 #define PTRBFHDR struct bufhdr *
#else
 #define PTRBFHDR struct bufhdr far *
#endif

     typedef struct bufhdr{
                     PTRBFHDR nxtqptr;
                     PTRBFELT hdreptr;
                     CHAR     numelts;
                     CHAR     msgtype;
#define OPENMSG  1
#define CLOSEMSG 2
#define DATAFMI  32
#define STATFMI  33
                     CHAR     srcl;
                     CHAR     srcp;
#define S3PROD   18                               /* 3270 Partner number     */
                     INTEGER  srci;
                     CHAR     destl;
                     CHAR     destp;
                     INTEGER  desti;
                     union {
                       struct {TPOPHDR  B1C;}B1B;
                       struct {TPCLHDR  B1E;}B1D;
                       struct {TPFMIHDR B1K;}B1J;
                       struct {TPASHDR  B1M;}B1L;
                     }B0Y;}
#define ophdr    B0Y.B1B.B1C
#define clhdr    B0Y.B1D.B1E
#define dfhdr    B0Y.B1J.B1K
#define sfhdr    B0Y.B1L.B1M
                     BUFHDR;

/*****************************************************************************/
/* RETURN CONSTANTS FOR SBPURCV                                              */
/*****************************************************************************/

#define CSUNORES 0 /* NO RESULT                                              */
#define CSUMSGRT 1 /* MESSAGE RETURNED                                       */
#define CSUPTHER 2 /* PATH ERROR                                             */
#define CSUTERM  3 /* TERMINATE                                              */
#define CSUBUFSH 4 /* BUFFER SHORTAGE                                        */

/*****************************************************************************/
/* PROCTYPE AND SERVTYPE PARAMETERS FOR SBPUINIT                             */
/*****************************************************************************/

#define CLIENT           2      /* client entry                              */
#define CES3270          2      /* SNAP-3270                                 */

/*****************************************************************************/
/* DL-Base return Values                                                     */
/*****************************************************************************/

#ifndef NO_ERROR
 #define NO_ERROR         0
#endif

#define CEDINNOMSG       0          /* status = no message or status         */
#define CEDINMSG         1          /* status = got message                  */
#define CEDINLLN         2          /* status = lost locality                */

/* values for SBPUINIT only */

#define DMBASE          550            /* Base level for Com Manager errors  */
#define DMLTABF         (DMBASE + 5)   /* L-table full                       */
#define DMMNWGI         (DMBASE + 12)  /* NetWkstaGetInfo call failed        */
#define DMDSTFL         (DMBASE + 13)  /* Service table full                 */
#define DMMPIPF         (DMBASE + 17)  /* Make pipe call failed              */
#define DMCOMNM         (DMBASE + 32)  /* No name found for this service     */
#define DMCOMDUP        (DMBASE + 46)  /* Duplicate COMNAME for service      */
#define DMNOTLOG        (DMBASE + 48)  /* User not logged on                 */
#define DMCFGOPN        (DMBASE + 66)  /* Failed to open the config file     */
#define DMCFREAD        (DMBASE + 68)  /* Error reading config file          */
#define DMNONAP         (DMBASE + 75)  /* NAP not up when starting service   */
#define WINBASE          950           /* Base level for Windows-only errors */
#define DMMAXAPP        (WINBASE+3)    /* Exceeded max # of concurrent apps  */

/*****************************************************************************/
/* Dmod/DL-Base entry points                                                 */
/*****************************************************************************/

#ifdef MSWIN_SUPPORT
 #ifndef APIENTRY
  #define APIENTRY WINAPI
 #endif
#endif

#ifdef OS2_SUPPORT
extern USHORT   APIENTRY  sbpuinit (HSEM FAR *, USHORT, USHORT, UCHAR FAR *);
extern USHORT   APIENTRY  sbpurcv (PTRBFHDR FAR *, INTEGER FAR*);
#endif

#ifdef WIN32_SUPPORT
extern USHORT WINAPI sbpuinit (HANDLE *, USHORT, USHORT, UCHAR *);
extern USHORT WINAPI sbpurcv (PTRBFHDR *, INTEGER *);
#endif

#ifdef MSWIN_SUPPORT
extern USHORT   WINAPI  sbpuinit (USHORT, USHORT, UCHAR FAR *);
#endif

#ifdef DOS_SUPPORT
extern USHORT   APIENTRY  sbpuinit (HSEM FAR *, USHORT, USHORT);
#endif

#ifndef WIN32_SUPPORT
extern USHORT   APIENTRY  sbpurcvx (BUFHDR FAR * FAR *, INTEGER, INTEGER);
extern VOID     APIENTRY  sbpusend (PTRBFHDR);
extern VOID     APIENTRY  sbputerm (VOID);
#else
extern USHORT WINAPI sbpurcvx (BUFHDR * *, INTEGER, INTEGER);
extern VOID   WINAPI sbpusend (PTRBFHDR);
extern VOID   WINAPI sbputerm (VOID);
#endif

#ifdef OS2_SUPPORT
extern USHORT APIENTRY sepdrout(USHORT (APIENTRY *) (BUFHDR far *, USHORT, USHORT));
#endif

#ifdef WIN32_SUPPORT
extern ULONG WINAPI sepdrout(ULONG (WINAPI *) (BUFHDR *, USHORT, USHORT));
#endif

#ifdef MSWIN_SUPPORT
extern USHORT WINAPI sepwrout(USHORT (WINAPI *) (BUFHDR far *, USHORT, USHORT));
#endif

#ifdef DOS_SUPPORT
extern USHORT APIENTRY sepdrout(USHORT (APIENTRY *) (BUFHDR far *, USHORT, USHORT));
#endif

/*****************************************************************************/
/* Buffer pool access routines                                               */
/*****************************************************************************/

#ifndef WIN32_SUPPORT
extern PTRBFHDR APIENTRY  sepdbubl (USHORT);
extern VOID     APIENTRY  sepdburl (PTRBFHDR);

extern VOID     APIENTRY  sbpibegt (PTRBFELT FAR *);
extern VOID     APIENTRY  sbpiberl (PTRBFELT FAR *);

extern VOID     APIENTRY  sepdchnk (USHORT FAR *, USHORT FAR *);
#else
extern PTRBFHDR WINAPI sepdbubl (USHORT);
extern VOID     WINAPI sepdburl (PTRBFHDR);

extern VOID     WINAPI sbpibegt (PTRBFELT *);
extern VOID     WINAPI sbpiberl (PTRBFELT *);

extern VOID     WINAPI sepdchnk (USHORT *, USHORT *);
#endif

/*****************************************************************************/
/* Structures for the 3270 user record.                                      */
/*****************************************************************************/

#define CERT3270  0x0002           /* 3270 user record type                  */
#define CECWKHAC  8                /* Length of Host Access Name             */
#define CECWKUNM  20               /* Length of 3270 user name               */
#define CECWKREM  25               /* Length of record remark                */
#define CE3MASMX  10               /* Max number of 3270 sessions            */

typedef struct tecwrksd
{
  UCHAR   cwshost[CECWKHAC + 1];   /* LU/Pool name accessed                  */
  USHORT  cwsestyp;                /* Session type (M2, M3, M4, M5, printer) */
#define CERTMOD2 0                 /* 24x80                                  */
#define CERTMOD3 1                 /* 32x80                                  */
#define CERTMOD4 2                 /* 43x80                                  */
#define CERTMOD5 3                 /* 27x132                                 */
#define CERTPRNT 4                 /* Host printer                           */
  USHORT  cwsmodov;                /* Has the user got override permission?  */
  USHORT  cwspad;                  /* 2 bytes of padding                     */
} TECWRKSD;

typedef struct tecwrkus
{
  USHORT   cwlen;                  /* Length of record                       */
  USHORT   cwtype;                 /* Type of record                         */
  UCHAR    cwname[CECWKUNM + 1];   /* User name                              */
  UCHAR    cwremark[CECWKREM + 1]; /* Comment field                          */
  UCHAR    cwstylef[9];            /* Initial style file name - no extnsn    */
  USHORT   cwvewrtm;               /* Can user view RTM info ?               */
  USHORT   cwalert;                /* Has user got ALERT permission ?        */
  USHORT   cwchghan;               /* Can change LU/Pool name accessed ?     */
  USHORT   cwmaxses;               /* Maximum number of active sessions 1-10 */
  USHORT   cwnumrec;               /* Number of sessions for user            */
  TECWRKSD cwsesdat[CE3MASMX];     /* Session information records            */
  USHORT   cwmodisf;               /* Permission to modify initial style     */
  USHORT   cwpad;                  /* 2 bytes of padding                     */
  USHORT   cwnumrmp;               /* Number of LUs/Pools in remap list      */
  TECWRKSD cwremap[1];             /* LU/Pool Remap list                     */
} TECWRKUS;

/*****************************************************************************/
/* Structures for the diagnostics record.                                    */
/*****************************************************************************/

#define CERTDIAG  0x0001           /* Diagnostics record type                */
#define CECNUMAL  20               /* Max number of ALERTs configurable      */
#define CECALRNM  52               /* Length of ALERT description 52 (arr sz)*/
#define CECALRNA  34               /* Actual length of ALERT desc is 34      */
#define CECALRPR  32               /* Length of parameter description        */
#define CECONAME  8                /* Length of connection name              */
#define CESTRLEN  128              /* Length of a string + 1                 */
#define CECCNLEN  15               /* Length of a computer name              */

typedef struct tedalert
{
  UCHAR    dalrtnam[CECALRNM + 1]; /* Description of the ALERT number        */
  UCHAR    daparam1[CECALRPR + 1]; /* Description of parameter 1             */
  UCHAR    daparam2[CECALRPR + 1]; /* Description of parameter 2             */
  UCHAR    daparam3[CECALRPR + 1]; /* Description of parameter 3             */
} TEDALERT;

typedef struct tediagns
{
  USHORT   dilen;                  /* Length of record                       */
  USHORT   ditype;                 /* Type of record                         */
  UCHAR    dinetmgt[CECONAME + 1]; /* Network Management Connection name     */
  USHORT   disrtmco;               /* Send RTM data at counter overflow      */
  USHORT   disrtmub;               /* Send RTM data at UNBIND                */
  USHORT   diwruldr;               /* RTM timers run until:                  */
#define CERTWRIT 0                 /*  0 - first data reaches screen         */
#define CERTUNLK 1                 /*  1 - host unlocks keyboard             */
#define CERTDIRE 2                 /*  2 - host lets user send               */
  USHORT   dirtmth1;               /* RTM threshold #1                       */
  USHORT   dirtmth2;               /* RTM threshold #2                       */
  USHORT   dirtmth3;               /* RTM threshold #3                       */
  USHORT   dirtmth4;               /* RTM threshold #4                       */
  TEDALERT dialerts[CECNUMAL];     /* ALERT description records              */
  UCHAR    diaudit[CESTRLEN];      /* Audit log filename                     */
  UCHAR    dierror[CESTRLEN];      /* Error log filename                     */
  USHORT   diaudlev;               /* Default audit level                    */
                                   /*   0   -   level 6                      */
                                   /*   1   -   level 8                      */
                                   /*   2   -   level 10                     */
  UCHAR    dipad[CECCNLEN + 1];    /* 16 bytes of padding                    */
} TEDIAGNS;

/*****************************************************************************/
/* Routine to access config information                                      */
/*****************************************************************************/
#ifndef WIN32_SUPPORT
USHORT APIENTRY sepdcrec(UCHAR FAR *, USHORT, USHORT FAR * );
#else
USHORT WINAPI sepdcrec(UCHAR *, USHORT, USHORT * );
#endif

/*****************************************************************************/
/* Return codes from sepdcrec                                                */
/*****************************************************************************/

#define NOCSSRVR 1                   /* No config server available           */
#define NODGNREC 2                   /* Diagnostics record not found         */
#define NOUSRREC 3                   /* No user record found for this user   */
#define BUF2SMAL 4                   /* Buffer too small                     */
#define NONOS    5                   /* Network not started                  */
#define NOTLOGON 6                   /* User not logged on to network        */
#define READERR  7                   /* File read error                      */
#define NONAP    8                   /* NAP not started                      */
#define MAXAPP   9                   /* Max # of client apps reached         */
#define ERROR_SERVER 14              /* Error on the server end of the RPC   */
#define ERROR_LOCAL_FAILURE 15       /* Error on the local end of the RPC    */

/*****************************************************************************/
/* Structure of version information block                                    */
/*****************************************************************************/

typedef struct cs_info {
  unsigned short    length;            /* length of this struct (bytes)      */
                                       /* (supplied parameter)               */
  unsigned char     major_ver;         /* CS major ver CS1.1->1, CS2.0->2    */
  unsigned char     minor_ver;         /* CS minor ver CS1.1->10 (dec)       */
  unsigned char     config_share[80];  /* name of share point of current     */
                                       /* config file = default location for */
                                       /* style file \\box\share\ (null      */
                                       /* terminated)                        */
  unsigned short    nos;               /* NOS that the LAN is running        */
#define Workstation 0
#define LANMan      1      /* Also LAN Server, unless we can differentiate   */
#define NetWare     2
} CS_INFO;

/*****************************************************************************/
/* Routine to get version information                                        */
/*****************************************************************************/
#ifndef WIN32_SUPPORT
USHORT APIENTRY sepdgetinfo(struct cs_info far * );
#else
USHORT WINAPI sepdgetinfo(struct cs_info * );
#endif

/*****************************************************************************/
/* Additional return code from sepdgetinfo.                                  */
/*****************************************************************************/
#define BADLNGTH 2


/*****************************************************************************/
/* Function definition for fmistrings dll entry point                        */
/*****************************************************************************/
int WINAPI GetFmiReturnCode (UINT,UINT,UINT,unsigned char FAR * );

/*****************************************************************************/
/* typedef for casting proc address return from GetProcAddress               */
/*****************************************************************************/
typedef int (FAR WINAPI * PGETFMISTR)(UINT, UINT, UINT, char FAR *);

/*****************************************************************************/
/* Macro for creating the first parameter for the GetFmiReturnCode call when */
/* using the error code and qualifier off a FMI status message.              */
/*****************************************************************************/
#define FMISTAT_TO_INT(code, qual)  ((INTEGER) (((code >> 8) << 8) | (qual >> 8)))

#ifdef WIN32_SUPPORT
  #pragma pack()
#endif

#ifdef __cplusplus
}
#endif

#endif
/* End of file fmi.h */

