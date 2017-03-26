#include <kos.h>
#include <lwip/lwip.h>
#include <unistd.h>

extern uint8 romdisk[];
KOS_INIT_ROMDISK(romdisk);

void httpd();
void do_httpd(void * foo) {
	httpd();
}

int main(int argc, char **argv) {
	net_init();
	lwip_kos_init();
	thd_create(do_httpd, NULL);

	vid_clear(50,0,70);
	bfont_draw_str(vram_s + 20*640+20, 640, 0, "KOSHttpd active");
	bfont_draw_str(vram_s + 44*640+20, 640, 0, "Press START to quit.");

	thd_sleep(1000*5);

	for ( ; ; ) {
		MAPLE_FOREACH_BEGIN(MAPLE_FUNC_CONTROLLER, cont_state_t, st)
			if (st->buttons & CONT_START)
				return 0;
		MAPLE_FOREACH_END()
	}

	return 0;
}





