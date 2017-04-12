#include <kos.h>

void mouse_test() {
	mouse_cond_t mcond;
	cont_cond_t cond;
	uint8 mcont, mmouse;
	int c = 'M', x = 20, y = 20;

	mcont = maple_first_controller();
	if (!mcont) {
		printf("No controllers attached!\r\n");
		return;
	}
	mmouse = maple_first_mouse();
	if (!mmouse) {
		printf("No mice attached!\r\n");
		return;
	}

	printf("Now doing mouse test\r\n");	
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
		
		/* Check for mouse input */
		if (mouse_get_cond(mmouse, &mcond)) {
			printf("Error checking mouse status\r\n");
			return;
		}

		/* Move the cursor if applicable */
		if (mcond.dx || mcond.dy || mcond.dz) {
			vid_clear(0,0,0);
			x += mcond.dx;
			y += mcond.dy;
			c += mcond.dz;
			bfont_draw(vram_s + (y*320+x), 320, 0, c);
		}

		timer_spin_sleep(10);
	}
}

int main(int argc, char **argv) {
	/* Do initial setup */
	dbgio_init();
	hardware_init();
	vid_set_mode(DM_320x240, PM_RGB565);

	mouse_test();

	return 0;
}
