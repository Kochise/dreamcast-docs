#include <kos.h>

void mouse_test() {
	mouse_cond_t mcond;
	cont_cond_t cond;
	uint8 mcont, mmouse;
	int c = 'M', x = 20, y = 20;

	printf("Now doing mouse test\n");	
	while (1) {
		mcont = maple_first_controller();
		if (!mcont) continue;
		mmouse = maple_first_mouse();
		if (!mmouse) continue;
		
		/* Check for start on the controller */
		if (cont_get_cond(mcont, &cond) < 0) {
			printf("Error getting controller status\n");
			return;
		}
		
		if (!(cond.buttons & CONT_START)) {
			printf("Pressed start\n");
			return;
		}
		
		usleep(10 * 1000);
		
		/* Check for mouse input */
		if (mouse_get_cond(mmouse, &mcond) < 0)
			continue;

		/* Move the cursor if applicable */
		if (mcond.dx || mcond.dy || mcond.dz) {
			vid_clear(0,0,0);
			x += mcond.dx;
			y += mcond.dy;
			c += mcond.dz;
			bfont_draw(vram_s + (y*640+x), 640, 0, c);
		}

		usleep(10 * 1000);
	}
}

int main(int argc, char **argv) {
	mouse_test();

	return 0;
}
