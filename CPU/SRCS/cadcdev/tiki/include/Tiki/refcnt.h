/*
   Tiki

   refcnt.h

   Copyright (C)2002 Dan Potter
   Copyright (C)2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_REFCNT_H
#define __TIKI_REFCNT_H

/// \file The base object class for all Tiki objects. This includes a
/// simple reference counting system for managing shared data objects.

#include <stdio.h>
#include <assert.h>

#include <set>
#include <map>
#include <list>

namespace Tiki {

/// The reference count base class itself. Any class you want handled
/// by reference counting should add this as a public base class.
class RefCnt {
public:
	RefCnt();
	virtual ~RefCnt();

	// Add a reference to the object
	void ref();

	// Remove a reference to the object; if we hit
	// zero then delete it
	void unref();

protected:
#if TIKI_PLAT == TIKI_WIN32
	long m_refcnt;
#else
	int	m_refcnt;
#endif
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

	/* T** operator&() const {
		return &p;
	} */

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

}

#endif	// __TIKI_REFCNT_H

