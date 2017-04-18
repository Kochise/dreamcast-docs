/*
 * Wave Sampling Library for SIP(Speech Input Peripheral)
 * based on Wave Sampling Library for SIP specification 0.84
 *
 * 1998-04-22
 * SEKI Masahiro, System R&D
 * 1998-05-17 recompiled for SHINOBI SDK version040jp2 by SEKI Masahiro
 * 1999-04-11 work around for SIP+MAXI problems by SEKI Masahiro
 * 1999-06-28 modified for wsStmIsOverflow by SEKI Masahiro
 * 1999-06-28 added for wsStmCopySample version 1.04 by SEKI Masahiro
 */

#ifndef _PROTO_WS_H
#define _PROTO_WS_H

/*
 * C VIRTUAL TYPES DEFINITIONS
 */

/**************************************************************************/
/******** Define **********************************************************/
/**************************************************************************/
/******** Function error code *********************************************/
#define WSD_ERR_OK            (0)         /* No error                     */
#define WSD_ERR_FATAL         (-1)        /* SIP restart by SIP cpu       */

/******** Maximum index of WSB handle *************************************/
#define WSD_BUF_WSBUF_MAX      (4)       /* Maximum number of WSBUF handle*/
/******** Maximum index of WSSTM handle ***********************************/
#define WSD_STM_WSSTM_MAX      (16)      /* Maximum number of WSSTM handle*/

/******** SAMPLING FREQUENCY **********************************************/
#define WSD_BUF_SFREQ_11KHZ    (0)         /* 11025 Hz sampling           */
#define WSD_BUF_SFREQ_8KHZ     (1)         /* 8000 Hz sampling            */

/******** BITS PER SAMPLING ***********************************************/
#define WSD_BUF_BPS_16BIT      (0)         /* 16bit linear sampling       */
#define WSD_BUF_BPS_8BIT       (1)         /* 8bit u-law codec sampling   */

/******** AMP GAIN ********************************************************/
#ifndef WSD_TRIAL_SIP
#define WSD_BUF_GAIN_MAX        (16)        /* MAXIMUM VOLUME              */
#define WSD_BUF_GAIN_MIN        (-15)       /* MINIMUM VOLUME              */
#else
#define WSD_BUF_GAIN_MAX        (8)         /* MAXIMUM VOLUME              */
#define WSD_BUF_GAIN_MIN        (-7)        /* MINIMUM VOLUME              */
#endif /* WSD_TRIAL_SIP */

/******** DEVICE ID ********************************************************/
#define WSD_DEV_A1              (1)         /* Device number               */
#define WSD_DEV_A2              (2)
#define WSD_DEV_A3              (3)
#define WSD_DEV_A4              (4)
#define WSD_DEV_A5              (5)
#define WSD_DEV_B1              (7)
#define WSD_DEV_B2              (8)
#define WSD_DEV_B3              (9)
#define WSD_DEV_B4              (10)
#define WSD_DEV_B5              (11)
#define WSD_DEV_C1              (13)
#define WSD_DEV_C2              (14)
#define WSD_DEV_C3              (15)
#define WSD_DEV_C4              (16)
#define WSD_DEV_C5              (17)
#define WSD_DEV_D1              (19)
#define WSD_DEV_D2              (20)
#define WSD_DEV_D3              (21)
#define WSD_DEV_D4              (22)
#define WSD_DEV_D5              (23)

/******** Wave sampling buffer status *************************************/
#define WSD_STAT_DISCNCT      (0)         /* SIP device is not connected  */
#define WSD_STAT_STOP         (1)         /* Sampling stopped             */
#define WSD_STAT_REC          (2)         /* Sampling on going            */
#define WSD_STAT_ERR          (3)         /* Error status                 */
#define WSD_STAT_RETRY        (4)         /* Retry in error               */
#define WSD_STAT_RESTART      (5)         /* Restart SIP by SIP cpu       */
#define WSD_STAT_RESET        (6)         /* Reset SIP for SIP+MAXI Workaround */

/******** Read pointer setting for wsStmSeekRdPos() ************************/
#define WSD_STM_SEEK_SET       (0)  /* Set read pointer to the oldest point*/
#define WSD_STM_SEEK_CUR       (1)  /* Set read pointer to current point   */
#define WSD_STM_SEEK_END       (2)  /* Set read pointer to the latest point*/


/***************************************************************************/
/******** Structures *******************************************************/
/***************************************************************************/
/******** Structure for writing point **************************************/
typedef struct _WSS_POS {
    Uint32 high;                   /* higher count                         */
    Uint32 low;                    /* lower count                          */
} WSS_POS;


/***************************************************************************/
/******** Handles **********************************************************/
/***************************************************************************/
/******** Handle for ring buffer *******************************************/
typedef struct _WSBUF_OBJ {
    Uint8 recStat;                 /* Recording status                     */
    Uint8 storeStat;               /* store status when any device insertion */
    Uint8 use;                     /* In use or not in use                 */
    Sint32 sfreq;                  /* Sampling frequency                   */
    Sint32 bps;                    /* Bits per a sample(16/8) 8:u-law codec*/
    Sint32 blksize;                /* Block size                           */
    Sint32 nblk;                   /* Numbers of block in a ring buffer    */
    Sint32 bufnsmpl;               /* Size of a ring buffer (unit:samples) */
    Sint32 gain;                   /* AMP GAIN level of SIP                */
    Sint32 seq;                    /* Sequence number when command sent    */
    Sint32 lastSeq;                /* The last sequence existence flag     */
    Sint32 device;                 /* Device number of Peripheral          */
    Sint32 command;                /* command to SIP                       */
    Sint32 lastCom;                /* last commnad                         */
    Sint32 initSeq;                /* number of initializing sequence      */
    Sint32 lastNsmpl;
    Sint32 sbfov;                  /* SIP sound buffer overflow flag       */
    WSS_POS wpos;                  /* Writing position in a ring buffer    */
    Sint32 err;                    /* error code                           */
    void *bufptr;                  /* Address of a ring buffer             */
} WSBUF_OBJ, *WSBUF;

/******** Structure for setting of SIP *************************************/
typedef struct _WSS_BUF_PRM {
    Sint32 sfreq;                  /* Sampling frequency                   */
    Sint32 bps;                    /* Bits per a sample(16/8) 8:u-law codec*/
    Sint32 blksize;                /* Block size                           */
    Sint32 nblk;                   /* Numbers of block in a ring buffer    */
    Sint32 gain;                   /* AMP GAIN level of SIP                */
    void *bufptr;                  /* Address of a ring buffer             */
} WSS_BUF_PRM;

/******** Handle for getting data ******************************************/
typedef struct _WSSTM_OBJ {
    Uint8 overFlag;                /* over-flow flag                       */
    Uint8 use;                     /* In use or not in use                 */
    WSBUF wsb;                     /* handle of buffer to streaming        */
    WSS_POS rpos;                  /* reading position                     */
} WSSTM_OBJ, *WSSTM;

Sint32 wsInit( void );
void wsFinish( void );

WSBUF wsBufCreate( Sint32 pno, WSS_BUF_PRM para );
void wsBufDestroy( WSBUF wsbuf );
Sint32 wsBufStart( WSBUF wsbuf );
Sint32 wsBufStop( WSBUF wsbuf );
void wsBufExecServer( void);
Sint32 wsBufGetStat( WSBUF wsbuf );
Sint32 wsBufGetErr( WSBUF wsbuf );
Sint32 wsBufGetNumSmpl( WSBUF wsbuf );
WSS_POS wsBufGetWrPos( WSBUF wsbuf );
Sint32 wsBufGetSfreq( WSBUF wsbuf );
Sint32 wsBufGetBitPerSmpl( WSBUF wsbuf );
Sint32 wsBufGetAmpGain( WSBUF wsbuf );
Sint32 wsBufSetAmpGain( WSBUF wsbuf, Sint32 gain );
Sint32 wsBufGetSBFOV( WSBUF wsbuf );

WSSTM wsStmCreate( WSBUF wsbuf );
void wsStmDestroy( WSSTM wsstm );
WSBUF wsStmGetWsbuf( WSSTM wsstm );
Sint32 wsStmGetNumSmpl(WSSTM wsstm );
WSS_POS wsStmSeekRdPos( WSSTM wsstm, WSS_POS pos, Sint32 mode );
WSS_POS wsStmGetRdPos( WSSTM wsstm );
WSS_POS wsStmAddRdPos( WSSTM wsstm, Sint32 nsmpl );
#if 0 /* 19990628 */
Bool wsStmIsOverFlow( WSSTM wsstm );
#else
Bool wsStmIsOverflow( WSSTM wsstm );
#endif
void wsStmClearOverflow( WSSTM wsstm );
Sint32 wsStmCopyPcm( WSSTM wsstm, void *buf, Sint32 bufsite );
#if 1 /* 19990628 */
Sint32 wsStmCopySample( WSSTM wsstm, void *buf, Sint32 nsample );
#endif

/*** Operate functions for WSS_POS *****************************************/
WSS_POS wsPosAdd( WSS_POS pos, Sint32 num );
WSS_POS wsPosAddPos( WSS_POS posa, WSS_POS posb );
WSS_POS wsPosMinus( WSS_POS posa, WSS_POS posb );
Sint32 wsPosDif( WSS_POS posa, WSS_POS posb );
Sint32 wsPosMod( WSS_POS pos, Sint32 num );
WSS_POS wsPosMul2( WSS_POS pos );
Sint32 wsPosCmp( WSS_POS posa, WSS_POS posb );

#endif /* _PROTO_WS_H */