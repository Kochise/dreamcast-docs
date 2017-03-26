#include <kos.h>
#include <vfdc.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

int FrameCB()
{
	cont_cond_t cond;
	

	if (cont_get_cond(maple_first_controller(), &cond) < 0)
		return FRAMECB_VIDEO_NEXTFRAME;
	if (!(cond.buttons & CONT_START))
		return FRAMECB_VIDEO_STOP;

	return FRAMECB_VIDEO_NEXTFRAME;
}


int main()
{
    /**
	 Play only 2 time the video and exit
	 */
	play_mpeg("/rd/test256.mpg",2,FrameCB,VMODE_PAL);
	return 0;
}