/*
 *   GDFS Streaming sample
 *   
 *   1999/01/19
 */


/***** constants *****/


#define STR_SCTSIZE  2048
#define STR_BYTE2SCT(x)  ((x) >> 11)
#define STR_SCT2BYTE(x)  ((x) << 11)


enum fStrErr {
	STR_ERR_INIT = -50,
	STR_ERR_MEMOVER,
	STR_ERR_ILGHNDL,
	STR_ERR_SEEK,
	STR_ERR_EOF,
	STR_OK = 0
};


/***** structures *****/


typedef struct fStrBuf {
	Sint32 total; /* バッファリングする最大セクタ数 */
					/* max sectors for buffering */
	Sint32 back; /* 後戻り可能セクタ数 */
					/* sectors for backtrack */
	Sint32 readlmt; /* 読み込み許可限界 */
					/* limit for pre-loading */
	void *buf; /* バッファへのポインタ (32 bytes align) */
				/* pointer of buffer */
} StrBuf;


typedef struct fStrHandle {
	Sint32 total; /* バッファリングする最大セクタ数 */
					/* max sectors for buffering */
	Sint32 back; /* 後戻り可能セクタ数 */
					/* sectors for backtrack */
	Sint32 readlmt; /* 読み込み許可限界 */
					/* limit for pre-loading */
	void *buf; /* バッファへのポインタ (32 bytes align) */
				/* pointer of buffer */
	Sint32 bufsize; /* バッファのバイトサイズ */
				/* buffer size */
	Sint32 filesize; /* ファイルサイズ */
				/* file size */
	Sint32 cur; /* 現在のバッファからの読み出し位置 */
				/* current seek point */
	Sint32 top; /* バッファの先頭 */
				/* top of buffer */
	Sint32 bottom; /* バッファの最後 */
					/* end of buffer */
	GDFS hn; /* 読み込み用ハンドル */
				/* handle */
	Sint32 rdsct; /* 読み込み中のセクタ数 */
					/* sectors on reading */
	Sint32 trnsed; /* 転送済みバイト数 */
					/* transferred size */
} StrHandle;

typedef StrHandle *STRHN;


typedef struct fStrWork {
	Sint32 max_stream; /* 最大同時オープン数 */
						/* max open numbers */
	StrHandle *strhandle;
} StrWork;


/*** APIs ***/


Sint32 StrInit(Sint32 max_stream, StrBuf *strbuf);
void StrFinish(void);
STRHN StrOpen(const char *fname, GDFS_DIRREC dirrec);
STRHN StrOpenNum(Sint32 strnum, const char *fname, GDFS_DIRREC dirrec);
Sint32 StrFread(void *ptr, Sint32 size, Sint32 n, STRHN hn);
Sint32 StrFseek(STRHN hn, Sint32 offset, Sint32 whence);
Sint32 StrFeof(STRHN hn);
Sint32 StrClose(STRHN hn);

void StrServer(void);

void *StrGetPtr(STRHN hn);
Sint32 StrGetContSize(STRHN hn);


/* eof */
