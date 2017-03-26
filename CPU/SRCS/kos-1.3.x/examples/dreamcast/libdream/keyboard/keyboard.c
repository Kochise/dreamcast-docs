#include <kos.h>

void kb_test() {
	uint8 mcont, mkb;
	cont_cond_t cond;
	int k, x = 20, y = 20+24;

	printf("Now doing keyboard test\n");	

	while (1) {
		mcont = maple_first_controller();
		if (!mcont) continue;
		mkb = maple_first_kb();
		if (!mkb) continue;
		
		/* Check for start on the controller */
		if (cont_get_cond(mcont, &cond) < 0) {
			return;
		}
		
		if (!(cond.buttons & CONT_START)) {
			printf("Pressed start\n");
			return;
		}
		
		usleep(10 * 1000);
		
		/* Check for keyboard input */
		/* if (kbd_poll(mkb)) {
			printf("Error checking keyboard status\n");
			return;
		} */

		/* Get queued keys */
		while ( (k = kbd_get_key()) != -1) {
			if (k > 0xff)
				printf("Special key %04x\n", k);
			
			if (k != 13) {
				bfont_draw(vram_s + y*640+x, 640, 0, k);
				x += 12;
			} else {
				x = 20;
				y += 24;
			}
		}
		
		if (k == 27) {
			printf("ESC pressed\n");
			break;
		}

		usleep(10 * 1000);
	}
}

int main(int argc, char **argv) {
	int x, y;

	for (y=0; y<480; y++)
		for (x=0; x<640; x++) {
			int c = (x ^ y) & 255;
			vram_s[y*640+x] = ((c >> 3) << 12)
				| ((c >> 2) << 5)
				| ((c >> 3) << 0);
		}

	kb_test();

	return 0;
}
