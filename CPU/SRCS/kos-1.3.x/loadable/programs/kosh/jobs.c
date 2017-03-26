/*
 * jobs.c
 *
 * Copyright (C)2003 Dan Potter
 */

#include "jobs.h"
#include <sys/process.h>
#include <stdlib.h>
#include <signal.h>

struct jobqueue jobs;

int chldhnd(int sig, void * data) {
        kprocess_t * proc = (kprocess_t *)data;

	if (job_is_listed(proc)) {
		job_remove(proc);
		process_wait(proc);
	}

	return 0;
}

int job_init() {
	TAILQ_INIT(&jobs);
	signal(SIGCHLD, chldhnd);
	return 0;
}

job_t * job_add(kprocess_t * proc) {
	job_t * np = calloc(1, sizeof(job_t));
	np->proc = proc;
	TAILQ_INSERT_TAIL(&jobs, np, list);
	return np;
}

int job_is_listed(kprocess_t * proc) {
	job_t * p;

	TAILQ_FOREACH(p, &jobs, list) {
		if (p->proc == proc)
			return 1;
	}
	return 0;
}

int job_remove(kprocess_t * proc) {
	job_t * p;

	TAILQ_FOREACH(p, &jobs, list) {
		if (p->proc == proc) {
			TAILQ_REMOVE(&jobs, p, list);
			free(p);
			return 1;
		}
	}
	return 0;
}

