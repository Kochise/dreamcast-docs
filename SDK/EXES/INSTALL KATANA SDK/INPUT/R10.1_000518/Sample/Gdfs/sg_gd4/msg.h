/* msg.h */


/*** Message Scroll Subroutine ***/


#define MAX_WIN_LINE  10
#define MAX_MSG_LEN   80

void initMsg(void);
void putMsg(const char *msg);
void drawMsg(Sint32 x, Sint32 y);

/* eof */
