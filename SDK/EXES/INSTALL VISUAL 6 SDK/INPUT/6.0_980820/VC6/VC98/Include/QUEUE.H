
//=============================================================================
//  Microsoft (R) Bloodhound (tm). Copyright (C) 1991-1993.
//
//  MODULE: queue.h
//
//  Modification History
//
//  raypa           03/17/93    Created.
//=============================================================================

#if !defined(_QUEUE_)

#include "list.h"

#define _QUEUE_
#pragma pack(1)

//=============================================================================
//  Macros.
//=============================================================================

typedef LIST QUEUE;                         //... Queue is a special list.

typedef QUEUE *LPQUEUE;

//=============================================================================
//  Macros.
//=============================================================================

#ifndef NO_INLINE

#define GetQueueHead(Queue)                 ((LPVOID) (((LPQUEUE) (Queue))->Head))

#define GetQueueTail(Queue)                 ((LPVOID) (((LPQUEUE) (Queue))->Tail))

#define GetQueueLength(Queue)               (((LPQUEUE) (Queue))->Length)

#define AddToFrontOfList(List, Link)        AddToList((List), NULL, (Link))

#define AddToEndOfList(List, Link)          AddToList((List), (Link), NULL)

#define DeleteFromFrontOfList(List)         DeleteFromList((List), GetHeadOfList(List))

#define DeleteFromEndOfList(List)           DeleteFromList((List), GetTailOfList(List))

#define InitializeQueue(Queue)              InitializeList(Queue)

#define Enqueue(Queue, Link)                AddToEndOfList(Queue, Link)

#define Requeue(Queue, Link)                AddToFrontOfList(Queue, Link)

#define Dequeue(Queue)                      ((LPVOID) DeleteFromFrontOfList(Queue))

#endif

#pragma pack()
#endif
