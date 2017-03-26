/* Taro ##version##

   taro.c
   (c)2002 Dan Potter
*/

#include "taro.h"

/* You can safely remove this line if you don't use a ROMDISK */
extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

pvr_init_params_t params = {
	{ PVR_BINSIZE_16, PVR_BINSIZE_0, PVR_BINSIZE_32, PVR_BINSIZE_0, PVR_BINSIZE_0 },
	512*1024
};
int main(int argc, char **argv) {
	int sfx;

	cont_btn_callback(0, CONT_START, (cont_btn_callback_t)arch_exit);
	pvr_init(&params);

	spiral_init();
	menu_init();

	/* Doesn't work under custom BIOS yet for some reason... */
	/* printf("stream_init:\n");
	snd_stream_init(NULL);
	printf("sfx_load:\n");
	sfx = snd_sfx_load("/rd/dc_kids2.wav");
	printf("sfx_play:\n");
	snd_sfx_play(sfx, 240, 0x80); */

	for( ; ; ) {
		pvr_set_bg_color(23.0/255.0, 0.0, 84.0/255.0);
		pvr_wait_ready();
		pvr_scene_begin();
		pvr_list_begin(PVR_LIST_TR_POLY);
		spiral_frame();
		menu_frame();
		pvr_list_finish();
		pvr_scene_finish();

		/* if (!(frame % 60)) {
			pvr_stats_t stats;
			pvr_get_stats(&stats);
			printf("framerate: %.2f fps\n", stats.frame_rate);
		} */
	}

	return 0;
}


