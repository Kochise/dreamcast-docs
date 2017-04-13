//-----------------------------------------------------------------------------
// Microsoft OLE DB TABLECOPY Sample
// Copyright (C) 1995-1998 Microsoft Corporation
//
// @doc
//
// @module LIST.H
//
//-----------------------------------------------------------------------------
#ifndef _LIST_H_
#define _LIST_H_
			
/////////////////////////////////////////////////////////////////////////////
// Includes
//
/////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////
// Defines
//
/////////////////////////////////////////////////////////////////////////////
typedef void* LISTPOS;


/////////////////////////////////////////////////////////////////////////////
// CNode
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> class CNode
{
public:
	// constructors
	CNode(TYPE val, CNode* pPrevNode, CNode* pNextNode);

	// members
	TYPE     m_data;       // element data
	CNode*   m_pNextNode;  // next CNode
	CNode*   m_pPrevNode;  // prev CNode
};


/////////////////////////////////////////////////////////////////////////////
// CNode::CNode
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> CNode<TYPE>::CNode(TYPE data, CNode* pPrevNode, CNode* pNextNode)
{
	//Constructor
	m_data = data;
	m_pPrevNode = pPrevNode;
	m_pNextNode = pNextNode;
}



/////////////////////////////////////////////////////////////////////////////
// CList
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> class CList
{
public:

	//constructors
	CList();
	virtual ~CList();

	//members
	
	//list modifying operations
	virtual LISTPOS	AddHead(TYPE element);		// Add to Head
	virtual LISTPOS	AddTail(TYPE element);		// Add to Tail

	virtual LISTPOS	InsertBefore(LISTPOS position, TYPE element);	// Add before position
	virtual LISTPOS	InsertAfter(LISTPOS position, TYPE element);	// Add after position

	virtual TYPE	RemoveHead();				// Remove from Head
	virtual TYPE	RemoveTail();				// Remove from Tail
	virtual TYPE	RemoveAt(LISTPOS position); // RemoveAt position
	virtual void	RemoveAll();				// Remove all elements

	//Seeking methods
	virtual LISTPOS	Find(TYPE element);	        // Find element

	//Peek methods
	virtual LISTPOS	GetHeadPosition();			// Head Position
	virtual LISTPOS	GetTailPosition();			// Tail Position

	virtual TYPE		GetHead();					// Head element
	virtual TYPE		GetTail();					// Tail element
	virtual TYPE		GetNext(LISTPOS& position); // Next element
	virtual TYPE		GetPrev(LISTPOS& position); // Prev element

	//Data methods
	virtual TYPE		GetAt(LISTPOS position) const;			//Get element value
	virtual TYPE		SetAt(LISTPOS position, TYPE element);	//Set element value

	//Array-like methods
	virtual LISTPOS	FindIndex(ULONG iIndex);	//Index element

	//informational methods
	virtual BOOL		IsEmpty();					// IsEmpty
	virtual ULONG		GetCount();					// Elements in the list

private:
	//data
	CNode<TYPE>*		m_pHeadNode;				// Head of CList
	CNode<TYPE>*		m_pTailNode;				// Tail of CList

	ULONG				m_ulElements;				// Elements in the list
};


/////////////////////////////////////////////////////////////////////////////
// CList::CList
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> CList<TYPE>::CList()
{
	//constructor
	m_pHeadNode = NULL;
	m_pTailNode = NULL;
	m_ulElements = 0;
}

/////////////////////////////////////////////////////////////////////////////
// CList::~CList
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> CList<TYPE>::~CList() 
{
	//Remove all elements
	RemoveAll();
}


/////////////////////////////////////////////////////////////////////////////
// CList::AddHead
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::AddHead(TYPE element) 
{
	//Add to the Head of the CList, (stack)
	CNode<TYPE>* pHeadNode = new CNode<TYPE>(element, NULL, m_pHeadNode);
	ASSERT(pHeadNode);

	//If there was a list hook the head->prev to the new head
	if(m_pHeadNode) 
	  m_pHeadNode->m_pPrevNode = pHeadNode;

	//If there isn't a tail element, hook it to the head
	if(!m_pTailNode)
	  m_pTailNode = pHeadNode;

	m_pHeadNode = pHeadNode;
	m_ulElements++;
	return m_pHeadNode;
}


/////////////////////////////////////////////////////////////////////////////
// CList::AddTail
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::AddTail(TYPE element) 
{
	//Add to the m_pTailNode of the CList
	CNode<TYPE>* pTailNode = new CNode<TYPE>(element, m_pTailNode, 0);
	ASSERT(pTailNode);

	//if previously empty
	if(!m_pHeadNode)
		m_pHeadNode = pTailNode;
	else
		m_pTailNode->m_pNextNode = pTailNode;

	m_pTailNode = pTailNode;
	m_ulElements++;
	return m_pTailNode;
}



/////////////////////////////////////////////////////////////////////////////
// CList::GetHeadPosition
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline LISTPOS CList<TYPE>::GetHeadPosition() 
{
	//return Head element Position
	return m_pHeadNode;
}

/////////////////////////////////////////////////////////////////////////////
// CList::GetTailPosition
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline LISTPOS CList<TYPE>::GetTailPosition() 
{
	//return Tail element Position
	return m_pTailNode;
}

/////////////////////////////////////////////////////////////////////////////
// CList::GetHead
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::GetHead() 
{
	//return Head element value
	ASSERT(m_pHeadNode);
	return m_pHeadNode->m_data;
}

/////////////////////////////////////////////////////////////////////////////
// CList::AddTail
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::GetTail() 
{
	// return Tail element value
	ASSERT(m_pTailNode);
	return m_pTailNode->m_data;
}


/////////////////////////////////////////////////////////////////////////////
// CList::GetNext
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::GetNext(LISTPOS& position) 
{
	ASSERT(position);

	//Set position to the next element
	CNode<TYPE>* pNode = (CNode<TYPE>*)position;
	position = pNode->m_pNextNode;

	//return the current element
	return pNode->m_data;
}


/////////////////////////////////////////////////////////////////////////////
// CList::GetPrev
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::GetPrev(LISTPOS& position) 
{
	ASSERT(position);
	
	//Set position to the next element
	CNode<TYPE>* pNode = (CNode<TYPE>*)position;
	position = pNode->m_pPrevNode;
	
	//return the current element
	return pNode->m_data;
}


/////////////////////////////////////////////////////////////////////////////
// CList::GetAt
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::GetAt(LISTPOS position) const
{
	ASSERT(position);
	return ((CNode<TYPE>*)position)->m_data;
}

/////////////////////////////////////////////////////////////////////////////
// CList::SetAt
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline TYPE CList<TYPE>::SetAt(LISTPOS position, TYPE element)
{
	ASSERT(position);

	//Save the old data
	CNode<TYPE>* pNode = (CNode<TYPE>*)position;
	TYPE oldData = pNode->m_data;

	//Store new data
	pNode->m_data = element;

	//return olddata
	return oldData;
}


/////////////////////////////////////////////////////////////////////////////
// CList::Find
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::Find(TYPE element) 
{
	//return pointer to found element
	for(CNode<TYPE>* p = m_pHeadNode; p; p = p->m_pNextNode)
	  if(p->m_data == element)
		return p;   // return position to found CNode

	return NULL;  // return NULL if not found
}


/////////////////////////////////////////////////////////////////////////////
// CList::IsEmpty
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline BOOL CList<TYPE>::IsEmpty() 
{
	// returns TRUE if Empty
	return m_ulElements == 0;
}



/////////////////////////////////////////////////////////////////////////////
// CList::RemoveHead
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> TYPE CList<TYPE>::RemoveHead() 
{
	//Remove and return from the Head of the List
	ASSERT(m_pHeadNode);

	CNode<TYPE>* pHeadNode = m_pHeadNode;	// pointer to the Removed node
	TYPE element = GetHead();				//make a copy, before deleteing

	m_pHeadNode = pHeadNode->m_pNextNode;		// reroute Head to exclude the first element
	if(m_pHeadNode)
		m_pHeadNode->m_pPrevNode = NULL;
	else
		m_pTailNode = NULL;

	m_ulElements--;
	delete pHeadNode;						// delete head
	return element;
}


/////////////////////////////////////////////////////////////////////////////
// CList::RemoveTail
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> TYPE CList<TYPE>::RemoveTail() 
{
	//Remove and return from the m_pTailNode of the CList
	ASSERT(m_pTailNode);

	CNode<TYPE>* pTailNode = m_pTailNode->m_pPrevNode;
	TYPE element = GetTail();  //make a copy before deleteing

	m_pTailNode = pTailNode;
	if(m_pTailNode)
		m_pTailNode->m_pNextNode = NULL;
	else
		m_pHeadNode = NULL;

	m_ulElements--;
	delete m_pTailNode;
	return element;
}


/////////////////////////////////////////////////////////////////////////////
// CList::RemoveAt
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> TYPE CList<TYPE>::RemoveAt(LISTPOS position)
{
	//Remove CList[position]
	ASSERT(position);

	CNode<TYPE>* pNode = (CNode<TYPE>*)position;
	TYPE oldData = pNode->m_data;

	// If removing the head
	if (pNode == m_pHeadNode)
		m_pHeadNode = pNode->m_pNextNode;
	else
		pNode->m_pPrevNode->m_pNextNode = pNode->m_pNextNode;
	
	//If removing the tail
	if (pNode == m_pTailNode)
		m_pTailNode = pNode->m_pPrevNode;
	else
		pNode->m_pNextNode->m_pPrevNode = pNode->m_pPrevNode;

	m_ulElements--;
	delete pNode;
	return oldData;
}


/////////////////////////////////////////////////////////////////////////////
// CList::RemoveAll
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> void CList<TYPE>::RemoveAll() 
{
	// Remove all items from the CList
	for(CNode<TYPE>* p = m_pHeadNode; p; p = p->m_pNextNode) 	
		delete p;

	m_pHeadNode   = NULL;
	m_pTailNode   = NULL;
	m_ulElements    = 0;
}


/////////////////////////////////////////////////////////////////////////////
// CList::GetCount
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> inline ULONG CList<TYPE>::GetCount() 
{
	// return the Length
	return m_ulElements;
}

				   
/////////////////////////////////////////////////////////////////////////////
// CList::InsertBefore
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::InsertBefore(LISTPOS position, TYPE element)
{
	//insert before the position
	if(position == m_pHeadNode)    // Add before Head
	  return AddHead(element);

	CNode<TYPE>* pOldNode = (CNode<TYPE>*)position;

	//otherwise a little more difficult
	CNode<TYPE>* pNewNode = new CNode<TYPE>(element, pOldNode->m_pPrevNode, pOldNode);
	
	//Create the new node
	pNewNode->m_pNextNode = new CNode<TYPE>(element, pOldNode->m_pPrevNode, pOldNode->m_pNextNode);

	//Hook up before after nodes to it
	pOldNode->m_pPrevNode->m_pNextNode = pNewNode;
	pOldNode->m_pPrevNode = pNewNode;

	m_ulElements++;
	return pNewNode;
}



/////////////////////////////////////////////////////////////////////////////
// CList::InsertAfter
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::InsertAfter(LISTPOS position, TYPE element)
{
	//insert after the position
	if(position == m_pTailNode)     // Add after the m_pTailNode
	  return AddTail(element);
	
	CNode<TYPE>* pOldNode = (CNode<TYPE>*)position;

	//other wise a little more difficult
	CNode<TYPE>* pNewNode = new CNode<TYPE>(element, pOldNode, pOldNode->m_pNextNode);
	
	//Hook up before after nodes to it
	pOldNode->m_pNextNode->m_pPrevNode = pNewNode;
	pOldNode->m_pNextNode = pNewNode;

	m_ulElements++;
	return pNewNode;
}


/////////////////////////////////////////////////////////////////////////////
// CList::FindIndex
//
/////////////////////////////////////////////////////////////////////////////
template <class TYPE> LISTPOS CList<TYPE>::FindIndex(ULONG iIndex)
{
	ASSERT(iIndex>=0 && iIndex<m_ulElements);

	CNode<TYPE>* pNode = m_pHeadNode;

	//Find the specified index
	while(iIndex--)
		pNode = pNode->m_pNextNode;

	return (LISTPOS)pNode;
}

#endif //_LIST_H_

