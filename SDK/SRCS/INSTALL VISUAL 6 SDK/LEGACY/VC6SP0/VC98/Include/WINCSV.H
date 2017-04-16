/* Copyright Data Connection Ltd. 1989                                       */
/* acssvcc.h                                                                 */
/* Copyright (c) 1989 Microsoft Corporation. All rights reserved.            */
/*****************************************************************************/
/*       Function prototypes for the Common Service Verbs                    */
/*****************************************************************************/
/*  3054  13/11/91  SW  Add pascal entry point function prototype            */
/*  W32   15/04/92  CD  Add WIN32 support                                    */
/*  WCSV  06/11/92  SW  Add prototype for WinCSV entry points                */
/*  0998  11/06/93  SP  Add Async Transfer_MS_Data + wait for Host's Rsp     */
/*  WCSV2 15/09/93  PP  Add WinCSV return codes                              */
/*  RCFX2 26/07/94  SF  Ensure Secondary return code is a ULONG              */
/*****************************************************************************/

#ifndef ACSSVCCH_INCLUDED
#define ACSSVCCH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#if (defined(WIN32) || defined(WINDOWS))
 #define CSVENTRY WINAPI
#else
 #define CSVENTRY far pascal
#endif



#if (defined(WIN32) || defined(WINDOWS))
#define	WCSVDESCRIPTION_LEN	127                                      /*0998*/

typedef struct tagWCSVDATA                                             /*0998*/
{                                                                      /*0998*/
  WORD    wVersion;                                                    /*0998*/
  char    szDescription[WCSVDESCRIPTION_LEN+1];                        /*0998*/
} WCSVDATA, * PWCSVDATA, FAR * LPWCSVDATA;                             /*0998*/

extern void   CSVENTRY WinCSV(long);                                   /*0998*/
extern HANDLE CSVENTRY WinAsyncCSV(HWND, long);                        /*0998*/
extern int    CSVENTRY WinCSVCleanup(void);                            /*0998*/
extern int    CSVENTRY WinCSVStartup(WORD wVersion, LPWCSVDATA lpData);/*0998*/
extern int    CSVENTRY GetCsvReturnCode (struct  svc_hdr FAR *, UINT, unsigned char FAR *);
/*WCSV2***********************************************************************/
/* WinCSV return codes                                                       */
/*****************************************************************************/
#define WCSVINVALID         CSV_FLIPI(0x01F0) /* invalid parameter           */
#define WCSVSYSNOTREADY     CSV_FLIPI(0x03F0) /* subsystem not started       */
#define WCSVVERNOTSUPPORTED CSV_FLIPI(0x04F0) /* requested ver not supported */

#endif

extern void CSVENTRY ACSSVC(long);
extern void CSVENTRY ACSSVC_C(long);
extern void CSVENTRY ACSSVC_P(long);                                   /*3054*/

/*****************************************************************************/
/* Ensure the correct packing of structures                                  */
/*****************************************************************************/
#ifdef WIN32
  #pragma pack(4)
#endif

/*****************************************************************************/
/*                       VCB structures                                      */
/*****************************************************************************/

struct svc_hdr
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved                               */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  };

struct convert
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned char direction;         /* Direction of conversion - ASCII to     */
                                   /* EBCDIC or vice-versa.                  */
  unsigned char char_set;          /* Character to use for the conversion    */
                                   /* A, AE, or user-defined G.              */
  unsigned short len;              /* Length of string to be converted.      */
#ifdef WIN32
  unsigned char     *source;       /* Pointer to string to be converted.     */
  unsigned char     *target;       /* Address to put converted string at.    */
#else
  unsigned char far *source;       /* Pointer to string to be converted.     */
  unsigned char far *target;       /* Address to put converted string at.    */
#endif
  };

struct define_trace
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned char reserv3[8];        /* Reserved.                              */
  unsigned char dt_set;            /* Trace state to be set (on/off).        */
  /***************************************************************************/
  /* In the following fields, used for specifying which sorts of tracing is  */
  /* required, only the most significant bit is currently used. Bits 1 to 7  */
  /* are reserved. Bit 0 can be set to 'ignore' or to 'change'.              */
  /***************************************************************************/
  unsigned char appc;              /* Tracing for APPC.                      */
  unsigned char reserv4;           /* Reserved.                              */
  unsigned char srpi;              /* Tracing for SRPI.                      */
  unsigned char sdlc;              /* Reserved.                              */
  unsigned char tkn_rng_dlc;       /* Reserved.                              */
  unsigned char pcnet_dlc;         /* Reserved.                              */
  unsigned char dft;               /* Reserved.                              */
  unsigned char acdi;              /* Reserved.                              */
  unsigned char reserv5;           /* Reserved.                              */
  unsigned char comm_serv;         /* Tracing for Comm_Serv_API.             */
  unsigned char ehllapi;           /* Reserved.                              */
  unsigned char x25_api;           /* Reserved.                              */
  unsigned char x25_dlc;           /* Reserved.                              */
  unsigned char twinax;            /* Reserved.                              */
  unsigned char reserv6;           /* Reserved.                              */
  unsigned char lua_api;           /* Reserved.                              */
  unsigned char etherand;          /* Reserved.                              */
  unsigned char subsym;            /* Reserved.                              */
  unsigned char reserv7[8];        /* Reserved.                              */
  unsigned char reset_trc;         /* Reserved.                              */
  unsigned short trunc;            /* Truncation size for trace records.     */
  unsigned short strg_size;        /* Reserved.                              */
  unsigned char reserv8[1];        /* Reserved.                              */
  unsigned char phys_link[8];      /* Reserved.                              */
  unsigned char reserv9[56];       /* Reserved.                              */
  };



struct get_cp_convert_table
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned short source_cp;        /* Source code page for conversion table. */
  unsigned short target_cp;        /* Target code page for conversion table. */
#ifdef WIN32
  unsigned char     *conv_tbl_addr;/* Address to put conversion table at.    */
#else
  unsigned char far *conv_tbl_addr;/* Address to put conversion table at.    */
#endif
  unsigned char char_not_fnd;      /* Character not found option: either     */
                                   /* substitute character or round trip.    */
  unsigned char substitute_char;   /* Substitute character to use.           */
  };



struct log_message
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned short msg_num;          /* Number of message to log.              */
  unsigned char origntr_id[8];     /* ID of the originator of the message.   */
  unsigned char msg_file_name[3];  /* Message file to search for the required*/
                                   /* message number.                        */
  unsigned char msg_act;           /* Message action - whether to inform     */
                                   /* operator.                              */
  unsigned short msg_ins_len;      /* Length of data for insertion in msg.   */
#ifdef WIN32
  unsigned char     *msg_ins_ptr;  /* Address of data for insertion in msg.  */
#else
  unsigned char far *msg_ins_ptr;  /* Address of data for insertion in msg.  */
#endif
  };

struct transfer_ms_data
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char data_type;         /* Data type supplied to the verb - can   */
                                   /* be: user-defined; alert subvectors;    */
                                   /* pdstats subvectors; NMVT.              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned char options;           /* Verb options. Bits 3 - 7 are reserved. */
                                   /* Bit 0: Time stamp subvector option.    */
                                   /* Bit 1: Product set id subvector option.*/
                                   /* Bit 2: Option to send NMVT to SSCP.    */
                                   /* Bit 3: Option for local logging.       */
  unsigned char reserv3;           /* Reserved.                              */
  unsigned char origntr_id[8];     /* ID of originator of NMVT.              */
  unsigned short dlen;             /* Length of data supplied to verb.       */
#ifdef WIN32
  unsigned char     *dptr;         /* Address at which supplied data resides.*/
#else
  unsigned char far *dptr;         /* Address at which supplied data resides.*/
#endif
  };


struct set_user_log_queue
  {
  unsigned short opcode;           /* Verb operation code                    */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary RETURN_CODE                    */
  unsigned long secondary_rc;      /* Secondary RETURN_CODE                  */
  unsigned char reserv3[8];        /* Reserved.                              */
  unsigned char queue_name[64];    /* Reserved.                              */
  unsigned char forward;           /* Reserved.                              */
  unsigned char suppress;          /* Reserved.                              */
  unsigned char selection;         /* Reserved.                              */
  unsigned short numbers[10];      /* Reserved.                              */
  };


struct copy_trace_to_file
  {
  unsigned short opcode;           /* Verb identifying operation code.       */
  unsigned char opext;             /* Reserved.                              */
  unsigned char reserv2;           /* Reserved.                              */
  unsigned short primary_rc;       /* Primary return code from verb.         */
  unsigned long secondary_rc;      /* Secondary (qualifying) return code.    */
  unsigned char reserv3[8];        /* Reserved.                              */
  unsigned char file_name[64];     /* Trace file name.                       */
  unsigned char file_option;       /* File options. New or overwrite.        */
  unsigned char reserv4[12];       /* Address at which supplied data resides.*/
  };


/*****************************************************************************/
/* Return the packing to what the user set                                   */
/*****************************************************************************/
#ifdef WIN32
  #pragma pack()
#endif

/*****************************************************************************/
/* ------------------------- macro definitions ----------------------------- */
/*****************************************************************************/

/*************************************************************************W32*/
/* define type conversion macros                                         *W32*/
/*************************************************************************W32*/
#ifndef CSVFLIPSET
#define CSVFLIPSET
#define CSV_LO_UC(w)    ((unsigned char)(((unsigned short)(w)) & 0xFF)) /*W32*/
#define CSV_HI_UC(w)    ((unsigned char)(((unsigned short)(w) >> 8)  \
                            & 0xff))                                    /*W32*/
#define CSV_MAKUS(l, h) (((unsigned short)(l)) |                     \
                          ((unsigned short)(h)) << 8)                   /*W32*/
#define CSV_MAKUL(l, h) ((unsigned long)(((unsigned short)(l))|      \
                          ((unsigned long)((unsigned short)(h))) << 16))/*W32*/
#define CSV_LO_US(l)  ((unsigned short)(((unsigned long)(l)) & 0xFFFF)) /*W32*/
#define CSV_HI_US(l)    ((unsigned short)(((unsigned long)(l) >> 16) \
                           & 0xffff))                                   /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* IF non-Intel THEN                                                     *W32*/
/*   set flipping to nop for now                                         *W32*/
/*************************************************************************W32*/
#ifdef NON_INTEL_BYTE_ORDER                                             /*W32*/
#define CSV_FLIPI(X)  (X)                                               /*W32*/
#define CSV_FLIPL(X)  (X)                                               /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* ELSE (Intel environment)                                              *W32*/
/*   define flipping macros                                              *W32*/
/*************************************************************************W32*/
#else                                                                   /*W32*/
#define CSV_FLIPI(X) CSV_MAKUS(CSV_HI_UC(X),CSV_LO_UC(X))               /*W32*/
#define CSV_FLIPL(X) CSV_MAKUL(CSV_FLIPI(CSV_HI_US(X)),               \
                                 CSV_FLIPI(CSV_LO_US(X)))               /*W32*/
#endif                                                                  /*W32*/
#endif

/*****************************************************************************/
/*        Verb op codes.                                                     */
/*****************************************************************************/

  #define SV_CONVERT                       CSV_FLIPI(0x1A00)
  #define SV_DEFINE_TRACE                  CSV_FLIPI(0x1D00)
  #define SV_GET_CP_CONVERT_TABLE          CSV_FLIPI(0x1900)
  #define SV_LOG_MESSAGE                   CSV_FLIPI(0x1F00)
  #define SV_TRANSFER_MS_DATA              CSV_FLIPI(0x1C00)

  #define SV_SET_USER_LOG_QUEUE            CSV_FLIPI(0x4B00)
  #define SV_COPY_TRACE_TO_FILE            CSV_FLIPI(0x4C00)
  #define SV_DEFINE_DUMP                   CSV_FLIPI(0x4D00)


/*****************************************************************************/
/*        Parameters for the Common Service Verbs.                           */
/*****************************************************************************/

  #define SV_ADD                                     0
  #define SV_CHANGE                                  1
  #define SV_IGNORE                                  0
  #define SV_NO_ADD                                  1
  #define SV_NO_SEND                                 1
  #define SV_SEND                                    0

  #define SV_A                                       0x01
  #define SV_AE                                      0x00
  #define SV_ALL                                     0x01
  #define SV_ALERT_SUBVECTORS                        0x02
  #define SV_ASCII_TO_EBCDIC                         0x00
  #define SV_EBCDIC_TO_ASCII                         0x01
  #define SV_FORWARD                                 0x02
  #define SV_INTRV                                   0x00
  #define SV_G                                       0x02
  #define SV_LOG                                     0x00
  #define SV_LOGS                                    0x00
  #define SV_NMVT                                    0x01
  #define SV_NO                                      0x00
  #define SV_NO_INTRV                                0x01
  #define SV_NO_LOG                                  0x01
  #define SV_NONE                                    0x00
  #define SV_OFF                                     0x00
  #define SV_ON                                      0x01
  #define SV_PDSTATS_SUBVECTORS                      0x03
  #define SV_ROUND_TRIP                              0x01
  #define SV_SOME                                    0x00
  #define SV_SUBSTITUTE                              0x00
  #define SV_SYSTEM_MESSAGES                         0x01
  #define SV_USER_DEFINED                            0x00
  #define SV_USER_MESSAGES                           0x02
  #define SV_YES                                     0x01

 /****************************************************************************/
 /*       Bit masks for enabling and disabling functions                     */
 /****************************************************************************/
  #define SV_BIT0                                    0x80        /* x....... */
  #define SV_BIT1                                    0x40        /* .x...... */
  #define SV_BIT2                                    0x20        /* ..x..... */
  #define SV_BIT3                                    0x10        /* ...x.... */
  #define SV_BIT4                                    0x08        /* ....x... */
  #define SV_BIT5                                    0x04        /* .....x.. */
  #define SV_BIT6                                    0x02        /* ......x. */
  #define SV_BIT7                                    0x01        /* .......x */

/*****************************************************************************/
/*        Return Codes from the Common Service Verbs.                        */
/*****************************************************************************/

  #define SV_COMM_SUBSYSTEM_NOT_LOADED     CSV_FLIPI(0xF012)
  #define SV_CONFIG_FILE_ERROR             CSV_FLIPI(0x0032)
  #define SV_INVALID_VERB                  CSV_FLIPI(0xFFFF)
  #define SV_INVALID_VERB_SEGMENT          CSV_FLIPI(0xF008)
  #define SV_OK                            CSV_FLIPI(0x0000)
  #define SV_PARAMETER_CHECK               CSV_FLIPI(0x0001)
  #define SV_STATE_CHECK                   CSV_FLIPI(0x0002)
  #define SV_UNEXPECTED_DOS_ERROR          CSV_FLIPI(0xF011)
  #define SV_CANCELLED                     CSV_FLIPI(0x0021)           /*0998*/
  #define SV_SERVER_RESOURCE_NOT_FOUND     CSV_FLIPI(0xF024)           /*0998*/
  #define SV_SERVER_RESOURCES_LOST         CSV_FLIPI(0xF026)           /*0998*/
  #define SV_THREAD_BLOCKING               CSV_FLIPI(0xF006)           /*0998*/

  #define SV_CONVERSION_ERROR              CSV_FLIPL(0x00000406)
  #define SV_DATA_EXCEEDS_RU_SIZE          CSV_FLIPL(0x00000302)
  #define SV_INVALID_CHARACTER_SET         CSV_FLIPL(0x00000402)
  #define SV_INVALID_CHAR_NOT_FOUND        CSV_FLIPL(0x00000630)
  #define SV_INVALID_DATA_SEGMENT          CSV_FLIPL(0x00000006)
  #define SV_INVALID_DATA_TYPE             CSV_FLIPL(0x00000303)
  #define SV_INVALID_DIRECTION             CSV_FLIPL(0x00000401)
  #define SV_INVALID_FIRST_CHARACTER       CSV_FLIPL(0x00000404)
  #define SV_INVALID_FORWARD               CSV_FLIPL(0x00000700)
  #define SV_INVALID_MESSAGE_ACTION        CSV_FLIPL(0x00000621)
  #define SV_INVALID_NMVT_ERROR            CSV_FLIPL(0x00000304)
  #define SV_INVALID_QUEUE                 CSV_FLIPL(0x00000704)
  #define SV_INVALID_RESET_TRACE           CSV_FLIPL(0x0000062F)
  #define SV_INVALID_SELECTION             CSV_FLIPL(0x00000702)
  #define SV_INVALID_SET                   CSV_FLIPL(0x00000624)
  #define SV_INVALID_SOURCE_CODE_PAGE      CSV_FLIPL(0x00000631)
  #define SV_INVALID_STORAGE_SIZE          CSV_FLIPL(0x00000627)
  #define SV_INVALID_SUPPRESS              CSV_FLIPL(0x00000701)
  #define SV_INVALID_TARGET_CODE_PAGE      CSV_FLIPL(0x00000632)
  #define SV_PD_MENUS_IN_PROGRESS          CSV_FLIPL(0x0000062E)
  #define SV_QUEUE_ALREADY_IN_EFFECT       CSV_FLIPL(0x00000705)
  #define SV_SSCP_PU_SESSION_NOT_ACTIVE    CSV_FLIPL(0x00000301)
  #define SV_TABLE_ERROR                   CSV_FLIPL(0x00000405)
  #define SV_TOO_HIGH_A_NUMBER             CSV_FLIPL(0x00000703)
  #define SV_SERVER_CONN_FAILURE           CSV_FLIPL(0x030000AB) /*0998**RCFX*/

/*****************************************************************************/
/* The following constants are needed for EE12 enhancements but could not    */
/* be found in the EE header file.                                           */
/*****************************************************************************/
  #define SV_NEW                                     0x00
  #define SV_OVERWRITE                               0x01

  #define SV_OUTPUT_DEVICE_FULL            CSV_FLIPI(0x0031)
  #define SV_FILE_ALREADY_EXISTS           CSV_FLIPI(0x0030)

  #define SV_TRACE_NOT_STOPPED             CSV_FLIPL(0x0000062A)
  #define SV_INVALID_FILE_OPTION           CSV_FLIPL(0x0000062B)
  #define SV_TRACE_BUFFER_EMPTY            CSV_FLIPL(0x0000062C)


#ifdef __cplusplus
}
#endif

#endif
