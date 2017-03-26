/*      
   Tsunami for KallistiOS ##version##
        
   refcnt.h

   (c)2002 Dan Potter

   $Id: refcnt.h,v 1.1 2002/09/09 08:43:37 bardtx Exp $
*/

#ifndef __TSUNAMI_REFCNT_H
#define __TSUNAMI_REFCNT_H

/// \file A simple reference counting system for managing shared
/// data objects.

#include <arch/arch.h>
#include <stdio.h>
#include <assert.h>

/// The reference count base class itself. Any class you want handled
/// by reference counting should add this as a public base class.
class RefCnt {
public:
	RefCnt() {
		m_refcnt = 0;
	}
	virtual ~RefCnt() {
		if (m_refcnt != 0) {
			dbglog(DBG_WARNING, "RefCnt::~RefCnt: **WARNING** My (%08lx), refcount isn't zero! It's %d.\n",
				(uint32)this, m_refcnt);
		}
		assert( m_refcnt == 0 );
	}

	// Add a reference to the object
	void ref() {
#ifndef NDEBUG
		if (this == NULL) {
			dbglog(DBG_WARNING, "RefCnt::ref() about to assert for caller=%08lx\n",
				arch_get_ret_addr());
		}
		assert( this != NULL );
#endif
		m_refcnt++;
	}

	// Remove a reference to the object; if we hit
	// zero then delete it
	void unref() {
#ifndef NDEBUG
		if (this == NULL) {
			dbglog(DBG_WARNING, "RefCnt::unref() about to assert for caller=%08lx\n",
				arch_get_ret_addr());
		}
		assert( this != NULL );
#endif

		m_refcnt--;
		if (m_refcnt < 0) {
			dbglog(DBG_WARNING, "RefCnt::unref() refcount underflow! this=%08lx, caller=%08lx\n",
				(uint32)this, arch_get_ret_addr());
			assert( false );
		} else {
			if (m_refcnt == 0)
				delete this;
		}
	}

private:
	int	m_refcnt;
};


/// A "smart pointer" to handle the RefCnt objects.
template <class T>
class RefPtr {
public:
	RefPtr() {
		p = NULL;
	}
	RefPtr(T * pi) {
		p = pi;
		if (p != NULL)
			p->ref();
	}
	RefPtr(const RefPtr<T>& pi) {
		p = pi.p;
		if (p != NULL)
			p->ref();
	}
	virtual ~RefPtr() {
		if (p)
			p->unref();
	}

	operator T*() const {
		return p;
	}

	T& operator*() const {
		assert( p != NULL );
		return *p;
	}

	T** operator&() const {
		return &p;
	}

	T* operator->() const {
		assert( p != NULL );
		return p;
	}

	bool operator!() const {
		return p == NULL;
	}

	T* operator=(T* pi) {
		if (pi != NULL)
			pi->ref();
		if (p != NULL)
			p->unref();
		p = pi;
		return p;
	}

	T* operator=(const RefPtr<T>& other) {
		if (other.p != NULL)
			other.p->ref();
		if (p != NULL)
			p->unref();
		p = other.p;
		return p;
	}

	bool operator==(const RefPtr<T>& other) {
		return other.p == p;
	}

	bool operator==(const T* other) {
		return other == p;
	}

private:
	T * p;
};


#endif	/* __TSUNAMI_REFCNT_H */

