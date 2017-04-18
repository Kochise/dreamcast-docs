/*
 *   GDFS Streaming sample
 *   
 *   1999/01/19
 */


#include <stdio.h>
#include <shinobi.h>
#include "fstr.h"


/***** variables *****/

/* workarea */
static StrWork strwork;
static StrWork *strwk = NULL;


/***** functions *****/


/*** static ***/


static void mcpy(char *src, char *dst, Sint32 size)
{
	while (size-- > 0) {
		*dst++ = *src++;
	}
}



/*** global ***/


Sint32 StrInit(Sint32 max_stream, StrBuf *strbuf)
{
	/* setup workarea */
	strwk = &strwork;
	strwk->max_stream = max_stream;
	strwk->strhandle = syMalloc(max_stream * sizeof(StrHandle));
	
	/* memory allocation error */
	if (strwk->strhandle == NULL) {
		return (Sint32) STR_ERR_MEMOVER;
	}
	
	/* setup handles */
	{
		Sint32 cnt;
		StrHandle *sh;
		sh = strwk->strhandle;
		
		/* setup steraminfo */
		for (cnt = 0; cnt < strwk->max_stream; cnt++, sh++, strbuf++) {
			sh->total = strbuf->total;
			sh->back = strbuf->back;
			sh->readlmt = strbuf->readlmt;
			sh->buf = strbuf->buf;
			sh->bufsize = strbuf->total * STR_SCTSIZE;
			sh->filesize = 0;
			sh->cur = 0;
			sh->top = 0;
			sh->bottom = 0;
			sh->hn = NULL;
			sh->rdsct = 0;
			sh->trnsed = 0;
		}
	}
	
	return (Sint32) STR_OK;
}


void StrFinish(void)
{
	if (strwk == NULL) return;
	
	/* close all handle */
	{
		Sint32 cnt;
		StrHandle *sh;
		sh = strwk->strhandle;
		
		/* setup steraminfo */
		for (cnt = 0; cnt < strwk->max_stream; cnt++, sh++) {
			if (sh->hn != NULL) gdFsClose(sh->hn);
		}
	}
	
	/* clear workarea */
	strwk = NULL;
}


STRHN StrOpen(const char *fname, GDFS_DIRREC dirrec)
{
	StrHandle *sh;
	
	if (strwk == NULL) return (STRHN) NULL;
	
	/* setup handles */
	{
		Sint32 cnt;
		sh = strwk->strhandle;
		
		/* setup steraminfo */
		for (cnt = 0; cnt < strwk->max_stream; cnt++, sh++) {
			if (sh->hn == NULL) {
				sh->cur = 0;
				sh->top = 0;
				sh->bottom = 0;
				sh->rdsct = 0;
				sh->trnsed = 0;
				break;
			}
		}
		
		if (cnt >= strwk->max_stream) return (STRHN) NULL;
	}
	
	/* open handle */
	sh->hn = gdFsOpen(fname, dirrec);
	if (sh->hn == NULL) return NULL;
	
	/* get filesize */
	if (! gdFsGetFileSize(sh->hn, &sh->filesize) ) sh->filesize = 0;
	
	/* start reading */
	sh->rdsct = gdFsReqRd32(sh->hn, sh->total, sh->buf);
	if (sh->rdsct < 0) sh->rdsct = 0;
	
	return sh;
}


STRHN StrOpenNum(Sint32 strnum, const char *fname, GDFS_DIRREC dirrec)
{
	StrHandle *sh;
	
	if (strwk == NULL) return (STRHN) NULL;
	
	sh = strwk->strhandle + (strnum % strwk->max_stream);
	
	if (sh->hn == NULL)  return (STRHN) NULL;
	
	sh->cur = 0;
	sh->top = 0;
	sh->bottom = 0;
	sh->rdsct = 0;
	sh->trnsed = 0;
	
	/* open handle */
	sh->hn = gdFsOpen(fname, dirrec);
	if (sh->hn == NULL) return NULL;
	
	/* get filesize */
	if (! gdFsGetFileSize(sh->hn, &sh->filesize) ) sh->filesize = 0;
	
	/* start reading */
	sh->rdsct = gdFsReqRd32(sh->hn, sh->total, sh->buf);
	if (sh->rdsct < 0) sh->rdsct = 0;
	
	return sh;
}


Sint32 StrFread(void *ptr, Sint32 size, Sint32 n, STRHN hn)
{
	Sint32 nbyte;
	
	/* illegal handle */
	if (hn == NULL) return (Sint32) STR_ERR_ILGHNDL;
	
	/* size > cache */
	nbyte = size * n;
	if (hn->cur + nbyte > hn->top) nbyte = hn->top - hn->cur;
	
	/* eof ? */
	if (hn->cur + nbyte > hn->filesize) nbyte = hn->filesize - hn->cur;
	
	/* not ready */
	if (nbyte <= 0) return (Sint32) 0;
	
	/* copy the data from buffer to ptr */
	{
		Sint32 bcur;
		Sint32 brst;
		bcur = (hn->cur % hn->bufsize);
		brst = hn->bufsize - bcur;
		
		if (nbyte <= brst) {
			mcpy((char *) hn->buf + bcur, (char *) ptr, nbyte);
		} else {
			mcpy((char *) hn->buf + bcur, (char *) ptr, brst);
			mcpy((char *) hn->buf, (char *) ptr + brst, nbyte - brst);
		}
	}
	
	hn->cur =  hn->cur + nbyte;
	
	/* check back-buffer size */
	{
		Sint32 backlmt;
		backlmt = STR_SCT2BYTE(STR_BYTE2SCT(hn->cur - (hn->back * STR_SCTSIZE)));
		if (hn->bottom < backlmt) {
			hn->bottom = backlmt;
		}
	}
	
	return (nbyte / size);
}


Sint32 StrFseek(STRHN hn, Sint32 offset, Sint32 whence)
{
	Sint32 pos;
	
	/* illegal handle */
	if (hn == NULL) return (Sint32) STR_ERR_ILGHNDL;
	
	if (hn->hn == NULL) return (Sint32) STR_ERR_ILGHNDL;
	
	/* calc pos */
	switch (whence) {
	case GDD_SEEK_SET:
		pos = offset;
		break;
		
	case GDD_SEEK_CUR:
		pos = hn->cur + offset;
		break;
		
	case GDD_SEEK_END:
		pos = hn->filesize + hn->cur;
		break;
		
	default:
		return (Sint32) STR_ERR_SEEK;
		break;
	}
	
	/* limit check */
	if (pos < 0 || pos > hn->filesize) {
		return (Sint32) STR_ERR_SEEK;
	}
	
	/* set a seek point */
	hn->cur = pos;
	
	/* buffer check */
	if (hn->cur < hn->bottom || hn->cur > hn->top) {
		hn->bottom = hn->top = hn->cur;
	}
	
	/* check back-buffer size */
	{
		Sint32 backlmt;
		backlmt = STR_SCT2BYTE(STR_BYTE2SCT(hn->cur - (hn->back * STR_SCTSIZE)));
		if (backlmt < 0) backlmt = 0;
		hn->bottom = hn->top = backlmt;
	}
	
	
	return (Sint32) STR_OK;
}


Sint32 StrFeof(STRHN hn)
{
	/* illegal handle */
	if (hn == NULL) return (Sint32) TRUE;
	
	if (hn->hn == NULL) return (Sint32) TRUE;
	
	if (hn->filesize <= hn->cur) return (Sint32) TRUE;
	
	return (Sint32) FALSE;
}


Sint32 StrClose(STRHN hn)
{
	/* illegal handle */
	if (hn == NULL) return (Sint32) STR_ERR_ILGHNDL;
	
	if (hn->hn == NULL) return (Sint32) STR_ERR_ILGHNDL;
	
	/* handle close */
	gdFsClose(hn->hn);
	
	hn->hn = NULL;
	
	return (Sint32) STR_OK;
}


void StrServer(void)
{
	Sint32 cnt;
	StrHandle *sh;
	
	/* if someone is reading now */
	sh = strwk->strhandle;
	
	/* check handles */
	for (cnt = 0; cnt < strwk->max_stream; cnt++, sh++) {
		if (sh->rdsct != 0 && sh->hn != NULL) {
			Sint32 stat;
			Sint32 numrd;
			
			stat = gdFsGetStat(sh->hn);
			numrd = gdFsGetNumRd(sh->hn);
			numrd = STR_SCT2BYTE(STR_BYTE2SCT(numrd));
			
			sh->top += (numrd - sh->trnsed);
			sh->trnsed = numrd;
			
			if (stat == GDD_STAT_COMPLETE) {
				sh->rdsct = 0;
				continue;
				
			} else if (stat == GDD_STAT_ERR) {
				sh->rdsct = 0;
				continue;
			}
			
			return;
		}
	}
	
	
	/* if somewone has empty buffer */
	sh = strwk->strhandle;
	
	/* check handles */
	for (cnt = 0; cnt < strwk->max_stream; cnt++, sh++) {
		if ( (sh->bottom + sh->bufsize > sh->top) && (sh->hn != NULL) ) {
			Sint32 btop;
			Sint32 brst;
			Sint32 bdif;
			Sint32 rdsize;
			
			if ( sh->top >=
					STR_BYTE2SCT(sh->filesize + STR_SCTSIZE - 1) * STR_SCTSIZE ) {
				/* eof */
				
				continue;
			}
			
			btop = (sh->top % sh->bufsize);
			brst = sh->bufsize - btop;
			bdif = sh->bottom + sh->bufsize - sh->top;
			
			if ( bdif < (sh->readlmt * STR_SCTSIZE) ) continue;
			
			if (bdif < brst) {
				rdsize = STR_BYTE2SCT(bdif);
			} else {
				rdsize = STR_BYTE2SCT(brst);
			}
			
			if (rdsize <= 0) continue;
			
			/* read request */
			sh->trnsed = 0;
			sh->rdsct = gdFsReqRd32(sh->hn, rdsize, (char *) sh->buf + btop);
			if (sh->rdsct < 0) sh->rdsct = 0;
			
			return;
		}
	}
}


void *StrGetPtr(STRHN hn)
{
	/* illegal handle */
	if (hn == NULL) return (void *) NULL;
	
	if (hn->hn == NULL) return (void *) NULL;
	
	return (void *) ((char *) hn->buf + (hn->cur % hn->bufsize));
}


Sint32 StrGetContSize(STRHN hn)
{
	/* illegal handle */
	if (hn == NULL) return (Sint32) 0;
	
	if (hn->hn == NULL) return (Sint32) 0;
	
	return hn->bufsize - (hn->cur % hn->bufsize);
}


/* eof */
