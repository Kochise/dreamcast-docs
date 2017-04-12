#include <kos.h>

void kb_test() {
	uint8 mcont, mkb;
	cont_cond_t cond;
	int k, x = 20, y = 20+24;

	printf("Now doing keyboard test\n");	

	mcont = maple_first_controller();
	if (!mcont) {
		printf("No controllers attached\r\n");
		return;
	}
	mkb = maple_first_kb();
	if (!mkb) {
		printf("No keyboards attached\r\n");
		return;
	}

	while (1) {
		/* Check for start on the controller */
		if (cont_get_cond(mcont, &cond)) {
			printf("Error getting controller status\r\n");
			return;
		}
		
		if (!(cond.buttons & CONT_START)) {
			printf("Pressed start\r\n");
			return;
		}
		
		timer_spin_sleep(10);
		
		/* Check for keyboard input */
		if (kbd_poll(mkb)) {
			printf("Error checking keyboard status\r\n");
			return;
		}

		/* Get queued keys */
		while ( (k = kbd_get_key()) != -1) {
			if (k > 0xff)
				printf("Special key %04x\r\n", k);
			
			if (k != 13) {
				bfont_draw(vram_s + y*320+x, 320, 0, k);
				x += 12;
			} else {
				x = 20;
				y += 24;
			}
		}
		
		if (k == 27) {
			printf("ESC pressed\r\n");
			break;
		}

		timer_spin_sleep(10);
	}
}

int main(int argc, char **argv) {
	int x, y;

	/* Do initial setup */	
	timer_init();
	hardware_init();

	vid_set_mode(DM_320x240, PM_RGB565);
	
	for (y=0; y<240; y++)
		for (x=0; x<320; x++) {
			int c = (x ^ y) & 255;
			vram_s[y*320+x] = ((c >> 3) << 12)
				| ((c >> 2) << 5)
				| ((c >> 3) << 0);
		}

	kb_test();

	return 0;
}
