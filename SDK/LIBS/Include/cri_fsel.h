#ifndef _FSEL_H_INCLUDED
#define _FSEL_H_INCLUDED
/****************************************************************************/
/*																			*/
/*			File Select Library (for Dreamcast)								*/
/*																			*/
/*				written by M.Oshimi			1999.2.9						*/
/*																			*/
/****************************************************************************/

#define		FSEL_VER		"1.03"

/*	ファイルセレクタの初期化 	*/
void FSEL_Init(void *dir, char *ext);
/*	ファイル選択	*/
char *FSEL_SelectFile(void);
/*	ファイル選択（完了復帰）	*/
char *FSEL_Select(long next, char *ext[]);
#endif
