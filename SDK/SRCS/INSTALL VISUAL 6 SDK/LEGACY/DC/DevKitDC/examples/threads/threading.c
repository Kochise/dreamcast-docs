/* threading.c 

   A simple thread example

   This small program shows off the threading (and also is used as
   a regression test to make sure threading is still approximately
   working =). See below for some more specific notes.

 */

#include <kos.h>

/* Semaphore used for timing below */
semaphore_t *sem;

/* This routine will be started as thread #1 */
void thd_1(void *v) {
	int i;

	for (i=0; i<30; i++) {
		printf("Hi from thread 1\n");
		thd_sleep(100);
		sem_signal(sem);
	}
	printf("Thread 1 exiting\n");
}

/* This routine will be started as thread #2 */
void thd_2(void *v) {
	int i;
	
	thd_sleep(50);
	for (i=0; i<30; i++) {
		sem_wait(sem);
		printf("Hi from thread 2\n");
	}
	printf("Thread 2 exiting\n");
}

/* The main program */
int main(int argc, char **argv) {
	int x, y;

	/* Hardware / basic OS init: IRQs disabled, threads enabled,
	   no initial romdisk */
	kos_init_all(THD_ENABLE, ROMDISK_NONE);

	/* Print a banner */	
	printf("This is a test KOS 1.1.x program.\n");

	/* Create two threads, but don't start them yet. Note that at this
	   point in your program, IRQs are still disabled. This is so that you
	   have full control over what happens to the threads. */
	thd_create(thd_1, NULL);
	thd_create(thd_2, NULL);

	/* Create a semaphore for timing purposes */
	sem = sem_create(1);

	/* Enabling IRQs starts the thread scheduler */
	irq_enable();

	/* In the foreground, draw a moire pattern on the screen */
	for (y=0; y<480; y++)
		for (x=0; x<640; x++)
			vram_s[y*640+x] = ((x*x) + (y*y)) & 0x1f;

	timer_spin_sleep(1000);
	thd_pslist();
	thd_pslist_queue();
	timer_spin_sleep(5000);

	/* Disable IRQs, thus turning off threading. All threads that were
	   running are now gone. If your threads were doing anything like
	   PowerVR or other hardware access, I recommend avoiding this sort
	   of brute-force shutdown approach =) */
	irq_disable();

	/* Shut it all down */
	kos_shutdown_all();
	printf("Done.\n");

	return 0;
}
