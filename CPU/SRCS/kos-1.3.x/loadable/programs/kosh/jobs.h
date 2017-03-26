/*
 * jobs.h
 *
 * Coprygiht (C) 2003 Dan Potter
 */
#ifndef _KOSH_JOBS_H
#define _KOSH_JOBS_H

#include <sys/queue.h>
#include <sys/process.h>

struct job;
TAILQ_HEAD(jobqueue, job);

typedef struct job {
	TAILQ_ENTRY(job)	list;
	kprocess_t		* proc;
} job_t;

int job_init();
job_t * job_add(kprocess_t * proc);
int job_is_listed(kprocess_t * proc);
int job_remove(kprocess_t * proc);

#endif

