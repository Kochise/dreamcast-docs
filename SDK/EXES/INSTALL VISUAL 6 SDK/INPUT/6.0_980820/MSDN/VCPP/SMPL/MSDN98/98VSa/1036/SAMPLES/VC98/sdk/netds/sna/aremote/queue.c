#include <windows.h>
#include "queue.h"

qnode *addtoq(queue *q, void *p) {
	qnode *t;

	t = (qnode *) LocalAlloc(0, sizeof(qnode));
	if (t == NULL) return NULL;
	t->ptr = p;
	t->next = NULL;
	if (q->head == NULL) {
		t->prev = NULL;
		q->head = t;
		q->tail = t;
	} else {
		t->prev = q->tail;
		q->tail->next = t;
		q->tail = t;
	}

	return t;
}

void *removeheadfromq(queue *q) {
	qnode *t;
	void *p;

	if (q->head == NULL) return NULL;

	t = q->head;
	q->head = t->next;
	if (q->head == NULL) q->tail = NULL;
	else q->head->prev = NULL;
	p = t->ptr;
	LocalFree(t);

	return p;
}

void *removeqnodefromq(queue *q, qnode *t) {
	void *p;

	if (q->head == t) q->head = t->next;
	if (q->tail == t) q->tail = t->prev;
	if (t->next != NULL) t->next->prev = t->prev;
	if (t->prev != NULL) t->prev->next = t->next;
	p = t->ptr;
	LocalFree(t);

	return p;
}

queue *newq(void) {	
	queue *q;

	q = (queue *) LocalAlloc(0, sizeof(queue));
	if (q == NULL) return NULL;
	q->head = NULL;
	q->tail = NULL;

	return q;
}
