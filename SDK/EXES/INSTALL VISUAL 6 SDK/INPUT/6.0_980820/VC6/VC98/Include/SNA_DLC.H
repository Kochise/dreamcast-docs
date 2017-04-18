/* sna_dlc.h */
/*
 * (C) Copyright Data Connection Limited 1989-1992.
 * (C) Copyright Microsoft Corporation 1991.
 * All Rights Reserved.
 */

#ifndef SNA_DLCH_INCLUDED
#define SNA_DLCH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Type definitions for message fields                                       */
/*****************************************************************************/
typedef signed long   LONGINT;
typedef signed short  INTEGER;
typedef signed char   SENUMERATED;
typedef signed short  LENUMERATED;
typedef unsigned char SUBRNG0;
typedef signed char   SUBRNG1;
typedef signed short  SUBRNG2;
typedef signed char   SET1;
typedef signed short  SET2;
typedef signed long   SET;
typedef SET2          THFORMAT;
#define VOID          void

/*****************************************************************************/
/* Element offset and length definitions                                     */
/*****************************************************************************/

#define SBCBELT1 1
#define SBCBELT3 13
#define SNANBEDA 268     /* LENGTH OF BUFFER ELEMENT */

/*****************************************************************************/
/* POINTERS TO STRUCTURES IN SBTBUFPT                                        */
/*****************************************************************************/
#ifdef WIN32_SUPPORT
#define PTRBFELT struct bufelt *
#define PTRBFHDR struct bufhdr *
#else
#define PTRBFELT struct bufelt far *
#define PTRBFHDR struct bufhdr far *
#endif

/*****************************************************************************/
/* SIZE OF BUFFER HEADER:                                                    */
/*   - 10 BYTES FOR FIXED PART                                               */
/*   - 16 BYTES FOR VARIANT PART                                             */
/*   - 2  BYTES FOR MATTERHORN EXTRA                                         */
/*****************************************************************************/
#define SVBUFSIZ 26


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
#define LINK     16
#define STAT     17
                      CHAR     appltype;
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
#define icreditr B01.B02.B03           /* Initial Credit for Receive       */
#define icredits B01.B02.B04           /* Initial Credit for Send          */
#define opninfo1 B01.B02.B05           /* Negotiable BIND indicator (FMI)  */
#define opnpad1  B01.B02.B06           /* Open (SSCP) Force type           */
#define operr1   B01.B07.B08
#define ERINIFAIL    0x0001            /* Hardware initialisation failed   */
#define ERLKNOTOPEN  0x0003            /* Link not open                    */
#define ERSTATOPEN   0x0005            /* Station already open             */
#define ERNOCB       0x0006            /* Station control blocks depleted  */
#define ERINVINDX    0x0007            /* Invalid link index               */
#define ERMAXSTAT    0x0008            /* No more stations/link allowed    */
#define ERINVXID     0x0008            /* Invalid XID length               */
#define ERDIFADDR    0x0009            /* Address different from RQ-OP-STN */
#define ERLINKOPN    0x0009            /* Link already open                */
#define ERBADADDR    0x000A            /* Invalid DLC address              */
#define ERLCCERR     0x000A            /* LCC error; fatal hardware failure*/
#define ERBADINDX    0x000B            /* Invalid link index               */
#define ERBADOPN     0x000C            /* Open(LINK) has insufficient data */
#define ERCONNTO     0x000D            /* Link connection timeout          */
#define ERNORES      0x000E            /* No resources free                */
#define EROPNPND     0x0011            /* Close(LINK) arrived, Open pending*/
#define ERDUPREQ     0x0012            /* Duplicate request                */
#define ERNOINC      0x0A11            /* Can't accept incoming call       */
#define operr2   B01.B07.B09
                    TPOPHDR;


#define SNA          0
#define APPL         1
#define AMOD         2
#define DLC          3


/*****************************************************************************/
/* CLOSE MESSAGE TYPE DECLARATIONS                                           */
/*****************************************************************************/
     typedef struct tpclhdr{                         /* CLOSE MESSAGE HEADER */
                      CHAR     closqual;    /* Close message qualifier       */
                      CHAR     clstype;     /* Close message connection type */
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
/* DLC MESSAGE TYPE DECLARATIONS                                             */
/*****************************************************************************/



     typedef struct tpddhdr{                      /* DLC DATA MESSAGE HEADER */
                     INTEGER  ddpad1;   /* Pad                              */
                     INTEGER  ddpad2;   /* Pad                              */
                     INTEGER  ddpad3;   /* Pad                              */
                     THFORMAT ddth01;   /* TH Flags                         */
                     CHAR     dddaf;    /* DAF in the TH                    */
                     CHAR     ddoaf;    /* OAF in the TH                    */
                     INTEGER  ddseqno;  /* Sequence Number in the TH        */
                   }TPDDHDR;


     typedef struct tpdshdr{                      /* DLC DATA MESSAGE HEADER */
                     CHAR     dstype;    /* DLC-Status type                  */
#define SENDXID  0x1a
#define RESOURCE 0x04
#define OUTAGE   0x18
#define STNCTCTD 0x17
#define RQOPNSTN 0x16
                     CHAR     dsqual;    /* Status Qualifier                 */
                     /*BOOLEAN*/union {
                       /*TRUE*/struct {CHAR     B0N;
                                    CHAR     B0O;
                                    INTEGER  B0P;
                                    INTEGER  B0Q;
                                    CHAR     B0R;}B0M;
                       /*FALSE*/struct {INTEGER  B0T;}B0S;
                   }B0L;}
#define dsuptype B0L.B0M.B0N             /* Status Qualifier                 */
#define dsmdset  B0L.B0M.B0N             /* RECFMS Counter Type              */
#define dsupcntr B0L.B0M.B0O             /* Req-Opn-Station Set-Mode flag    */
#define dspad    B0L.B0M.B0P             /* RECFMS Counter Value             */
#define dserror  B0L.B0M.B0Q             /* Pad                              */
#define dsoutsq  B0L.B0M.B0R             /* Internal value for Counter       */
#define dlccred  B0L.B0S.B0T             /* Outage Sub-qualifier             */
                   TPDSHDR;              /* DLC-Status Credit Increment      */




/*****************************************************************************/
/* SNAP-LINK HMOD MESSAGE TYPE DECLARATIONS                                  */
/*****************************************************************************/

     typedef struct tpdlhdr{                         /* HMOD  MESSAGE HEADER */
                      CHAR     dlcnr;    /* N(R) Value                       */
                      CHAR     dlcns;    /* N(S) Value                       */
                      INTEGER  dlclkidx; /* Link Index                       */
                      CHAR     dlcerst1; /* Error Status 1                   */
                      CHAR     dlcerst2; /* Error Status 2                   */
                    }TPDLHDR;


/*****************************************************************************/
/* MAIN DEFINITION OF MESSAGE HEADER                                         */
/*****************************************************************************/
     typedef struct bufhdr{
                     PTRBFHDR nxtqptr;
                     PTRBFELT hdreptr;
                     CHAR     numelts;
                     CHAR     msgtype;
#define OPENMSG  1
#define CLOSEMSG 2
#define DLCSTAT  17
#define DLCDATA  16
                     CHAR     srcl;
                     CHAR     srcp;
#define SLPROD   22
                     INTEGER  srci;
                     CHAR     destl;
                     CHAR     destp;
                     INTEGER  desti;
                     union {
                       struct {TPOPHDR  B1C;}B1B;
                       struct {TPCLHDR  B1E;}B1D;
                       struct {TPDDHDR  B1G;}B1F;
                       struct {TPDSHDR  B1I;}B1H;
                       struct {TPDLHDR  B1K;}B1J;
                     }B0Y;}
#define ophdr    B0Y.B1B.B1C
#define clhdr    B0Y.B1D.B1E
#define ddhdr    B0Y.B1F.B1G
#define dshdr    B0Y.B1H.B1I
#define dlhdr    B0Y.B1J.B1K
                     BUFHDR;


/*****************************************************************************/
/* MAIN DEFINITION OF MESSAGE ELEMENT                                        */
/*****************************************************************************/

/**STRUCT+********************************************************************/
/* Structure: BUFELT                                                         */
/*                                                                           */
/* Description: Main definition of SNAPS Buffer Element                      */
/*****************************************************************************/
     typedef struct bufelt{
                     PTRBFELT elteptr;   /* Pointer to next element in buffer*/
                     INTEGER  startd;    /* Offset (from 1) of start of data */
                     INTEGER  endd;      /* Offset (from 1) of last data byte*/
                     CHAR     trpad;
                     CHAR     dataru[268]; /* The data bytes themselves      */
                     } BUFELT;
/**STRUCT-********************************************************************/

/*****************************************************************************/
/* IF Win32 environment THEN                                                 */
/*   IF intel format THEN                                                    */
/*     define flipping macros                                                */
/*     define anti-flipping macros to NOP                                    */
/*****************************************************************************/
#ifdef WIN32
#ifndef NON_INTEL_BYTE_ORDER
#define PFLIPI(X) (unsigned short)_rotl(((unsigned short)(X))*(unsigned long)0x00010001,8)
#define PFLIPL(X) MAKEULONG(PFLIPI(HIUSHORT(X)),PFLIPI(LOUSHORT(X)))
#define PANTIFLIPI(X) (X)

/*****************************************************************************/
/* ELSE (non-intel)                                                          */
/*   set flipping to nop for now                                             */
/*   set anti-flipping on                                                    */
/*****************************************************************************/
#else
#define PFLIPI(X)  (X)
#define PFLIPL(X)  (X)
#define PANTIFLIPI(X) (unsigned short)_rotl((unsigned short)(X),8)
#endif

/*****************************************************************************/
/* ELSE (not Win32, must be Intel environment)                               */
/*   define flipping macros                                                  */
/*****************************************************************************/
#else
#define PFLIPI(X) (unsigned short)_rotl((unsigned short)(X),8)
#define PFLIPL(X) MAKEULONG(PFLIPI(HIUSHORT(X)),PFLIPI(LOUSHORT(X)))
#define PANTIFLIPI(X) (X)
#endif

/*****************************************************************************/
/* Buffer pool access routines                                               */
/*****************************************************************************/

#ifdef WIN32_SUPPORT


  #ifdef OLD_IHV_PROTOS
    extern PTRBFHDR WINAPI     sepdbubl (USHORT);
    extern VOID     WINAPI     sepdburl (PTRBFHDR);
    extern VOID     WINAPI     sbpibegt (PTRBFELT *);
    extern VOID     WINAPI     sbpiberl (PTRBFELT *);
  #else
    extern PTRBFHDR WINAPI     SNAGetBuffer     (USHORT);
    extern VOID     WINAPI     SNAReleaseBuffer (PTRBFHDR);
    extern VOID     WINAPI     SNAGetElement    (PTRBFELT *);
    extern VOID     WINAPI     SNAReleaseElement(PTRBFELT *);
  #endif

#else
  extern PTRBFHDR far  sepdbubl (USHORT);
  extern VOID     far  sepdburl (PTRBFHDR);
  extern VOID     far  sbpibegt (PTRBFELT far *);
  extern VOID     far  sbpiberl (PTRBFELT far *);
#endif

#ifdef WIN32_SUPPORT
extern CHAR        WINAPI  snpugetc(PTRBFELT, INTEGER);
extern VOID        WINAPI  snpuputc(PTRBFELT, INTEGER, CHAR);
extern INTEGER     WINAPI  snpugeti(PTRBFELT, INTEGER);
extern VOID        WINAPI  snpuputi(PTRBFELT, INTEGER, INTEGER);
extern VOID        WINAPI  snpugetl(PTRBFELT, INTEGER, LONGINT *);
extern VOID        WINAPI  snpuputl(PTRBFELT, INTEGER, LONGINT);
#else
extern CHAR     far  snpugetc(PTRBFELT, INTEGER);
extern VOID     far  snpuputc(PTRBFELT, INTEGER, CHAR);
extern INTEGER  far  snpugeti(PTRBFELT, INTEGER);
extern VOID     far  snpuputi(PTRBFELT, INTEGER, INTEGER);
extern VOID     far  snpugetl(PTRBFELT, INTEGER, LONGINT FAR *);
extern VOID     far  snpuputl(PTRBFELT, INTEGER, LONGINT);
#endif


/*****************************************************************************/
/* Include the remainder of SNA Services definitions                         */
/*****************************************************************************/
#include <sna_cnst.h>

#ifdef __cplusplus
}
#endif

#endif
/* End of file cs_dlc.h */

