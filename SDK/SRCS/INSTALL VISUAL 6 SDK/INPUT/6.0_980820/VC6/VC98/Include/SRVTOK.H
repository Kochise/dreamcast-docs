//  TDS tokens
//
#define SRV_TDS_TEXT           (BYTE) 0x23
#define SRV_TDS_VARBINARY      (BYTE) 0x25
#define SRV_TDS_INTN           (BYTE) 0x26
#define SRV_TDS_VARCHAR        (BYTE) 0x27
#define SRV_TDS_LOGIN          (BYTE) 0xad
#define SRV_TDS_BINARY         (BYTE) 0x2d
#define SRV_TDS_IMAGE          (BYTE) 0x22
#define SRV_TDS_CHAR           (BYTE) 0x2f
#define SRV_TDS_INT1           (BYTE) 0x30
#define SRV_TDS_BIT            (BYTE) 0x32
#define SRV_TDS_INT2           (BYTE) 0x34
#define SRV_TDS_INT4           (BYTE) 0x38
#define SRV_TDS_MONEY          (BYTE) 0x3c
#define SRV_TDS_DATETIME       (BYTE) 0x3d
#define SRV_TDS_FLT8           (BYTE) 0x3e
#define SRV_TDS_FLTN           (BYTE) 0x6d
#define SRV_TDS_MONEYN         (BYTE) 0x6e
#define SRV_TDS_DATETIMN       (BYTE) 0x6f
#define SRV_TDS_OFFSET         (BYTE) 0x78
#define SRV_TDS_RETURNSTATUS   (BYTE) 0x79
#define SRV_TDS_PROCID         (BYTE) 0x7c
#define SRV_TDS_COLNAME        (BYTE) 0xa0
#define SRV_TDS_COLFMT         (BYTE) 0xa1
#define SRV_TDS2_COLFMT        (BYTE) 0x2a // Only used on TDS 2.0, 3.4
#define SRV_TDS_TABNAME        (BYTE) 0xa4
#define SRV_TDS_COLINFO        (BYTE) 0xa5
#define SRV_TDS_ORDER          (BYTE) 0xa9
#define SRV_TDS_ERROR          (BYTE) 0xaa
#define SRV_TDS_INFO           (BYTE) 0xab
#define SRV_TDS_RETURNVALUE    (BYTE) 0xac
#define SRV_TDS_CONTROL        (BYTE) 0xae
#define SRV_TDS_ROW            (BYTE) 0xd1
#define SRV_TDS_DONE           (BYTE) 0xfd
#define SRV_TDS_DONEPROC       (BYTE) 0xfe
#define SRV_TDS_DONEINPROC     (BYTE) 0xff

//
// These are version 4.2 additions
//
#define SRV_TDS_FLT4            (BYTE) 0x3b
#define SRV_TDS_MONEY4          (BYTE) 0x7a
#define SRV_TDS_DATETIM4        (BYTE) 0x3a

#define SRV_TDS_NULL            (BYTE) 0x1f    //Null parameter from server

//
// These are version 4.6 additions
//
#define SRV_TDS_ENVCHANGE      (BYTE) 0xe3

//
// These are version 6.0 additions
//
#define SRV_TDS_NUMERIC        (BYTE) 0x3f
#define SRV_TDS_NUMERICN       (BYTE) 0x6c

#define SRV_TDS_DECIMAL        (BYTE) 0x37
#define SRV_TDS_DECIMALN       (BYTE) 0x6a
