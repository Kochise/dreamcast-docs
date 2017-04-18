#ifndef _GUN_H_
#define _GUN_H_

#include <shinobi.h>

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */


#define GUN_A            0  /* Gun Controller A                            */
#define GUN_B            1  /* Gun Controller B                            */
#define GUN_C            2  /* Gun Controller C                            */
#define GUN_D            3  /* Gun Controller D                            */

#define GUN_VGA          0  /* VGA                                         */
#define GUN_NTSC_640x480 1  /* NTSC 640x480                                */
#define GUN_NTSC_320x240 2  /* NTSC 320x240                                */


/******** ƒKƒ“î•ñ\‘¢‘Ì ***************************************************/
/******** Gun information structure ****************************************/
typedef struct {
	Sint32 IsGun;           /* ƒKƒ“‚ªÚ‘±‚³‚ê‚Ä‚¢‚é‚©‚Ç‚¤‚©                */
	                        /* Is gun connected ?                          */
	Sint32 OnScreen;        /* ƒKƒ“‚ª‰æ–Ê“à‚ğŒü‚¢‚Ä‚¢‚é‚©                  */
	                        /* Does the muzzle point to the inside of      */
	                        /* a screen ?                                  */
	Sint32 x, y;            /* ƒKƒ“À•W                                    */
	                        /* Gun position                                */
	Sint32 rawX, rawY;      /* ƒKƒ“À•W(¶ƒf[ƒ^)                          */
	                        /* Gun position(raw data)                      */
	Sint32 trigger;         /* ƒgƒŠƒKî•ñ                                  */
	                        /* Is the trigger pressed ?                    */
} GUNINFO;

void GunInit(Sint32 tvmode);
void GunMain(void);
void GunExit(void);
const GUNINFO* GunGetInfo(Uint32 port);


#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _GUN_H_ */
