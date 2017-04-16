/******************************************************************************/
/* lua_c.h   - include file for SNAP-IX LUA API.                              */
/* (C) Copyright Data Connection Ltd. 1990                                    */
/******************************************************************************/

/*****************************************************************************/
/* Change History                                                            */
/*                                                                           */
/*LUA*   15/05/91  LP  This file new for LUA support                         */
/*L030*  12/09/91  LP  Check for terminated apps in Windows environment      */
/*512S*  25/11/91  LP  Extend max # sessions allowed from 16 to 512 for OS/2 */
/*L055*  13/01/92  LP  Move error codes to rui.c to keep lua_c.h like EE file*/
/*W32*   30/03/92  AD  Win32 port                                            */
/*9999   11/08/93  PP  Fix LUA_INVALID_ADAPTED and add LUA_RESPONSE_ALREADY_ */
/*                     SENT                                                  */
/*9998   15/09/93  PP  Pull substructures out                                */
/*l110   16/12/93  PP  Add RUI_INIT status messages                          */
/*****************************************************************************/

#ifndef LUA_CH_INCLUDED
#define LUA_CH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*************************************************************************W32*/
/* define type conversion macros                                         *W32*/
/*************************************************************************W32*/
#define LUA_LO_UC(w)    ((unsigned char)(((unsigned short)(w)) & 0xFF)) /*W32*/
#define LUA_HI_UC(w)    ((unsigned char)(((unsigned short)(w) >> 8)  \
                            & 0xff))                                    /*W32*/
#define LUA_MAKUS(l, h) (((unsigned short)(l)) |                     \
                          ((unsigned short)(h)) << 8)                   /*W32*/
#define LUA_MAKUL(l, h) ((unsigned long)(((unsigned short)(l))|      \
                          ((unsigned long)((unsigned short)(h))) << 16))/*W32*/
#define LUA_LO_US(l)   ((unsigned short)(((unsigned long)(l)) & 0xFFFF))/*W32*/
#define LUA_HI_US(l)    ((unsigned short)(((unsigned long)(l) >> 16) \
                           & 0xffff))                                   /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* IF non-Intel THEN                                                     *W32*/
/*   set flipping to nop for now                                         *W32*/
/*   reverse order of bit fields                                         *W32*/
/*************************************************************************W32*/
#ifdef NON_INTEL_BYTE_ORDER                                             /*W32*/
#define LUA_FLIPI(X)  (X)                                               /*W32*/
#define LUA_FLIPL(X)  (X)                                               /*W32*/
#define LUA_FLIPRQD                                                     /*W32*/
                                                                        /*W32*/
/*************************************************************************W32*/
/* ELSE (Intel environment)                                              *W32*/
/*   define flipping macros                                              *W32*/
/*************************************************************************W32*/
#else                                                                   /*W32*/
#define LUA_FLIPI(X) LUA_MAKUS(LUA_HI_UC(X),LUA_LO_UC(X))               /*W32*/
#define LUA_FLIPL(X) LUA_MAKUL(LUA_FLIPI(LUA_HI_US(X)),           \
                                 LUA_FLIPI(LUA_LO_US(X)))               /*W32*/
#endif                                                                  /*W32*/


/*L055************************************************************************/
/*L055* Error codes moved to rui.c - 10 #defines deleted                     */
/*L055************************************************************************/

/*W32*************************************************************************/
/*W32* Make all constant definitions hardware independent                    */
/*W32*************************************************************************/

/*****************************************************************************/
/* LUA VERB TYPES                                                            */
/*****************************************************************************/
#define LUA_VERB_RUI                      LUA_FLIPI(0x5200)
#define LUA_VERB_SLI                      LUA_FLIPI(0x5200)

/*****************************************************************************/
/* LUA OPCODES ( RUI and SLI )                                               */
/*****************************************************************************/
#define LUA_OPCODE_RUI_INIT               LUA_FLIPI(0x0180)
#define LUA_OPCODE_RUI_TERM               LUA_FLIPI(0x0280)
#define LUA_OPCODE_RUI_READ               LUA_FLIPI(0x0380)
#define LUA_OPCODE_RUI_WRITE              LUA_FLIPI(0x0480)
#define LUA_OPCODE_RUI_PURGE              LUA_FLIPI(0x0580)
#define LUA_OPCODE_RUI_BID                LUA_FLIPI(0x0680)

#define LUA_OPCODE_SLI_OPEN               LUA_FLIPI(0x0100)
#define LUA_OPCODE_SLI_CLOSE              LUA_FLIPI(0x0200)
#define LUA_OPCODE_SLI_RECEIVE            LUA_FLIPI(0x0300)
#define LUA_OPCODE_SLI_SEND               LUA_FLIPI(0x0400)
#define LUA_OPCODE_SLI_PURGE              LUA_FLIPI(0x0500)
#define LUA_OPCODE_SLI_BID                LUA_FLIPI(0x0600)
#define LUA_OPCODE_SLI_BIND_ROUTINE       LUA_FLIPI(0x1100)
#define LUA_OPCODE_SLI_STSN_ROUTINE       LUA_FLIPI(0x1200)
#define LUA_OPCODE_SLI_CRV_ROUTINE        LUA_FLIPI(0x1300)

/*****************************************************************************/
/* LUA PRIMARY RETURN CODES                                                  */
/*****************************************************************************/
#define LUA_OK                            0x0000
#define LUA_PARAMETER_CHECK               LUA_FLIPI(0x0001)
#define LUA_STATE_CHECK                   LUA_FLIPI(0x0002)
#define LUA_SESSION_FAILURE               LUA_FLIPI(0x000F)
#define LUA_UNSUCCESSFUL                  LUA_FLIPI(0x0014)
#define LUA_NEGATIVE_RSP                  LUA_FLIPI(0x0018)
#define LUA_CANCELLED                     LUA_FLIPI(0x0021)
#define LUA_IN_PROGRESS                   LUA_FLIPI(0x0030)
#define LUA_STATUS                        LUA_FLIPI(0x0040)
#define LUA_COMM_SUBSYSTEM_ABENDED        LUA_FLIPI(0xF003)
#define LUA_COMM_SUBSYSTEM_NOT_LOADED     LUA_FLIPI(0xF004)
#define LUA_INVALID_VERB_SEGMENT          LUA_FLIPI(0xF008)
#define LUA_UNEXPECTED_DOS_ERROR          LUA_FLIPI(0xF011)
#define LUA_STACK_TOO_SMALL               LUA_FLIPI(0xF015)
#define LUA_INVALID_VERB                  0xFFFF

/*****************************************************************************/
/* LUA SECONDARY RETURN CODES                                                */
/*****************************************************************************/
#define LUA_SEC_RC_OK                     LUA_FLIPL(0x00000000)
#define LUA_INVALID_LUNAME                LUA_FLIPL(0x00000001)
#define LUA_BAD_SESSION_ID                LUA_FLIPL(0x00000002)
#define LUA_DATA_TRUNCATED                LUA_FLIPL(0x00000003)
#define LUA_BAD_DATA_PTR                  LUA_FLIPL(0x00000004)
#define LUA_DATA_SEG_LENGTH_ERROR         LUA_FLIPL(0x00000005)
#define LUA_RESERVED_FIELD_NOT_ZERO       LUA_FLIPL(0x00000006)
#define LUA_INVALID_POST_HANDLE           LUA_FLIPL(0x00000007)
#define LUA_PURGED                        LUA_FLIPL(0x0000000C)
#define LUA_BID_VERB_SEG_ERROR            LUA_FLIPL(0x0000000F)
#define LUA_NO_PREVIOUS_BID_ENABLED       LUA_FLIPL(0x00000010)
#define LUA_NO_DATA                       LUA_FLIPL(0x00000011)
#define LUA_BID_ALREADY_ENABLED           LUA_FLIPL(0x00000012)
#define LUA_VERB_RECORD_SPANS_SEGMENTS    LUA_FLIPL(0x00000013)
#define LUA_INVALID_FLOW                  LUA_FLIPL(0x00000014)
#define LUA_NOT_ACTIVE                    LUA_FLIPL(0x00000015)
#define LUA_VERB_LENGTH_INVALID           LUA_FLIPL(0x00000016)
#define LUA_REQUIRED_FIELD_MISSING        LUA_FLIPL(0x00000019)
#define LUA_READY                         LUA_FLIPL(0x00000030)
#define LUA_NOT_READY                     LUA_FLIPL(0x00000031)
#define LUA_INIT_COMPLETE                 LUA_FLIPL(0x00000032)
#define LUA_SESSION_END_REQUESTED         LUA_FLIPL(0x00000033)
#define LUA_NO_SLI_SESSION                LUA_FLIPL(0x00000034)
#define LUA_SESSION_ALREADY_OPEN          LUA_FLIPL(0x00000035)
#define LUA_INVALID_OPEN_INIT_TYPE        LUA_FLIPL(0x00000036)
#define LUA_INVALID_OPEN_DATA             LUA_FLIPL(0x00000037)
#define LUA_UNEXPECTED_SNA_SEQUENCE       LUA_FLIPL(0x00000038)
#define LUA_NEG_RSP_FROM_BIND_ROUTINE     LUA_FLIPL(0x00000039)
#define LUA_NEG_RSP_FROM_CRV_ROUTINE      LUA_FLIPL(0x0000003A)
#define LUA_NEG_RSP_FROM_STSN_ROUTINE     LUA_FLIPL(0x0000003B)
#define LUA_CRV_ROUTINE_REQUIRED          LUA_FLIPL(0x0000003C)
#define LUA_STSN_ROUTINE_REQUIRED         LUA_FLIPL(0x0000003D)
#define LUA_INVALID_OPEN_ROUTINE_TYPE     LUA_FLIPL(0x0000003E)
#define LUA_MAX_NUMBER_OF_SENDS           LUA_FLIPL(0x0000003F)
#define LUA_SEND_ON_FLOW_PENDING          LUA_FLIPL(0x00000040)
#define LUA_INVALID_MESSAGE_TYPE          LUA_FLIPL(0x00000041)
#define LUA_RECEIVE_ON_FLOW_PENDING       LUA_FLIPL(0x00000042)
#define LUA_DATA_LENGTH_ERROR             LUA_FLIPL(0x00000043)
#define LUA_CLOSE_PENDING                 LUA_FLIPL(0x00000044)
#define LUA_NEGATIVE_RSP_CHASE            LUA_FLIPL(0x00000046)
#define LUA_NEGATIVE_RSP_SHUTC            LUA_FLIPL(0x00000047)
#define LUA_NEGATIVE_RSP_RSHUTD           LUA_FLIPL(0x00000048)
#define LUA_NO_RECEIVE_TO_PURGE           LUA_FLIPL(0x0000004A)
#define LUA_CANCEL_COMMAND_RECEIVED       LUA_FLIPL(0x0000004D)
#define LUA_RUI_WRITE_FAILURE             LUA_FLIPL(0x0000004E)
#define LUA_SLI_BID_PENDING               LUA_FLIPL(0x00000051)
#define LUA_SLI_PURGE_PENDING             LUA_FLIPL(0x00000052)
#define LUA_PROCEDURE_ERROR               LUA_FLIPL(0x00000053)
#define LUA_INVALID_SLI_ENCR_OPTION       LUA_FLIPL(0x00000054)
#define LUA_RECEIVED_UNBIND               LUA_FLIPL(0x00000055)
#define LUA_DATA_INCOMPLETE               LUA_FLIPL(0x00000060)
#define LUA_SLI_LOGIC_ERROR               LUA_FLIPL(0x0000007F)
#define LUA_TERMINATED                    LUA_FLIPL(0x00000080)
#define LUA_NO_RUI_SESSION                LUA_FLIPL(0x00000081)
#define LUA_DUPLICATE_RUI_INIT            LUA_FLIPL(0x00000082)
#define LUA_INVALID_PROCESS               LUA_FLIPL(0x00000083)
#define LUA_API_MODE_CHANGE               LUA_FLIPL(0x00000085)
#define LUA_COMMAND_COUNT_ERROR           LUA_FLIPL(0x00000087)
#define LUA_NO_READ_TO_PURGE              LUA_FLIPL(0x00000088)
#define LUA_MULTIPLE_WRITE_FLOWS          LUA_FLIPL(0x00000089)
#define LUA_DUPLICATE_READ_FLOW           LUA_FLIPL(0x0000008A)
#define LUA_DUPLICATE_WRITE_FLOW          LUA_FLIPL(0x0000008B)
#define LUA_LINK_NOT_STARTED              LUA_FLIPL(0x0000008C)
#define LUA_INVALID_ADAPTER               LUA_FLIPL(0x0000008D)
#define LUA_ENCR_DECR_LOAD_ERROR          LUA_FLIPL(0x0000008E)
#define LUA_ENCR_DECR_PROC_ERROR          LUA_FLIPL(0x0000008F)
#define LUA_NEG_NOTIFY_RSP                LUA_FLIPL(0x000000BE)
#define LUA_RUI_LOGIC_ERROR               LUA_FLIPL(0x000000BF)
#define LUA_LU_INOPERATIVE                LUA_FLIPL(0x000000FF)

/*****************************************************************************/
/* THE FOLLOWING SECONDARY RETURN CODES ARE SNA SENSE CODES                  */
/*****************************************************************************/
#define LUA_NON_UNIQ_ID                   LUA_FLIPL(0xC0001001)
#define LUA_NON_UNIQ_NAU_AD               LUA_FLIPL(0xC0001002)
#define LUA_INV_NAU_ADDR                  LUA_FLIPL(0xC0002001)
#define LUA_INV_ADPT_NUM                  LUA_FLIPL(0xC0002002)

#define LUA_RESOURCE_NOT_AVAILABLE        LUA_FLIPL(0x08010000)
#define LUA_SESSION_LIMIT_EXCEEDED        LUA_FLIPL(0x08050000)
#define LUA_SLU_SESSION_LIMIT_EXCEEDED    LUA_FLIPL(0x0805000A)
#define LUA_MODE_INCONSISTENCY            LUA_FLIPL(0x08090000)
#define LUA_BRACKET_RACE_ERROR            LUA_FLIPL(0x080B0000)
#define LUA_INSUFFICIENT_RESOURCES        LUA_FLIPL(0x08120000)
#define LUA_BB_REJECT_NO_RTR              LUA_FLIPL(0x08130000)
#define LUA_BB_REJECT_RTR                 LUA_FLIPL(0x08140000)
#define LUA_RECEIVER_IN_TRANSMIT_MODE     LUA_FLIPL(0x081B0000)
#define LUA_REQUEST_NOT_EXECUTABLE        LUA_FLIPL(0x081C0000)
#define LUA_INVALID_SESSION_PARAMETERS    LUA_FLIPL(0x08210000)
#define LUA_UNIT_OF_WORK_ABORTED          LUA_FLIPL(0x08240000)
#define LUA_FM_FUNCTION_NOT_SUPPORTED     LUA_FLIPL(0x08260000)
#define LUA_LU_COMPONENT_DISCONNECTED     LUA_FLIPL(0x08310000)
#define LUA_INVALID_PARAMETER_FLAGS       LUA_FLIPL(0x08330000)
#define LUA_INVALID_PARAMETER             LUA_FLIPL(0x08350000)
#define LUA_NEGOTIABLE_BIND_ERROR         LUA_FLIPL(0x08350001)
#define LUA_BIND_FM_PROFILE_ERROR         LUA_FLIPL(0x08350002)
#define LUA_BIND_TS_PROFILE_ERROR         LUA_FLIPL(0x08350003)
#define LUA_BIND_LU_TYPE_ERROR            LUA_FLIPL(0x0835000E)
#define LUA_CRYPTOGRAPHY_INOPERATIVE      LUA_FLIPL(0x08480000)
#define LUA_REQ_RESOURCES_NOT_AVAIL       LUA_FLIPL(0x084B0000)
#define LUA_SSCP_LU_SESSION_NOT_ACTIVE    LUA_FLIPL(0x08570000)
#define LUA_SYNC_EVENT_RESPONSE           LUA_FLIPL(0x08670000)
#define LUA_REC_CORR_TABLE_FULL           LUA_FLIPL(0x08780001)
#define LUA_SEND_CORR_TABLE_FULL          LUA_FLIPL(0x08780002)
#define LUA_SESSION_SERVICE_PATH_ERROR    LUA_FLIPL(0x087D0000)

#define LUA_RU_DATA_ERROR                 LUA_FLIPL(0x10010000)
#define LUA_RU_LENGTH_ERROR               LUA_FLIPL(0x10020000)
#define LUA_FUNCTION_NOT_SUPPORTED        LUA_FLIPL(0x10030000)
#define LUA_HDX_BRACKET_STATE_ERROR       LUA_FLIPL(0x10050121)
#define LUA_RESPONSE_ALREADY_SENT         LUA_FLIPL(0x10050122)
#define LUA_EXR_SENSE_INCORRECT           LUA_FLIPL(0x10050123)
#define LUA_RESPONSE_OUT_OF_ORDER         LUA_FLIPL(0x10050124)
#define LUA_CHASE_RESPONSE_REQUIRED       LUA_FLIPL(0x10050125)
#define LUA_CATEGORY_NOT_SUPPORTED        LUA_FLIPL(0x10070000)

#define LUA_INCORRECT_SEQUENCE_NUMBER     LUA_FLIPL(0x20010000)
#define LUA_CHAINING_ERROR                LUA_FLIPL(0x20020000)
#define LUA_BRACKET                       LUA_FLIPL(0x20030000)
#define LUA_DIRECTION                     LUA_FLIPL(0x20040000)
#define LUA_DATA_TRAFFIC_RESET            LUA_FLIPL(0x20050000)
#define LUA_DATA_TRAFFIC_QUIESCED         LUA_FLIPL(0x20060000)
#define LUA_DATA_TRAFFIC_NOT_RESET        LUA_FLIPL(0x20070000)
#define LUA_NO_BEGIN_BRACKET              LUA_FLIPL(0x20080000)
#define LUA_SC_PROTOCOL_VIOLATION         LUA_FLIPL(0x20090000)
#define LUA_IMMEDIATE_REQ_MODE_ERROR      LUA_FLIPL(0x200A0000)
#define LUA_QUEUED_RESPONSE_ERROR         LUA_FLIPL(0x200B0000)
#define LUA_ERP_SYNC_EVENT_ERROR          LUA_FLIPL(0x200C0000)
#define LUA_RSP_BEFORE_SENDING_REQ        LUA_FLIPL(0x200D0000)
#define LUA_RSP_CORRELATION_ERROR         LUA_FLIPL(0x200E0000)
#define LUA_RSP_PROTOCOL_ERROR            LUA_FLIPL(0x200F0000)

#define LUA_INVALID_SC_OR_NC_RH           LUA_FLIPL(0x40010000)
#define LUA_BB_NOT_ALLOWED                LUA_FLIPL(0x40030000)
#define LUA_EB_NOT_ALLOWED                LUA_FLIPL(0x40040000)
#define LUA_EXCEPTION_RSP_NOT_ALLOWED     LUA_FLIPL(0x40060000)
#define LUA_DEFINITE_RSP_NOT_ALLOWED      LUA_FLIPL(0x40070000)
#define LUA_PACING_NOT_SUPPORTED          LUA_FLIPL(0x40080000)
#define LUA_CD_NOT_ALLOWED                LUA_FLIPL(0x40090000)
#define LUA_NO_RESPONSE_NOT_ALLOWED       LUA_FLIPL(0x400A0000)
#define LUA_CHAINING_NOT_SUPPORTED        LUA_FLIPL(0x400B0000)
#define LUA_BRACKETS_NOT_SUPPORTED        LUA_FLIPL(0x400C0000)
#define LUA_CD_NOT_SUPPORTED              LUA_FLIPL(0x400D0000)
#define LUA_INCORRECT_USE_OF_FI           LUA_FLIPL(0x400F0000)
#define LUA_ALTERNATE_CODE_NOT_SUPPORT    LUA_FLIPL(0x40100000)
#define LUA_INCORRECT_RU_CATEGORY         LUA_FLIPL(0x40110000)
#define LUA_INCORRECT_REQUEST_CODE        LUA_FLIPL(0x40120000)
#define LUA_INCORRECT_SPEC_OF_SDI_RTI     LUA_FLIPL(0x40130000)
#define LUA_INCORRECT_DR1I_DR2I_ERI       LUA_FLIPL(0x40140000)
#define LUA_INCORRECT_USE_OF_QRI          LUA_FLIPL(0x40150000)
#define LUA_INCORRECT_USE_OF_EDI          LUA_FLIPL(0x40160000)
#define LUA_INCORRECT_USE_OF_PDI          LUA_FLIPL(0x40170000)

#define LUA_NAU_INOPERATIVE               LUA_FLIPL(0x80030000)
#define LUA_NO_SESSION                    LUA_FLIPL(0x80050000)

/*****************************************************************************/
/* LUA_RH.RUC masks                                                          */
/*****************************************************************************/
#define  LUA_RH_FMD                       0
#define  LUA_RH_NC                        1
#define  LUA_RH_DFC                       2
#define  LUA_RH_SC                        3

/*****************************************************************************/
/* LUA MESSAGE TYPES                                                         */
/*****************************************************************************/
#define LUA_MESSAGE_TYPE_LU_DATA          0x01
#define LUA_MESSAGE_TYPE_SSCP_DATA        0x11
#define LUA_MESSAGE_TYPE_RSP              0x02
#define LUA_MESSAGE_TYPE_BID              0xC8
#define LUA_MESSAGE_TYPE_BIND             0x31
#define LUA_MESSAGE_TYPE_BIS              0x70
#define LUA_MESSAGE_TYPE_CANCEL           0x83
#define LUA_MESSAGE_TYPE_CHASE            0x84
#define LUA_MESSAGE_TYPE_CLEAR            0xA1
#define LUA_MESSAGE_TYPE_CRV              0xD0
#define LUA_MESSAGE_TYPE_LUSTAT_LU        0x04
#define LUA_MESSAGE_TYPE_LUSTAT_SSCP      0x14
#define LUA_MESSAGE_TYPE_QC               0x81
#define LUA_MESSAGE_TYPE_QEC              0x80
#define LUA_MESSAGE_TYPE_RELQ             0x82
#define LUA_MESSAGE_TYPE_RQR              0xA3
#define LUA_MESSAGE_TYPE_RTR              0x05
#define LUA_MESSAGE_TYPE_SBI              0x71
#define LUA_MESSAGE_TYPE_SHUTD            0xC0
#define LUA_MESSAGE_TYPE_SIGNAL           0xC9
#define LUA_MESSAGE_TYPE_SDT              0xA0
#define LUA_MESSAGE_TYPE_STSN             0xA2
#define LUA_MESSAGE_TYPE_UNBIND           0x32

/*****************************************************************************/
/* LUA INIT TYPES (Used for SLI only)                                        */
/*****************************************************************************/
#define LUA_INIT_TYPE_SEC_IS              0x01
#define LUA_INIT_TYPE_SEC_LOG             0x02
#define LUA_INIT_TYPE_PRIM                0x03
#define LUA_INIT_TYPE_PRIM_SSCP           0x04

/*****************************************************************************/
/* LUA SLI_OPEN EXTENSION ROUTINE TYPES                                      */
/*****************************************************************************/
#define LUA_ROUTINE_TYPE_BIND             0x01
#define LUA_ROUTINE_TYPE_CRV              0x02
#define LUA_ROUTINE_TYPE_STSN             0x03
#define LUA_ROUTINE_TYPE_END              0x00

/*****************************************************************************/
/* LUA VERB RECORD STRUCTURES                                                */
/*****************************************************************************/


/*************************************************************************W32*/
/* If Win32 environment then ensure that packing is correct              *W32*/
/*************************************************************************W32*/
#ifdef WIN32                                                            /*W32*/
#pragma pack(4)                                                         /*W32*/
#endif                                                                  /*W32*/


/*****************************************************************************/
/* Transmission header structure                                             */
/*****************************************************************************/
struct LUA_TH
      {
#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char    flags_fid  : 4;        /* Format Identification Type 2*/
      unsigned char    flags_mpf  : 2;        /* Segmenting Mapping Field    */
      unsigned char    flags_odai : 1;        /* OAF-DAF Assignor Indicator  */
      unsigned char    flags_efi  : 1;        /* Expedited Flow Indicator    */
#else                                                                   /*W32*/
      unsigned char    flags_efi  : 1;        /* Expedited Flow Indicator    */
      unsigned char    flags_odai : 1;        /* OAF-DAF Assignor Indicator  */
      unsigned char    flags_mpf  : 2;        /* Segmenting Mapping Field    */
      unsigned char    flags_fid  : 4;        /* Format Identification Type 2*/
#endif                                                                  /*W32*/
      unsigned char               : 8;        /* Reserved Field              */
      unsigned char    daf;                   /* Destination Address Field   */
      unsigned char    oaf;                   /* Originating Address Field   */
      unsigned char    snf[2];                /* Sequence Number Field       */
      };

/*****************************************************************************/
/* Request/Response unit header strcuture                                    */
/*****************************************************************************/
struct LUA_RH
      {
#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char    rri  : 1;              /* Request-Response Indicator  */
      unsigned char    ruc  : 2;              /* RU Category                 */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    fi   : 1;              /* Format Indicator            */
      unsigned char    sdi  : 1;              /* Sense Data Included Ind     */
      unsigned char    bci  : 1;              /* Begin Chain Indicator       */
      unsigned char    eci  : 1;              /* End Chain Indicator         */
#else                                                                   /*W32*/
      unsigned char    eci  : 1;              /* End Chain Indicator         */
      unsigned char    bci  : 1;              /* Begin Chain Indicator       */
      unsigned char    sdi  : 1;              /* Sense Data Included Ind     */
      unsigned char    fi   : 1;              /* Format Indicator            */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    ruc  : 2;              /* RU Category                 */
      unsigned char    rri  : 1;              /* Request-Response Indicator  */
#endif                                                                  /*W32*/

#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char    dr1i : 1;              /* DR 1 Indicator              */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    dr2i : 1;              /* DR 2 Indicator              */
      unsigned char    ri   : 1;              /* Response Indicator          */
      unsigned char         : 2;              /* Reserved Field              */
      unsigned char    qri  : 1;              /* Queued Response Indicator   */
      unsigned char    pi   : 1;              /* Pacing Indicator            */
#else                                                                   /*W32*/
      unsigned char    pi   : 1;              /* Pacing Indicator            */
      unsigned char    qri  : 1;              /* Queued Response Indicator   */
      unsigned char         : 2;              /* Reserved Field              */
      unsigned char    ri   : 1;              /* Response Indicator          */
      unsigned char    dr2i : 1;              /* DR 2 Indicator              */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    dr1i : 1;              /* DR 1 Indicator              */
#endif                                                                  /*W32*/

#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char    bbi  : 1;              /* Begin Bracket Indicator     */
      unsigned char    ebi  : 1;              /* End Bracket Indicator       */
      unsigned char    cdi  : 1;              /* Change Direction Indicator  */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    csi  : 1;              /* Code Selection Indicator    */
      unsigned char    edi  : 1;              /* Enciphered Data Indicator   */
      unsigned char    pdi  : 1;              /* Padded Data Indicator       */
      unsigned char         : 1;              /* Reserved Field              */
#else                                                                   /*W32*/
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    pdi  : 1;              /* Padded Data Indicator       */
      unsigned char    edi  : 1;              /* Enciphered Data Indicator   */
      unsigned char    csi  : 1;              /* Code Selection Indicator    */
      unsigned char         : 1;              /* Reserved Field              */
      unsigned char    cdi  : 1;              /* Change Direction Indicator  */
      unsigned char    ebi  : 1;              /* End Bracket Indicator       */
      unsigned char    bbi  : 1;              /* Begin Bracket Indicator     */
#endif                                                                  /*W32*/
      };

/*****************************************************************************/
/* Structure for LUA_FLAG1                                                   */
/*****************************************************************************/
struct LUA_FLAG1                              /* LUA_FLAG1                   */
      {
#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char  bid_enable  : 1;         /* Bid Enabled Indicator       */
      unsigned char  reserv1     : 1;         /* reserved                    */
      unsigned char  close_abend : 1;         /* Close Immediate Flag        */
      unsigned char  nowait      : 1;         /* Don't Wait for Data Flag    */
      unsigned char  sscp_exp    : 1;         /* SSCP expedited flow         */
      unsigned char  sscp_norm   : 1;         /* SSCP normal flow            */
      unsigned char  lu_exp      : 1;         /* LU expedited flow           */
      unsigned char  lu_norm     : 1;         /* lu normal flow              */
#else                                                                   /*W32*/
      unsigned char  lu_norm     : 1;         /* lu normal flow              */
      unsigned char  lu_exp      : 1;         /* LU expedited flow           */
      unsigned char  sscp_norm   : 1;         /* SSCP normal flow            */
      unsigned char  sscp_exp    : 1;         /* SSCP expedited flow         */
      unsigned char  nowait      : 1;         /* Don't Wait for Data Flag    */
      unsigned char  close_abend : 1;         /* Close Immediate Flag        */
      unsigned char  reserv1     : 1;         /* reserved                    */
      unsigned char  bid_enable  : 1;         /* Bid Enabled Indicator       */
#endif                                                                  /*W32*/
      };
/*****************************************************************************/
/* Structure for LUA_FLAG2                                                   */
/*****************************************************************************/
struct LUA_FLAG2                              /* LUA_FLAG2                   */
      {
#ifdef LUA_FLIPRQD                                                      /*W32*/
      unsigned char  bid_enable  : 1;         /* Bid Enabled Indicator       */
      unsigned char  async       : 1;         /* flags asynchronous verb
                                                 completion                  */
      unsigned char              : 2;         /* reserved                    */
      unsigned char  sscp_exp    : 1;         /* SSCP expedited flow         */
      unsigned char  sscp_norm   : 1;         /* SSCP normal flow            */
      unsigned char  lu_exp      : 1;         /* LU expedited flow           */
      unsigned char  lu_norm     : 1;         /* lu normal flow              */
#else                                                                   /*W32*/
      unsigned char  lu_norm     : 1;         /* lu normal flow              */
      unsigned char  lu_exp      : 1;         /* LU expedited flow           */
      unsigned char  sscp_norm   : 1;         /* SSCP normal flow            */
      unsigned char  sscp_exp    : 1;         /* SSCP expedited flow         */
      unsigned char              : 2;         /* reserved                    */
      unsigned char  async       : 1;         /* flags asynchronous verb
                                                 completion                  */
      unsigned char  bid_enable  : 1;         /* Bid Enabled Indicator       */
#endif                                                                  /*W32*/
      };

/*****************************************************************************/
/* Structure for common verb header                                          */
/*****************************************************************************/
   struct LUA_COMMON
     {
    unsigned short lua_verb;                   /* Verb Code                  */
    unsigned short lua_verb_length;            /* Length of Verb Record      */
    unsigned short lua_prim_rc;                /* Primary Return Code        */
    unsigned long  lua_sec_rc;                 /* Secondary Return Code      */
    unsigned short lua_opcode;                 /* Verb Operation Code        */
    unsigned long  lua_correlator;             /* User Correlation Field     */
    unsigned char  lua_luname[8];              /* Local LU Name              */
    unsigned short lua_extension_list_offset;  /* Offset of DLL Extention Lis*/
    unsigned short lua_cobol_offset;           /* Offset of Cobol Extension  */
    unsigned long  lua_sid;                    /* Session ID                 */
    unsigned short lua_max_length;             /* Receive Buffer Length      */
    unsigned short lua_data_length;            /* Data Length                */
    char far       *lua_data_ptr;              /* Data Buffer Pointer        */
    unsigned long  lua_post_handle;            /* Posting handle             */

    struct LUA_TH  lua_th;                     /* LUA TH Fields              */

    struct LUA_RH  lua_rh;                     /* LUA RH Fields              */

    struct LUA_FLAG1 lua_flag1;                /* LUA_FLAG1                  */

    unsigned char lua_message_type;            /* sna message command type   */

    struct LUA_FLAG2 lua_flag2;                /* LUA_FLAG2                  */

    unsigned char lua_resv56[7];               /* Reserved Field             */
    unsigned char lua_encr_decr_option;        /* Cryptography Option        */
     } ;


/******************* COMMAND SPECIFIC VERB DEFINITIONS ***************/

/*****************************************************************************/
/* Structure for extension routines                                          */
/*****************************************************************************/
struct LUA_EXT_ENTRY
       {
        unsigned char lua_routine_type;       /* Extension Routine Type      */
        unsigned char lua_module_name[9];     /* Extension Module Name       */
        unsigned char lua_procedure_name[33]; /* Extension Procedure Name    */
       } ;

/*****************************************************************************/
/* LUA SPECIFIC FIELDS FOR THE SLI_OPEN VERB                                 */
/*****************************************************************************/
   struct SLI_OPEN
     {
     unsigned char  lua_init_type;            /* Type of Session Initiation  */
     unsigned char  lua_resv65;               /* Reserved Field              */
     unsigned short lua_wait;                 /* Secondary Retry Wait Time   */

     struct LUA_EXT_ENTRY  lua_open_extension[3];

     unsigned char lua_ending_delim;          /* Extension List Delimiter    */
     } ;

/*****************************************************************************/
/*  LUA SPECIFIC FIELDS FOR THE SLI_OPEN, SLI_SEND RUI_BID AND SLI_BID VERBS */
/*****************************************************************************/
   union LUA_SPECIFIC
     {
     struct   SLI_OPEN       open;
     unsigned char           lua_sequence_number[2];     /* sequence number */
     unsigned char           lua_peek_data[12];          /* Data Pending    */
     } ;

/*****************************************************************************/
/* GENERIC LUA VERB RECORD TYPEDEF DECLARATION                               */
/*****************************************************************************/
   typedef struct
    {
    struct LUA_COMMON       common;    /* common verb header command         */
    union  LUA_SPECIFIC     specific;  /* command specific portion of record */
    }  LUA_VERB_RECORD;



#if (defined WINDOWS) || (defined WIN32)
/*****************************************************************************/
/*WLUA* Return codes from WinLUAStartup                                      */
/*****************************************************************************/
#define WLUASYSNOTREADY                 1
#define WLUAVERNOTSUPPORTED             2
#define WLUAINVALID                     3
#define WLUAFAILURE                     4
#define WLUAINITREJECT                  5

#define WLUADESCRIPTION_LEN             40

typedef struct
{
  WORD wVersion;
  char szDescription[WLUADESCRIPTION_LEN + 1];
} LUADATA;

/*****************************************************************************/
/*WLUA* Return codes from WinLUA                                             */
/*****************************************************************************/
#define WLUAINVALIDHANDLE               10
#define WLUASTARTUPNOTCALLED            11
/*l110************************************************************************/
/*l110* New codes for RUI_INIT status messages                               */
/*l110************************************************************************/
#define WLUALINKINACTIVE                12
#define WLUALINKACTIVATING              13
#define WLUAPUINACTIVE                  14
#define WLUAPUACTIVE                    15
#define WLUAPUREACTIVATED               16
#define WLUALUINACTIVE                  17
#define WLUALUACTIVE                    18
#define WLUALUREACTIVATED               19
#define WLUASIDINVALID                  20
#define WLUASIDZERO                     21
#define WLUAALREADYACTIVE               22
#define WLUANTFYINVALID                 23
#define WLUAGLOBALHANDLER               24
#define WLUAGETLU                       25
#define WLUAUNKNOWN                     255


#define WLUA_NTFY_EVENT                  1
#define WLUA_NTFY_MSG_CORRELATOR         2
#define WLUA_NTFY_MSG_SID                3
/*l110************************************************************************/
/*l110* End changes                                                          */
/*l110************************************************************************/


#endif

/*WLUA************************************************************************/
/*WLUA* Function prototypes                                                  */
/*WLUA************************************************************************/
#ifdef WIN32
  #define LOADDS
#else
  #define LOADDS _loadds
#endif
#if (defined WINDOWS) || (defined WIN32)

int  WINAPI LOADDS WinRUI        (HWND, LUA_VERB_RECORD FAR *);
int  WINAPI LOADDS WinSLI        (HWND, LUA_VERB_RECORD FAR *);
BOOL WINAPI LOADDS WinRUICleanup (void);
BOOL WINAPI LOADDS WinSLICleanup (void);
int  WINAPI LOADDS WinRUIStartup (WORD, LUADATA FAR *);
int  WINAPI LOADDS WinSLIStartup (WORD, LUADATA FAR *);
void WINAPI LOADDS RUI           (LUA_VERB_RECORD FAR *);
void WINAPI LOADDS RUI_CALL      (LUA_VERB_RECORD FAR *);
void WINAPI LOADDS SLI           (LUA_VERB_RECORD FAR *);

int WINAPI LOADDS WinRUIGetLastInitStatus (DWORD  dwSid,               /*l110*/
                                    HANDLE hStatusHandle,              /*l110*/
                                    DWORD  dwNotifyType,               /*l110*/
                                    BOOL   bClearPrevious);            /*l110*/
int WINAPI GetLuaReturnCode      (struct LUA_COMMON FAR *, UINT, unsigned char FAR *);

#else
void pascal far _loadds RUI      (LUA_VERB_RECORD FAR *);
#endif


/*************************************************************************W32*/
/* If Win32 environment then restore original packing format             *W32*/
/*************************************************************************W32*/
#ifdef WIN32                                                            /*W32*/
#pragma pack()                                                          /*W32*/
#endif                                                                  /*W32*/

/*****************************************************************************/
/* RUI ENTRY POINT DECLARATION                                               */
/*PORT* Remove prototype defintions since EE header file does not have any   */
/*****************************************************************************/

#ifdef __cplusplus
}
#endif

#endif
