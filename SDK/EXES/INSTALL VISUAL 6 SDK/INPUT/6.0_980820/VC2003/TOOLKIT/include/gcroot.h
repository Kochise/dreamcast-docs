//
//	gcroot.h - Template class that wraps GCHandle from mscorlib.dll.
//		Copyright (C) 2000-2001 Microsoft Corporation
//		All rights reserved.
//
//	Use this class to declare gc "pointers" that live in the C++ heap.
//	
//	Example:
//		struct StringList {
//			gcroot<String*> str;
//			StringList *next;
//			StringList(); // should have ctors and dtors
//			~StringList();
//		};
//
//	By convention, we maintain a 1-to-1 relationship between C++ objects
//	and the handle slots they "point" to.  Thus, two distinct C++ objects
//	always refer to two distinct handles, even if they "point" to the same
//	object.  Therefore, when the C++ object is destroyed, its handle can
//	be freed without error.
//
//	Note that we cannot currently embed a GCHandle directly in an unmanaged C++
//	class.  We therefore store an integer (intptr_t), and use the conversion methods of
//	GCHandle to reconstitute a GCHandle from the integer on demand.
//	


#if _MSC_VER > 1000
#pragma once
#endif

#if !defined(_INC_GCROOT)
#define _INC_GCROOT

#using <mscorlib.dll>

#include <stddef.h>

template <class T> struct gcroot {

	typedef System::Runtime::InteropServices::GCHandle GCHandle;

	// always allocate a new handle during construction (see above)
	//
	gcroot() {
		_handle = GCHandle::op_Explicit(GCHandle::Alloc(0))
#ifdef _WIN32
						.ToInt32()
#elif defined(_WIN64)
						.ToInt64()
#else
#error ERROR: either _WIN64 or _WIN32 must be defined
#endif
		;
	}

	// this can't be T& here because & does not yet work on managed types
	// (T should be a pointer anyway).
	//
	gcroot(T t) {
		_handle = GCHandle::op_Explicit(GCHandle::Alloc(t))
#ifdef _WIN32
						.ToInt32()
#elif defined(_WIN64)
						.ToInt64()
#else
#error ERROR: either _WIN64 or _WIN32 must be defined
#endif
		;
	}

	gcroot(const gcroot& r) {
		// don't copy a handle, copy what it points to (see above)
		_handle = GCHandle::op_Explicit(
						GCHandle::Alloc(
							GCHandle::op_Explicit(r._handle).Target ))
#ifdef _WIN32
						.ToInt32()
#elif defined(_WIN64)
						.ToInt64()
#else
#error ERROR: either _WIN64 or _WIN32 must be defined
#endif
		;
	}

	// Since C++ objects and handles are allocated 1-to-1, we can 
	// free the handle when the object is destroyed
	//
	~gcroot() {
		GCHandle g = GCHandle::op_Explicit(_handle);
		g.Free();
		_handle = 0; // should fail if reconstituted
	}

	gcroot& operator=(T t) {
		// no need to check for valid handle; was allocated in ctor
		GCHandle::op_Explicit(_handle).Target = t;
		return *this;
	}

	gcroot& operator=(const gcroot &r) {
		// no need to check for valid handle; was allocated in ctor
		T t = (T)r;
		GCHandle::op_Explicit(_handle).Target = t;
		return *this;
	}

	operator T () const {
		// gcroot is typesafe, so use static_cast
		return static_cast<T>( GCHandle::op_Explicit(_handle).Target );
	}

	// don't return T& here because & to gc pointer not yet implemented
	// (T should be a pointer anyway).
	T operator->() const {
		// gcroot is typesafe, so use static_cast
		return static_cast<T>(GCHandle::op_Explicit(_handle).Target);
	}

private:
	// Don't let anyone copy the handle value directly, or make a copy
	// by taking the address of this object and pointing to it from
	// somewhere else.  The root will be freed when the dtor of this
	// object gets called, and anyone pointing to it still will
	// cause serious harm to the Garbage Collector.
	//
	intptr_t _handle;
	T* operator& ();
};

#endif  // _INC_GCROOT 
