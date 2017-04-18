/******************************************************************************
 *
 * cardprobe.c - カードドライバの識別の宣言
 *
 * -- 著作権表示 --
 *
 *  Copyright(C) 1999 by ACCESS Co.,Ltd.
 *  All right reseved.
 *
 * -- 変更記録 --
 *
 *  $Log: /NetFront/TCP/dm_sdk/dmcast/cardprobe.h $
 * 
 * 1     99/12/09 14:35 Hamamoto
 * ドライバ自動切替
 *
 *****************************************************************************/
#ifdef __cplusplus /* Support for C++ */
extern "C" {
#endif /* __cplusplus */

#if !defined(CARDPROBE_H)
#define CARDPROBE_H

extern int AT_CardType;
#define AT_CARD_TYPE_PPP       1
#define AT_CARD_TYPE_LAN       2
#define AT_CARD_TYPE_UNKNOWN   (-1)

extern int AT_CardProbe(void);
extern int AT_GetCardType(void);
#endif /* !defined(CARDPROBE_H) */

#ifdef __cplusplus
} /* End of extern "C" { */
#endif /* __cplusplus */
/*****************************************************************************/
/* Muleの設定(必ず各行が1行コメントでなければ認識されないので注意) */
/* Local Variables: */
/* mode: c */
/* tab-width: 4 */
/*****************************************************************************/
