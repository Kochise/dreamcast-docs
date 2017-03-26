#include <arch/timer.h>

int spinlock_is_locked() {
	return 0;
}

void arch_sleep(int x) {
	return;
}

void irq_restore(int x) {
	return;
}

int irq_disable() {
	return 0;
}

void irq_create_context(irq_context_t *context, uint32 stack_pointer,
	uint32 routine, uint32 *args, int usermode)
{
	return;
}

void irq_set_context(irq_context_t * c) {
	return;
}

uint64 timer_ms_gettime64() { return 0; }

timer_primary_callback_t timer_primary_set_callback(timer_primary_callback_t callback) {
	return NULL;
}

void timer_primary_wakeup(uint32 millis) {
}

void timer_spin_sleep(int x) {
	return;
}

int irq_set_handler(irq_t source, irq_handler hnd) {
	return 0;
}

void timer_primary_enable() {
	return;
}

int thd_block_now(irq_context_t * c) {
	return 0;
}
