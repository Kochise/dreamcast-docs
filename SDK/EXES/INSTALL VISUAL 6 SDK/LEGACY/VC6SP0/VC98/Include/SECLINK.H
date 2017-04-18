/* Copyright Data Connection Ltd. 1989 */
/*****************************************************************************/
/* Link Device Driver interface constants and structures.                    */
/*****************************************************************************/
/*****************************************************************************/
/* WIN32  16/04/92  SW   Added more helpful names from WIN32 hdr file        */
/* IHV    03/06/92  MF2  Add semfisui.h                                      */
/* CDDD1  06/04/93  CD   Change TxFrame DevIoctl code                        */
/* STAT1  21/01/94  CD   Fix what we do with stats (& general cleanup)       */
/* MODEM  06/04/95  AB   Add support for the modem status program            */
/*****************************************************************************/

/*****************************************************************************/
/* This include file is used in 3 components                                 */
/*                                                                           */
/* - the NT   driver                         LINK_NTDRIVER                   */
/* - the X25  link service for NT            LINK_NTX25                      */
/* - the SDLC link service for NT            LINK_NTSDLC                     */
/*                                                                           */
/* These are distinguished based on #defines as set in the following         */
/*                                                                           */
/*****************************************************************************/

#ifdef        IMADRIVER
  #define     LINK_NTDRIVER
#else
  #ifdef      SDLC
    #define LINK_NTSDLC
  #else
    #define LINK_NTX25
  #endif
#endif


/*****************************************************************************/
/* Device function codes for DosDevIOCtl to link device driver               */
/*****************************************************************************/
#define IoctlCodeSetEvent               0x410
#define IoctlCodeSetLinkChar            0x420
#define IoctlCodeSetV24                 0x430
#define IoctlCodeTxFrame                0x441   /* Main Tx so 1         CDDD1*/
#define IoctlCodeAbortTransmit          0x450
#define IoctlCodeAbortReceiver          0x460
#define IoctlCodeSetInterfaceRecord     0x610   /* Retired                   */
#define IoctlCodeGetV24                 0x623   /* No data buffer so 3       */
#define IoctlCodeRxFrame                0x632   /* Main Rx so 2              */
#define IoctlCodeReadInterfaceRecord    0x642

/*****************************************************************************/
/* Constants for the driver-specific IOCtl return codes.                     */
/*****************************************************************************/
#define CEDNODMA 0xff80     /* Warning (NO DMA!) from set link chrctrstcs    */

/*****************************************************************************/
/* Equates for the link options byte 1.                                      */
/*****************************************************************************/
#define CEL4WIRE 0x80
#define CELNRZI  0x40
#define CELPDPLX 0x20
#define CELSDPLX 0x10
#define CELCLOCK 0x08
#define CELDSRS  0x04
#define CELSTNBY 0x02
#define CELDMA   0x01

/*****************************************************************************/
/* Equates for the driver set link characteristics byte 1.                   */
/*****************************************************************************/
#define CED4WIRE 0x80
#define CEDNRZI  0x40
#define CEDHDLC  0x20
#define CEDFDPLX 0x10
#define CEDCLOCK 0x08
#define CEDDMA   0x04
#define CEDRSTAT 0x02
#define CEDCSTAT 0x01

/* Nicer names for NT-style code */

#define LinkOption_4Wire           CED4WIRE
#define LinkOption_NRZI            CEDNRZI
#define LinkOption_HDLC            CEDHDLC
#define LinkOption_FullDuplex      CEDFDPLX
#define LinkOption_InternalClock   CEDCLOCK
#define LinkOption_DMA             CEDDMA
#define LinkOption_ResetStatistics CEDRSTAT


/*****************************************************************************/
/* Equates for the ouput V24 interface flags.                                */
/*****************************************************************************/
#define CED24RTS 0x01
#define CED24DTR 0x02
#define CED24DRS 0x04
#define CED24SLS 0x08
#define CED24TST 0x10

/* Nicer names for NT-style code */

#define IR_OV24RTS  CED24RTS
#define IR_OV24DTR  CED24DTR
#define IR_OV24DSRS CED24DRS
#define IR_OV24SlSt CED24SLS
#define IR_OV24Test CED24TST


/*****************************************************************************/
/* Equates for the input V24 interface flags.                                */
/*****************************************************************************/
#define CED24CTS 0x01
#define CED24DSR 0x02
#define CED24DCD 0x04
#define CED24RI  0x08

/* Nicer names for NT-style code */

#define IR_IV24CTS  CED24CTS
#define IR_IV24DSR  CED24DSR
#define IR_IV24DCD  CED24DCD
#define IR_IV24RI   CED24RI
#define IR_IV24Test 0x10


/*****************************************************************************/
/* Structure for the device driver interface record.                         */
/*****************************************************************************/

#define CEDSTCRC  0         /* Frames received with incorrect CRC            */
#define CEDSTOFL  1         /* Frames received longer than the maximum       */
#define CEDSTUFL  2         /* Frames received less than 4 octets long       */
#define CEDSTSPR  3         /* Frames received ending on a non-octet bndry   */
#define CEDSTABT  4         /* Aborted frames received                       */
#define CEDSTTXU  5         /* Transmitter interrupt underruns               */
#define CEDSTRXO  6         /* Receiver    interrupt overruns                */
#define CEDSTDCD  7         /* DCD (RLSD) lost during frame reception        */
#define CEDSTCTS  8         /* CTS lost while transmitting                   */
#define CEDSTDSR  9         /* DSR drops                                     */
#define CEDSTHDW 10         /* Hardware failures - adapter errors            */

#define CEDSTMAX 11

#define SA_CRC_Error       CEDSTCRC
#define SA_RxFrameTooBig   CEDSTOFL
#define SA_RxFrameTooShort CEDSTUFL
#define SA_Spare           CEDSTSPR
#define SA_RxAbort         CEDSTABT
#define SA_TxUnderrun      CEDSTTXU
#define SA_RxOverrun       CEDSTRXO
#define SA_DCDDrop         CEDSTDCD
#define SA_CTSDrop         CEDSTCTS
#define SA_DSRDrop         CEDSTDSR
#define SA_HardwareError   CEDSTHDW  /* e.g. CmdBufferFull not set  */

#define SA_Max_Stat        CEDSTMAX


typedef struct         _INTERFACE_RECORD
{
  /***************************************************************************/
  /* Note: we are here trying to mirror the OS/2 layout, complete with       */
  /*       lengths.  However, due to the (justifiable) pickiness of the 32-  */
  /*       bit compiler, all shorts have been changed to 'int's - that way   */
  /*       the results of calculations can be assigned to them without a lot */
  /*       of shenanigans (or typecasting).                                  */
  /***************************************************************************/
  int                   RxFrameCount;   /* incremented after each frame rx'd */
  int                   TxMaxFrSizeNow; /* max available frame size av. now  */
                                        /* (changes after each Tx DevIoctl   */
                                        /* to DD or after Tx completed)      */
  int                   StatusCount;    /* How many status events have been  */
                                        /* triggered.                        */
  UCHAR                 V24In;          /* Last 'getv24i/f' value got        */
  UCHAR                 V24Out;         /* Last 'setv24 outputs' value set   */

/*       The values for the indices into the link statistics array of the    */
/*       various types of statistic.                                         */
  int                   StatusArray[SA_Max_Stat];

}                       IR,
                     * PIR;

/*****************************************************************************/
/* New structure used by the link to acumulate stats                   *STAT1*/
/*****************************************************************************/
typedef struct _STATS
{
  int                   StatusCount;
  int                   StatusArray[SA_Max_Stat];
} STATS;


/*****************************************************************************/
/* Structure for the set link characteristics parameter block.               */
/*****************************************************************************/

typedef struct  _SLPARMS
{
        int     SLFrameSize;            /* max frame size on link - must be  */
                                         /* in range 270 to ?2K-ish          */
        LONG    SLDataRate;             /* not used by us - external clocks  */
        UCHAR   SLOurAddress1;          /* ) e.g C1/FF or 00/00 or 01/03     */
        UCHAR   SLOurAddress2;          /* )                                 */
        UCHAR   SLLinkOptionsByte;      /* see documentation & LinkOption_*  */
        UCHAR   SLSpare1;
}
                SLPARMS;

#ifndef IMADRIVER
/*****************************************************************************/
/* DEVICEIOCTL macros                                                        */
/*****************************************************************************/
/* NT_SUCCESS ripped of from DDK's ntdef.h, which we do not want to include  */
/* for now temporarily (12/5/92)                                             */

#define NT_SUCCESS(Status) ((NTSTATUS)(Status) >= 0)

#define SETEVENTHANDLE(H)                                                    \
           NtDeviceIoControlFile(seldrvrh,H,NULL,NULL,&IoStatus,             \
                                   IoctlCodeSetEvent,NULL,0L,NULL,0L)

#define SETINTERFACERECORD(R)                                                \
           NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,          \
                                   IoctlCodeSetInterfaceRecord,&R,sizeof(R), \
                                   NULL,0L)

#define SETV24STATUS                                                         \
           NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,          \
                                   IoctlCodeSetV24,NULL,0L,                  \
                                   &pInterfaceRecord->V24Out,1L);            \
                                                                             \
         if (SavedIROut != (pInterfaceRecord->V24Out & 0x03))                \
         {                                                                   \
           SavedIROut = (pInterfaceRecord->V24Out & 0x03);                   \
           pModemStatus->V24Out = pInterfaceRecord->V24Out;                  \
         }

#define GETV24STATUS(rc)                                                     \
         rc |= NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,      \
                                   IoctlCodeGetV24,NULL,0L,NULL,0L);         \
         rc |= READINTERFACERECORD;                                          \
         if (SavedIRIn != (InterfaceRecord.V24In & 0x0F))                    \
         {                                                                   \
           SavedIRIn = (InterfaceRecord.V24In & 0x0F);                       \
           pModemStatus->V24In = InterfaceRecord.V24In;                      \
         }


/*****************************************************************************/
/* Check for reset stats request and reset if required                 *STAT1*/
/*****************************************************************************/
#define SETLINKCHARACTERISTICS(A,rc)                                         \
           rc = NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,     \
                                  IoctlCodeSetLinkChar,&A,sizeof(A),NULL,0L);\
           if (A.SLLinkOptionsByte & CEDRSTAT)                               \
           {                                                                 \
             memset(&Stats,0,sizeof(STATS));                                 \
           }

/*****************************************************************************/
/* Note we now pass the user buffer in the input fields, not the output      */
/* fields                                                               CDDD1*/
/*****************************************************************************/
#define TRANSMITFRAME(A,B)                                                   \
           NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,          \
                                   IoctlCodeTxFrame,A,B,NULL,0L);


#define RECEIVEFRAME(A,B)                                                    \
           NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,          \
                                   IoctlCodeRxFrame,NULL,0L,A,B);

/*****************************************************************************/
/* Due to a problem sharing a structure between the driver and link we're    */
/* going to get the driver to reset it's stats after every call to read the  */
/* interface record, and get the link to accumulate the stats          *STAT1*/
/*****************************************************************************/
#define READINTERFACERECORD                                                  \
           NtDeviceIoControlFile(seldrvrh,NULL,NULL,NULL,&IoStatus,          \
                                   IoctlCodeReadInterfaceRecord,NULL,0L,     \
                                   &InterfaceRecord,sizeof(InterfaceRecord));\
           if (!rc)                                                          \
           {                                                                 \
             int i;                                                          \
             Stats.StatusCount += InterfaceRecord.StatusCount;               \
             for (i=0;i<SA_Max_Stat;i++)                                     \
             {                                                               \
               Stats.StatusArray[i] += InterfaceRecord.StatusArray[i];       \
             }                                                               \
           }
#endif
