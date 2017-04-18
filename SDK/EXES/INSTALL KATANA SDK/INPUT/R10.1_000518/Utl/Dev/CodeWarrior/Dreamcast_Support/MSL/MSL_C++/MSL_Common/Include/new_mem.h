/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:41 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef NEW_ALLOC_H
#define NEW_ALLOC_H

#include <mcompile.h>     // hh 971226 added
#include <cstddef>        // hh 971226 added
#include <cstdlib>        // hh 971226 added
#include <new>            // hh 971226 added

#define MSIPL_ALIGN       8
#define MSIPL_MAX_BYTES   128
#define MSIPL_NFREELISTS  MSIPL_MAX_BYTES/MSIPL_ALIGN

#ifdef MSIPL_STL_ALLOCATOR
#define msipl_stl_allocator allocator
#else
#define simple_allocator allocator
#endif

#ifndef DefAllocator
#define DefAllocator allocator
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

template <class T>
class simple_allocator;

template <class T>
class msipl_stl_allocator;

class base_allocator {

protected:
     union obj 
     {
          union obj * free_list_link;
          char client_data[1]; 
     };

     static obj  *free_list[MSIPL_NFREELISTS]; 
     static char *start_free;
     static char *end_free;
     static size_t heap_size;
     DEC_STATIC_MUTEX_P (_mutex)

     static size_t ROUND_UP (size_t bytes) 
     {
          return (((bytes) + MSIPL_ALIGN-1) & ~ (MSIPL_ALIGN - 1));
     }

     static size_t FREELIST_INDEX (size_t bytes) 
     {
          return (((bytes) + MSIPL_ALIGN-1)/MSIPL_ALIGN - 1);
     }

     static void* chunk_alloc (size_t size, int &nobjs);
     static void* refill (size_t n);
};


inline void* base_allocator::chunk_alloc (size_t size, int &nobjs)
{
     char * result;
     size_t total_bytes = size * nobjs;
     size_t bytes_left = size_t(end_free - start_free);
 
     if (bytes_left >= total_bytes) {
          result = start_free;
          start_free += total_bytes;
          return (result);
     } 
     else if (bytes_left >= size) {
          nobjs = int(bytes_left/size);
          total_bytes = size * nobjs;
          result = start_free;
          start_free += total_bytes;
          return (result);
     }
     else {
          size_t bytes_to_get = 2 * total_bytes + ROUND_UP (heap_size >> 4);
 
          if (bytes_left > 0) {
               obj * * my_free_list = free_list + FREELIST_INDEX (bytes_left);
               ((obj *)start_free) -> free_list_link = *my_free_list;
               *my_free_list = (obj *)start_free;
          }
          start_free = (char *)malloc (bytes_to_get);
          if (0 == start_free) {
               int i;
               obj * * my_free_list, *p;

               for (i = int(size); i <= MSIPL_MAX_BYTES; i += MSIPL_ALIGN) {
                    my_free_list = free_list + FREELIST_INDEX (size_t(i));
                    p = *my_free_list;
                    if (0 != p) {
                         *my_free_list = p -> free_list_link;
                         start_free = (char *)p;
                         end_free = start_free + i;
                         return (chunk_alloc (size, nobjs));
                    }
               }
               if (! (start_free = (char *)malloc (bytes_to_get)))
                    THROW_BAD_ALLOC;
          }
          heap_size += bytes_to_get;
          end_free = start_free + bytes_to_get;
          return (chunk_alloc (size, nobjs));
     }
}

inline void* base_allocator::refill (size_t n)
{
     int nobjs = 20;
     char * chunk = (char *)chunk_alloc (n, nobjs);
     obj * * my_free_list;
     obj * result;
     obj * current_obj, * next_obj;
     int i;

     if (1 == nobjs) return (chunk);
     my_free_list = free_list + FREELIST_INDEX (n);

     /* Build free list in chunk */
     result = (obj *)chunk;
     *my_free_list = next_obj = (obj *) (chunk + n);
     for (i=1; ; i++) {
          current_obj = next_obj;
          next_obj = (obj *) ((char *)next_obj + n);
          if (nobjs - 1 == i) {
               current_obj -> free_list_link = 0;
               break;
          } 
          else {
               current_obj -> free_list_link = next_obj;
          }
     }
     return (result);
}


null_template
class msipl_stl_allocator<void> {

public:
     typedef size_t           size_type;
     typedef ptrdiff_t        difference_type;
     typedef void*            pointer;
     typedef const void*      const_pointer;
     typedef void             value_type;

#ifdef MSIPL_MEMBER_TEMPLATE
     template <class U>
     struct rebind {
          typedef msipl_stl_allocator<U>  other;
     };
#endif
};


template <class T>
class msipl_stl_allocator : private base_allocator {

public:
     typedef size_t                        size_type;
     typedef ptrdiff_t                     difference_type;
     typedef T*                            pointer;
     typedef const T*                      const_pointer;
     typedef T&                            reference;
     typedef const T&                      const_reference;
     typedef T                             value_type;
 
#ifdef MSIPL_MEMBER_TEMPLATE
     template <class U>
     struct rebind {
         typedef msipl_stl_allocator<U>  other;
     };
#endif

     typedef base_allocator::obj           obj;

     T* allocate (size_t n);
     
     void deallocate (T* p, size_t n);
   
     pointer address (reference x) const
     { 
          return (pointer)&x; 
     }

     const_pointer address (const_reference x) const
     { 
          return (const_pointer)&x; 
     }

     size_type max_size () const MSIPL_THROW
     { 
          return max (size_type (1), size_type (size_type (-1)/sizeof (T))); 
     }

     void construct (pointer p, const T& val)
     {
          if (p != NULL)
               new ((void*)p) T (val);
          else
               MSIPL_THROW_ME(invalid_argument, "constructing null pointer.\n")
     }

     void destroy (pointer p)
     {
          if (p != NULL)
               ((T*)p)->~T ();
          else
               MSIPL_THROW_ME(invalid_argument, "destroying null pointer.\n")
     }

     msipl_stl_allocator () MSIPL_THROW {}

#ifdef MSIPL_MEMBER_TEMPLATE
     template<class U>
     msipl_stl_allocator (const msipl_stl_allocator<U>&) MSIPL_THROW {}
#else
     msipl_stl_allocator (const msipl_stl_allocator&) MSIPL_THROW {}
#endif

     ~msipl_stl_allocator () MSIPL_THROW {}

private:
     static void* reallocate (void *p, size_t old_sz, size_t new_sz);

};


template <class T>
inline 
T* msipl_stl_allocator<T>::allocate (size_t n)
{
     if (!n) return 0;
     n *= sizeof (T);
     if (n > MSIPL_MAX_BYTES) {
          T * tmp = (T*)(::operator new (__FILE, __LINE__) (n));  // hh 981221
          if (!tmp)
               THROW_BAD_ALLOC;
          return tmp;
     }
     LOCK_P (bl_mutex, _mutex);
     obj * * my_free_list = free_list + FREELIST_INDEX (n);
     obj * result = *my_free_list;
     if (result == 0) 
          return (pointer)refill (ROUND_UP (n));
     *my_free_list = result->free_list_link;
     return (pointer)((void *)result);
}

template <class T>
inline 
void msipl_stl_allocator<T>::deallocate (T* p, size_t n)
{
     if (!n) return;
     n *= sizeof (T);
    if (p&&n) {
          if (n > MSIPL_MAX_BYTES) {
               ::operator delete (p);
               return;
          }
          LOCK_P (bl_mutex, _mutex);
          obj *q = (obj *) ((void*)p);
          obj * * my_free_list = free_list + FREELIST_INDEX (n);
          q->free_list_link = *my_free_list;
          *my_free_list = q;
    }
}

template <class T>
inline 
void* msipl_stl_allocator<T>::reallocate (void *p, size_t old_sz, size_t new_sz)
{
     void * result;
     size_t copy_sz;

     if (old_sz > MSIPL_MAX_BYTES && new_sz > MSIPL_MAX_BYTES) {
          return (realloc (p, new_sz));
     }
     if (ROUND_UP (old_sz) == ROUND_UP (new_sz)) return (p);
     result = allocate (new_sz);
     copy_sz = new_sz > old_sz? old_sz : new_sz;
     memcpy (result, p, copy_sz);
     deallocate (p, old_sz);
     return (result);
}

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* NEW_ALLOC_H */

// hh 971223 added alignment wrapper
// hh 971226 added a bunch of headers
// hh 981221 msipl_stl_allocator<T>::allocate was asking for n*sizeof(T)^2 bytes instead of
//           n*sizeof(T).
