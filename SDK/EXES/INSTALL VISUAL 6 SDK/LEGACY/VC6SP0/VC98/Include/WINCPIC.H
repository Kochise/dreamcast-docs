/* wincpic.h */
/* Copyright Data Connection Ltd. 1992 */
/* Copyright (c) 1992, Microsoft Corporation.  All rights reserved.          */
/*****************************************************************************/
/* CPI-Communications constants and function prototypes file                 */
/*****************************************************************************/

#ifndef CMCH_INCLUDED
#define CMCH_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

/*****************************************************************************/
/* Ensure the correct packing of structures                                  */
/*****************************************************************************/
#ifdef WIN32
  #pragma pack(4)
#endif

/*****************************************************************************/
/* Type Definitions                                                          */
/*****************************************************************************/


#ifdef DOS5
#define CM_INT32 signed long int
#define CM_ENTRY extern void pascal far _loadds
#define CM_PTR   far *
#endif

#ifdef WINDOWS
#define WINSNA
#define CM_INT32 signed long int
#define CM_ENTRY extern void pascal far _loadds
#define CM_PTR   far *
#endif

#ifdef WIN32
#define WINSNA
#ifdef SET_UNALIGNED_ACCESS_FOR_THUNK
#define CM_INT32 signed long int UNALIGNED
#else
#define CM_INT32 signed long int
#endif
#define CM_ENTRY extern void WINAPI
#define CM_PTR   *
#define CM_EVENT_HANDLE HANDLE
#endif

typedef CM_INT32 CM_CONVERSATION_STATE;
typedef CM_INT32 CM_CONVERSATION_TYPE;
typedef CM_INT32 CM_DATA_RECEIVED_TYPE;
typedef CM_INT32 CM_DEALLOCATE_TYPE;
typedef CM_INT32 CM_ERROR_DIRECTION;
typedef CM_INT32 CM_FILL;
typedef CM_INT32 CM_PREPARE_TO_RECEIVE_TYPE;
typedef CM_INT32 CM_RECEIVE_TYPE;
typedef CM_INT32 CM_REQUEST_TO_SEND_RECEIVED;
typedef CM_INT32 CM_RETURN_CODE;
typedef CM_INT32 CM_RETURN_CONTROL;
typedef CM_INT32 CM_SEND_TYPE;
typedef CM_INT32 CM_STATUS_RECEIVED;
typedef CM_INT32 CM_SYNC_LEVEL;
typedef CM_INT32 CM_END_TYPE;
typedef CM_INT32 CM_PROCESSING_MODE;

typedef CM_INT32 XC_CONVERSATION_SECURITY_TYPE;
typedef CM_INT32 XC_TP_NAME_TYPE;

/**STRUCT+********************************************************************/
/* Side information struct used by xcmssi to define side information         */
/*****************************************************************************/
typedef struct side_info_entry
{
  unsigned char   sym_dest_name[8];            /* symbolic destination name  */
  unsigned char   partner_LU_name[17];         /* fully Q'd PLU name         */
  unsigned char   reserved[3];                 /* future expansion ??        */
  XC_TP_NAME_TYPE TP_name_type;                /* set to XC_APPLICATION_TP   */
                                               /*  or to XC_SNA_SERVICE_TP   */
  unsigned char   TP_name[64];                 /* TP name                    */
  unsigned char   mode_name[8];                /* mode name                  */
  XC_CONVERSATION_SECURITY_TYPE
                  conversation_security_type;  /* set to XC_SECURITY_NONE    */
                                               /*  or to XC_SECURITY_SAME    */
                                               /*  or to XC_SECURITY_PROGRAM */
  unsigned char   security_user_ID[8];         /* user_ID                    */
  unsigned char   security_password[8];        /* password                   */
} SIDE_INFO;
/**STRUCT-********************************************************************/


/*****************************************************************************/
/* Constant Definitions                                                      */
/*****************************************************************************/

/*****************************************************************************/
/* Values for the conversation_state                                         */
/*****************************************************************************/
#define CM_INITIALIZE_STATE              (CM_CONVERSATION_STATE) 2
#define CM_SEND_STATE                    (CM_CONVERSATION_STATE) 3
#define CM_RECEIVE_STATE                 (CM_CONVERSATION_STATE) 4
#define CM_SEND_PENDING_STATE            (CM_CONVERSATION_STATE) 5
#define CM_CONFIRM_STATE                 (CM_CONVERSATION_STATE) 6
#define CM_CONFIRM_SEND_STATE            (CM_CONVERSATION_STATE) 7
#define CM_CONFIRM_DEALLOCATE_STATE      (CM_CONVERSATION_STATE) 8

#define CM_DEFER_RECEIVE_STATE           (CM_CONVERSATION_STATE) 9
#define CM_DEFER_DEALLOCATE_STATE        (CM_CONVERSATION_STATE) 10
#define CM_SYNC_POINT_STATE              (CM_CONVERSATION_STATE) 11
#define CM_SYNC_POINT_SEND_STATE         (CM_CONVERSATION_STATE) 12
#define CM_SYNC_POINT_DEALLOCATE_STATE   (CM_CONVERSATION_STATE) 13
#define CM_INITIALIZE_INCOMING_STATE     (CM_CONVERSATION_STATE) 14

/*****************************************************************************/
/* Values for the conversation_type                                          */
/*****************************************************************************/
#define CM_BASIC_CONVERSATION   (CM_CONVERSATION_TYPE) 0
#define CM_MAPPED_CONVERSATION  (CM_CONVERSATION_TYPE) 1


/*****************************************************************************/
/* Values for data_received                                                  */
/*****************************************************************************/
#define CM_NO_DATA_RECEIVED          (CM_DATA_RECEIVED_TYPE) 0
#define CM_DATA_RECEIVED             (CM_DATA_RECEIVED_TYPE) 1
#define CM_COMPLETE_DATA_RECEIVED    (CM_DATA_RECEIVED_TYPE) 2
#define CM_INCOMPLETE_DATA_RECEIVED  (CM_DATA_RECEIVED_TYPE) 3


/*****************************************************************************/
/* Values for the deallocate_type                                            */
/*****************************************************************************/
#define CM_DEALLOCATE_SYNC_LEVEL  (CM_DEALLOCATE_TYPE) 0
#define CM_DEALLOCATE_FLUSH       (CM_DEALLOCATE_TYPE) 1
#define CM_DEALLOCATE_CONFIRM     (CM_DEALLOCATE_TYPE) 2
#define CM_DEALLOCATE_ABEND       (CM_DEALLOCATE_TYPE) 3


/*****************************************************************************/
/* Values for the error_direction                                            */
/*****************************************************************************/
#define CM_RECEIVE_ERROR  (CM_ERROR_DIRECTION) 0
#define CM_SEND_ERROR     (CM_ERROR_DIRECTION) 1


/*****************************************************************************/
/* Values for fill type                                                      */
/*****************************************************************************/
#define CM_FILL_LL      (CM_FILL) 0
#define CM_FILL_BUFFER  (CM_FILL) 1


/*****************************************************************************/
/* Values for specify_processing_mode                                        */
/*****************************************************************************/
#define CM_BLOCKING                    (CM_PROCESSING_MODE) 0
#define CM_NON_BLOCKING                (CM_PROCESSING_MODE) 1


/*****************************************************************************/
/* Values for prepare_to_receive_type                                        */
/*****************************************************************************/
#define CM_PREP_TO_RECEIVE_SYNC_LEVEL  (CM_PREPARE_TO_RECEIVE_TYPE) 0
#define CM_PREP_TO_RECEIVE_FLUSH       (CM_PREPARE_TO_RECEIVE_TYPE) 1
#define CM_PREP_TO_RECEIVE_CONFIRM     (CM_PREPARE_TO_RECEIVE_TYPE) 2


/*****************************************************************************/
/* Values for the receive_type                                               */
/*****************************************************************************/
#define CM_RECEIVE_AND_WAIT   (CM_RECEIVE_TYPE) 0
#define CM_RECEIVE_IMMEDIATE  (CM_RECEIVE_TYPE) 1


/*****************************************************************************/
/* Values for request_to_send_received                                       */
/*****************************************************************************/
#define CM_REQ_TO_SEND_NOT_RECEIVED  (CM_REQUEST_TO_SEND_RECEIVED) 0
#define CM_REQ_TO_SEND_RECEIVED      (CM_REQUEST_TO_SEND_RECEIVED) 1

/*****************************************************************************/
/* Values for return_code (including CPI-RR value, which start at 100)       */
/*****************************************************************************/
#define CM_OK                            (CM_RETURN_CODE) 0
#define CM_ALLOCATE_FAILURE_NO_RETRY     (CM_RETURN_CODE) 1
#define CM_ALLOCATE_FAILURE_RETRY        (CM_RETURN_CODE) 2
#define CM_CONVERSATION_TYPE_MISMATCH    (CM_RETURN_CODE) 3
#define CM_PIP_NOT_SPECIFIED_CORRECTLY   (CM_RETURN_CODE) 5
#define CM_SECURITY_NOT_VALID            (CM_RETURN_CODE) 6
#define CM_SYNC_LVL_NOT_SUPPORTED_LU     (CM_RETURN_CODE) 7
#define CM_SYNC_LVL_NOT_SUPPORTED_PGM    (CM_RETURN_CODE) 8
#define CM_TPN_NOT_RECOGNIZED            (CM_RETURN_CODE) 9

#define CM_SYNC_LEVEL_NOT_SUPPORTED_LU   (CM_RETURN_CODE) 7
#define CM_SYNC_LEVEL_NOT_SUPPORTED_PGM  (CM_RETURN_CODE) 8
#define CM_TPN_NOT_RECOGNISED            (CM_RETURN_CODE) 9

#define CM_TP_NOT_AVAILABLE_NO_RETRY     (CM_RETURN_CODE) 10
#define CM_TP_NOT_AVAILABLE_RETRY        (CM_RETURN_CODE) 11
#define CM_DEALLOCATED_ABEND             (CM_RETURN_CODE) 17
#define CM_DEALLOCATED_NORMAL            (CM_RETURN_CODE) 18
#define CM_PARAMETER_ERROR               (CM_RETURN_CODE) 19
#define CM_PRODUCT_SPECIFIC_ERROR        (CM_RETURN_CODE) 20
#define CM_PROGRAM_ERROR_NO_TRUNC        (CM_RETURN_CODE) 21
#define CM_PROGRAM_ERROR_PURGING         (CM_RETURN_CODE) 22
#define CM_PROGRAM_ERROR_TRUNC           (CM_RETURN_CODE) 23
#define CM_PROGRAM_PARAMETER_CHECK       (CM_RETURN_CODE) 24
#define CM_PROGRAM_STATE_CHECK           (CM_RETURN_CODE) 25
#define CM_RESOURCE_FAILURE_NO_RETRY     (CM_RETURN_CODE) 26
#define CM_RESOURCE_FAILURE_RETRY        (CM_RETURN_CODE) 27
#define CM_UNSUCCESSFUL                  (CM_RETURN_CODE) 28
#define CM_DEALLOCATED_ABEND_SVC         (CM_RETURN_CODE) 30
#define CM_DEALLOCATED_ABEND_TIMER       (CM_RETURN_CODE) 31
#define CM_SVC_ERROR_NO_TRUNC            (CM_RETURN_CODE) 32
#define CM_SVC_ERROR_PURGING             (CM_RETURN_CODE) 33
#define CM_SVC_ERROR_TRUNC               (CM_RETURN_CODE) 34

#define CM_OPERATION_INCOMPLETE          (CM_RETURN_CODE) 35
#define CM_SYSTEM_EVENT                  (CM_RETURN_CODE) 36
#define CM_OPERATION_NOT_ACCEPTED        (CM_RETURN_CODE) 37

#define CM_TAKE_BACKOUT                  (CM_RETURN_CODE) 100
#define CM_DEALLOCATED_ABEND_BO          (CM_RETURN_CODE) 130
#define CM_DEALLOCATED_ABEND_SVC_BO      (CM_RETURN_CODE) 131
#define CM_DEALLOCATED_ABEND_TIMER_BO    (CM_RETURN_CODE) 132
#define CM_RESOURCE_FAIL_NO_RETRY_BO     (CM_RETURN_CODE) 133
#define CM_RESOURCE_FAILURE_RETRY_BO     (CM_RETURN_CODE) 134
#define CM_DEALLOCATED_NORMAL_BO         (CM_RETURN_CODE) 135

/*****************************************************************************/
/* Values for return_control                                                 */
/*****************************************************************************/
#define CM_WHEN_SESSION_ALLOCATED  (CM_RETURN_CONTROL) 0
#define CM_IMMEDIATE               (CM_RETURN_CONTROL) 1


/*****************************************************************************/
/* Values for the send_type                                                  */
/*****************************************************************************/
#define CM_BUFFER_DATA               (CM_SEND_TYPE) 0
#define CM_SEND_AND_FLUSH            (CM_SEND_TYPE) 1
#define CM_SEND_AND_CONFIRM          (CM_SEND_TYPE) 2
#define CM_SEND_AND_PREP_TO_RECEIVE  (CM_SEND_TYPE) 3
#define CM_SEND_AND_DEALLOCATE       (CM_SEND_TYPE) 4


/*****************************************************************************/
/* Values for status_received                                                */
/*****************************************************************************/
#define CM_NO_STATUS_RECEIVED        (CM_STATUS_RECEIVED) 0
#define CM_SEND_RECEIVED             (CM_STATUS_RECEIVED) 1
#define CM_CONFIRM_RECEIVED          (CM_STATUS_RECEIVED) 2
#define CM_CONFIRM_SEND_RECEIVED     (CM_STATUS_RECEIVED) 3
#define CM_CONFIRM_DEALLOC_RECEIVED  (CM_STATUS_RECEIVED) 4

#define CM_TAKE_COMMIT               (CM_STATUS_RECEIVED) 5
#define CM_TAKE_COMMIT_SEND          (CM_STATUS_RECEIVED) 6
#define CM_TAKE_COMMIT_DEALLOCATE    (CM_STATUS_RECEIVED) 7

/*****************************************************************************/
/* Values for the sync_level                                                 */
/*****************************************************************************/
#define CM_NONE     (CM_SYNC_LEVEL) 0
#define CM_CONFIRM  (CM_SYNC_LEVEL) 1

/*****************************************************************************/
/* Values for maximum sizes of strings and buffers                           */
/*****************************************************************************/
#define CM_CID_SIZE   (8)         /* conversation ID           */
#define CM_CTX_SIZE   (32)        /* context ID                */
#define CM_LD_SIZE    (512)       /* log data                  */
#define CM_MN_SIZE    (8)         /* mode name                 */
#define CM_PLN_SIZE   (17)        /* partner LU name           */
#define CM_PW_SIZE    (10)        /* password                  */
#define CM_SDN_SIZE   (8)         /* symbolic destination name */
#define CM_TPN_SIZE   (64)        /* TP name                   */
#define CM_UID_SIZE   (10)        /* userid ID                 */

/*****************************************************************************/
/* Values for the conversation_security_type (NS/2 compatible)               */
/*****************************************************************************/
#define XC_SECURITY_NONE     (XC_CONVERSATION_SECURITY_TYPE) 0
#define XC_SECURITY_SAME     (XC_CONVERSATION_SECURITY_TYPE) 1
#define XC_SECURITY_PROGRAM  (XC_CONVERSATION_SECURITY_TYPE) 2


/*****************************************************************************/
/* Values for the TP_name_type (NS/2 compatible)                             */
/*****************************************************************************/
#define XC_APPLICATION_TP  (XC_TP_NAME_TYPE) 0
#define XC_SNA_SERVICE_TP  (XC_TP_NAME_TYPE) 1


/*****************************************************************************/
/* Function prototypes for CPIC call routines                                */
/*****************************************************************************/

/* Accept_Conversation */
CM_ENTRY cmaccp(unsigned char CM_PTR,               /* conversation_ID       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Allocate */
CM_ENTRY cmallc(unsigned char CM_PTR,               /* conversation_ID       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Cancel_Conversation */
CM_ENTRY cmcanc(unsigned char CM_PTR,               /* conversation_ID       */
                CM_INT32 CM_PTR);                   /* return_code     *WSNA1*/

/* Confirm */
CM_ENTRY cmcfm(unsigned char CM_PTR,                /* conversation_ID       */
               CM_REQUEST_TO_SEND_RECEIVED CM_PTR,  /* request_to_send_rec.. */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Confirmed */
CM_ENTRY cmcfmd(unsigned char CM_PTR,               /* conversation_ID       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Deallocate */
CM_ENTRY cmdeal(unsigned char CM_PTR,               /* conversation_ID       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_Conversation_State */
CM_ENTRY cmecs(unsigned char CM_PTR,                /* conversation_ID       */
               CM_CONVERSATION_STATE CM_PTR,        /* conversation_state    */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Extract_Conversation_Type */
CM_ENTRY cmect(unsigned char CM_PTR,                /* conversation_ID       */
               CM_CONVERSATION_TYPE CM_PTR,         /* conversation type     */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Extract_Mode_Name */
CM_ENTRY cmemn(unsigned char CM_PTR,                /* conversation_ID       */
               unsigned char CM_PTR,                /* mode_name             */
               CM_INT32 CM_PTR,                     /* mode_name_length      */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Extract_Partner_LU_Name */
CM_ENTRY cmepln(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* partner_LU_name       */
                CM_INT32 CM_PTR,                    /* partner_LU_name_len.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_Sync_Level */
CM_ENTRY cmesl(unsigned char CM_PTR,                /* conversation_ID       */
               CM_SYNC_LEVEL CM_PTR,                /* sync_level            */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Extract_TP_Name */
CM_ENTRY cmetpn(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* TP_name               */
                CM_INT32 CM_PTR,                    /* TP_name_length        */
                CM_INT32 CM_PTR);                   /* return_code     *WSNA1*/

/* Flush */
CM_ENTRY cmflus(unsigned char CM_PTR,               /* conversation_ID       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Initialize_Conversation */
CM_ENTRY cminit(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* sym_dest_name         */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Prepare_To_Receive */
CM_ENTRY cmptr(unsigned char CM_PTR,                /* conversation_ID       */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Receive */
CM_ENTRY cmrcv(unsigned char CM_PTR,                /* conversation_ID       */
               unsigned char CM_PTR,                /* buffer                */
               CM_INT32 CM_PTR,                     /* requested_length      */
               CM_DATA_RECEIVED_TYPE CM_PTR,        /* data_received         */
               CM_INT32 CM_PTR,                     /* received_length       */
               CM_STATUS_RECEIVED CM_PTR,           /* status_received       */
               CM_REQUEST_TO_SEND_RECEIVED CM_PTR,  /* request_to_send_rec.. */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Request_To_Send */
CM_ENTRY cmrts(unsigned char CM_PTR,                /* conversation_ID       */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Send */
CM_ENTRY cmsend(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* buffer                */
                CM_INT32 CM_PTR,                    /* send_length           */
                CM_REQUEST_TO_SEND_RECEIVED CM_PTR, /* request_to_send_rec.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Send_Error */
CM_ENTRY cmserr(unsigned char CM_PTR,               /* conversation_ID       */
                CM_REQUEST_TO_SEND_RECEIVED CM_PTR, /* request_to_send_rec.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Type */
CM_ENTRY cmsct(unsigned char CM_PTR,                /* conversation_ID       */
               CM_CONVERSATION_TYPE CM_PTR,         /* conversation_type     */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Deallocate_Type */
CM_ENTRY cmsdt(unsigned char CM_PTR,                /* conversation_ID       */
               CM_DEALLOCATE_TYPE CM_PTR,           /* deallocate_type       */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Error_Direction */
CM_ENTRY cmsed(unsigned char CM_PTR,                /* conversation_ID       */
               CM_ERROR_DIRECTION CM_PTR,           /* error_direction       */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Fill */
CM_ENTRY cmsf(unsigned char CM_PTR,                 /* conversation_ID       */
              CM_FILL CM_PTR,                       /* fill                  */
              CM_RETURN_CODE CM_PTR);               /* return_code           */

/* Set_Log_Data */
CM_ENTRY cmsld(unsigned char CM_PTR,                /* conversation_ID       */
               unsigned char CM_PTR,                /* log_data              */
               CM_INT32 CM_PTR,                     /* log_data_length       */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Specify_Local_TP_Name */
CM_ENTRY cmsltp(unsigned char CM_PTR,		    /* TP name		     */
		CM_INT32 CM_PTR,		     /* TP_name_length	      */
		CM_INT32 CM_PTR);		    /* return_code     *WSNA1*/

/* Set_Processing_Mode */
CM_ENTRY cmspm(unsigned char CM_PTR,                /* conversation_ID       */
               CM_INT32 CM_PTR,                     /* processing mode       */
               CM_INT32 CM_PTR);                    /* return_code     *WSNA1*/


/* Set_Mode_Name */
CM_ENTRY cmsmn(unsigned char CM_PTR,                /* conversation_ID       */
               unsigned char CM_PTR,                /* mode_name             */
               CM_INT32 CM_PTR,                     /* mode_name_length      */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Partner_LU_Name */
CM_ENTRY cmspln(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* partner_LU_name       */
                CM_INT32 CM_PTR,                    /* partner_LU_name_len.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Prepare_To_Receive_Type */
CM_ENTRY cmsptr(unsigned char CM_PTR,               /* conversation_ID       */
                CM_PREPARE_TO_RECEIVE_TYPE CM_PTR,  /* prepare_to_receive_.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Receive_Type */
CM_ENTRY cmsrt(unsigned char CM_PTR,                /* conversation_ID       */
               CM_RECEIVE_TYPE CM_PTR,              /* receive_type          */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Return_Control */
CM_ENTRY cmsrc(unsigned char CM_PTR,                /* conversation_ID       */
               CM_RETURN_CONTROL CM_PTR,            /* return_control        */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Send_Type */
CM_ENTRY cmsst(unsigned char CM_PTR,                /* conversation_ID       */
               CM_SEND_TYPE CM_PTR,                 /* send_type             */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_Sync_Level */
CM_ENTRY cmssl(unsigned char CM_PTR,                /* conversation_ID       */
               CM_SYNC_LEVEL CM_PTR,                /* sync_level            */
               CM_RETURN_CODE CM_PTR);              /* return_code           */

/* Set_TP_name */
CM_ENTRY cmstpn(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* TP_name               */
                CM_INT32 CM_PTR,                    /* TP_name_legth         */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Test_Request_To_Send_Received */
CM_ENTRY cmtrts(unsigned char CM_PTR,               /* conversation_ID       */
                CM_REQUEST_TO_SEND_RECEIVED CM_PTR, /* request_to_send_rec.. */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Wait_For_Conversation */
CM_ENTRY cmwait(unsigned char CM_PTR,               /* conversation_ID       */
                CM_INT32 CM_PTR,                    /* conversation ret code */
                CM_INT32 CM_PTR);                   /* return_code     *WSNA1*/

/*****************************************************************************/
/* Function Prototypes for additional NS/2 compatible call routines          */
/*****************************************************************************/

/* Delete_CPIC_Side_Information */
CM_ENTRY xcmdsi(unsigned char CM_PTR,               /* key_lock              */
                unsigned char CM_PTR,               /* sym_dest_name         */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_CPIC_Side_Information */
CM_ENTRY xcmesi(CM_INT32 CM_PTR,                    /* entry_number          */
                unsigned char CM_PTR,                       /* sym_dest_name         */
                SIDE_INFO CM_PTR,                   /* side_info_entry       */
                CM_INT32 CM_PTR,                    /* side_info_length      */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_CPIC_Side_Information */
CM_ENTRY xcmssi(unsigned char CM_PTR,               /* key_lock              */
                SIDE_INFO CM_PTR,                   /* side_info_entry       */
                CM_INT32 CM_PTR,                    /* side_info length      */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_Conversation_Security_Type */
CM_ENTRY xcecst(unsigned char CM_PTR,               /* conversation_ID       */
                XC_CONVERSATION_SECURITY_TYPE CM_PTR, /* conversation_sec... */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_Conversation_User_ID */
CM_ENTRY xcecsu(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* user_ID               */
                CM_INT32 CM_PTR,                    /* user_ID_length        */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_Password */
CM_ENTRY xcscsp(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* password              */
                CM_INT32 CM_PTR,                    /* password_length       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_Type */
CM_ENTRY xcscst(unsigned char CM_PTR,               /* conversation_ID       */
                XC_CONVERSATION_SECURITY_TYPE CM_PTR, /* conversation_sec... */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_User_ID */
CM_ENTRY xcscsu(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* user_ID               */
                CM_INT32 CM_PTR,                    /* user_ID_length        */
                CM_RETURN_CODE CM_PTR);             /* return_code           */


/*****************************************************************************/
/* Also have new prototypes with cm not xc                                   */
/*****************************************************************************/
/* Extract_Conversation_Security_Type */
CM_ENTRY cmecst(unsigned char CM_PTR,               /* conversation_ID       */
                XC_CONVERSATION_SECURITY_TYPE CM_PTR, /* conversation_sec... */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Extract_Conversation_User_ID */
CM_ENTRY cmecsu(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* user_ID               */
                CM_INT32 CM_PTR,                    /* user_ID_length        */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_Password */
CM_ENTRY cmscsp(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* password              */
                CM_INT32 CM_PTR,                    /* password_length       */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_Type */
CM_ENTRY cmscst(unsigned char CM_PTR,               /* conversation_ID       */
                XC_CONVERSATION_SECURITY_TYPE CM_PTR, /* conversation_sec... */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

/* Set_Conversation_Security_User_ID */
CM_ENTRY cmscsu(unsigned char CM_PTR,               /* conversation_ID       */
                unsigned char CM_PTR,               /* user_ID               */
                CM_INT32 CM_PTR,                    /* user_ID_length        */
                CM_RETURN_CODE CM_PTR);             /* return_code           */

#ifdef WINSNA
/* Specify_Windows_Handle */
CM_ENTRY xchwnd(HWND,                               /* Window HWND     *WSNA1*/
                CM_INT32 CM_PTR);                   /* return_code           */
#endif

/*****************************************************************************/
/* Function prototypes for undocumented NS/2 compatible call routines.  As   */
/* these routines are undocumented the prototypes do not include any         */
/* parameters.  These are needed to allow binary compatibility with NS/2     */
/* CPI-C applications, with the proviso that only documented calls are       */
/* actually used.                                                            */
/*****************************************************************************/

CM_ENTRY allocate_memory();
CM_ENTRY free_cpic_memory();
CM_ENTRY icmssi();


#ifdef WINSNA
/*---------------------------------------------------------------------------*/
/* Windows CPI-C Extention Return Codes.                                     */
/*---------------------------------------------------------------------------*/

#define WCPICALREADY         0xF000   /* An async call is already outstanding */
#define WCPICINVALID         0xF001   /* Async Task Id is invalid             */
#define WCPICCANCEL          0xF002   /* Blocking call was cancelled          */
#define WCPICSYSNOTREADY     0xF003   /* Underlying subsystem not started     */
#define WCPICVERNOTSUPPORTED 0xF004   /* Application version not supported    */


/*----------------------------------------------------------------------------*/
/* Api structre definitions                                                   */
/*----------------------------------------------------------------------------*/
#define WCPICDESCRIPTION_LEN    127

typedef struct tagWCPICDATA {
        WORD    wVersion;
        char    szDescription[WCPICDESCRIPTION_LEN+1];
} WCPICDATA, * PWCPICDATA, FAR * LPWCPICDATA;

/*****************************************************************************/
/* ------------- Windows CPI-C function prototypes ------------------------- */
/*****************************************************************************/

extern BOOL WINAPI    WinCPICCleanup(void);
extern BOOL WINAPI    WinCPICIsBlocking(void);
extern int WINAPI     WinCPICStartup(WORD, LPWCPICDATA );
extern FARPROC WINAPI WinCPICSetBlockingHook( FARPROC );
extern BOOL WINAPI    WinCPICUnhookBlockingHook(void);
#ifdef WIN32
extern VOID WINAPI    WinCPICSetEvent(unsigned char   CM_PTR,
                                      CM_EVENT_HANDLE CM_PTR,
                                      CM_RETURN_CODE CM_PTR);
extern VOID WINAPI    WinCPICExtractEvent(unsigned char   CM_PTR,
                                          CM_EVENT_HANDLE CM_PTR,
                                          CM_RETURN_CODE CM_PTR);
#endif

#define WIN_CPIC_ASYNC_COMPLETE_MESSAGE "WinAsyncCPI-C"

#endif

/*
 * These macros allow you to write programs that are easier to read, since
 * you can use the full name of the CPI-C call rather than its 6 character
 * entry point.
 *
 * When porting code that uses these macros, you will have to ensure that
 * the macros are defined on the target platform.
 */

#ifdef READABLE_MACROS

#define Accept_Conversation(v1,v2)            cmaccp(v1,v2)
#define Allocate(v1,v2)                       cmallc(v1,v2)
#define Cancel_Conversation(v1,v2)            cmcanc(v1,v2)
#define Confirm(v1,v2,v3)                     cmcfm(v1,v2,v3)
#define Confirmed(v1,v2)                      cmcfmd(v1,v2)
#define Deallocate(v1,v2)                     cmdeal(v1,v2)
#define Extract_Conversation_Security_User_ID(v1,v2,v3,v4)  cmecsu(v1,v2,v3,v4)
#define Extract_Conversation_Security_Type(v1,v2,v3) cmecst(v1,v2,v3)
#define Extract_Mode_Name(v1,v2,v3,v4)        cmemn(v1,v2,v3,v4)
#define Extract_Partner_LU_Name(v1,v2,v3,v4)  cmepln(v1,v2,v3,v4)
#define Extract_Sync_Level(v1,v2,v3)          cmesl(v1,v2,v3)
#define Extract_TP_Name(v1,v2,v3,v4)          cmetpn(v1,v2,v3,v4)
#define Flush(v1,v2)                          cmflus(v1,v2)
#define Initialize_Conversation(v1,v2,v3)     cminit(v1,v2,v3)
#define Prepare_To_Receive(v1,v2)             cmptr(v1,v2)
#define Receive(v1,v2,v3,v4,v5,v6,v7,v8)      cmrcv(v1,v2,v3,v4,v5,v6,v7,v8)
#define Request_To_Send(v1,v2)                cmrts(v1,v2)
#define Send_Error(v1,v2,v3)                  cmserr(v1,v2,v3)
#define Set_Conversation_Type(v1,v2,v3)       cmsct(v1,v2,v3)
#define Set_Deallocate_Type(v1,v2,v3)         cmsdt(v1,v2,v3)
#define Set_Error_Direction(v1,v2,v3)         cmsed(v1,v2,v3)
#define Send_Data(v1,v2,v3,v4,v5)             cmsend(v1,v2,v3,v4,v5)
#define Set_Fill(v1,v2,v3)                    cmsf(v1,v2,v3)
#define Set_Log_Data(v1,v2,v3,v4)             cmsld(v1,v2,v3,v4)
#define Set_Mode_Name(v1,v2,v3,v4)            cmsmn(v1,v2,v3,v4)
#define Set_Partner_LU_Name(v1,v2,v3,v4)      cmspln(v1,v2,v3,v4)
#define Set_Prepare_To_Receive_Type(v1,v2,v3) cmsptr(v1,v2,v3)
#define Set_Processing_Mode(v1,v2,v3)         cmspm(v1,v2,v3)
#define Set_Receive_Type(v1,v2,v3)            cmsrt(v1,v2,v3)
#define Set_Return_Control(v1,v2,v3)          cmsrc(v1,v2,v3)
#define Set_Send_Type(v1,v2,v3)               cmsst(v1,v2,v3)
#define Set_Sync_Level(v1,v2,v3)              cmssl(v1,v2,v3)
#define Set_TP_Name(v1,v2,v3,v4)              cmstpn(v1,v2,v3,v4)
#define Specify_Local_TP_Name(v1,v2,v3)       cmsltp(v1,v2,v3)
#define Set_Conversation_Security_Password(v1,v2,v3,v4) cmscsp(v1,v2,v3,v4)
#define Set_Conversation_Security_Type(v1,v2,v3) cmscst(v1,v2,v3)
#define Set_Conversation_Security_User_ID(v1,v2,v3,v4) cmscsu(v1,v2,v3,v4)
#define Test_Request_To_Send_Received(v1,v2,v3) cmtrts(v1,v2,v3)
#define Wait_For_Conversation(v1,v2,v3)       cmwait(v1,v2,v3)
#define Specify_Windows_Handle(v1,v2)         xchwnd(v1,v2)

#endif

#ifdef __cplusplus
}
#endif

/*****************************************************************************/
/* Restore to default packing of structures                                  */
/*****************************************************************************/
#ifdef WIN32
  #pragma pack()
#endif

#endif


