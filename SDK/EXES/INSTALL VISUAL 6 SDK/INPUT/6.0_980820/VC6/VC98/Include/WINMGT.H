
/**MOD+***********************************************************************/
/* Module:    acsmgtc.c                                                      */
/*                                                                           */
/* Purpose:   header file for CNOS and DISPLAY API structures                */
/*                                                                           */
/* (C) COPYRIGHT DATA CONNECTION LIMITED 1991, 1992                          */
/*                                                                           */
/**MOD-***********************************************************************/

#ifndef ACSMGTCH_INCLUDED
#define ACSMGTCH_INCLUDED

/*****************************************************************************/
/* Change for ES1.0 which also defines luw_id_overlay                        */
/*****************************************************************************/
#include <winappc.h>

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
/* Definitions from APPCDEF.H file (retired)                                 */
/*****************************************************************************/

typedef struct fqpcid_overlay {
    unsigned char  unique_proc_id[8];   /* Unique procedure identifier       */
    unsigned char  fq_length;           /* Length of Fully Qualified Name    */
    unsigned char  fq_name[17];         /* Fully Qualified Name (EBCDIC)     */
                                        /*    1-17 bytes (EBCDIC type A)     */
} FQPCID_OVERLAY;

typedef struct alt_alias_overlay {
    unsigned char  alt_plu_alias[8];    /* Alternate Partner LU Alias (ASCII */
                                        /* 1-8 bytes                         */
} ALT_ALIAS_OVERLAY;

#define MGT_LO_UC(w)    ((unsigned char)(((unsigned short)(w)) & 0xFF))
#define MGT_HI_UC(w)    ((unsigned char)(((unsigned short)(w) >> 8) & 0xff))
#define MGT_MAKUS(l, h) (((unsigned short)(l)) | ((unsigned short)(h)) << 8)
#define MGT_MAKUL(l, h) ((unsigned long)(((unsigned short)(l))|      \
                          ((unsigned long)((unsigned short)(h))) << 16))
#define MGT_LO_US(l)      ((unsigned short)(((unsigned long)(l)) & 0xFFFF))
#define MGT_HI_US(l)    ((unsigned short)(((unsigned long)(l) >> 16) \
                           & 0xffff))
/*****************************************************************************/
/* CONSTFLIP macros.  Ordinary flipping macros include function calls and so */
/* PFLIPI(constant) does not appear constant to the compiler                 */
/*****************************************************************************/
#ifdef NON_INTEL_BYTE_ORDER
#define CONSTFLIPI(X)  (X)
#define CONSTFLIPL(X)  (X)

/*****************************************************************************/
/* ELSE (Intel environment)                                                  */
/* define flipping macros                                                    */
/*****************************************************************************/
#else
#define CONSTFLIPI(X) MGT_MAKUS(MGT_HI_UC(X),MGT_LO_UC(X))
#define CONSTFLIPL(X) MGT_MAKUL(CONSTFLIPI(MGT_HI_US(X)),  \
                                CONSTFLIPI(MGT_LO_US(X)))
#endif

/*****************************************************************************/
/* Primary Return Codes                                                      */
/*****************************************************************************/

   #define  AP_CNOS_LOCAL_RACE_REJECT        CONSTFLIPI(0x0017) /* 0017 */
   #define  AP_CNOS_PARTNER_LU_REJECT        CONSTFLIPI(0x0018) /* 0018 */
   #define  AP_INVALID_KEY                   CONSTFLIPI(0xF020) /* F020 */



/*****************************************************************************/
/* Secondary Return Codes                                                    */
/*****************************************************************************/


   #define  AP_ALL_MODE_MUST_RESET                 CONSTFLIPL(0x00000153L)
   #define  AP_AUTOACT_EXCEEDS_SESSLIM             CONSTFLIPL(0x00000152L)
   #define  AP_BAD_MODE_NAME                       CONSTFLIPL(0x00000157L)
   #define  AP_BAD_SNASVCMG_LIMITS                 CONSTFLIPL(0x00000154L)
   #define  AP_CANT_RAISE_LIMITS                   CONSTFLIPL(0x00000151L)
   #define  AP_CHANGE_SRC_DRAINS                   CONSTFLIPL(0x0000015DL)
   #define  AP_CNOS_ACCEPTED                       CONSTFLIPL(0x00000000L)
   #define  AP_CNOS_COMMAND_RACE_REJECT            CONSTFLIPL(0x0000015FL)
   #define  AP_CNOS_IMPLICIT_PARALLEL              CONSTFLIPL(0x00000150L)
   #define  AP_CNOS_MODE_CLOSED                    CONSTFLIPL(0x00000156L)
   #define  AP_CNOS_MODE_NAME_REJECT               CONSTFLIPL(0x00000157L)
   #define  AP_CNOS_NEGOTIATED                     CONSTFLIPL(0x00000007L)
   #define  AP_CPSVCMG_MODE_NOT_ALLOWED            CONSTFLIPL(0x00000519L)
   #define  AP_EXCEEDS_MAX_ALLOWED                 CONSTFLIPL(0x0000015CL)
   #define  AP_LU_DETACHED                         CONSTFLIPL(0x0000015EL)
   #define  AP_MIN_GT_TOTAL                        CONSTFLIPL(0x00000155L)
   #define  AP_MODE_CLOSED                         CONSTFLIPL(0x00000156L)
   #define  AP_RESET_SNA_DRAINS                    CONSTFLIPL(0x00000159L)
   #define  AP_SINGLE_NOT_SRC_RESP                 CONSTFLIPL(0x0000015AL)
   #define  AP_SNASVCMG_RESET_NOT_ALLOWED          CONSTFLIPL(0x00000167L)

   #define  AP_DISPLAY_INFO_EXCEEDS_LEN            CONSTFLIPL(0x000001B4L)
   #define  AP_DISPLAY_INVALID_CONSTANT            CONSTFLIPL(0x000001B5L)



/*****************************************************************************/
/* Parameter values                                                          */
/*****************************************************************************/

   #define  AP_SOURCE                              (0x00)
   #define  AP_TARGET                              (0x01)

   #define  AP_ONE                                 (0x00)
   #define  AP_ALL                                 (0x01)


   #define  AP_QUEUED_OPERATOR_STARTED             (0x00)
   #define  AP_QUEUED_AM_STARTED                   (0x01)
   #define  AP_NONQUEUED_AM_STARTED                (0x02)
   #define  AP_QUEUED_OPERATOR_PRELOADED           (0x03)

   #define  AP_BACKGROUND                          (0x00)
   #define  AP_FULL_SCREEN                         (0x01)
   #define  AP_PRESENTATION_MANAGER                (0x02)
   #define  AP_VIO_WINDOWABLE                      (0x03)

   #define  AP_LEARN                               (0x00)
   #define  AP_LEN                                 (0x01)
   #define  AP_NN                                  (0x02)
   #define  AP_EN                                  (0x03)

   #define  AP_SEC_NONSECURE                       (0x01)
   #define  AP_SEC_PUBLIC_SWITCHED_NETWORK         (0x20)
   #define  AP_SEC_UNDERGROUND_CABLE               (0x40)
   #define  AP_SEC_SECURE_CONDUIT                  (0x60)
   #define  AP_SEC_GUARDED_CONDUIT                 (0x80)
   #define  AP_SEC_ENCRYPTED                       (0xA0)
   #define  AP_SEC_GUARDED_RADIATION               (0xC0)
   #define  AP_SEC_MAXIMUM                         (0xFF)

   #define  AP_PROP_DELAY_MINIMUM                  (0x00)
   #define  AP_PROP_DELAY_LAN                      (0x4C)
   #define  AP_PROP_DELAY_TELEPHONE                (0x71)
   #define  AP_PROP_DELAY_PKT_SWITCHED_NET         (0x91)
   #define  AP_PROP_DELAY_SATELLITE                (0x99)
   #define  AP_PROP_DELAY_MAXIMUM                  (0xFF)

   #define  AP_SWITCHED                            (0x01)
   #define  AP_NONSWITCHED                         (0x02)

   #define  AP_SECONDARY                           (0x00)
   #define  AP_PRIMARY                             (0x01)
   #define  AP_NEGOTIABLE                          (0x03)

   #define  AP_OUTBOUND                            (0x00)
   #define  AP_INBOUND                             (0x01)

   #define  AP_NOT_IN_PROGRESS                     (0x00)
   #define  AP_IN_PROGRESS                         (0x01)

   #define  AP_NOT_SUPPORTED                       (0x00)
   #define  AP_SUPPORTED                           (0x01)

   #define  AP_SSCP_PU_SESSION                     (0x00)
   #define  AP_SSCP_LU_SESSION                     (0x01)
   #define  AP_LU_LU_SESSION                       (0x02)

   #define  AP_DEACTIVATED                         (0x00)
   #define  AP_ACTIVATED                           (0x80)
   #define  AP_ACTIVATING                          (0x40)
   #define  AP_DEACTIVATING                        (0x20)
   #define  AP_DETACHING                           (0x10)

   #define  AP_HOST_CONNECTION                     (0x01)
   #define  AP_PEER_CONNECTION                     (0x02)
   #define  AP_BOTH_CONNECTION                     (0x03)

   #define  AP_CONALS_PND                          (0x02)
   #define  AP_XID_PND                             (0x03)
   #define  AP_CONTACT_PND                         (0x05)
   #define  AP_CONTACTED                           (0x06)
   #define  AP_DISC_PND                            (0x07)
   #define  AP_DISC_RQ                             (0x08)

   #define  AP_3270_EMULATION                      (0x00)
   #define  AP_LUA                                 (0x01)

   #define  AP_LU0                                 (0x00)
   #define  AP_LU1                                 (0x01)
   #define  AP_LU2                                 (0x02)
   #define  AP_LU3                                 (0x03)
   #define  AP_LU62                                (0x06)
   #define  AP_UNKNOWN                             (0xFF)

   #define  AP_LEASED_LINE                         (0x00)
   #define  AP_VX32                                (0x01)

   #define  AP_DISCONNECT                          (0x00)
   #define  AP_CONNECT                             (0x01)
   #define  AP_AUTO_CONNECT                        (0x02)

   #define  AP_FIXED                               (0x12)
   #define  AP_ADAPTIVE                            (0x13)

   #define  AP_NOT_BOUND                           (0x00)
   #define  AP_BOUND                               (0x80)
   #define  AP_BINDING                             (0x40)
   #define  AP_UNBINDING                           (0x20)

/*****************************************************************************/
/* End Definitions from APPCDEF.H file (retired)                             */
/*****************************************************************************/

typedef struct cnos {
    unsigned short opcode;              /* Verb operation code               */
                                        /* AP_CNOS                           */
    unsigned char  reserv2[2];          /* Reserved                          */
    unsigned short primary_rc;          /* Primary RETURN_CODE               */
    unsigned long  secondary_rc;        /* Secondary RETURN_CODE             */
    unsigned char  key[8];              /* Key (ASCII)                       */
    unsigned char  lu_alias[8];         /* LU Alias (ASCII)                  */
                                        /* 0 or 1-8 bytes                    */
    unsigned char  plu_alias[8];        /* Partner LU Alias (ASCII)          */
                                        /* 0 or 1-8 bytes                    */
    unsigned char  fqplu_name[17];      /* FQ Partner LU Name (EBCDIC type A */
                                        /* 0-17 bytes                        */
    unsigned char  reserv3;                    /* Reserved                          */
    unsigned char  mode_name[8];        /* Mode Name (EBCDIC type A)         */
                                        /* 0-8 bytes                         */
    unsigned int   mode_name_select:1;  /* Bit 15                            */
                                        /* Mode name select                  */
                                        /* AP_ONE                            */
                                        /* AP_ALL                            */
    unsigned int   set_negotiable:1;    /* Bit 14                            */
                                        /* Set negotiable?                   */
                                        /* AP_NO                             */
                                        /* AP_YES                            */
    unsigned int   reserv4:6;           /* Bits 8-13                         */
                                        /* Reserved                          */
    unsigned int   reserv5:8;           /* Bits 0-7                          */
                                        /* Reserved                          */
    unsigned short plu_mode_sess_lim;   /* Partner LU mode session limit     */
                                        /* 0-32767                           */
    unsigned short min_conwinners_source;
                                        /* Minimum contention winners source */
                                        /* 0-32767                           */
    unsigned short min_conwinners_target;
                                        /* Minimum contention winners target */
                                        /* 0-32767                           */
    unsigned short auto_act;            /* Auto Activate                     */
                                        /* 0-32767                           */
    unsigned int   drain_target:1;      /* Bit 15                            */
                                        /* Drain Target?                     */
                                        /* AP_NO                             */
                                        /* AP_YES                            */
    unsigned int   drain_source:1;      /* Bit 14                            */
                                        /* Drain Source?                     */
                                        /* AP_NO                             */
                                        /* AP_YES                            */
    unsigned int   responsible:1;       /* Bit 13                            */
                                        /* Responsible?                      */
                                        /* AP_SOURCE                         */
                                        /* AP_TARGET                         */
    unsigned int   reserv6:5;           /* Bits 8-12                         */
                                        /* Reserved                          */
    unsigned int   reserv7:8;           /* Bit 0-7                           */
                                        /* Reserved                          */
} CNOS;

typedef struct display {
    unsigned short opcode;              /* Verb operation code               */
                                        /*    AP_DISPLAY                     */
    unsigned char  reserv2[2];          /* Reserved                          */
    unsigned short primary_rc;          /* Primary RETURN_CODE               */
    unsigned long  secondary_rc;        /* Secondary RETURN_CODE             */
    unsigned long  init_sect_len;       /* Length of this section            */
    unsigned long  buffer_len;          /* Length of passed buffer           */
    unsigned char  far *buffer_ptr;     /* Passed address                    */
    unsigned long  num_sections;        /* Number of sections                */
    unsigned long  display_len;         /* Returned, length used             */
    unsigned long  area_needed;         /* Returned, length required         */
    unsigned char  sna_global_info;     /* SNA global info?                  */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  lu62_info;           /* LU 6.2 info?                      */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  am_info;             /* Attach Manager info?              */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  tp_info;             /* TP info?                          */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  sess_info;           /* Session info?                     */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  link_info;           /* Link info?                        */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  lu_0_3_info;         /* LU 0, 1, 2, & 3 info?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  gw_info;             /* Gateway info?                     */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  x25_physical_link_info; /* X.25 info?                     */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  sys_def_info;        /* System Default info?              */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  adapter_info;        /* Adapter info?                     */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  lu_def_info;         /* LU definition info?               */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  plu_def_info;        /* Remote LU def info?               */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  mode_def_info;       /* Mode Definition info?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  link_def_info;       /* Link Definition info?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  ms_info;             /* Management Services info?         */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */

    /* Returned Pointers */

    /* Note that the address of the first of these pointers is */
    /*    address of the verb control block + init_sect_len    */

    struct sna_global_info_sect far          *sna_global_info_ptr;
    struct lu62_info_sect far                *lu62_info_ptr;
    struct am_info_sect far                  *am_info_ptr;
    struct tp_info_sect far                  *tp_info_ptr;
    struct sess_info_sect far                *sess_info_ptr;
    struct link_info_sect far                *link_info_ptr;
    struct lu_0_3_info_sect far              *lu_0_3_info_ptr;
    struct gw_info_sect far                  *gw_info_ptr;
    struct x25_physical_link_info_sect far   *x25_physical_link_info_ptr;
    struct sys_def_info_sect far             *sys_def_info_ptr;
    struct adapter_info_sect far             *adapter_info_ptr;
    struct lu_def_info_sect far              *lu_def_info_ptr;
    struct plu_def_info_sect far             *plu_def_info_ptr;
    struct mode_def_info_sect far            *mode_def_info_ptr;
    struct link_def_info_sect far            *link_def_info_ptr;
    struct ms_info_sect far                  *ms_info_ptr;
} DISPLAY;



typedef struct psid_struct             /* Product set id structure */
{
    unsigned char  machine_type[4];     /* Machine type                      */
    unsigned char  machine_mod_num[3];  /* Machine model number              */
    unsigned char  plant_of_mfg[2];     /* IBM manufacturing plant           */
    unsigned char  machine_seq_num[7];  /* Machine sequence number           */
} type_product_set_id;


typedef struct sna_global_info_sect {  /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: sna_global_info_ptr           */
  /**************************************************************************/

    unsigned char  version;             /* Communications Manager version    */
    unsigned char  release;             /* Communications Manager release    */
    unsigned char  net_name[8];         /* NETID (EBCDIC type A)             */
    unsigned char  pu_name[8];          /* PU name (EBCDIC type A)           */
    unsigned char  node_id[4];          /* Node ID used in XID               */
    type_product_set_id product_set_id; /* Product Set ID                    */
    unsigned char  alias_cp_name[8];    /* Alias CP Name (ASCII)             */
    unsigned char  node_type;           /* Node Type                         */
                                        /*    AP_NN                          */
                                        /*    AP_EN                          */
                                        /*    AP_LEN                         */
    unsigned char  cp_nau_addr;         /* CP NAU Address                    */
                                        /*  0 (not used...independent LU) OR */
                                        /*  1-254                            */
    unsigned char  corr_serv_disk;      /* Reserved                          */
    unsigned char  reserved;            /* Reserved                          */
    unsigned char  appc_version;        /* APPC version                      */
    unsigned char  appc_release;        /* APPC release                      */
    unsigned short appc_fixlevel;       /* APPC fix level                    */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} SNA_GLOBAL_INFO_SECT;



typedef struct lu62_info_sect {        /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: lu62_info_ptr                 */
  /**************************************************************************/

    unsigned long  lu62_init_sect_len;  /* Structure length                  */
    unsigned short num_lu62s;           /* Number of configured LUs displaye */
    unsigned short total_lu62s;         /* Total Number of configured LUs    */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/
} LU62_INFO_SECT;

typedef struct lu62_overlay {           /* One for each LU                   */

  /**************************************************************************/
  /* The address of the first of these structures should be: lu62_info_ptr +*/
  /* lu62_info_ptr->lu62_init_sect_len to find the next LU, add:            */
  /* lu62_entry_len                                                         */
  /**************************************************************************/

    unsigned long  lu62_entry_len;      /* Size of this LU entry             */
    unsigned long  lu62_overlay_len;    /* This value contains               */
                                        /*    sizeof(struct lu62_overlay) -  */
                                        /*    sizeof(lu62_entry_len)         */
    unsigned char  lu_name[8];          /* LU Name (EBCDIC type A)           */
    unsigned char  lu_alias[8];         /* LU Alias (ASCII)                  */
    unsigned short num_plus;            /* Number of partner LUs             */
    unsigned char  fqlu_name[17];       /* Fully Qualified LU Name           */
                                        /*    (EBCDIC type A)                */
    unsigned char  default_lu;          /* Default LU?                       */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned char  lu_local_addr;       /* NAU address 0-254                 */
    unsigned short lu_sess_lim;         /* Configured session limit          */
                                        /*    0-255                          */
    unsigned char  max_tps;             /* Max number of TPs 1-255           */
    unsigned char  lu_type;             /* Always LU type 6.2                */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LU62_OVERLAY;

typedef struct plu62_overlay {         /* One for each partner LU           */

  /**************************************************************************/
  /* The address of the first of these structures should be: The address of */
  /* the current lu62_overlay + lu62_overlay_len + sizeof(lu62_entry_len)   */
  /* To find the next partner LU, add: plu62_entry_len.                     */
  /**************************************************************************/

    unsigned long  plu62_entry_len;     /* Size of this partner LU           */
    unsigned long  plu62_overlay_len;   /* This value contains               */
                                        /*    sizeof(struct plu62_overlay) - */
                                        /*    sizeof(plu62_entry_len)        */
    unsigned char  plu_alias[8];        /* Partner LU Alias (ASCII)          */
    unsigned short num_modes;           /* Number of modes                   */
    unsigned char  plu_un_name[8];      /* Partner LU Uninterpreted Name     */
                                        /*    (EBCDIC)                       */
    unsigned char  fqplu_name[17];      /* Fully Qualified Partner LU Name   */
                                        /*    (EBCDIC type A)                */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned short plu_sess_lim;        /* Partner LU session limit          */
    unsigned char  dlc_name[8];         /* DLC name (ASCII)                  */
    unsigned char  adapter_num;         /* DLC adapter number                */
    unsigned char  dest_addr_len;       /* Length of adapter addr            */
    unsigned char  dest_addr[32];       /* Destination adapter addr          */
    unsigned int   par_sess_supp:1;     /* Bit 15  Parallel sessions?        */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   reserv4:7;           /* Bits 8-14  Reserved               */
    unsigned int   def_already_ver:1;   /* Bit 7  Configured already verif?  */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   def_conv_sec:1;      /* Bit 6  Configured conv security?  */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   def_sess_sec:1;      /* Bit 5  Configured session securit */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   reserv5:5;           /* Bits 0-4  Reserved                */
    unsigned int   act_already_ver:1;   /* Bit 15  Active already verified?  */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   act_conv_sec:1;      /* Bit 14  Active conversation sec?  */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   reserv6:6;           /* Bits 8-13  Reserved               */
    unsigned int   implicit_part:1;     /* Bit 7  Implicit partner?          */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   reserv7:7;           /* Bits 0-6  Reserved                */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} PLU62_OVERLAY;

typedef struct mode_overlay {           /* One for each mode                 */

  /**************************************************************************/
  /* The address of the first of these structures should be: The address of */
  /* the current plu62_overlay + plu62_overlay_len + sizeof(plu62_entry_len)*/
  /* To find the next mode, add: mode_entry_len.                            */
  /**************************************************************************/

    unsigned long  mode_entry_len;      /* Size of this mode                 */
    unsigned char  mode_name[8];        /* Mode Name (EBCDIC type A)         */
    unsigned short max_ru_size_upp;     /* Upper Limit on Max RU             */
    unsigned short max_ru_size_low;     /* Lower Limit on Max RU             */
    unsigned short max_neg_sess_lim;    /* Max Limit on Sessions             */
    unsigned short curr_sess_lim;       /* Current Session Limit             */
    unsigned short min_win_lim;         /* Min Negotiated Winners            */
    unsigned short min_lose_lim;        /* Min Negotiated Losers             */
    unsigned short act_sess_count;      /* Active Session Count              */
    unsigned short pend_sess_count;     /* Pending Session Count             */
    unsigned short auto_act_sess_count; /* Auto Activate Session Count       */
    unsigned short act_win_lim;         /* Active Winner Sessions            */
    unsigned short act_lose_lim;        /* Active Loser Sessions             */
    unsigned short term_count;          /* Session Termination Count         */

    unsigned int   drain_target:1;      /* Bit 15  Drain Target?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   drain_source:1;      /* Bit 14  Drain Source?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   reserv3:6;           /* Bits 8-13  Reserved               */
    unsigned int   pacing_size:8;       /* Bits 0-7  Pacing size             */
    /* The preceeding fields were previously defined as "unsigned char".    */
    /* They have been integrated into a bitfield to eliminate warning       */
    /* messages about 'bitfield types other than int'.                      */

    unsigned int   implicit_mode:1;     /* Bit 15  Implicit Mode?            */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   reserv4:7;           /* Bits 8-14  Reserved               */
    unsigned int   reserv5:8;           /* Bits 0-7  Reserved                */

    /************************************************************************/
    /* Reserved Additional fields may be added here in future releases      */
    /************************************************************************/

} MODE_OVERLAY;

typedef struct am_info_sect {           /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: am_info_ptr                   */
  /**************************************************************************/

    unsigned long  am_init_sect_len;    /* Structure length                  */
    unsigned char  am_active;           /* Attach Manager active?            */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  reserv4;             /* Reserved                          */
    unsigned short num_tps;             /* Number of configured TPs          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} AM_INFO_SECT;

typedef struct am_overlay {             /* One for each configued TP         */

  /**************************************************************************/
  /* The address of the first of these structures should be: am_info_ptr +  */
  /* am_info_ptr->am_init_sect_len. To find the next block of TP,           */
  /* information, add: am_entry_len.                                        */
  /**************************************************************************/


    unsigned long  am_entry_len;        /* Size of this structure            */
    unsigned char  tp_name[64];         /* TP name (EBCDIC type AE)          */
    unsigned char  filespec[64];        /* TP filespec (ASCII)               */

    unsigned int   reserv3:1;           /* Bit 15  Reserved                  */
    unsigned int   sync_level_conf:1;   /* Bit 14  Sync Level (Confirm) ?    */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   sync_level_none:1;   /* Bit 13  Sync Level (None) ?       */
                                        /*    AP_NOT_SUPPORTED               */
                                        /*    AP_SUPPORTED                   */
    unsigned int   reserv4:5;           /* Bits 8-12  Reserved               */
    unsigned int   conv_type:8;         /* Bits 0-7  Conversation type       */
                                        /*    AP_BASIC_CONVERSATION          */
                                        /*    AP_MAPPED_CONVERSATION         */
                                        /*    AP_EITHER                      */
    /* The preceeding fields were previously defined as "unsigned char".    */
    /* They have been integrated into a bitfield to eliminate warning       */
    /* messages about 'bitfield types other than int'.                      */

    unsigned short in_all_qdpth_lim;    /* Incoming Allocate queue depth lim */
    unsigned short in_all_qdpth;        /* Incoming Allocate queue depth     */
    short  in_all_timeout;              /* Incoming Allocate t/o             */
                                        /*    AP_HOLD_FOREVER or time in sec */
    unsigned short num_rcv_all_pend;    /* Number of pending                 */
                                        /* RECEIVE_ALLOCATEs                 */
    short  rcv_all_timeout;             /* RECEIVE_ALLOCATE t/o              */
                                        /*    AP_HOLD_FOREVER or time in sec */
    unsigned char  tp_type;             /* TP type                           */
                                        /*    AP_QUEUED_OPERATOR_STARTED     */
                                        /*    AP_QUEUED_AM_STARTED           */
                                        /*    AP_NONQUEUED_AM_STARTED        */
                                        /*    AP_QUEUED_OPERATOR_PRELOADED   */
    unsigned char  pgm_state;           /* Program state                     */
                                        /*    AP_INACTIVE                    */
                                        /*    AP_LOADED                      */
                                        /*    AP_LOADING                     */
                                        /*    AP_RUNNING                     */
    unsigned char  conv_sec;            /* Conversation security?            */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  reserv5;             /* Reserved                          */
    unsigned short process_id;          /* OS/2 process ID                   */
    unsigned char  parm_string[32];     /* Pgm parameter string              */
    unsigned char  program_type;        /* Program Type                      */
                                        /*    AP_BACKGROUND                  */
                                        /*    AP_FULL_SCREEN                 */
                                        /*    AP_PRESENTATION_MANAGER        */
                                        /*    AP_VIO_WINDOWABLE              */
    unsigned char  reserv5a;            /* Reserved                          */
    unsigned char  tp_initiated;        /* TP initiated                      */
                                        /*    AP_LOCALLY                     */
                                        /*    AP_REMOTELY                    */
    unsigned char  reserv6;             /* Reserved                          */
    unsigned char  icon_filespec[80];   /* Icon Filespec (ASCII)             */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} AM_OVERLAY;

typedef struct tp_info_sect {           /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: tp_info_ptr                   */
  /**************************************************************************/

    unsigned long  tp_init_sect_len;    /* Structure length                  */
    unsigned short num_tps;             /* Number of active TPs displayed    */
    unsigned short total_tps;           /* Total Number of Active TPs        */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} TP_INFO_SECT;

typedef struct tp_overlay {             /* One for each active TP            */

  /**************************************************************************/
  /* The address of the first of these structures should be: tp_info_ptr +  */
  /* tp_info_ptr->tp_init_sect_len.  To find the next block of active TP    */
  /* information, add: tp_entry_len                                         */
  /**************************************************************************/


    unsigned long  tp_entry_len;        /* Size of this TP record            */
    unsigned long  tp_overlay_len;      /* This value contains               */
                                        /*    sizeof(struct tp_overlay) -    */
                                        /*    sizeof(tp_entry_len)           */
    unsigned short num_conv;            /* Number of conversations           */
    unsigned char  tp_id[8];            /* TP ID                             */
    unsigned char  tp_name[64];         /* TP name (EBCDIC type AE)          */
    unsigned char  user_id[10];         /* User ID (EBCDIC type AE)          */
    unsigned int   reserv3:7;           /* Bits 9-15 Reserved                */
    unsigned int   loc_or_rem:1;        /* Bit 8  Initiated local or remote? */
                                        /*    AP_LOCAL                       */
                                        /*    AP_REMOTE                      */
    unsigned int   reserv4:8;           /* Bits 0-7 Reserved                 */
    unsigned char  lu_alias[8];         /* LU_ALIAS (ASCII)                  */
    LUW_ID_OVERLAY luw_id;              /* Logical Unit of Work ID           */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} TP_OVERLAY;

typedef struct conv_overlay {          /* One for each active conv          */

  /**************************************************************************/
  /* The address of the first of these structures should be: The address of */
  /* the current tp_overlay + tp_overlay_len + sizeof(tp_entry_len). To find*/
  /* the next block of conversation information, add: conv_entry_len        */
  /**************************************************************************/

    unsigned long  conv_entry_len;      /* Size of conversation information  */
    unsigned long  conv_id;             /* Conversation ID                   */
    unsigned char  reserv3[9];          /* Reserved                          */
    unsigned char  state;               /* Conversation state                */
                                        /*    AP_SEND_STATE                  */
                                        /*    AP_RECEIVE_STATE               */
                                        /*    AP_CONFIRM_STATE               */
                                        /*    AP_CONFIRM_SEND_STATE          */
                                        /*    AP_CONFIRM_DEALL_STATE         */
                                        /*    AP_PEND_POST_STATE             */
    unsigned char  sess_id[8];          /* Session ID                        */
    unsigned char  sync_level;          /* Sync level                        */
                                        /*    AP_NONE                        */
                                        /*    AP_CONFIRM                     */
    unsigned char  conv_type;           /* Conversation type                 */
                                        /*    AP_BASIC_CONVERSATION          */
                                        /*    AP_MAPPED_CONVERSATION         */
    unsigned long  conv_group_id;       /* Conversation Group ID             */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} CONV_OVERLAY;

typedef struct sess_info_sect {        /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: sess_info_ptr                 */
  /**************************************************************************/

    unsigned long  sess_init_sect_len;  /* Structure length                  */
    unsigned short num_sessions;        /* Number of Active Sessions         */
    unsigned short total_sessions;      /* Total Number of Active Sessions   */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} SESS_INFO_SECT;

typedef struct sess_overlay {          /* One for each active sess          */

  /**************************************************************************/
  /* The address of the first of these structures should be: sess_info_ptr +*/
  /* sess_info_ptr->sess_init_sect_len.  To find the next block of session  */
  /* information, add: sess_entry_len                                       */
  /**************************************************************************/

    unsigned long  sess_entry_len;      /* Size of session info              */
    unsigned long  reserv3;             /* Reserved                          */
    unsigned char  sess_id[8];          /* Session ID                        */
    unsigned long  conv_id;             /* Conversation ID                   */
    unsigned char  lu_alias[8];         /* LU Alias (ASCII)                  */
    unsigned char  plu_alias[8];        /* Partner LU Alias (ASCII)          */
    unsigned char  mode_name[8];        /* Mode Name (EBCDIC type A)         */
    unsigned short send_ru_size;        /* Max RU size for send              */
    unsigned short rcv_ru_size;         /* Max RU size for receive           */
    unsigned char  send_pacing_size;    /* Send pacing size                  */
    unsigned char  rcv_pacing_size;     /* Receive pacing size               */
    unsigned char  link_id[12];         /* Link ID (in APPC), or             */
                                        /* First Hop Link Name (in APPN)     */
    unsigned char  daf;                 /* Outbound DAF                      */
    unsigned char  oaf;                 /* Outbound OAF                      */
    unsigned char  odai;                /* ODAI                              */
    unsigned char  sess_type;           /* Type of session                   */
                                        /*    AP_SSCP_PU_SESSION             */
                                        /*    AP_SSCP_LU_SESSION             */
                                        /*    AP_LU_LU_SESSION               */
    unsigned char  conn_type;           /* Type of connection                */
                                        /*    AP_HOST_CONNECTION             */
                                        /*    AP_PEER_CONNECTION             */
                                        /*    AP_BOTH_CONNECTION             */
    unsigned char  reserv4;             /* Reserved                          */
    FQPCID_OVERLAY fqpcid;              /* Fully Qualified Procedure         */
                                        /* Correlation Identifier            */
    unsigned char  cgid[4];             /* Conversation Group ID             */
    unsigned char  fqlu_name[17];       /* Local Fully Qualifed LU Name      */
                                        /*        (EBCDIC)                   */
    unsigned char  fqplu_name[17];      /* Partner Fully Qualifed LU Name    */
                                        /*        (EBCDIC)                   */
    unsigned char  pacing_type;         /* Type of Pacing                    */
                                        /*    AP_FIXED                       */
                                        /*    AP_ADAPTIVE                    */
    unsigned char  reserv5;             /* Reserved                          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} SESS_OVERLAY;

typedef struct link_info_sect {        /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: link_info_ptr                 */
  /**************************************************************************/

    unsigned long  link_init_sect_len;  /* Structure length                  */
    unsigned short num_links;           /* Number of active links            */

    /*************************************************************************/
    /* This field added to make link_info_sect in API match the Link info    */
    /* section returned by the NS/2 management DLL.                          */
    /*************************************************************************/
    unsigned short total_links;         /* Total number of active links      */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LINK_INFO_SECT;


typedef struct link_overlay {          /* One for each active link          */

  /**************************************************************************/
  /* The address of the first of these structures should be: link_info_ptr +*/
  /* link_info_ptr->link_init_sect_len.  To find the next block of link     */
  /* information, add: link_entry_len                                       */
  /**************************************************************************/

    unsigned long  link_entry_len;      /* Size of link info, incl link spec */
    unsigned char  link_id[12];         /* Link ID (Link Name in EBCDIC A)   */
    unsigned char  dlc_name[8];         /* DLC name (ASCII)                  */
    unsigned char  adapter_num;         /* DLC adapter number                */
    unsigned char  dest_addr_len;       /* Length of adapter addr            */
    unsigned char  dest_addr[32];       /* Destination adapter addr          */
    unsigned char  inbound_outbound;    /* Inbound or outbound?              */
                                        /*    AP_OUTBOUND                    */
                                        /*    AP_INBOUND                     */
    unsigned char  state;               /* Link state                        */
                                        /*    AP_CONALS_PND                  */
                                        /*    AP_XID_PND                     */
                                        /*    AP_CONTACT_PND                 */
                                        /*    AP_CONTACTED                   */
                                        /*    AP_DISC_PND                    */
                                        /*    AP_DISC_RQ                     */
    unsigned char  deact_link_flag;     /* Deactivate logical link           */
                                        /*    AP_NOT_IN_PROGRESS             */
                                        /*    AP_IN_PROGRESS                 */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned short num_sessions;        /* Number of active sessions 0-65535 */
    unsigned short ru_size;             /* RU size 99-32767 (BTU Size)       */
    unsigned short reserv4;             /* Reserved                          */
    unsigned char  adj_fq_cp_name[17];  /* Adjacent Fully Qualified CP Name  */
    unsigned char  reserv5;             /* Reserved                          */
    unsigned char  adj_node_type;       /* Adjacent Node Type                */
                                        /*    AP_EN                          */
                                        /*    AP_NN                          */
                                        /*    AP_LEN                         */
    unsigned char  cp_cp_sess_spt;      /* CP CP Session Support             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  conn_type;           /* Type of Connection                */
                                        /*    AP_HOST_CONNECTION             */
                                        /*    AP_PEER_CONNECTION             */
                                        /*    AP_BOTH_CONNECTION             */
    unsigned char  ls_role;             /* Link Station Role                 */
                                        /*    AP_NEGOTIABLE                  */
                                        /*    AP_PRIMARY                     */
                                        /*    AP_SECONDARY                   */
    unsigned char  line_type;           /* Line Type                         */
                                        /*    AP_SWITCHED                    */
                                        /*    AP_NONSWITCHED                 */
    unsigned char  tg_number;           /* Transmission Group Number         */
    unsigned long  eff_capacity;        /* Effective Capacity                */
                                        /*    0 | 1200 | 2400 | ...          */
                                        /*    ... | 16M | ...                */
    unsigned char  conn_cost;           /* Cost Per Connect Time             */
    unsigned char  byte_cost;           /* Cost Per Byte                     */
    unsigned char  propagation_delay;   /* AP_PROP_DELAY_MINIMUM             */
                                        /*    AP_PROP_DELAY_LAN              */
                                        /*    AP_PROP_DELAY_TELEPHONE        */
                                        /*    AP_PROP_DELAY_PKT_SWITCHED_NET */
                                        /*    AP_PROP_DELAY_SATELLITE        */
                                        /*    AP_PROP_DELAY_MAXIMUM          */
    unsigned char  user_def_1;          /* User Defined 1                    */
    unsigned char  user_def_2;          /* User Defined 2                    */
    unsigned char  user_def_3;          /* User Defined 3                    */
    unsigned char  security;            /* Security                          */
                                        /*    AP_SEC_NONSECURE               */
                                        /*    AP_SEC_PUBLIC_SWITCHED_NETWORK */
                                        /*    AP_SEC_UNDERGROUND_CABLE       */
                                        /*    AP_SEC_SECURE_CONDUIT          */
                                        /*    AP_SEC_GUARDED_CONDUIT         */
                                        /*    AP_SEC_ENCRYPTED               */
                                        /*    AP_SEC_GUARDED_RADIATION       */
    unsigned char  reserv6;             /* Reserved                          */

    /************************************************************************/
    /* Additional fields of unspecified length are located in this position.*/
    /* Use link_entry_len to skip over them.                                */
    /************************************************************************/

} LINK_OVERLAY;

typedef struct lu_0_3_info_sect {      /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: lu_0_3_info_ptr               */
  /**************************************************************************/

    unsigned long  lu_0_3_init_sect_len; /* Structure length                 */
    unsigned short num_lu_0_3s;         /* Number of configured LUs          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LU_0_3_INFO_SECT;

typedef struct lu_0_3_overlay {        /* One for each configured LU        */

  /**************************************************************************/
  /* The address of the first of these structures should be: lu_0_3_info_ptr*/
  /* + lu_0_3_info_ptr->lu_0_3_init_sect_len.  To find the next one, add:   */
  /* lu_0_3_entry_len.                                                      */
  /**************************************************************************/

    unsigned long  lu_0_3_entry_len;    /* Size of this LU info              */
    unsigned char  access_type;         /* Access type                       */
                                        /*    AP_3270_EMULATION              */
                                        /*    AP_LUA                         */
    unsigned char  lu_type;             /* LU type                           */
                                        /*    AP_LU0                         */
                                        /*    AP_LU1                         */
                                        /*    AP_LU2                         */
                                        /*    AP_LU3                         */
    unsigned char  lu_daf;              /* NAU address                       */
    unsigned char  lu_short_name;       /* LU Short Name (ASCII)             */
    unsigned char  lu_long_name[8];     /* LU Long Name (ASCII)              */
    unsigned char  sess_id[8];          /* Session ID                        */
    unsigned char  dlc_name[8];         /* DLC Name (ASCII)                  */
    unsigned char  adapter_num;         /* DLC Adapter number                */
    unsigned char  dest_addr_len;       /* Length of Adapter Addr            */
    unsigned char  dest_addr[32];       /* Destination Adapter Addr          */
    unsigned char  sscp_lu_sess_state;  /* SSCP-LU Session State             */
                                        /*    AP_DEACTIVATED                 */
                                        /*    AP_ACTIVATED                   */
                                        /*    AP_ACTIVATING                  */
                                        /*    AP_DEACTIVATING                */
                                        /*    any of these 4 states can be   */
                                        /*    &'ed with: AP_DETACHING        */
    unsigned char  lu_lu_sess_state;    /* LU-LU Session State               */
                                        /*    AP_NOT_BOUND                   */
                                        /*    AP_BOUND                       */
                                        /*    AP_BINDING                     */
                                        /*    AP_UNBINDING                   */
    unsigned char  link_id[12];         /* Link ID                           */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LU_0_3_OVERLAY;

typedef struct gw_info_sect {          /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: gw_info_ptr                   */
  /**************************************************************************/

    unsigned long  gw_init_sect_len;    /* Structure length                  */
    unsigned short num_gw_lus;          /* Number of configured              */

    /************************************************************************/
    /* gateway LUs Additional fields may be added here in future releases   */
    /************************************************************************/

} GW_INFO_SECT;

typedef struct gw_overlay {            /* One for each gateway LU           */

  /**************************************************************************/
  /* The address of the first of these structures should be: gw_info_ptr +  */
  /* gw_info_ptr->gw_init_sect_len. To find the next one, add: gw_entry_len.*/
  /**************************************************************************/

    unsigned long  gw_entry_len;        /* Size of the gateway info          */
    unsigned char  ws_lu_name[8];       /* WS LU name (EBCDIC)               */
    unsigned char  ws_pu_name[8];       /* WS PU name (EBCDIC)               */
    unsigned char  ws_pool_class;       /* WS pool class                     */
    unsigned char  ws_local_addr;       /* Workstation local address         */
    unsigned char  host_local_addr;     /* Host local address                */
    unsigned char  ws_lu_type;          /* Workstation LU type               */
                                        /*    AP_LU0                         */
                                        /*    AP_LU1                         */
                                        /*    AP_LU2                         */
                                        /*    AP_LU3                         */
                                        /*    AP_LU62                        */
                                        /*    AP_UNKNOWN                     */
    unsigned char  host_lu_name[17];    /* Host LU name (EBCDIC)             */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned char  ws_dlc_name[8];      /* WS DLC name (ASCII)               */
    unsigned char  ws_adapter_num;      /* Workstation adapter num           */
    unsigned char  ws_dest_addr_len;    /* WS dest addr length               */
    unsigned char  ws_dest_addr[32];    /* WS destination addr               */
    unsigned int   ws_link_act:1;       /* Bit  15 WS link active?           */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_lu_pend_term:1;   /* Bit 14 LU-LU pending termination? */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_lu_pend_init:1;   /* Bit 13  LU-LU pending initiation? */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_lu_act:1;         /* Bit 12  LU-LU Active?             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_cp_pend_term:1;   /* Bit 11 LU-CP Pending Termination? */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_cp_pend_init:1;   /* Bit 10  LU-CP pending initiation? */
                                        /*    AP_NO                          */
                                        /* AP_YES                            */
    unsigned int   lu_cp_act_offline:1; /* Bit 9  LU-CP active offline?      */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   lu_cp_act_online:1;  /* Bit 8  LU-CP active online?       */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned int   reserv4:8;           /* Bits 0-7  Reserved                */

    /************************************************************************/
    /* Reserved Additional fields may be added here in future releases      */
    /************************************************************************/

} GW_OVERLAY;

typedef struct x25_physical_link_info_sect { /* One of these                */

  /**************************************************************************/
  /* The address of this structure should be: x25_info_ptr                  */
  /**************************************************************************/

    unsigned long  x25_init_sect_len;   /* Structure length                  */
    unsigned short num_x25_links;       /* Number of X.25 physical links     */
    unsigned short num_x25_link_entries;
                                        /* Total Number of X.25 phys. links  */

    /************************************************************************/
    /* physical link entries Additional fields may be added here in future  */
    /* releases                                                             */
    /************************************************************************/

} X25_PHYSICAL_LINK_INFO_SECT;

typedef struct x25_overlay {           /* One for each X.25 link            */

  /**************************************************************************/
  /* The address of the first of these structures should be: x25_info_ptr + */
  /* x25_info_ptr->x25_init_sect_len.  To find the next one, add:           */
  /* x25_entry_len                                                          */
  /**************************************************************************/

    unsigned long  x25_entry_len;       /* Size of X.25 information          */
    unsigned char  link_name[8];        /* X.25 Link Name (ASCII)            */
    unsigned char  link_comments[60];   /* Comment Field (ASCII)             */
    unsigned short adapter_slot_num;    /* Adapter Slot Number               */
    unsigned char  link_type;           /* Link Type                         */
                                        /*    AP_LEASED_LINE                 */
                                        /*    AP_VX32                        */
    unsigned char  link_mode;           /* Link Mode                         */
                                        /*    AP_DISCONNECT                  */
                                        /*    AP_CONNECT                     */
                                        /*    AP_AUTO_CONNECT                */
    unsigned char  link_state;          /* Link State                        */
                                        /*    AP_CONNECTING                  */
                                        /*    AP_CONNECTED                   */
                                        /*    AP_ERROR_LEVEL_1               */
                                        /*    AP_ERROR_LEVEL_2               */
                                        /*    AP_DISCONNECTING               */
                                        /*    AP_DISCONNECTED                */
                                        /*    AP_ADAPTER_ERROR               */
                                        /*    AP_ADAPTER_ACCESS_ERROR        */
                                        /*    AP_INCOMING_WAIT               */
    unsigned char  link_direction;      /* Link Direction                    */
                                        /*    AP_INCOMING                    */
                                        /*    AP_OUTGOING                    */
                                        /*    AP_2_WAY                       */
    unsigned short num_act_pvcs;        /* Number of Active PVCs             */
    unsigned short total_num_pvcs;      /* Total Number of PVCs              */
    unsigned short num_act_svcs;        /* Number of Active SVCs             */
    unsigned short num_incoming_svcs;   /* Num of Incoming SVCs              */
    unsigned short num_2_way_svcs;      /* Number of 2-way SVCs              */
    unsigned short num_outgoing_svcs;   /* Num of Outgoing SVCs              */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} X25_OVERLAY;

typedef struct sys_def_info_sect {     /*                                   */

  /**************************************************************************/
  /* The address of this structure should be: sys_def_info_ptr              */
  /**************************************************************************/

    unsigned char  default_mode_name[8];
                                        /* Default Mode Name (EBCDIC type A) */
    unsigned char  default_local_lu_name[8];
                                        /* Default Local LU Name (EBCDIC     */
                                        /*    type A)                        */
    unsigned char  implicit_inb_rlu_supp; /* Implicit Remote LU Support      */
                                        /* AP_NO                             */
                                        /*    AP_YES                         */
    unsigned char  max_held_alerts;     /* Max Held Alerts 0-255             */
    unsigned char  tp_conv_sec_rqd;     /* TP Conversation Security Requeste */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned short max_mc_ll_send_size; /* Maximum Mapped Conversation       */
                                        /* Logical Record Send Size          */
                                        /*    0 or 2048 - 32767              */
    unsigned char  dir_for_attaches[64]; /* Directory For Inbound Attaches   */
    unsigned char  tp_operation;        /* Default TP Operation              */
                                        /*    AP_QUEUED_OPERATOR_STARTED     */
                                        /*    AP_QUEUED_AM_STARTED           */
                                        /*    AP_NONQUEUED_AM_STARTED        */
                                        /*    AP_QUEUED_OPERATOR_PRELOADED   */
    unsigned char  tp_program_type;     /* Default TP Program Type           */
                                        /*    AP_BACKGROUND                  */
                                        /*    AP_FULL_SCREEN                 */
                                        /*    AP_PRESENTATION_MANAGER        */
                                        /*    AP_VIO_WINDOWABLE              */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} SYS_DEF_INFO_SECT;

typedef struct adapter_info_sect {     /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: adapter_info_ptr              */
  /**************************************************************************/

    unsigned long  adapter_init_sect_len; /* Structure length                */
    unsigned short num_adapters;        /* Number of Adapters Displayed      */
    unsigned short total_adapters;      /* Total Number of Adapters          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} ADAPTER_INFO_SECT;

typedef struct adapter_overlay {       /* One for each adapter Displayed    */

  /**************************************************************************/
  /* The address of the first of these structures should be:                */
  /* adapter_info_ptr + adapter_info_ptr->adapter_init_sect_len.            */
  /* To find the next one, add: adapter_entry_len                           */
  /**************************************************************************/

    unsigned long  adapter_entry_len;   /* Size of Adapter Info              */
    unsigned char  dlc_name[8];         /* DLC Name (ASCII)                  */
    unsigned char  adapter_number;      /* Adapter Number                    */
                                        /*    0-255                          */
    unsigned char  ls_role;             /* Link Station Role                 */
                                        /*    AP_NEGOTIABLE                  */
                                        /*    AP_PRIMARY                     */
                                        /*    AP_SECONDARY                   */
    unsigned long  eff_capacity;        /* Effective Capacity                */
                                        /*    1200 | 2400 |...|16M|...       */
    unsigned char  conn_cost;           /* Cost Per Connect Time             */
    unsigned char  byte_cost;           /* Cost Per Byte                     */
    unsigned char  propagation_delay;   /* AP_PROP_DELAY_MINIMUM             */
                                        /*    AP_PROP_DELAY_LAN              */
                                        /*    AP_PROP_DELAY_TELEPHONE        */
                                        /*    AP_PROP_DELAY_PKT_SWITCHED_NET */
                                        /*    AP_PROP_DELAY_SATELLITE        */
                                        /*    AP_PROP_DELAY_MAXIMUM          */
    unsigned char  user_def_1;          /* User Defined 1                    */
    unsigned char  user_def_2;          /* User Defined 2                    */
    unsigned char  user_def_3;          /* User Defined 3                    */
    unsigned char  security;            /* Security                          */
                                        /*    AP_SEC_NONSECURE               */
                                        /*    AP_SEC_PUBLIC_SWITCHED_NETWORK */
                                        /*    AP_SEC_UNDERGROUND_CABLE       */
                                        /*    AP_SEC_SECURE_CONDUIT          */
                                        /*    AP_SEC_GUARDED_CONDUIT         */
                                        /*    AP_SEC_ENCRYPTED               */
                                        /*    AP_SEC_GUARDED_RADIATION       */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned char  line_type;           /* Line Yype                         */
                                        /*    AP_SWITCHED                    */
                                        /*    AP_NONSWITCHED                 */
    unsigned char  lim_res;             /* Limited Resource ?                */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned short lim_res_timeout;     /* Limited Resource Timeout          */
                                        /*    0-127 ???                      */
    unsigned short max_btu_size;        /* Maximum BTU Size 99-32767         */
    unsigned char  rcv_window;          /* Receive Window 0-127              */
    unsigned char  send_window;         /* Send Window 0-127                 */
    unsigned short max_ls_used;         /* Max Link Stations                 */
    unsigned char  abm_support;         /* Asynchronous Balanced Mode Used?  */
                                        /* AP_NO                             */
                                        /*    AP_YES                         */
    unsigned char  reserv4;             /* Reserved                          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} ADAPTER_OVERLAY;


typedef struct lu_def_info_sect {      /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: lu_def_info_ptr               */
  /**************************************************************************/

    unsigned long  lu_def_init_sect_len; /* Structure length                 */
    unsigned short num_lu_def;          /* Number of LU Definitions Displaye */
    unsigned short total_lu_def;        /* Total Number of LU Definitions    */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LU_DEF_INFO_SECT;

typedef struct lu_def_overlay {        /* One for each lu_def Displayed     */

  /**************************************************************************/
  /* The address of the first of these structures should be: lu_def_info_ptr*/
  /* + lu_def_info_ptr->lu_def_init_sect_len.  To find the next one, add:   */
  /* lu_def_entry_len                                                       */
  /**************************************************************************/

    unsigned long  lu_def_entry_len;    /* Size of lu def info               */
    unsigned char  lu_name[8];          /* LU_NAME (EBCDIC type A)           */
    unsigned char  lu_alias[8];         /* LU_ALIAS (ASCII)                  */
    unsigned char  lu_nau_addr;         /* NAU address 0-254                 */
    unsigned char  reserv3;             /* Reserved                          */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LU_DEF_OVERLAY;

typedef struct plu_def_info_sect {     /*   One of these                    */

  /**************************************************************************/
  /* The address of this structure should be: plu_def_info_ptr              */
  /**************************************************************************/

    unsigned long  plu_def_init_sect_len; /* Struct length                   */
    unsigned short num_plu_def;         /* Number of Partner LU defs Display */
    unsigned short total_plu_def;       /* Total Number of Partner LU defs   */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} PLU_DEF_INFO_SECT;

typedef struct plu_def_overlay {       /* One for each plu_def displayed    */

  /**************************************************************************/
  /* The address of the first of these structures should be:                */
  /* plu_def_info_ptr + plu_def_info_ptr->plu_def_init_sect_len.  To find   */
  /* the next one, add: plu_def_entry_len.                                  */
  /**************************************************************************/

    unsigned long  plu_def_entry_len;   /* Size of plu def info              */
    unsigned char  fqplu_name[17];      /* PLU Name (EBCDIC)                 */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned char  plu_alias[8];        /* Partner LU Alias                  */
    unsigned char  plu_uninterpreted_name[8];
                                        /* Partner LU Uninterpreted Name     */
                                        /*           (EBCDIC)                */
    unsigned short max_mc_ll_ssize;     /* Maximum Mapped Conversation       */
                                        /* Logical Record Send Size          */
                                        /*    0 or 2048 - 32767              */
    unsigned char  conv_security;       /* Conversation Security             */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  parallel_sess;       /* Parallel Session Support          */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  alt_alias_flag;      /* Alternate PLU aliases flag        */
                                        /*    0 = Alternate PLU aliases      */
                                        /*        appended to end of struct  */
    unsigned char  num_of_alt_aliases;  /* Number of alternate PLU aliases   */
                                        /* (not including the plu_alias).    */
                                        /*    0 or # of alt_alias_overlays   */
    /************************************************************************/
    /* The address of the first alternate partner LU alias is:              */
    /* plu_def_overlay + sizeof(struct plu_def_overlay).  To build the addr */
    /* of the next partner LU alias, add: sizeof(struct alt_alias_overlay). */
    /* See struct alt_alias_overlay in APPCDEF.H.                           */
    /************************************************************************/

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} PLU_DEF_OVERLAY;

typedef struct mode_def_info_sect {    /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: mode_def_info_ptr             */
  /**************************************************************************/

    unsigned long  mode_def_init_sect_len; /* Struct length                  */
    unsigned short num_mode_def;        /* Number of Mode Definitions Dsplyd */
    unsigned short total_mode_def;      /* Total Number of Mode Definitions  */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} MODE_DEF_INFO_SECT;

typedef struct mode_def_overlay {      /* One for each mode_def Displayed   */

  /**************************************************************************/
  /* The address of the first of these structures should be:                */
  /* mode_def_info_ptr + mode_def_info_ptr->mode_def_init_sect_len.  To find*/
  /* the next one, add: mode_def_entry_len                                  */
  /**************************************************************************/

    unsigned long  mode_def_entry_len;  /* Size of mode def info             */
    unsigned char  cos_name[8];         /* COS Name (EBCDIC)                 */
    unsigned char  mode_name[8];        /* Mode Name (EBCDIC)                */
    unsigned short reserv3;             /* reserved                          */
    unsigned short rusize_upper;        /* max RU size upper bound           */
                                        /*    256-65535                      */
    unsigned char  rcv_window;          /* receive pacing window             */
                                        /*    0 or 1-63                      */
    unsigned char  default_ru_size;     /* default ru size?                  */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned short  max_neg_sess_lim;   /* Max limit on sessions             */
    unsigned short  curr_sess_lim;      /* Current session limit             */
    unsigned short  min_win_lim;        /* Min negotiated winners            */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} MODE_DEF_OVERLAY;

typedef struct link_def_info_sect {    /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: link_def_info_ptr             */
  /**************************************************************************/

    unsigned long  link_def_init_sect_len; /* Structure length               */
    unsigned short num_link_def;        /* Number of Active Links Displayed  */
    unsigned short total_link_def;      /* Total Number of Active Links      */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} LINK_DEF_INFO_SECT;

typedef struct link_def_overlay {      /* One for each active link Displayed*/

  /**************************************************************************/
  /* The address of the first of these structures should be:                */
  /* link_def_info_ptr + link_def_info_ptr->link_def_init_sect_len. To find */
  /* the next block of link information, add: link_def_entry_len            */
  /**************************************************************************/

    unsigned long  link_def_entry_len;  /* Size of link info,                */
                                        /* including link specific           */
    unsigned char  link_name[8];        /* Link Name (EBCDIC)                */
    unsigned char  adj_fq_cp_name[17];  /* Adjacent Fully Qualified CP Name  */
                                        /*           (EBCDIC)                */
    unsigned char  adj_node_type;       /* adjacent node type                */
                                        /*    AP_LEARN                       */
                                        /*    AP_LEN                         */
                                        /*    AP_ADJACENT_NN                 */
    unsigned char  dlc_name[8];         /* DLC name (ASCII)                  */
    unsigned char  adapter_num;         /* DLC adapter number                */
    unsigned char  dest_addr_len;       /* Length of adapter addr            */
    unsigned char  dest_addr[32];       /* Destination adapter addr          */
    unsigned char  cp_cp_sess_spt;      /* CP CP session support?            */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  preferred_nn_server; /* Is this the Pref. NN Server?      */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  auto_act_link;       /* Auto Activate Link?               */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  tg_number;           /* Transmission Group Number         */
    unsigned char  lim_res;             /* Limited Resource ?                */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
                                        /*    AP_USE_ADAPTER_DEF_CHAR        */
    unsigned char  solicit_sscp_session; /* Solicit SSCP Session?            */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  initself;            /* Initself Indicator                */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  bind_support;        /* Bind Support?                     */
                                        /*    AP_NO                          */
                                        /*    AP_YES                         */
    unsigned char  ls_role;             /* link station role                 */
                                        /*    AP_NEGOTIABLE                  */
                                        /*    AP_PRIMARY                     */
                                        /*    AP_SECONDARY                   */
    unsigned char  line_type;           /* Line Type                         */
                                        /*    AP_SWITCHED                    */
                                        /*    AP_NONSWITCHED                 */
    unsigned long  eff_capacity;        /* Effective Capacity                */
                                        /*    0 | 1200 | 2400 | ...          */
                                        /*    ... | 16M | ...                */
    unsigned char  conn_cost;           /* Cost Per Connect Time             */
    unsigned char  byte_cost;           /* Cost Per Byte                     */
    unsigned char  propagation_delay;   /* AP_PROP_DELAY_MINIMUM             */
                                        /*    AP_PROP_DELAY_LAN              */
                                        /*    AP_PROP_DELAY_TELEPHONE        */
                                        /*    AP_PROP_DELAY_PKT_SWITCHED_NET */
                                        /*    AP_PROP_DELAY_SATELLITE        */
                                        /*    AP_PROP_DELAY_MAXIMUM          */
    unsigned char  user_def_1;          /* User Defined 1                    */
    unsigned char  user_def_2;          /* User Defined 2                    */
    unsigned char  user_def_3;          /* User Defined 3                    */
    unsigned char  security;            /* Security                          */
                                        /*    AP_SEC_NONSECURE               */
                                        /*    AP_SEC_PUBLIC_SWITCHED_NETWORK */
                                        /*    AP_SEC_UNDERGROUND_CABLE       */
                                        /*    AP_SEC_SECURE_CONDUIT          */
                                        /*    AP_SEC_GUARDED_CONDUIT         */
                                        /*    AP_SEC_ENCRYPTED               */
                                        /*    AP_SEC_GUARDED_RADIATION       */
    unsigned char  reserv;                     /* Reserved                          */

    /************************************************************************/
    /* Additional fields of unspecified length are located in this position.*/
    /* Use link_entry_len to skip over them.                                */
    /************************************************************************/

} LINK_DEF_OVERLAY;

typedef struct ms_info_sect  {          /* One of these                      */

  /**************************************************************************/
  /* The address of this structure should be: ms_info_ptr                   */
  /**************************************************************************/

    unsigned long  ms_init_sect_len;    /* Structure length                  */
    unsigned char  held_mds_mu_alerts;  /* Held mds alerts                   */
                                        /*    1-255                          */
    unsigned char  held_nmvt_alerts;    /* Held nmvt alerts                  */
                                        /*    1-255                          */
    unsigned short num_fps;             /* Number of Focal Points Displayed  */
    unsigned short total_fps;           /* Total Number of Focal Points      */
    unsigned short num_ms_appls;        /* Num. of MS Applications Displayed */
    unsigned short total_ms_appls;      /* Total Number of MS Applications   */
    unsigned short num_act_trans;       /* # of Active Transactions Displaye */
    unsigned short total_act_trans;     /* Total Num. of Active Transactions */

    /************************************************************************/
    /* Additional fields may be added here in future releases               */
    /************************************************************************/

} MS_INFO_SECT;

typedef struct ms_fp_overlay {         /* One each MS Focal Point Displayed */

  /**************************************************************************/
  /* The address of the first of these structures should be: ms_info_ptr +  */
  /* ms_info_ptr->ms_init_sect_len.  To find the next the next one, add:    */
  /* ms_fp_entry_len.                                                       */
  /**************************************************************************/

    unsigned long  ms_fp_entry_len;     /* Size of MS Focal point info       */
    unsigned char  ms_appl_name[8];     /* MS Application name               */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */
    unsigned char  ms_category[4];      /* MS Category                       */
                                        /* 0 or 4 byte SNA Defined Category  */
    unsigned char  fp_fq_cp_name[17];   /* Focal Point Fully Qual. CP Name   */
                                        /*    (EBCDIC type A)                */
    unsigned char  bkup_appl_name[8];   /* Backup MS Application Name        */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */
    unsigned char  bkup_fp_fq_cp_name[17]; /* Backup Focal Point Name        */
                                        /*    (EBCDIC type A)                */
    unsigned char  reserv1;             /* Reserved                          */
    unsigned char  fp_type;             /* focal point rank                  */
                                        /*    AP_EXPLICIT_PRIMARY_FP         */
                                        /*    AP_BACKUP_FP                   */
                                        /*    AP_DEFAULT_PRIMARY_FP          */
                                        /*    AP_DOMAIN_FP                   */
                                        /*    AP_HOST_FP                     */
                                        /*    AP_NO_FP                       */
    unsigned char  fp_status;           /* focal point status                */
                                        /*    AP_NOT_ACTIVE                  */
                                        /*    AP_ACTIVE                      */
                                        /*    AP_PENDING                     */
                                        /*    AP_NEVER_ACTIVE                */
    unsigned char  fp_routing;          /* focal point routing               */
                                        /*    AP_DEFAULT                     */
                                        /*    AP_DIRECT                      */

    /************************************************************************/
    /* Additional fields of unspecified length are located in this position.*/
    /* Use ms_fp_entry_len to skip over them.                               */
    /************************************************************************/

} MS_FP_OVERLAY;

typedef struct ms_appl_overlay {       /* One each MS application Displayed */

  /**************************************************************************/
  /* The first ms_appl_overlay follows immediately after the last ms_fp     */
  /* overlay.  Hence, the address of the first ms_appl_overlay should be:   */
  /* the address of the last ms_fp_overlay + ms_fp_entry length.            */
  /* To find the next ms_appl_overlay, add:  ms_appl_entry_length.          */
  /**************************************************************************/

    unsigned long  ms_appl_entry_len;   /* Size of MS application info       */
    unsigned char  ms_appl_name[8];     /* MS Application name               */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */
    unsigned char  ms_category[4];      /* MS Category                       */
                                        /* 0 or 4 byte SNA Defined Category  */
    unsigned char  q_name[81];          /* OS/2 Queue Name (ASCIIZ)          */
    unsigned char  reserv3;             /* Reserved                          */
    unsigned char  reserv4;             /* Reserved                          */
    unsigned char  reserv5;             /* Reserved                          */

    /************************************************************************/
    /* Additional fields of unspecified length are located in this position.*/
    /* Use ms_appl_entry_len to skip over them.                             */
    /************************************************************************/

} MS_APPL_OVERLAY;

typedef struct ms_act_trans_overlay  {  /* One each MS active trans Displayed*/

  /**************************************************************************/
  /* The first ms_act_trans_overlay follows immediately after the last      */
  /* ms_appl overlay.  Hence, the address of the first ms_act_trans_overlay */
  /* should be:                                                             */
  /*  the address of the last ms_appl_overlay + ms_appl_entry length.       */
  /* To find the next ms_act_trans_overlay, add:  ms_act_trans_entry_length.*/
  /**************************************************************************/

    unsigned long  ms_act_trans_entry_len; /* Size of info                   */
    unsigned char  fq_origin_cp_name[17];
                                        /* Fully Qualified Origin CP Name    */
                                        /*    (EBCDIC type A)                */
    unsigned char  origin_ms_appl_name[8]; /* Origin MS Application Name     */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */
    unsigned char  fq_dest_cp_name[17]; /* Fully Qualified Dest. CP Name     */
                                        /*    (EBCDIC type A)                */
    unsigned char  dest_ms_appl_name[8]; /* Dest. MS Application Name        */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */

    /************************************************************************/
    /* the following 3 fields are part of the Unit of Work (UOW)            */
    /************************************************************************/

    unsigned char  fq_req_loc_cp_name[17]; /* Requester Location             */
                                        /*    (EBCDIC type A)                */
    unsigned char  req_agent_appl_name[8]; /* Requester Application Name     */
                                        /*    4 byte SNA Defined MS Appl Name*/
                                        /* or 1-8 byte (EBCDIC type A)       */
    unsigned char  seq_num_dt[15];      /* Sequence Number / date - time     */

    /************************************************************************/
    /* Additional fields of unspecified length are located in this position.*/
    /* Use ms_act_trans_entry_len to skip over them.                        */
    /************************************************************************/

} MS_ACT_TRANS_OVERLAY;

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