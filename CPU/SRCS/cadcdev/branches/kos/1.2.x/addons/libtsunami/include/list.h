/*      
   Tsunami for KallistiOS ##version##

   list.h

   (c)2002 Dan Potter

   $Id: list.h,v 1.3 2003/04/24 02:57:20 bardtx Exp $
*/

#ifndef __TSUNAMI_LIST_H
#define __TSUNAMI_LIST_H

/// \file A basic linked-list class. The only real constraint here
/// is that the type T must be a subclass of RefCnt or something that
/// provides similar methods. This cheats a little by implementing
/// all the core functionality via the BSD queue macros, but it provides
/// a much nicer C++ interface.

#include <assert.h>
#include <string.h>
#include <sys/queue.h>
#include "refcnt.h"

template <class T>
class List;

template <class T>
struct ListNode {
public:
	ListNode<T>(List<T> * head, T * d)
		: m_head(head), m_data(d), m_inlist(false)
	{ }

	virtual ~ListNode<T>() {
		assert( !m_inlist );
	}

	/// Get the next list item
	ListNode<T> * getNext() const {
		assert( m_inlist );
		if ( !m_inlist )
			return NULL;

		return TAILQ_NEXT(this, m_listptr);
	}

	/// Get this list item's data
	T * getData() const { return m_data; }

	/// Perform an operation on this list item's data
	T * operator->() const {
		assert( m_data != NULL );
		return (T*)m_data;
	}

	/// Remove this item from the list (doesn't delete it)
	void remove() {
		assert( m_inlist );
		if (!m_inlist) return;

		TAILQ_REMOVE(&m_head->m_list, this, m_listptr);
		m_inlist = false;
	}

	/// Insert another element before us
	void insertBefore(ListNode<T> * other) {
		assert( !m_inlist );
		if (m_inlist) return;

		TAILQ_INSERT_BEFORE(other, this, m_listptr);
		m_inlist = true;
	}

	/// Insert another element after us
	void insertAfter(ListNode<T> * other) {
		assert( !m_inlist );
		if (m_inlist) return;

		TAILQ_INSERT_AFTER(&m_head->m_list, other, this, m_listptr);
		m_inlist = true;
	}

private:
	List<T>				* m_head;
	RefPtr<T>			m_data;
	bool				m_inlist;

	friend class List<T>;
	TAILQ_ENTRY(ListNode<T>)	m_listptr;
};


template <class T>
class List {
public:
	List() {
		TAILQ_INIT(&m_list);
	}
	
	virtual ~List() {
		delAll();
	}

	/// Insert an item at the head of the list. A reference will be added.
	void insertHead(T * item) {
		ListNode<T> * ni = new ListNode<T>(this, item);
		TAILQ_INSERT_HEAD(&m_list, ni, m_listptr);
		ni->m_inlist = true;
	}

	/// Insert an item at the tail of the list. A reference will be added.
	void insertTail(T * item) {
		ListNode<T> * ni = new ListNode<T>(this, item);
		TAILQ_INSERT_TAIL(&m_list, ni, m_listptr);
		ni->m_inlist = true;
	}

	/// Delete the named item. Return true if we actually had it. Its
	/// reference will be removed if it is found.
	bool del(T * item) {
		ListNode<T> * n;
		
		TAILQ_FOREACH(n, &m_list, m_listptr) {
			if (n->getData() == item) {
				n->remove();
				delete n;
				return true;
			}
		}

		return false;
	}

	/// Remove all items from the list.
	void delAll() {
		ListNode<T> * n, * t;

		// Pull each item from the list and destroy it
		t = TAILQ_FIRST(&m_list);
		while (t) {
			n = t->getNext();
			t->m_inlist = false;
			delete t;
			t = n;
		}

		// Re-init the list
		TAILQ_INIT(&m_list);
	}

	/// Return the element at the head of the list
	ListNode<T>	* getHead() const {
		return TAILQ_FIRST(&m_list);
	}

private:
	friend class ListNode<T>;
	
	TAILQ_HEAD(listnodehead, ListNode<T>) m_list;

public:
	/// Return the element at the end of the list
	ListNode<T>	* getTail() const {
		return TAILQ_LAST(&m_list, listnodehead);
	}
};

#endif	// __TSUNAMI_LIST_H
