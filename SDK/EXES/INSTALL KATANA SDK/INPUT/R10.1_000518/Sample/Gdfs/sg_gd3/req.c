#include <stdio.h>

#include <shinobi.h>
#include "req.h"


/***** macros *****/


/***** structs *****/


typedef struct read_request {
	GDFS hn;
	Sint32 size;
	void *buf;
} ReadReq;


typedef struct request_work {
	Sint32 mode;
	Sint32 qTop;
	Sint32 qBottom;
	Sint32 qNum;
	GDFS cHn;
	ReadReq req_tbl[REQ_MAX];
} ReqWork;


/***** variables *****/

ReqWork reqwk;
ReqWork *preqwk = NULL; 


/***** functions *****/

Sint32 ReqInit(void)
{
	/* alloc the workarea */
	preqwk = &reqwk;
	
	preqwk->mode = 0;
	preqwk->qTop = 0;
	preqwk->qBottom = 0;
	preqwk->qNum = 0;
}


GDFS ReqRead(GDFS gdfs, Sint32 nsct, void *buf)
{
	ReadReq *preq;
	
	if (preqwk->qNum >= REQ_MAX) {
		/* request buffer is full ? */
		return (GDFS) NULL;
	}
	
	preqwk->qNum++;
	preq = preqwk->req_tbl + preqwk->qTop;
	preqwk->qTop = (preqwk->qTop + 1) % REQ_MAX;
	
	/* store a request */
	preq->hn = gdfs;
	preq->size = nsct;
	preq->buf = buf;
	
	return gdfs;
}


Sint32 ReqExec(void)
{
	switch (preqwk->mode) {
	case 0: /* idle */
		if (gdFsGetWorkHn() == NULL) {
			if (preqwk->qNum > 0) {
				ReadReq *preq;
				Sint32 ret;
				
				/* get a request */
				preq = preqwk->req_tbl + preqwk->qBottom;
				
				/* exec next request */
				ret = gdFsReqRd32(preq->hn, preq->size, preq->buf);
				
				if (ret > 0) {
					/* success */
					preqwk->cHn = preq->hn;
					preqwk->mode = 1;
				}
			}
		}
		break;
		
	case 1: /* working */
		{
			Sint32 stat;
			
			stat = gdFsGetStat(preqwk->cHn);
			
			if (stat == GDD_STAT_COMPLETE) {
				/* go to next */
				preqwk->qNum--;
				preqwk->qBottom = (preqwk->qBottom + 1) % REQ_MAX;
				
				preqwk->mode = 0;
				
			} else if (stat == GDD_STAT_ERR) {
				/* retry */
				
				preqwk->mode = 0;
			}
		}
		break;
	}
	
	return preqwk->qNum;
}


/* eof */
