/*
 * file: mdmAPI.h
 * desc: Virtual serial interface library for Dreamcast modem.
 * date: 1998/05/21 J.Terakawa
 *
 */

#define MDD_MCR_DTR_ON  (0x01<<0)
#define MDD_MCR_DTR_OFF (0x00<<0)
#define MDD_MCR_DTR_MASK (~0x01)

#define MDD_MCR_RTS_ON  (0x01<<1)
#define MDD_MCR_RTS_OFF (0x00<<1)
#define MDD_MCR_RTS_MASK (~0x02)

#define MDD_LCR_CHARLEN_8 (0x03<<0)
#define MDD_LCR_CHARLEN_7 (0x02<<0)
#define MDD_LCR_CHARLEN_6 (0x01<<0)
#define MDD_LCR_CHARLEN_5 (0x00<<0)
#define MDD_LCR_CHARLEN_MASK (~0x03)

#define MDD_LCR_PARITY_NONE  (0x00<<3)
#define MDD_LCR_PARITY_ODD   (0x01<<3)
#define MDD_LCR_PARITY_EVEN  (0x03<<3)
#define MDD_LCR_PARITY_MARK  (0x05<<3)
#define MDD_LCR_PARITY_SPACE (0x07<<3)
#define MDD_LCR_PARITY_MASK  (~(0x07<<3))

#define MDD_LCR_STOPBIT_1B (0x00<<2)
#define MDD_LCR_STOPBIT_2B (0x01<<2)
#define MDD_LCR_STOPBIT_MASK (~(0x01<<2))

#define MDD_LCR_SETBREAK_ON  (0x01<<6)
#define MDD_LCR_SETBREAK_OFF (0x00<<6)
#define MDD_LCR_SETBREAK_MASK (~(0x01<<6))

#define MDD_LINESPEED_300 1
#define MDD_LINESPEED_1200 2
#define MDD_LINESPEED_2400 3
#define MDD_LINESPEED_4800 4
#define MDD_LINESPEED_9600 6
#define MDD_LINESPEED_14400 8
#define MDD_LINESPEED_19200 10
#define MDD_LINESPEED_38400 27
#define MDD_LINESPEED_57600 46
#define MDD_LINESPEED_115200 51
#define MDD_LINESPEED_230400 53
#define MDD_LINESPEED_460800 54

typedef struct {
  /* DDAL -> DTE */
  char Dtr;
  char Rts;
  char CharLen; /* charlen, parity, stopbitlen */
  char Parity;
  char StopBit;
  char SetBreak;
  char LineSpeed;
  /* DTE->DDAL */
  char Cts;
  char Dsr;
  char Ri;
  char Dcd;
  char Brk;
} MDS_DCB;

typedef Uint32 MDM;
typedef Uint32 MD_DEVICE;

#define MDD_DEVICE_G2_MODEM 1

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

void mdmInit(char *TxBuf, char *RxBuf, int TxBufSize, int RxBufSize);/* buffer size 指定,初期化 */

MDM mdmOpen(MD_DEVICE dev); /* DTR,RTS,... などは mdmSetCommState を使用してデフォルト値を設定する */

int mdmRead(MDM mdmHandle, char *buf, int size); /* 戻り値は読めたバイト数 */

int mdmWrite(MDM mdmHandle, char *buf, int size); /* 戻り値は書けたバイト数 */

void mdmSetCommState(MDS_DCB mdmDcb); /* DTR, RTS, CharLen, StopBitLen, Parity, SetBreak, LineSpeed の設定 */
void mdmSetCommState2(MDM mdmHandle, MDS_DCB mdmDcb); /* DTR, RTS, CharLen, StopBitLen, Parity, SetBreak, LineSpeed の設定 */

void mdmGetCommState(MDS_DCB *pmdmDcb); /* CTS, DSR, RI,DCD,BRK の取得 */
void mdmGetCommState2(MDM mdmHandle, MDS_DCB *pmdmDcb); /* CTS, DSR, RI,DCD,BRK の取得 */

void mdmDropDtr(MDM mdmHandle);
void mdmEnableDtr(MDM mdmHandle);
int mdmRxAvailSize(MDM mdmHandle);
int mdmRxFreeSize(MDM mdmHandle);
int mdmTxAvailSize(MDM mdmHandle);
int mdmTxFreeSzie(MDM mdmHandle);
void mdmPurgeTxBuffer(MDM mdmHandle);
void mdmPurgeRxBuffer(MDM mdmHandle);
void mdmClose(MDM mdmHandle);

void mdmFinish(void);

#ifdef __cplusplus
}
#endif /* __cplusplus */
