/*
 *  AVE-TCP 3.1 SDK source code.       
 *
 * 	at_types.h
 *
 *	共通型、共通定数定義ヘッダファイル
 *
 *	Copyright (C) 1998 ACCESS CO.,LTD.
 */

#ifdef __cplusplus	/* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#ifndef AT_TYPES_H
#define AT_TYPES_H

#include "at_pltfm.h" 

/*******************************************************************/
/* 
 *  ネットワークデータ型
 */
/*******************************************************************/

/* ネットワークバイトオーダ(big endiun)の32ビット整数: AT_NINT32 */
typedef union at_nint32 {
    AT_UINT32 u32;
    AT_UBYTE  b[4];
} AT_NINT32;

/*ネットワークバイトオーダ(big endiun)の16ビット整数: AT_NINT16 */
typedef union at_nint16 {
    AT_UINT16 u16;
    AT_UBYTE  b[2];
} AT_NINT16;

/*******************************************************************/
/* 
 *  バイトオーダの変換
 */
/*******************************************************************/

#ifdef AT_LITTLE_ENDIAN 
  /* 2バイト整数のネットワークバイトオーダ化 */
#define AT_HTONS(s) ( (((s) & 0x0ff) << 8) | (((s) & 0xff00) >> 8) )
  /* 4バイト整数のネットワークバイトオーダ化 */
#define AT_HTONL(l) \
	((((l)&0xff000000) >> 24) | (((l)&0x00ff0000) >> 8) | \
		(((l)&0x00ff00) << 8) | (((l)&0x00ff) << 24))
#else /* !AT_LITTLE_ENDIAN */
#define AT_HTONS(s) (s)
#define AT_HTONL(l) (l)
#endif /* AT_LITTLE_ENDIAN */

/*******************************************************************/
/* 
 *  NDI/DL 用
 */
/*******************************************************************/

typedef AT_UINT32 AT_MTU; /* MTU */

#define AT_ETHER_HW_ADDR_LEN 6	/* Ethernetのハードウェアアドレス長 */
#define AT_ETHER_TYPE_LEN 2		/* Ethernetのタイプフィールド長 */
#define AT_ETHER_DL_HEADER_LEN (AT_ETHER_HW_ADDR_LEN*2+AT_ETHER_TYPE_LEN) /* Ethernetパケットのデータリンクヘッダ長 : 10/27/98 */
#define AT_ETHER_MIN_PACKET_LEN (46+AT_ETHER_DL_HEADER_LEN) /* Ethernetの最小パケット長(ヘッダを含む) : 10/28/98 */

 /* Ethernetのハードウェアアドレス */
typedef struct {
	AT_UBYTE hw_addr[AT_ETHER_HW_ADDR_LEN];
} AT_ETHER_HW_ADDR;

/* IPアドレス */
typedef AT_NINT32 AT_IP_ADDR;
 /* IPネットマスク */
typedef AT_NINT32 AT_IP_NETMASK;

/*******************************************************************/
/* 
 *  共通定数
 */
/*******************************************************************/
#define	AT_SUCCESS		0
#define	AT_ERR_INTERNAL	-1
#define	AT_ERR_UNKNOWN	-1
#define	AT_ERR_UNREACH	-2
/*** ------> ERR_INTERNAL ****/
#define	AT_FAIL	-1
/*	ERR_UNKNOWN is temporary	*/
/*	after exchange err code		*/

#define	AT_ON    1
#define	AT_OFF   0
#define	AT_YES   1
#define	AT_NO    0
#define	AT_TRUE  1
#define	AT_FALSE 0

/*******************************************************************/
/* 
 *  共通型
 */
/*******************************************************************/

typedef AT_SINT32 AT_datasize_t;

/*******************************************************************/
/* 
 *  共通マクロ
 */
/*******************************************************************/

#define AT_MIN(a,b) (((a)<(b))?(a):(b))
#define AT_MAX(a,b) (((a)>(b))?(a):(b))

/*******************************************************************/
/* 
 *  共通構造体
 */
/*******************************************************************/

typedef struct _AT_Vptr {
  AT_UINT32 buff;
  AT_UBYTE type;
#define AT_PTR_TYPE_NONE     0
#define AT_PTR_TYPE_LOCAL    1  /* internal data */
#define AT_PTR_TYPE_POOL     2  /* mempool data */
#define AT_PTR_TYPE_EXTERNAL 3  /* external data */
}AT_Vptr;

typedef struct {
	AT_SINT16	len;
	AT_Vptr	vptr;
} AT_VptrArray;

typedef struct _AT_RevBuffs {
	AT_datasize_t bufnum;
	AT_datasize_t	total_len;
	AT_VptrArray buffers[1];
} AT_RevBuffs;

typedef AT_RevBuffs AT_Buffs;

typedef struct _AT_MaxBuffs {
	AT_datasize_t	bufnum;
	AT_datasize_t total_len;
	AT_VptrArray	buffers[12];
} AT_MaxBuffs;

#endif /* AT_TYPES_H */

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
