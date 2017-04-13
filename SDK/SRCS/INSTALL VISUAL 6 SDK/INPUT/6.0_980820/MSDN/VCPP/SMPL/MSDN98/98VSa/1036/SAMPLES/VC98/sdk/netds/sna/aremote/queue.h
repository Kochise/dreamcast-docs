#ifndef __QUEUE_H__
#define __QUEUE_H__
typedef struct qnode_st {
	struct qnode_st	*next;
	struct qnode_st	*prev;
	void 		*ptr;
	int		qnodeid;		/* do not change	*/
} qnode;

typedef struct queue_st {
	qnode		*head;
	qnode		*tail;
} queue;

qnode *addtoq(queue *q, void *p);
void *removeheadfromq(queue *q);
void *removeqnodefromq(queue *q, qnode *t);
queue *newq(void);
#endif /* __QUEUE_H__ */

