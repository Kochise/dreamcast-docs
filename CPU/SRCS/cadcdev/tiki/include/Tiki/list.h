/*
   Tiki

   list.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_LIST_H
#define __TIKI_LIST_H

/// \file A basic linked-list class. The only real constraint here
/// is that the type T must be a subclass of RefCnt or something that
/// provides similar methods. This cheats a little by implementing
/// all the core functionality via the BSD queue macros, but it provides
/// a much nicer C++ interface.

#include <assert.h>
#include "refcnt.h"

// Needed due to namespace pollution on Win32. :(
#if TIKI_PLAT == TIKI_WIN32
#undef SLIST_ENTRY
#endif
#include <sys/queue.h>

namespace Tiki {

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
	
	/// Get the previous list item
	ListNode<T> * getPrev() const {
		assert( m_inlist );
		if ( !m_inlist )
			return NULL;
		
		return TAILQ_PREV(this, List<T>::listnodehead, m_listptr);
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

	/// Insert us before another element
	void insertBefore(ListNode<T> * other) {
		assert( !m_inlist );
		if (m_inlist) return;

		TAILQ_INSERT_BEFORE(other, this, m_listptr);
		m_inlist = true;
	}

	/// Insert us after another element
	void insertAfter(ListNode<T> * other) {
		assert( !m_inlist );
		if (m_inlist) return;

		TAILQ_INSERT_AFTER(&m_head->m_list, other, this, m_listptr);
		m_inlist = true;
	}
	
	/// Insert us at the front of the list
	void insertHead() {
		assert( !m_inlist );
		if (m_inlist) return;
		
		TAILQ_INSERT_HEAD(&m_head->m_list, this, m_listptr);
		m_inlist = true;
	}

	/// Insert us at the end of the list
	void insertTail() {
		assert( !m_inlist );
		if (m_inlist) return;
		
		TAILQ_INSERT_TAIL(&m_head->m_list, this, m_listptr);
		m_inlist = true;
	}

	/// Causes this item to be re-sorted in this list.
	/// Note: Requires an operator< in the wrapped object.
	void reSort() {
		// Look through the list for something we can go before.
		ListNode<T> * n;
		TAILQ_FOREACH(n, &m_head->m_list, m_listptr) {
			if (m_data->operator<(*(n->m_data))) {
				remove();
				insertBefore(n);
				return;
			}
		}
		
		// Needs to go at the end.
		remove();
		insertTail();
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
		ni->insertHead();
	}

	/// Insert an item at the tail of the list. A reference will be added.
	void insertTail(T * item) {
		ListNode<T> * ni = new ListNode<T>(this, item);
		ni->insertTail();
	}

	/// Insert the item into the list at the proper sorted location.
	/// Note: Requires an operator< in the wrapped object.
	void insertSorted(T * item) {
		// Look through the list for something it can go before.
		ListNode<T> * n, * ni = new ListNode<T>(this, item);
		TAILQ_FOREACH(n, &m_list, m_listptr) {
			if (item->operator<(*(n->getData()))) {
				ni->insertBefore(n);
				return;
			}
		}
		
		// Looks like it goes at the end.
		ni->insertTail();
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
	friend struct ListNode<T>;
	
	TAILQ_HEAD(listnodehead, ListNode<T>) m_list;

public:
	/// Return the element at the end of the list
	ListNode<T>	* getTail() const {
		return TAILQ_LAST(&m_list, listnodehead);
	}
};

}

#endif	// __TIKI_LIST_H
