/*+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

Copyright (c) 1999 Microsoft Corporation

Module Name:

    CQueue.cpp

Abstract:

    Queue functionality.

-------------------------------------------------------------------*/

// ++++ Include Files +++++++++++++++++++++++++++++++++++++++++++++++
#include "Keyboard.hpp"

CQueue::CQueue()
{
    m_pcellHead = NULL;
    m_pcellTail = NULL;
}

CQueue::~CQueue()
{
    int nTrash;

    while (!IsEmpty())
        Dequeue(&nTrash);
}

void
CQueue::Enqueue(int iValue)
{
    typeCell *pcellNew = new typeCell;
    pcellNew->nElement  = iValue;
    pcellNew->pcellNext = NULL;
    
    if (IsEmpty())
    {
        m_pcellHead = m_pcellTail = pcellNew;
    }
    else
        m_pcellTail->pcellNext = pcellNew;
}

// FALSE == empty list
BOOL
CQueue::Dequeue(int *pnValue)
{
    typeCell *pcellTemp;

    if (IsEmpty())
        return FALSE;

    *pnValue = m_pcellHead->nElement;
    pcellTemp = m_pcellHead;
    m_pcellHead = m_pcellHead->pcellNext;
    delete pcellTemp;

    return TRUE;
}

BOOL
CQueue::IsEmpty()
{
    return (m_pcellHead == NULL);
}
