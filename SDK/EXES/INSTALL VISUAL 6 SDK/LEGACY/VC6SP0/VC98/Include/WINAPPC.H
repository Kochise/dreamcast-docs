/* Copyright Data Connection Ltd. 1989 */
/*****************************************************************************/
/*                                                                           */
/*****************************************************************************/
/* winappc.h */
/* Copyright (c) 1989, Microsoft Corporation.  All rights reserved.          */

/*****************************************************************************/
/* APPC constant, vcb and function definitions                               */
/*****************************************************************************/

/*****************************************************************************/
/* Change History                                                            */
/*  CPIC  07/05/91  GH  Add get_conv_state verb, and support for fully       */
/*                      qualified network names in the (mc)allocate VCBs     */
/*  CPIC  03/06/91  GH  Changed FQname support. Name now '.' separated.      */
/*  CPIC  14/06/91  GH  Added constants for the conv_state parameter         */
/*  SCSN  08/08/91  GH  Fixed the AP_SEND_DATA_CONFIRM_SYNC_NONE defn.       */
/*  CPIC  22/08/91  GH  Removed the FQ-flag in (mc)allocate VCBs             */
/*  9997  23/10/91  AD  Change TP_ENDED end_type field to EE friendly 'type' */
/*  3054  13/11/91  SW  Add pascal entry point function prototype            */
/*  xxxx  02/01/92  SW  Update what_rcvd values                              */
/*  CNOS  17/01/92  PP  Add opcode for CNOS.  NS/2 allows management verbs   */
/*                      to go through APPC entry point                       */
/*  W32   24/02/92  AD  Win32 port                                           */
/*  CPIC  24/02/92  AD  Move CPIC specific constants and types               */
/*  W32   14/04/92  AD  remove far keyword for Win32, add pack pragma        */
/*  DISP  14/04/92  TB  Add definition for DISPLAY opcode.                   */
/*  DSP2  04/06/92  TB  Check to see if appc_c.h already included mgmt hdrs  */
/*  ES10  03/11/92  SP  Add support for ES 1.0 APPC extensions               */
/*  WSNA2 27/10/92  CD  Changes for WinSNA                                   */
/*  DFLU  18/02/93  SP  Add rc for Bad Partner LU Alias                      */
/*  IBM1  29/06/93  NGR Add #defines and typedefs from ES include files      */
/*  EVNT  14/12/93  DK  Allow completion to be notified by setting an event  */
/*  GRC   20/01/94  DK  Add definition of GetAppcReturnCode                  */
/*  RPRP  24/10/95  JD  Implement TEST_RTS_AND_POST                          */
/*  SYNC  25/03/96  SGF Syncpoint Support                                    */
/*  APOR  02/12/96  DA  Implement POST_ON_RECEIPT                            */
/*  SELD  02/01/97  DA  Send error log data on mapped conversations          */
/*  RELD  02/01/97  DA  Recv error log data                                  */
/*  5178  02/25/97  SGF Single signon for priviledged proxy                  */
/*  7239  03/05/97  SGF Make single signon strings UNICODE                   */
/*****************************************************************************/

/*****************************************************************************/
/* If winappc.h not already included then define APPC_C_INCLUDED to avoid it */
/* being included again. This is needed as winappc.h is included in the      */
/* management header acsmgtc.h.  *DSP2*                                      */
/*****************************************************************************/
#ifndef APPC_C_INCLUDED
#define APPC_C_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Set WINSNA if this is Win16 or Win32                                *WSNA2*/
/*****************************************************************************/
#if ( defined(WINDOWS) || defined(WIN32) )
 #define WINSNA
#endif




/* ========================================================================= */
/*****************************************************************************/
/* ------------------------- macro definitions ----------------------------- */
/*****************************************************************************/

/*************************************************************************W32*/
/* for Win32 environment:                                                *W32*/
/* -  ensure correct packing                                             *W32*/
/* -  remove references to far                                           *W32*/
/*************************************************************************W32*/
#ifdef WIN32                                                            /*W32*/
                                                                        /*W32*/
#pragma pack(4)                                                         /*W32*/
#define far                                                             /*W32*/
                                                                        /*W32*/
#endif                                                                  /*W32*/

/*************************************************************************W32*/
/* define type conversion macros                                         *W32*/
/*************************************************************************W32*/
#define APPC_LO_UC(w)    ((unsigned char)(((unsigned short)(w)) & 0xFF))/*W32*/
#define APPC_HI_UC(w)    ((unsigned char)(((unsigned short)(w) >> 8)  \
                            & 0xff))                                    /*W32*/
#define APPC_MAKUS(l, h) (((unsigned short)(l)) |                     \
                          ((unsigned short)(h)) << 8)                   /*W32*/
#define APPC_MAKUL(l, h) ((unsigned long)(((unsigned short)(l))|      \
                          ((unsigned long)((unsigned short)(h))) << 16))/*W32*/
#define APPC_LO_US(l)   ((unsigned short)(((unsigned long)(l)) & 0xFFFF))/*W32*/
#define APPC_HI_US(l)    ((unsigned short)(((unsigned long)(l) >> 16) \
                           & 0xffff))                                   /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* IF non-Intel THEN                                                     *W32*/
/*   set flipping to nop for now                                         *W32*/
/*************************************************************************W32*/
#ifdef NON_INTEL_BYTE_ORDER                                             /*W32*/
#define APPC_FLIPI(X)  (X)                                              /*W32*/
#define APPC_FLIPL(X)  (X)                                              /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* ELSE (Intel environment)                                              *W32*/
/*   define flipping macros                                              *W32*/
/*************************************************************************W32*/
#else                                                                   /*W32*/
#define APPC_FLIPI(X) APPC_MAKUS(APPC_HI_UC(X),APPC_LO_UC(X))           /*W32*/
#define APPC_FLIPL(X) APPC_MAKUL(APPC_FLIPI(APPC_HI_US(X)),           \
                                 APPC_FLIPI(APPC_LO_US(X)))             /*W32*/
#endif                                                                  /*W32*/

#ifdef WIN32
#define far
#endif

/* ========================================================================= */
/*****************************************************************************/
/* ------------------------- verb opcodes ---------------------------------- */
/*****************************************************************************/

/*****************************************************************************/
/* control verbs                                                             */
/*****************************************************************************/
#define AP_TP_STARTED                   APPC_FLIPI(0x1400)        /* X'1400' */
#define AP_RECEIVE_ALLOCATE             APPC_FLIPI(0x1600)        /* X'1600' */
#define AP_TP_ENDED                     APPC_FLIPI(0x1300)        /* X'1300' */

/*****************************************************************************/
/* New opcode for RCV_ALLOC with a list of TP names                    *WSNA5*/
/*                                                                           */
/* Though defined for all OS, this verb will only be allowed for WINSNA      */
/* environments                                                              */
/*****************************************************************************/
#define AP_RECEIVE_ALLOCATE_X           APPC_FLIPI(0x9600) /*X'1600' + X'8000'*/

/*****************************************************************************/
/* management verbs                                                *DISP*CNOS*/
/*****************************************************************************/
#define AP_CNOS                         APPC_FLIPI(0x1500)        /* X'1500' */
#define AP_DISPLAY                      APPC_FLIPI(0X1B00)        /* X'1B00' */

/*****************************************************************************/
/* mapped conversation verbs                                                 */
/*****************************************************************************/
#define AP_M_ALLOCATE                   APPC_FLIPI(0x0100)        /* X'0100' */
#define AP_M_CONFIRM                    APPC_FLIPI(0x0300)        /* X'0300' */
#define AP_M_CONFIRMED                  APPC_FLIPI(0x0400)        /* X'0400' */
#define AP_M_DEALLOCATE                 APPC_FLIPI(0x0500)        /* X'0500' */
#define AP_M_FLUSH                      APPC_FLIPI(0x0600)        /* X'0600' */
#define AP_M_GET_ATTRIBUTES             APPC_FLIPI(0x0700)        /* X'0700' */
#define AP_M_PREPARE_TO_RECEIVE         APPC_FLIPI(0x0a00)        /* X'0a00' */
#define AP_M_RECEIVE_AND_POST           APPC_FLIPI(0x0d00)        /* X'0d00' */
#define AP_M_RECEIVE_AND_WAIT           APPC_FLIPI(0x0b00)        /* X'0b00' */
#define AP_M_RECEIVE_IMMEDIATE          APPC_FLIPI(0x0c00)        /* X'0c00' */
#define AP_M_REQUEST_TO_SEND            APPC_FLIPI(0x0e00)        /* X'0e00' */
#define AP_M_SEND_CONVERSATION          APPC_FLIPI(0x1800) //ES10 /* X'1800' */
#define AP_M_SEND_DATA                  APPC_FLIPI(0x0f00)        /* X'0f00' */
#define AP_M_SEND_ERROR                 APPC_FLIPI(0x1000)        /* X'1000' */
#define AP_M_TEST_RTS                   APPC_FLIPI(0x1200)        /* X'1200' */
#define AP_M_TEST_RTS_AND_POST          APPC_FLIPI(0x8100)        /* X'8100' */ /*RPRP*/
#ifdef WIN32                                                                    /*APOR*/
#define AP_M_POST_ON_RECEIPT            APPC_FLIPI(0x8200)        /* X'8200' */ /*APOR*/
#endif                                                                          /*APOR*/
#define AP_M_RECEIVE_LOG_DATA           APPC_FLIPI(0x8300)        /* X'8300' */ /*RELD*/

/*****************************************************************************/
/* basic conversation verbs                                                  */
/*****************************************************************************/
#define AP_B_ALLOCATE                   APPC_FLIPI(0x0100)        /* X'0100' */
#define AP_B_CONFIRM                    APPC_FLIPI(0x0300)        /* X'0300' */
#define AP_B_CONFIRMED                  APPC_FLIPI(0x0400)        /* X'0400' */
#define AP_B_DEALLOCATE                 APPC_FLIPI(0x0500)        /* X'0500' */
#define AP_B_FLUSH                      APPC_FLIPI(0x0600)        /* X'0600' */
#define AP_B_GET_ATTRIBUTES             APPC_FLIPI(0x0700)        /* X'0700' */
#define AP_B_PREPARE_TO_RECEIVE         APPC_FLIPI(0x0a00)        /* X'0a00' */
#define AP_B_RECEIVE_AND_POST           APPC_FLIPI(0x0d00)        /* X'0d00' */
#define AP_B_RECEIVE_AND_WAIT           APPC_FLIPI(0x0b00)        /* X'0b00' */
#define AP_B_RECEIVE_IMMEDIATE          APPC_FLIPI(0x0c00)        /* X'0c00' */
#define AP_B_REQUEST_TO_SEND            APPC_FLIPI(0x0e00)        /* X'0e00' */
#define AP_B_SEND_CONVERSATION          APPC_FLIPI(0x1800) //ES10 /* X'1800' */
#define AP_B_SEND_DATA                  APPC_FLIPI(0x0f00)        /* X'0f00' */
#define AP_B_SEND_ERROR                 APPC_FLIPI(0x1000)        /* X'1000' */
#define AP_B_TEST_RTS                   APPC_FLIPI(0x1200)        /* X'1200' */
#define AP_B_TEST_RTS_AND_POST          APPC_FLIPI(0x8100)        /* X'8100' */ /*RPRP*/
#ifdef WIN32                                                                    /*APOR*/
#define AP_B_POST_ON_RECEIPT            APPC_FLIPI(0x8200)        /* X'8200' */ /*APOR*/
#endif                                                                          /*APOR*/
#define AP_B_RECEIVE_LOG_DATA           APPC_FLIPI(0x8300)        /* X'8300' */ /*RELD*/

/*****************************************************************************/
/* type independent verbs                                                    */
/*****************************************************************************/
#define AP_GET_TP_PROPERTIES            APPC_FLIPI(0x1700) //ES10 /* X'1700' */
#define AP_GET_TYPE                     APPC_FLIPI(0x0800)        /* X'0800' */
#define AP_GET_STATE                    APPC_FLIPI(0x0900)        /* X'0900' */
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_SET_TP_PROPERTIES            APPC_FLIPI(0x7e00)  /* X'7e00'  *SYNC*/
#define AP_GET_LU_STATUS                APPC_FLIPI(0x7f00)  /* X'7f00'  *SYNC*/
#endif                                                                 /*SYNC*/

/* ========================================================================= */
/*****************************************************************************/
/* ------------------- primary and secondary return codes ------------------ */
/*****************************************************************************/
#define AP_OK                           APPC_FLIPI(0x0000)      /* X'0000'   */

#define AP_PARAMETER_CHECK              APPC_FLIPI(0x0001)      /* X'0001'   */
  #define AP_BAD_TP_ID                   APPC_FLIPL(0x00000001) /*X'00000001'*/
  #define AP_BAD_CONV_ID                 APPC_FLIPL(0x00000002) /*X'00000002'*/
  #define AP_BAD_LU_ALIAS                APPC_FLIPL(0x00000003) /*X'00000003'*/
  #define AP_INVALID_DATA_SEGMENT        APPC_FLIPL(0x00000006) /*X'00000006'*/
  #define AP_BAD_CONV_TYPE               APPC_FLIPL(0x00000011) /*X'00000011'*/
  #define AP_BAD_SYNC_LEVEL              APPC_FLIPL(0x00000012) /*X'00000012'*/
  #define AP_BAD_SECURITY                APPC_FLIPL(0x00000013) /*X'00000013'*/
  #define AP_BAD_RETURN_CONTROL          APPC_FLIPL(0x00000014) /*X'00000014'*/
  #define AP_PIP_LEN_INCORRECT           APPC_FLIPL(0x00000016) /*X'00000016'*/
  #define AP_NO_USE_OF_SNASVCMG          APPC_FLIPL(0x00000017) /*X'00000017'*/
  #define AP_UNKNOWN_PARTNER_MODE        APPC_FLIPL(0x00000018) /*X'00000018'*/
  #define AP_CONFIRM_ON_SYNC_LEVEL_NONE  APPC_FLIPL(0x00000031) /*X'00000031'*/
  #define AP_DEALLOC_BAD_TYPE            APPC_FLIPL(0x00000051) /*X'00000051'*/
  #define AP_DEALLOC_LOG_LL_WRONG        APPC_FLIPL(0x00000057) /*X'00000057'*/
  #define AP_P_TO_R_INVALID_TYPE         APPC_FLIPL(0x000000a1) /*X'000000a1'*/
  #define AP_RCV_AND_WAIT_BAD_FILL       APPC_FLIPL(0x000000b5) /*X'000000b5'*/
  #define AP_RCV_IMMD_BAD_FILL           APPC_FLIPL(0x000000c4) /*X'000000c4'*/
  #define AP_RCV_AND_POST_BAD_FILL       APPC_FLIPL(0x000000d5) /*X'000000d5'*/
  #define AP_INVALID_SEMAPHORE_HANDLE    APPC_FLIPL(0x000000d6) /*X'000000d6'*/
  #define AP_BAD_RETURN_STATUS_WITH_DATA APPC_FLIPL(0x000000d7) /*X'000000d7'*/
  #define AP_BAD_LL                      APPC_FLIPL(0x000000f1) /*X'000000f1'*/
  #define AP_SEND_DATA_INVALID_TYPE      APPC_FLIPL(0x000000f4) /*X'000000f4'*/
  #define AP_INVALID_SESSION_ID          APPC_FLIPL(0x00000512) /*X'00000512'*/
                                                                       /*ES10*/
/*#define AP_SEND_DATA_CONFIRM_ON_SYNC_LEVEL_NONE 0xf5000000*/ /*X'000000f5' */
  #define AP_SEND_DATA_CONFIRM_SYNC_NONE APPC_FLIPL(0x000000f5) /*X'000000f5'*/
                                                                       /*SCSN*/
  #define AP_BAD_PARTNER_LU_ALIAS        APPC_FLIPL(0x0000015b) /*X'0000015b'*/
                                                                       /*DFLU*/

  #define AP_SEND_ERROR_LOG_LL_WRONG     APPC_FLIPL(0x00000102) /*X'00000102'*/
  #define AP_SEND_ERROR_BAD_TYPE         APPC_FLIPL(0x00000103) /*X'00000103'*/
  #define AP_BAD_ERROR_DIRECTION         APPC_FLIPL(0x00000105) /*X'00000105'*/
  #define AP_TOO_MANY_TPS                APPC_FLIPL(0x00000243) /*X'00000243'*/
  #define AP_BAD_TYPE                    APPC_FLIPL(0x00000250) /*X'00000250'*/
  #define AP_UNDEFINED_TP_NAME           APPC_FLIPL(0x00000506) /*X'00000506'*/
  #define AP_INVALID_SET_PROT            APPC_FLIPL(0x00000700) /*X'00000700'SYNC*/
  #define AP_INVALID_NEW_PROT            APPC_FLIPL(0x00000701) /*X'00000701'SYNC*/
  #define AP_INVALID_SET_UNPROT          APPC_FLIPL(0x00000702) /*X'00000702'SYNC*/
  #define AP_INVALID_NEW_UNPROT          APPC_FLIPL(0x00000703) /*X'00000703'SYNC*/
  #define AP_INVALID_SET_USER            APPC_FLIPL(0x00000704) /*X'00000704'SYNC*/
  #define AP_INVALID_DATA_TYPE           APPC_FLIPL(0x00000705) /*X'00000705'SYNC*/
  #define AP_BAD_LOCAL_LU_ALIAS          APPC_FLIPL(0x01000003) /*X'01000003'SYNC*/
  #define AP_BAD_REMOTE_LU_ALIAS         APPC_FLIPL(0x02000003) /*X'02000003'SYNC*/
#ifdef WIN32                                                               /*APOR*/
  #define AP_POST_ON_RECEIPT_BAD_FILL    APPC_FLIPL(0x03000003) /*X'03000003'APOR*/
#endif                                                                     /*APOR*/
#define AP_STATE_CHECK                  APPC_FLIPI(0x0002)      /* X'0002'   */
  #define AP_CONFIRM_BAD_STATE           APPC_FLIPL(0x00000032) /*X'00000032'*/
  #define AP_CONFIRM_NOT_LL_BDY          APPC_FLIPL(0x00000033) /*X'00000033'*/
  #define AP_CONFIRMED_BAD_STATE         APPC_FLIPL(0x00000041) /*X'00000041'*/
  #define AP_DEALLOC_FLUSH_BAD_STATE     APPC_FLIPL(0x00000052) /*X'00000052'*/
  #define AP_DEALLOC_CONFIRM_BAD_STATE   APPC_FLIPL(0x00000053) /*X'00000053'*/
  #define AP_DEALLOC_NOT_LL_BDY          APPC_FLIPL(0x00000055) /*X'00000055'*/
  #define AP_FLUSH_NOT_SEND_STATE        APPC_FLIPL(0x00000061) /*X'00000061'*/
  #define AP_P_TO_R_NOT_LL_BDY           APPC_FLIPL(0x000000a2) /*X'000000a2'*/
  #define AP_P_TO_R_NOT_SEND_STATE       APPC_FLIPL(0x000000a3) /*X'000000a3'*/
  #define AP_RCV_AND_WAIT_BAD_STATE      APPC_FLIPL(0x000000b1) /*X'000000b1'*/
  #define AP_RCV_AND_WAIT_NOT_LL_BDY     APPC_FLIPL(0x000000b2) /*X'000000b2'*/
  #define AP_RCV_IMMD_BAD_STATE          APPC_FLIPL(0x000000c1) /*X'000000c1'*/
  #define AP_RCV_AND_POST_BAD_STATE      APPC_FLIPL(0x000000d1) /*X'000000d1'*/
  #define AP_RCV_AND_POST_NOT_LL_BDY     APPC_FLIPL(0x000000d2) /*X'000000d2'*/
  #define AP_R_T_S_BAD_STATE             APPC_FLIPL(0x000000e1) /*X'000000e1'*/
  #define AP_SEND_DATA_NOT_SEND_STATE    APPC_FLIPL(0x000000f2) /*X'000000f2'*/
  #define AP_SEND_DATA_NOT_LL_BDY        APPC_FLIPL(0x000000f6) /*X'000000f6'*/
  #define AP_ATTACH_MANAGER_INACTIVE     APPC_FLIPL(0x00000508) /*X'00000508'*/
  #define AP_ALLOCATE_NOT_PENDING        APPC_FLIPL(0x00000509) /*X'00000509'*/
  #define AP_INVALID_PROCESS             APPC_FLIPL(0x00000525) /*X'00000525'*/

#define AP_ALLOCATION_ERROR             APPC_FLIPI(0x0003)      /* X'0003'   */
  #define AP_ALLOCATION_FAILURE_NO_RETRY APPC_FLIPL(0x00000004) /*X'00000004'*/
  #define AP_ALLOCATION_FAILURE_RETRY    APPC_FLIPL(0x00000005) /*X'00000005'*/
  #define AP_SECURITY_NOT_VALID          APPC_FLIPL(0x080f6051) /*X'080f6051'*/
  #define AP_TRANS_PGM_NOT_AVAIL_RETRY   APPC_FLIPL(0x084b6031) /*X'084b6031 */
  #define AP_TRANS_PGM_NOT_AVAIL_NO_RETRY APPC_FLIPL(0x084c0000) /*X'084c0000*/
  #define AP_TP_NAME_NOT_RECOGNIZED      APPC_FLIPL(0x10086021) /*X'10086021'*/
  #define AP_PIP_NOT_ALLOWED             APPC_FLIPL(0x10086031) /*X'10086031'*/
  #define AP_PIP_NOT_SPECIFIED_CORRECTLY APPC_FLIPL(0x10086032) /*X'10086032'*/
  #define AP_CONVERSATION_TYPE_MISMATCH  APPC_FLIPL(0x10086034) /*X'10086034'*/
  #define AP_SYNC_LEVEL_NOT_SUPPORTED    APPC_FLIPL(0x10086041) /*X'10086041'*/

#define AP_DEALLOC_ABEND                APPC_FLIPI(0x0005)      /* X'0005'   */
#define AP_DEALLOC_ABEND_PROG           APPC_FLIPI(0x0006)      /* X'0006'   */
#define AP_DEALLOC_ABEND_SVC            APPC_FLIPI(0x0007)      /* X'0007'   */
#define AP_DEALLOC_ABEND_TIMER          APPC_FLIPI(0x0008)      /* X'0008'   */
#define AP_DEALLOC_NORMAL               APPC_FLIPI(0x0009)      /* X'0009'   */
#define AP_PROG_ERROR_NO_TRUNC          APPC_FLIPI(0x000c)      /* X'000c'   */
#define AP_PROG_ERROR_TRUNC             APPC_FLIPI(0x000d)      /* X'000d'   */
#define AP_PROG_ERROR_PURGING           APPC_FLIPI(0x000e)      /* X'000e'   */
#define AP_CONV_FAILURE_RETRY           APPC_FLIPI(0x000f)      /* X'000f'   */
#define AP_CONV_FAILURE_NO_RETRY        APPC_FLIPI(0x0010)      /* X'0010'   */
#define AP_SVC_ERROR_NO_TRUNC           APPC_FLIPI(0x0011)      /* X'0011'   */
#define AP_SVC_ERROR_TRUNC              APPC_FLIPI(0x0012)      /* X'0012'   */
#define AP_SVC_ERROR_PURGING            APPC_FLIPI(0x0013)      /* X'0013'   */
#define AP_UNSUCCESSFUL                 APPC_FLIPI(0x0014)      /* X'0014'   */
#define AP_CONVERSATION_TYPE_MIXED      APPC_FLIPI(0x0019)      /* X'0019'   */
#define AP_CANCELLED                    APPC_FLIPI(0x0021)      /* X'0021'   */
#define AP_SECURITY_REQUESTED_NOT_SUPPORTED  APPC_FLIPI(0x0022) /* X'0022'   */
#define AP_TP_BUSY                      APPC_FLIPI(0xf002)      /* X'f002'   */

#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_BACKED_OUT                   APPC_FLIPI(0x0023)  /* X'0022'  *SYNC*/
  #define AP_BO_NO_RESYNC            APPC_FLIPL(0x08240000) /*X'08240000'SYNC*/
  #define AP_BO_RESYNC               APPC_FLIPL(0x08240001) /*X'08240001'SYNC*/
#endif                                                                 /*SYNC*/

#define AP_COMM_SUBSYSTEM_ABENDED       APPC_FLIPI(0xf003)      /* X'f003'   */
#define AP_COMM_SUBSYSTEM_NOT_LOADED    APPC_FLIPI(0xf004)      /* X'f004'   */
#define AP_CONV_BUSY                    APPC_FLIPI(0xf005)      /* X'f005'   */
#define AP_THREAD_BLOCKING              APPC_FLIPI(0xf006)      /* X'f006'   */
#define AP_INVALID_VERB_SEGMENT         APPC_FLIPI(0xf008)      /* X'f008'   */
#define AP_UNEXPECTED_DOS_ERROR         APPC_FLIPI(0xf011)      /* X'f011'   */
#define AP_STACK_TOO_SMALL              APPC_FLIPI(0xf015)      /* X'f015'   */
#define AP_INVALID_VERB                 APPC_FLIPI(0xffff)      /* X'ffff'   */

/* ========================================================================= */
/*****************************************************************************/
/* ---------------------------- parameters --------------------------------- */
/*****************************************************************************/

/*****************************************************************************/
/* opext and conv_type                                                       */
/*****************************************************************************/
#define AP_BASIC_CONVERSATION             0x00
#define AP_BASIC                          0x00                         /*IBM1*/
#define AP_MAPPED_CONVERSATION            0x01
#define AP_MAPPED                         0x01                         /*IBM1*/

/*****************************************************************************/
/* rts_rcvd and return_status_with_data                                      */
/*****************************************************************************/
#define AP_NO                             0x00
#define AP_YES                            0x01

/****************************************************************************/
/* sync_level, security and send_type                                        */
/*****************************************************************************/
#define AP_NONE                           0x00

/*****************************************************************************/
/* sync_level                                                                */
/*****************************************************************************/
#define AP_CONFIRM_SYNC_LEVEL             0x01
#define AP_CONFIRM                        0x01                         /*IBM1*/
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_SYNCPT                         0x02                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* security                                                                  */
/*****************************************************************************/
#define AP_SAME                           0x01
#define AP_PGM                            0x02
#define AP_STRONG                         0x03
#define AP_PROXY                          0x80                         /*5178*/
#define AP_PROXY_SAME                     0x81                         /*5178*/
#define AP_PROXY_PGM                      0x82                         /*5178*/
#define AP_PROXY_STRONG                   0x83                         /*5178*/

/*****************************************************************************/
/* dealloc_type and ptr_type                                                 */
/*****************************************************************************/
#define AP_SYNC_LEVEL                     0x00

/*****************************************************************************/
/* dealloc_type and ptr_type                                                 */
/*****************************************************************************/
#define AP_FLUSH                          0x01
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_CONFIRM_TYPE                   0x0B                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* dealloc_type                                                              */
/*****************************************************************************/
#define AP_ABEND_PROG                     0x02
#define AP_ABEND_SVC                      0x03
#define AP_ABEND_TIMER                    0x04
#define AP_ABEND                          0x05
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_TP_NOT_AVAIL_RETRY             0x06                         /*SYNC*/
#define AP_TP_NOT_AVAIL_NO_RETRY          0x07                         /*SYNC*/
#define AP_TPN_NOT_RECOGNIZED             0x08                         /*SYNC*/
#define AP_PIP_DATA_NOT_ALLOWED           0x09                         /*SYNC*/
#define AP_PIP_DATA_INCORRECT             0x0A                         /*SYNC*/
#define AP_RESOURCE_FAILURE_NO_RETRY      0x0C                         /*SYNC*/
#define AP_CONV_TYPE_MISMATCH             0x0D                         /*SYNC*/
#define AP_SYNC_LVL_NOT_SUPPORTED         0x0E                         /*SYNC*/
#define AP_SECURITY_PARAMS_INVALID        0x0F                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* locks                                                                     */
/*****************************************************************************/
#define AP_SHORT                          0x00
#define AP_LONG                           0x01

#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
/************************************************************************SYNC*/
/* data_type                                                            *SYNC*/
/************************************************************************SYNC*/
#define AP_APPLICATION                    0x00                         /*SYNC*/
#define AP_USER_CONTROL_DATA              0x01                         /*SYNC*/
#define AP_PS_HEADER                      0x02                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* what_rcvd                                                                 */
/*****************************************************************************/
#define AP_DATA                          APPC_FLIPI(0x0001)     /* X'0001'   */
#define AP_DATA_COMPLETE                 APPC_FLIPI(0x0002)     /* X'0002'   */
#define AP_NOT_DATA                      APPC_FLIPI(0x0003)     /* X'0003'   */ /*APOR*/
#define AP_DATA_INCOMPLETE               APPC_FLIPI(0x0004)     /* X'0004'   */
#define AP_SEND                          APPC_FLIPI(0x0100)     /* X'0100'   */
#define AP_CONFIRM_WHAT_RECEIVED         APPC_FLIPI(0x0200)     /* X'0200'   */
#define AP_CONFIRM_SEND                  APPC_FLIPI(0x0300)     /* X'0300'   */
#define AP_CONFIRM_DEALLOCATE            APPC_FLIPI(0x0400)     /* X'0400'   */

#define AP_DATA_COMPLETE_SEND            APPC_FLIPI(0x0102)     /* X'0102'   */
#define AP_DATA_COMPLETE_CONFIRM         APPC_FLIPI(0x0202)     /* X'0202'   */
#define AP_DATA_COMPLETE_CONFIRM_SEND    APPC_FLIPI(0x0302)     /* X'0302'   */
#define AP_DATA_COMPLETE_CONFIRM_DEALL   APPC_FLIPI(0x0402)     /* X'0402'   */

#define AP_DATA_SEND                     APPC_FLIPI(0x0101)     /* X'0101'   */
#define AP_DATA_CONFIRM                  APPC_FLIPI(0x0201)     /* X'0201'   */
#define AP_DATA_CONFIRM_SEND             APPC_FLIPI(0x0301)     /* X'0301'   */
#define AP_DATA_CONFIRM_DEALLOCATE       APPC_FLIPI(0x0401)     /* X'0401'   */

#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_USER_CONTROL_DATA_COMPLETE    APPC_FLIPI(0x0008) /* X'0008'  *SYNC*/
#define AP_USER_CONTROL_DATA_INCOMPLETE  APPC_FLIPI(0x0010) /* X'0010'  *SYNC*/
#define AP_PS_HEADER_COMPLETE            APPC_FLIPI(0x0020) /* X'0020'  *SYNC*/
#define AP_PS_HEADER_INCOMPLETE          APPC_FLIPI(0x0040) /* X'0040'  *SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* fill                                                                      */
/*****************************************************************************/
#define AP_BUFFER                         0x00
#define AP_LL                             0x01

/*****************************************************************************/
/* rtn_ctl                                                                   */
/*****************************************************************************/
#define AP_WHEN_SESSION_ALLOCATED         0x00
#define AP_IMMEDIATE                      0x01
#define AP_WHEN_SESSION_FREE              0x02
#define AP_WHEN_CONWINNER_ALLOCATED       0x03                         /*ES10*/
#define AP_WHEN_CONV_GROUP_ALLOCATED      0x04                         /*ES10*/

/*****************************************************************************/
/* err_type                                                                  */
/*****************************************************************************/
#define AP_PROG                           0x00
#define AP_SVC                            0x01
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_BACKOUT_NO_RESYNC              0x02                         /*SYNC*/
#define AP_BACKOUT_RESYNC                 0x03                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* send_type                                                                 */
/*****************************************************************************/
#define AP_SEND_DATA_FLUSH                0x01
#define AP_SEND_DATA_CONFIRM              0x02
#define AP_SEND_DATA_P_TO_R_FLUSH         0x03
#define AP_SEND_DATA_P_TO_R_SYNC_LEVEL    0x04
#define AP_SEND_DATA_DEALLOC_FLUSH        0x05
#define AP_SEND_DATA_DEALLOC_SYNC_LEVEL   0x06
#define AP_SEND_DATA_DEALLOC_ABEND        0x07
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
#define AP_SEND_DATA_P_TO_R_CONFIRM       0x08                         /*SYNC*/
#define AP_SEND_DATA_DEALLOC_CONFIRM      0x09                         /*SYNC*/
#endif                                                                 /*SYNC*/

/*****************************************************************************/
/* err_dir                                                                   */
/*****************************************************************************/
#define  AP_RCV_DIR_ERROR                 0x00
#define  AP_SEND_DIR_ERROR                0x01

/*****************************************************************************/
/* end_type                                                                  */
/*****************************************************************************/
#define AP_SOFT                           0x00
#define AP_HARD                           0x01

/*****************************************************************************/
/* conv_state                                                                */
/*****************************************************************************/
#define AP_RESET_STATE            1
#define AP_SEND_STATE             2
#define AP_RECEIVE_STATE          3
#define AP_CONFIRM_STATE          4
#define AP_CONFIRM_SEND_STATE     5
#define AP_CONFIRM_DEALL_STATE    6
#define AP_PEND_POST_STATE        7
#define AP_PEND_DEALL_STATE       8
#define AP_END_CONV_STATE         9
#define AP_SEND_PENDING_STATE    10

#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
/************************************************************************SYNC*/
/* values for type parameter on implied forget callback                 *SYNC*/
/************************************************************************SYNC*/
#define AP_DATA_FLOW                      0x00                         /*SYNC*/
#define AP_UNBIND                         0x01                         /*SYNC*/
#define AP_FAILURE                        0x02                         /*SYNC*/
                                                                       /*SYNC*/
#endif                                                                 /*SYNC*/

/************************************************************************SYNC*/
/* extension bit for the opext field                                    *SYNC*/
/************************************************************************SYNC*/
#define AP_EXTD_VCB                       0x80                    /*5178*SYNC*/

/* ========================================================================= */
/*****************************************************************************/
/* ------------------------- vcb structures -------------------------------- */
/*****************************************************************************/

/*****************************************************************************/
/* common vcb header                                                         */
/*****************************************************************************/
struct appc_hdr
{
  unsigned short opcode;
  unsigned char  opext;
  unsigned char  reserv2;
  unsigned short primary_rc;
  unsigned long  secondary_rc;
};

/*****************************************************************************/
/* control vcbs                                                              */
/*****************************************************************************/
struct tp_started
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     lu_alias[8];
  unsigned char     tp_id[8];
  unsigned char     tp_name[64];
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     syncpoint_rqd;  /* present if opext & AP_EXTD_VCB   *SYNC*/
                                    /* AP_NO                            *SYNC*/
                                    /* AP_YES                           *SYNC*/
#endif                                                                 /*SYNC*/
};


struct receive_allocate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_name[64];
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     sync_level;         /* AP_NONE                           */
                                        /* AP_CONFIRM_SYNC_LEVEL             */
                                        /* AP_SYNCPT                    *SYNC*/
  unsigned char     conv_type;          /* AP_BASIC_CONVERSATION             */
                                        /* AP_MAPPED_CONVERSATION            */
  unsigned char     user_id[10];
  unsigned char     lu_alias[8];
  unsigned char     plu_alias[8];
  unsigned char     mode_name[8];
  unsigned char     reserv3[2];
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned char     fqplu_name[17];     /* fully qualified lu name      *ES10*/
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     pip_incoming;       /* Supplied:                    *SYNC*/
                                        /*   AP_NO:  TP does not accept *SYNC*/
                                        /*           PIP data           *SYNC*/
                                        /*   AP_YES: TP does accept PIP *SYNC*/
                                        /*           data               *SYNC*/
                                        /* Returned:                    *SYNC*/
                                        /*   AP_NO:  PIP data not       *SYNC*/
                                        /*           available          *SYNC*/
                                        /*   AP_YES: PIP data available *SYNC*/
  unsigned char     syncpoint_rqd;      /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     reserv4[3];                                        /*SYNC*/
#else                                                                  /*SYNC*/
  unsigned char     reserv4[5];
#endif                                                                 /*SYNC*/
};


struct tp_ended
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned char     type;               /* AP_SOFT                      *9997*/
                                        /* AP_HARD                           */
};


/*****************************************************************************/
/* mapped conversation vcbs                                                  */
/*****************************************************************************/
struct mc_allocate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
  unsigned char     sync_level;         /* AP_NONE                           */
                                        /* AP_CONFIRM_SYNC_LEVEL             */
                                        /* AP_SYNCPT                    *SYNC*/
  unsigned char     reserv4[2];
  unsigned char     rtn_ctl;            /* AP_WHEN_SESSION_ALLOCATED         */
                                        /* AP_IMMEDIATE                      */
                                        /* AP_WHEN_SESSION_FREE              */
                                        /* AP_WHEN_CONWINNER_ALLOCATED  *ES10*/
                                        /* AP_WHEN_CONV_GROUP_ALLOCATED *ES10*/
  unsigned char     reserv5;
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned long     sense_data;         /* alloc failure sense data     *ES10*/
  unsigned char     plu_alias[8];
  unsigned char     mode_name[8];
  unsigned char     tp_name[64];
  unsigned char     security;           /* AP_NONE                           */
                                        /* AP_SAME                           */
                                        /* AP_PGM                            */
                                        /* AP_PROXY_NONE                *5178*/
                                        /* AP_PROXY_SAME                *5178*/
                                        /* AP_PROXY_PGM                 *5178*/
  unsigned char     reserv6[11];
  unsigned char     pwd[10];
  unsigned char     user_id[10];
  unsigned short    pip_dlen;
  unsigned char far *pip_dptr;
  unsigned char     reserv7;            /*CPIC* reserved for NS/2 compat.    */
  unsigned char     fqplu_name[17];     /*CPIC* fully qualified PLU name     */
  unsigned char     reserv8[8];         /*CPIC* reduced this from 26 to 8    */
#ifdef WIN32
  LPWSTR            proxy_user;         /* present if opext&AP_EXTD_VCB *5178*/
  LPWSTR            proxy_domain;       /* present if opext&AP_EXTD_VCB *5178*/
  unsigned char     reserv9[16];        /* present if opext&AP_EXTD_VCB *5178*/
#endif
};


struct mc_confirm
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
};


struct mc_confirmed
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct mc_deallocate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
  unsigned char     dealloc_type;       /* AP_SYNC_LEVEL                     */
                                        /* AP_FLUSH                          */
                                        /* AP_CONFIRM_TYPE              *SYNC*/
                                        /* AP_ABEND                          */
                                        /* AP_TP_NOT_AVAIL_RETRY        *SYNC*/
                                        /* AP_TP_NOT_AVAIL_NO_RETRY     *SYNC*/
                                        /* AP_TPN_NOT_RECOGNIZED        *SYNC*/
                                        /* AP_PIP_DATA_NOT_ALLOWED      *SYNC*/
                                        /* AP_PIP_DATA_INCORRECT        *SYNC*/
                                        /* AP_RESOURCE_FAILURE_NO_RETRY *SYNC*/
                                        /* AP_CONV_TYPE_MISMATCH        *SYNC*/
                                        /* AP_SYNC_LVL_NOT_SUPPORTED    *SYNC*/
                                        /* AP_SECURITY_PARAMS_INVALID   *SYNC*/
  unsigned char     reserv4[2];
  unsigned char     reserv5[4];
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  void       (WINAPI *callback)();      /* present if opext&AP_EXTD_VCB *SYNC*/
  void             *correlator;         /* present if opext&AP_EXTD_VCB *SYNC*/
  unsigned char     reserv6[4];         /* present if opext&AP_EXTD_VCB *SYNC*/
#endif                                                                 /*SYNC*/
};


struct mc_flush
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct mc_get_attributes
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
  unsigned char     sync_level;         /* AP_NONE                           */
                                        /* AP_CONFIRM_SYNC_LEVEL             */
                                        /* AP_SYNCPT                    *SYNC*/
  unsigned char     mode_name[8];
  unsigned char     net_name[8];
  unsigned char     lu_name[8];
  unsigned char     lu_alias[8];
  unsigned char     plu_alias[8];
  unsigned char     plu_un_name[8];
  unsigned char     reserv4[2];
  unsigned char     fqplu_name[17];
  unsigned char     reserv5;
  unsigned char     user_id[10];
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned char     conv_corr_len;      /* conversation correlator lgth *ES10*/
  unsigned char     conv_corr[8];       /* conversation correlator      *ES10*/
  unsigned char     reserv6[13];
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     luw_id[26];          /* present if opext&AP_EXTD_VCB*SYNC*/
  unsigned char     sess_id[8];          /* present if opext&AP_EXTD_VCB*SYNC*/
#endif                                                                 /*SYNC*/
};


struct mc_prepare_to_receive
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     ptr_type;           /* AP_SYNC_LEVEL                     */
                                        /* AP_FLUSH                          */
                                        /* AP_CONFIRM_TYPE              *SYNC*/
  unsigned char     locks;              /* AP_SHORT                          */
                                        /* AP_LONG                           */
};


struct mc_receive_and_post
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv5;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char far *sema;
  unsigned char     reserv6;
};


struct mc_receive_and_wait
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_SEND                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv5;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char     reserv6[5];
};


struct mc_receive_immediate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_SEND                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv5;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char     reserv6[5];
};


struct mc_request_to_send
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct mc_send_conversation                                            /*ES10*/
{                                                                      /*ES10*/
  unsigned short    opcode;                                            /*ES10*/
  unsigned char     opext;                                             /*ES10*/
  unsigned char     reserv2;                                           /*ES10*/
  unsigned short    primary_rc;                                        /*ES10*/
  unsigned long     secondary_rc;                                      /*ES10*/
  unsigned char     tp_id[8];                                          /*ES10*/
  unsigned char     reserv3[8];                                        /*ES10*/
  unsigned char     rtn_ctl;            /* AP_WHEN_SESSION_ALLOCATED    *ES10*/
                                        /* AP_IMMEDIATE                 *ES10*/
                                        /* AP_WHEN_SESSION_FREE         *ES10*/
                                        /* AP_WHEN_CONWINNER_ALLOCATED  *ES10*/
                                        /* AP_WHEN_CONV_GROUP_ALLOCATED *ES10*/
  unsigned char     reserv4;                                           /*ES10*/
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned long     sense_data;         /* alloc failure sense data     *ES10*/
  unsigned char     plu_alias[8];                                      /*ES10*/
  unsigned char     mode_name[8];                                      /*ES10*/
  unsigned char     tp_name[64];                                       /*ES10*/
  unsigned char     security;           /* AP_NONE                      *ES10*/
                                        /* AP_SAME                      *ES10*/
                                        /* AP_PGM                       *ES10*/
  unsigned char     reserv5[11];                                       /*ES10*/
  unsigned char     pwd[10];                                           /*ES10*/
  unsigned char     user_id[10];                                       /*ES10*/
  unsigned short    pip_dlen;                                          /*ES10*/
  unsigned char far *pip_dptr;                                         /*ES10*/
  unsigned char     reserv6;                                           /*ES10*/
  unsigned char     fqplu_name[17];                                    /*ES10*/
  unsigned char     reserv7[8];                                        /*ES10*/
  unsigned short    dlen;                                              /*ES10*/
  unsigned char far *dptr;                                             /*ES10*/
};                                                                     /*ES10*/


struct mc_send_data
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     data_type;           /* type of data to be sent     *SYNC*/
                                         /* AP_APPLICATION              *SYNC*/
                                         /* AP_USER_CONTROL_DATA        *SYNC*/
                                         /* AP_PS_HEADER                *SYNC*/
#else                                                                  /*SYNC*/
  unsigned char     reserv3;
#endif                                                                 /*SYNC*/
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char     type;               /* AP_SEND_DATA_FLUSH                */
                                        /* AP_SEND_DATA_CONFIRM              */
                                        /* AP_SEND_DATA_P_TO_R_FLUSH         */
                                        /* AP_SEND_DATA_P_TO_R_SYNC_LEVEL    */
                                        /* AP_SEND_DATA_P_TO_R_CONFIRM  *SYNC*/
                                        /* AP_SEND_DATA_DEALLOC_FLUSH        */
                                        /* AP_SEND_DATA_DEALLOC_SYNC_LEVEL   */
                                        /* AP_SEND_DATA_DEALLOC_CONFIRM *SYNC*/
                                        /* AP_SEND_DATA_DEALLOC_ABEND        */
  unsigned char     reserv4;
};


struct mc_send_error
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     err_type;            /* type of error               *SYNC*/
                                         /* AP_PROG                     *SYNC*/
                                         /* AP_BACKOUT_NO_RESYNC        *SYNC*/
                                         /* AP_BACKOUT_RESYNC           *SYNC*/
#else                                                                  /*SYNC*/
  unsigned char     reserv3;
#endif                                                                 /*SYNC*/
  unsigned char     err_dir;            /* AP_RCV_DIR_ERROR                  */
                                        /* AP_SEND_DIR_ERROR                 */
  unsigned char     reserv4;
  unsigned short    log_dlen;                                          /*SELD*/
  unsigned char far *log_dptr;                                         /*SELD*/
};

struct mc_test_rts
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
};

struct mc_test_rts_and_post                                            /*RPRP*/
{                                                                      /*RPRP*/
  unsigned short    opcode;                                            /*RPRP*/
  unsigned char     opext;                                             /*RPRP*/
  unsigned char     reserv2;                                           /*RPRP*/
  unsigned short    primary_rc;                                        /*RPRP*/
  unsigned long     secondary_rc;                                      /*RPRP*/
  unsigned char     tp_id[8];                                          /*RPRP*/
  unsigned long     conv_id;                                           /*RPRP*/
  unsigned char     reserv3;                                           /*RPRP*/
  unsigned long     handle;                                            /*RPRP*/
};                                                                     /*RPRP*/

#ifdef WIN32                                                           /*APOR*/
struct mc_post_on_receipt                                              /*APOR*/
{                                                                      /*APOR*/
  unsigned short        opcode;                                        /*APOR*/
  unsigned char         opext;                                         /*APOR*/
  unsigned char         reserv1;                                       /*APOR*/
  unsigned short        primary_rc;                                    /*APOR*/
  unsigned long         secondary_rc;                                  /*APOR*/
  unsigned char         tp_id[8];                                      /*APOR*/
  unsigned long         conv_id;                                       /*APOR*/
  unsigned short        reserv2;                                       /*APOR*/
  unsigned char         reserv3;                                       /*APOR*/
  unsigned char         reserv4;                                       /*APOR*/
  unsigned short        max_len;                                       /*APOR*/
  unsigned short        reserv5;                                       /*APOR*/
  unsigned char far *   reserv6;                                       /*APOR*/
  unsigned char         reserv7[5];                                    /*APOR*/
  unsigned long         sema;                                          /*APOR*/
};                                                                     /*APOR*/
#endif                                                                 /*APOR*/

struct mc_receive_log_data                                             /*RELD*/
{                                                                      /*RELD*/
  unsigned short        opcode;                                        /*RELD*/
  unsigned char         opext;                                         /*RELD*/
  unsigned char         reserv1;                                       /*RELD*/
  unsigned short        primary_rc;                                    /*RELD*/
  unsigned long         secondary_rc;                                  /*RELD*/
  unsigned char         tp_id[8];                                      /*RELD*/
  unsigned long         conv_id;                                       /*RELD*/
  unsigned short        log_dlen;                                      /*RELD*/
  unsigned char far *   log_dptr;                                      /*RELD*/
};                                                                     /*RELD*/

/*****************************************************************************/
/* basic conversation vcbs                                                   */
/*****************************************************************************/
struct allocate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     conv_type;          /* AP_BASIC_CONVERSATION             */
                                        /* AP_MAPPED_CONVERSATION            */
  unsigned char     sync_level;         /* AP_NONE                           */
                                        /* AP_CONFIRM_SYNC_LEVEL             */
                                        /* AP_SYNCPT                    *SYNC*/
  unsigned char     reserv3[2];
  unsigned char     rtn_ctl;            /* AP_WHEN_SESSION_ALLOCATED         */
                                        /* AP_IMMEDIATE                      */
                                        /* AP_WHEN_SESSION_FREE              */
                                        /* AP_WHEN_CONWINNER_ALLOCATED  *ES10*/
                                        /* AP_WHEN_CONV_GROUP_ALLOCATED *ES10*/
  unsigned char     reserv4;
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned long     sense_data;         /* alloc failure sense data     *ES10*/
  unsigned char     plu_alias[8];
  unsigned char     mode_name[8];
  unsigned char     tp_name[64];
  unsigned char     security;           /* AP_NONE                           */
                                        /* AP_SAME                           */
                                        /* AP_PGM                            */
                                        /* AP_PROXY_NONE                *5178*/
                                        /* AP_PROXY_SAME                *5178*/
                                        /* AP_PROXY_PGM                 *5178*/
  unsigned char     reserv5[11];
  unsigned char     pwd[10];
  unsigned char     user_id[10];
  unsigned short    pip_dlen;
  unsigned char far *pip_dptr;
  unsigned char     reserv7;            /*CPIC* for NS/2 compatability       */
  unsigned char     fqplu_name[17];     /*CPIC* fully qualified PLU name     */
  unsigned char     reserv8[8];         /*CPIC* reduced this from 26 to 8    */
#ifdef WIN32
  LPWSTR            proxy_user;         /* present if opext&AP_EXTD_VCB *5178*/
  LPWSTR            proxy_domain;       /* present if opext&AP_EXTD_VCB *5178*/
  unsigned char     reserv9[16];        /* present if opext&AP_EXTD_VCB *5178*/
#endif
};


struct confirm
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
};


struct confirmed
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct deallocate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
  unsigned char     dealloc_type;       /* AP_SYNC_LEVEL                     */
                                        /* AP_FLUSH                          */
                                        /* AP_CONFIRM_TYPE              *SYNC*/
                                        /* AP_ABEND_PROG                     */
                                        /* AP_ABEND_SVC                      */
                                        /* AP_ABEND_TIMER                    */
                                        /* AP_TP_NOT_AVAIL_RETRY        *SYNC*/
                                        /* AP_TP_NOT_AVAIL_NO_RETRY     *SYNC*/
                                        /* AP_TPN_NOT_RECOGNIZED        *SYNC*/
                                        /* AP_PIP_DATA_NOT_ALLOWED      *SYNC*/
                                        /* AP_PIP_DATA_INCORRECT        *SYNC*/
                                        /* AP_RESOURCE_FAILURE_NO_RETRY *SYNC*/
                                        /* AP_CONV_TYPE_MISMATCH        *SYNC*/
                                        /* AP_SYNC_LVL_NOT_SUPPORTED    *SYNC*/
                                        /* AP_SECURITY_PARAMS_INVALID   *SYNC*/
  unsigned short    log_dlen;
  unsigned char far *log_dptr;
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  void       (WINAPI *callback)();      /* present if opext&AP_EXTD_VCB *SYNC*/
  void             *correlator;         /* present if opext&AP_EXTD_VCB *SYNC*/
  unsigned char     reserv6[4];         /* present if opext&AP_EXTD_VCB *SYNC*/
#endif                                                                 /*SYNC*/
};


struct flush
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct get_attributes
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
  unsigned char     sync_level;         /* AP_NONE                           */
                                        /* AP_CONFIRM_SYNC_LEVEL             */
                                        /* AP_SYNCPT                    *SYNC*/
  unsigned char     mode_name[8];
  unsigned char     net_name[8];
  unsigned char     lu_name[8];
  unsigned char     lu_alias[8];
  unsigned char     plu_alias[8];
  unsigned char     plu_un_name[8];
  unsigned char     reserv4[2];
  unsigned char     fqplu_name[17];
  unsigned char     reserv5;
  unsigned char     user_id[10];
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned char     conv_corr_len;      /* conversation correlator lgth *ES10*/
  unsigned char     conv_corr[8];       /* conversation correlator      *ES10*/
  unsigned char     reserv6[13];
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     luw_id[26];          /* present if opext&AP_EXTD_VCB*SYNC*/
  unsigned char     sess_id[8];          /* present if opext&AP_EXTD_VCB*SYNC*/
#endif                                                                 /*SYNC*/
};


struct prepare_to_receive
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     ptr_type;           /* AP_SYNC_LEVEL                     */
                                        /* AP_FLUSH                          */
                                        /* AP_CONFIRM_TYPE              *SYNC*/
  unsigned char     locks;              /* AP_SHORT                          */
                                        /* AP_LONG                           */
};


struct receive_and_post
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_DATA_COMPLETE                  */
                                        /* AP_DATA_INCOMPLETE                */
                                        /* AP_SEND                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     fill;               /* AP_BUFFER                         */
                                        /* AP_LL                             */
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char far *sema;
  unsigned char     reserv5;
};


struct receive_and_wait
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_DATA_COMPLETE                  */
                                        /* AP_DATA_INCOMPLETE                */
                                        /* AP_SEND                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     fill;               /* AP_BUFFER                         */
                                        /* AP_LL                             */
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char     reserv5[5];
};


struct receive_immediate
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned short    what_rcvd;          /* AP_NONE                           */
                                        /* AP_DATA                           */
                                        /* AP_DATA_COMPLETE                  */
                                        /* AP_DATA_INCOMPLETE                */
                                        /* AP_SEND                           */
                                        /* AP_CONFIRM_WHAT_RECEIVED          */
                                        /* AP_CONFIRM_SEND                   */
                                        /* AP_CONFIRM_DEALLOCATE             */
  unsigned char     rtn_status;         /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     fill;               /* AP_BUFFER                         */
                                        /* AP_LL                             */
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     reserv4;
  unsigned short    max_len;
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char     reserv5[5];
};


struct request_to_send
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
};


struct send_conversation                                               /*ES10*/
{                                                                      /*ES10*/
  unsigned short    opcode;                                            /*ES10*/
  unsigned char     opext;                                             /*ES10*/
  unsigned char     reserv2;                                           /*ES10*/
  unsigned short    primary_rc;                                        /*ES10*/
  unsigned long     secondary_rc;                                      /*ES10*/
  unsigned char     tp_id[8];                                          /*ES10*/
  unsigned char     reserv3[8];                                        /*ES10*/
  unsigned char     rtn_ctl;            /* AP_WHEN_SESSION_ALLOCATED    *ES10*/
                                        /* AP_IMMEDIATE                 *ES10*/
                                        /* AP_WHEN_SESSION_FREE         *ES10*/
                                        /* AP_WHEN_CONWINNER_ALLOCATED  *ES10*/
                                        /* AP_WHEN_CONV_GROUP_ALLOCATED *ES10*/
  unsigned char     reserv4;                                           /*ES10*/
  unsigned long     conv_group_id;      /* conversation group id        *ES10*/
  unsigned long     sense_data;         /* allocation failure sense data*ES10*/
  unsigned char     plu_alias[8];                                      /*ES10*/
  unsigned char     mode_name[8];                                      /*ES10*/
  unsigned char     tp_name[64];                                       /*ES10*/
  unsigned char     security;           /* AP_NONE                      *ES10*/
                                        /* AP_SAME                      *ES10*/
                                        /* AP_PGM                       *ES10*/
  unsigned char     reserv5[11];                                       /*ES10*/
  unsigned char     pwd[10];                                           /*ES10*/
  unsigned char     user_id[10];                                       /*ES10*/
  unsigned short    pip_dlen;                                          /*ES10*/
  unsigned char far *pip_dptr;                                         /*ES10*/
  unsigned char     reserv6;                                           /*ES10*/
  unsigned char     fqplu_name[17];                                    /*ES10*/
  unsigned char     reserv7[8];                                        /*ES10*/
  unsigned short    dlen;                                              /*ES10*/
  unsigned char far *dptr;                                             /*ES10*/
};                                                                     /*ES10*/


struct send_data
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     data_type;           /* type of data to be sent     *SYNC*/
                                         /* AP_APPLICATION              *SYNC*/
                                         /* AP_USER_CONTROL_DATA        *SYNC*/
                                         /* AP_PS_HEADER                *SYNC*/
#else                                                                  /*SYNC*/
  unsigned char     reserv3;
#endif                                                                 /*SYNC*/
  unsigned short    dlen;
  unsigned char far *dptr;
  unsigned char type;                   /* AP_SEND_DATA_FLUSH                */
                                        /* AP_SEND_DATA_CONFIRM              */
                                        /* AP_SEND_DATA_P_TO_R_FLUSH         */
                                        /* AP_SEND_DATA_P_TO_R_SYNC_LEVEL    */
                                        /* AP_SEND_DATA_P_TO_R_CONFIRM  *SYNC*/
                                        /* AP_SEND_DATA_DEALLOC_FLUSH        */
                                        /* AP_SEND_DATA_DEALLOC_SYNC_LEVEL   */
                                        /* AP_SEND_DATA_DEALLOC_CONFIRM *SYNC*/
                                        /* AP_SEND_DATA_DEALLOC_ABEND        */
  unsigned char     reserv4;
};


struct send_error
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     rts_rcvd;           /* AP_NO                             */
                                        /* AP_YES                            */
  unsigned char     err_type;           /* AP_PROG                           */
                                        /* AP_SVC                            */
                                        /* AP_BACKOUT_NO_RESYNC         *SYNC*/
                                        /* AP_BACKOUT_RESYNC            *SYNC*/
  unsigned char     err_dir;            /* AP_RCV_DIR_ERROR                  */
                                        /* AP_SEND_DIR_ERROR                 */
  unsigned char     reserv3;
  unsigned short    log_dlen;
  unsigned char far *log_dptr;
};


struct test_rts
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     reserv3;
};

struct test_rts_and_post                                               /*RPRP*/
{                                                                      /*RPRP*/
  unsigned short    opcode;                                            /*RPRP*/
  unsigned char     opext;                                             /*RPRP*/
  unsigned char     reserv2;                                           /*RPRP*/
  unsigned short    primary_rc;                                        /*RPRP*/
  unsigned long     secondary_rc;                                      /*RPRP*/
  unsigned char     tp_id[8];                                          /*RPRP*/
  unsigned long     conv_id;                                           /*RPRP*/
  unsigned char     reserv3;                                           /*RPRP*/
  unsigned long     handle;                                            /*RPRP*/
};                                                                     /*RPRP*/

#ifdef WIN32                                                           /*APOR*/
struct post_on_receipt                                                 /*APOR*/
{                                                                      /*APOR*/
  unsigned short        opcode;                                        /*APOR*/
  unsigned char         opext;                                         /*APOR*/
  unsigned char         reserv1;                                       /*APOR*/
  unsigned short        primary_rc;                                    /*APOR*/
  unsigned long         secondary_rc;                                  /*APOR*/
  unsigned char         tp_id[8];                                      /*APOR*/
  unsigned long         conv_id;                                       /*APOR*/
  unsigned short        reserv2;                                       /*APOR*/
  unsigned char         fill;                                          /*APOR*/
  unsigned char         reserv4;                                       /*APOR*/
  unsigned short        max_len;                                       /*APOR*/
  unsigned short        reserv5;                                       /*APOR*/
  unsigned char far *   reserv6;                                       /*APOR*/
  unsigned char         reserv7[5];                                    /*APOR*/
  unsigned long         sema;                                          /*APOR*/
};                                                                     /*APOR*/
#endif                                                                 /*APOR*/

struct receive_log_data                                                /*RELD*/
{                                                                      /*RELD*/
  unsigned short        opcode;                                        /*RELD*/
  unsigned char         opext;                                         /*RELD*/
  unsigned char         reserv1;                                       /*RELD*/
  unsigned short        primary_rc;                                    /*RELD*/
  unsigned long         secondary_rc;                                  /*RELD*/
  unsigned char         tp_id[8];                                      /*RELD*/
  unsigned long         conv_id;                                       /*RELD*/
  unsigned short        log_dlen;                                      /*RELD*/
  unsigned char far *   log_dptr;                                      /*RELD*/
};                                                                     /*RELD*/


/*****************************************************************************/
/* type independent vcbs                                                     */
/*****************************************************************************/
typedef struct luw_id_overlay                                          /*ES10*/
{                                                                      /*ES10*/
  unsigned char     fqlu_name_len;                                     /*ES10*/
  unsigned char     fqlu_name[17];                                     /*ES10*/
  unsigned char     instance[6];                                       /*ES10*/
  unsigned char     sequence[2];                                       /*ES10*/
} LUW_ID_OVERLAY;                                                      /*ES10*/
                                                                       /*ES10*/
struct get_tp_properties                                               /*ES10*/
{                                                                      /*ES10*/
  unsigned short    opcode;                                            /*ES10*/
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     opext;                                             /*SYNC*/
  unsigned char     reserv2;                                           /*SYNC*/
#else                                                                  /*SYNC*/
  unsigned char     reserv2[2];                                        /*ES10*/
#endif                                                                 /*SYNC*/
  unsigned short    primary_rc;                                        /*ES10*/
  unsigned long     secondary_rc;                                      /*ES10*/
  unsigned char     tp_id[8];                                          /*ES10*/
  unsigned char     tp_name[64];                                       /*ES10*/
  unsigned char     lu_alias[8];                                       /*ES10*/
  unsigned char     luw_id[26];         /* Logical Unit of Work id      *ES10*/
  unsigned char     fqlu_name[17];      /* fully qualified LU name      *ES10*/
  unsigned char     reserv3[10];                                       /*ES10*/
  unsigned char     user_id[10];                                       /*ES10*/
#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
  unsigned char     prot_luw_id[26];    /* present if opext & AP_EXTD   *SYNC*/
#endif                                                                 /*SYNC*/
};                                                                     /*ES10*/

#ifdef SYNCPT_SUPPORT                                                  /*SYNC*/
struct set_tp_properties                                               /*SYNC*/
{                                                                      /*SYNC*/
  unsigned short    opcode;                                            /*SYNC*/
  unsigned char     opext;                                             /*SYNC*/
  unsigned char     reserv2;                                           /*SYNC*/
  unsigned short    primary_rc;                                        /*SYNC*/
  unsigned long     secondary_rc;                                      /*SYNC*/
  unsigned char     tp_id[8];                                          /*SYNC*/
  unsigned char     set_prot_id;        /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     new_prot_id;        /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     prot_id[26];                                       /*SYNC*/
  unsigned char     set_unprot_id;      /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     new_unprot_id;      /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     unprot_id[26];                                     /*SYNC*/
  unsigned char     set_user_id;        /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     reserv3;                                           /*SYNC*/
  unsigned char     user_id[10];                                       /*SYNC*/
  unsigned char     reserv4[10];                                       /*SYNC*/
};                                                                     /*SYNC*/
                                                                       /*SYNC*/
struct get_lu_status                                                   /*SYNC*/
{                                                                      /*SYNC*/
  unsigned short    opcode;                                            /*SYNC*/
  unsigned char     opext;                                             /*SYNC*/
  unsigned char     reserv2;                                           /*SYNC*/
  unsigned short    primary_rc;                                        /*SYNC*/
  unsigned long     secondary_rc;                                      /*SYNC*/
  unsigned char     tp_id[8];                                          /*SYNC*/
  unsigned char     plu_alias[8];                                      /*SYNC*/
  unsigned short    active_sess;                                       /*SYNC*/
  unsigned char     zero_sess;          /* AP_NO                        *SYNC*/
                                        /* AP_YES                       *SYNC*/
  unsigned char     reserv3[7];                                        /*SYNC*/
};                                                                     /*SYNC*/
#endif                                                                 /*SYNC*/

struct get_type
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     conv_type;          /* AP_BASIC_CONVERSATION             */
                                        /* AP_MAPPED_CONVERSATION            */
};


struct get_state
{
  unsigned short    opcode;
  unsigned char     opext;
  unsigned char     reserv2;
  unsigned short    primary_rc;
  unsigned long     secondary_rc;
  unsigned char     tp_id[8];
  unsigned long     conv_id;
  unsigned char     conv_state;                             /* AP_RESET etc. */
};



/************************************************************************IBM1*/
/* Add typedefs for OS/2 ES compatability.                              *IBM1*/
/************************************************************************IBM1*/
typedef struct tp_started            TP_STARTED;
typedef struct receive_allocate      RECEIVE_ALLOCATE;
typedef struct tp_ended              TP_ENDED;
typedef struct mc_allocate           MC_ALLOCATE;
typedef struct mc_confirm            MC_CONFIRM;
typedef struct mc_confirmed          MC_CONFIRMED;
typedef struct mc_deallocate         MC_DEALLOCATE;
typedef struct mc_flush              MC_FLUSH;
typedef struct mc_get_attributes     MC_GET_ATTRIBUTES;
typedef struct mc_prepare_to_receive MC_PREPARE_TO_RECEIVE;
typedef struct mc_receive_and_post   MC_RECEIVE_AND_POST;
typedef struct mc_receive_and_wait   MC_RECEIVE_AND_WAIT;
typedef struct mc_receive_immediate  MC_RECEIVE_IMMEDIATE;
typedef struct mc_request_to_send    MC_REQUEST_TO_SEND;
typedef struct mc_send_conversation  MC_SEND_CONVERSATION;
typedef struct mc_send_data          MC_SEND_DATA;
typedef struct mc_send_error         MC_SEND_ERROR;
typedef struct mc_test_rts           MC_TEST_RTS;
typedef struct mc_test_rts_and_post  MC_TEST_RTS_AND_POST;             /*RPRP*/
#ifdef WIN32                                                           /*APOR*/
typedef struct mc_post_on_receipt    MC_POST_ON_RECEIPT;               /*APOR*/
#endif                                                                 /*APOR*/
typedef struct mc_receive_log_data   MC_RECEIVE_LOG_DATA;              /*RELD*/
typedef struct allocate              ALLOCATE;
typedef struct confirm               CONFIRM;
typedef struct confirmed             CONFIRMED;
typedef struct deallocate            DEALLOCATE;
typedef struct flush                 FLUSH;
typedef struct get_attributes        GET_ATTRIBUTES;
typedef struct prepare_to_receive    PREPARE_TO_RECEIVE;
typedef struct receive_and_post      RECEIVE_AND_POST;
typedef struct receive_and_wait      RECEIVE_AND_WAIT;
typedef struct receive_immediate     RECEIVE_IMMEDIATE;
typedef struct request_to_send       REQUEST_TO_SEND;
typedef struct send_conversation     SEND_CONVERSATION;
typedef struct send_data             SEND_DATA;
typedef struct send_error            SEND_ERROR;
typedef struct test_rts              TEST_RTS;
typedef struct test_rts_and_post     TEST_RTS_AND_POST;                /*RPRP*/
#ifdef WIN32                                                           /*APOR*/
typedef struct post_on_receipt       POST_ON_RECEIPT;                  /*APOR*/
#endif                                                                 /*APOR*/
typedef struct receive_log_data      RECEIVE_LOG_DATA;                 /*RELD*/
typedef struct get_tp_properties     GET_TP_PROPERTIES;
typedef struct get_type              GET_TYPE;

/* ========================================================================= */
/*****************************************************************************/
/* ---------------------- APPC function prototypes ------------------------- */
/*****************************************************************************/

#ifdef WIN32                                                            /*W32*/
 #ifndef WINSNA                                                       /*WSNA2*/
  extern void pascal APPC(long);                                        /*W32*/
 #endif                                                               /*WSNA2*/
extern void pascal APPC_P(long);                                        /*W32*/
extern void pascal APPC_C(long);                                        /*W32*/
#else                                                                   /*W32*/
 #ifndef WINSNA                                                       /*WSNA2*/
  extern void pascal far _loadds APPC(long);                           /*1.1X*/
 #endif                                                               /*WSNA2*/
extern void pascal far _loadds APPC_P(long);                           /*1.1P*/
extern void pascal far _loadds APPC_C(long);
#endif                                                                  /*W32*/


/*****************************************************************************/
/* WinSNA function prototypes                                          *WSNA2*/
/*****************************************************************************/
#ifdef WINSNA


/*---------------------------------------------------------------------------*/
/* Windows APPC Extension Return Codes.                                              */
/*---------------------------------------------------------------------------*/

#define WAPPCALREADY         0xF000   /* An async call is already outstanding */
#define WAPPCINVALID         0xF001   /* Async Task Id is invalid             */
#define WAPPCCANCEL          0xF002   /* Blocking call was cancelled          */
#define WAPPCSYSNOTREADY     0xF003   /* Underlying subsystem not started     */
#define WAPPCVERNOTSUPPORTED 0xF004   /* Application version not supported    */


/*----------------------------------------------------------------------------*/
/* Api structre definitions                                                   */
/*----------------------------------------------------------------------------*/
#define WAPPCDESCRIPTION_LEN    127

typedef struct tagWAPPCDATA
{
  WORD    wVersion;
  char    szDescription[WAPPCDESCRIPTION_LEN+1];
} WAPPCDATA, * PWAPPCDATA, FAR * LPWAPPCDATA;


 extern void    WINAPI APPC(long);
 extern HANDLE  WINAPI WinAsyncAPPC( HWND, long);
 extern HANDLE  WINAPI WinAsyncAPPCEx( HANDLE, long);                  /*EVNT*/
 extern BOOL    WINAPI WinAPPCCleanup(void);
 extern BOOL    WINAPI WinAPPCIsBlocking(void);
 extern int     WINAPI WinAPPCCancelAsyncRequest( HANDLE );
 extern BOOL    WINAPI WinAPPCCancelBlockingCall(void);
 extern int     WINAPI WinAPPCStartup(WORD, LPWAPPCDATA);
 extern FARPROC WINAPI WinAPPCSetBlockingHook(FARPROC);
 extern BOOL    WINAPI WinAPPCUnhookBlockingHook(void);
 extern int     WINAPI GetAppcReturnCode (struct appc_hdr FAR * vpb,   /*GRC */
                                          UINT        buffer_length,
                                          unsigned char FAR * buffer_addr);

 #define WIN_APPC_ASYNC_COMPLETE_MESSAGE "WinAsyncAPPC"


#endif


/*************************************************************************W32*/
/* for Win32 environment, restore original packing mode                  *W32*/
/*************************************************************************W32*/
#ifdef WIN32                                                            /*W32*/
                                                                        /*W32*/
#pragma pack()                                                          /*W32*/
                                                                        /*W32*/
#endif                                                                  /*W32*/

#ifdef __cplusplus
}
#endif

/*****************************************************************************/
/* End ifndef APPC_C_INCLUDED *DSP2*                                         */
/*****************************************************************************/
#endif

/* winappc.h */
