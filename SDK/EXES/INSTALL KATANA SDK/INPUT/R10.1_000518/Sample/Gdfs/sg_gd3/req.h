
/***** macros *****/

#define REQ_MAX  16


/***** functions *****/

Sint32 ReqInit(void);
GDFS ReqRead(GDFS gdfs, Sint32 nsct, void *buf);
Sint32 ReqExec(void);

/* eof */
