/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:41 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  slist.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_SLIST_H
#define MSIPL_SLIST_H
 
#include <mcompile.h>
 
#include <memory>      // hh 971220 fixed MOD_INCLUDE
#include <algobase.h>  // hh 971220 fixed MOD_INCLUDE
#include <iterator>    // hh 971223 added header <iterator>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

template <class T, class DEFTEMPARG (Allocator, allocator<T>) >
class slist {

public:
     struct slist_node;
     class iterator;
     class const_iterator;
     friend class iterator;
     friend class const_iterator;

     typedef typename Allocator::reference         reference;
     typedef typename Allocator::const_reference   const_reference;
     typedef typename Allocator::size_type         size_type;
     typedef typename Allocator::difference_type   difference_type;
     typedef          T                            value_type;
     typedef          Allocator                    allocator_type;
     typedef typename Allocator::pointer           pointer;
     typedef typename Allocator::const_pointer     const_pointer;
     typedef ALLOC_BIND (slist_node)               slist_node_allocator_type;
     typedef typename slist_node_allocator_type::pointer
                                                   link_type;

     struct slist_node {
          link_type next;
          T data;
     };
 
protected:
     link_type                  head;
     link_type                  cache;
     Allocator                  value_allocator;
     slist_node_allocator_type  slist_node_allocator;
     DEC_OBJ_LOCK(_mutex)

     link_type get_node ()
     {
          WRITE_LOCK(_mutex);
          link_type tmp = cache;
          if (cache)
               cache = (link_type)cache->next;
          else
               tmp = slist_node_allocator.allocate ((size_type)1);
          tmp->next = tmp;
          return tmp;
     }

public:
     class iterator
          : public MSIPLSTD::iterator<forward_iterator_tag, T, 
                                      difference_type, pointer, reference>
     {
          friend class slist<T, Allocator>;
          friend class const_iterator;
 
     protected:
          link_type node;
          DEC_OBJ_LOCK(*iter_mutex)

     #ifdef MSIPL_OBJECT_LOCK
          iterator (link_type x, const slist<T, Allocator>* ptr) : node (x)
          , iter_mutex (&((slist<T, Allocator>*)ptr)->_mutex)
          {}
     #else
		iterator(link_type x, const slist<T, Allocator>*)  // hh 980306 removed unused arg
			: node (x)
		{
		}
     #endif

     public:
          iterator () : node (0)
     #ifdef MSIPL_OBJECT_LOCK
          , iter_mutex (0)
     #endif
          {} 

          ~iterator () {}

          bool operator== (const iterator& x) const
          { 
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node == x.node; }
          }
          bool operator== (const const_iterator& x) const
          { 
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node == x.node; }
          } 
          bool operator!= (const iterator& x) const
          {      
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node != x.node; }
          } 
          bool operator!= (const const_iterator& x) const
          { 
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node != x.node; }
          } 
          reference operator* () const
          {
               READ_LOCK(*iter_mutex);
               return (*node).data;
          }
          pointer operator-> () const
          {
               READ_LOCK(*iter_mutex);
               return &(operator* ());
          }
          iterator& operator++ ()
          {
               WRITE_LOCK(*iter_mutex);
               node = (link_type) ((*node).next);
               return *this;
          }
          iterator operator++ (int)
          {
               iterator tmp = *this;
               ++*this;
               return tmp;
          }
     };

     class const_iterator
          : public MSIPLSTD::iterator<forward_iterator_tag, T, 
                                      difference_type, pointer, reference>
     {
          friend class slist<T, Allocator>;
          friend class slist<T, Allocator>::iterator;  // dwa, hh 980306 added iterator qualifier
 
     protected:
          link_type node;
          DEC_OBJ_LOCK(*iter_mutex)

     #ifdef MSIPL_OBJECT_LOCK
          const_iterator (link_type x, const slist<T, Allocator>* ptr):node (x)
          , iter_mutex (&((slist<T, Allocator>*)ptr)->_mutex)
          {}
     #else
		const_iterator(link_type x, const slist<T, Allocator>*)  // hh 980306 removed unused arg
			: node (x)
		{
		}
     #endif
 
     public:
          const_iterator (): node (0) {}

          const_iterator (const slist<T, Allocator>::iterator& x) : node (x.node)  // dwa, hh 980306 added iterator qualifier
     #ifdef MSIPL_OBJECT_LOCK
          , iter_mutex (x.iter_mutex)
     #endif
          {}
 
          ~const_iterator () {}

          bool operator== (const const_iterator& x) const
          { 
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node == x.node; }
          }
          bool operator!= (const const_iterator& x) const
          { 
               READ_LOCK(*iter_mutex); 
               { READ_LOCK(*(x.iter_mutex)); 
               return node != x.node; }
          }
          const_reference operator* () const
          {
               READ_LOCK(*iter_mutex);
               return (*node).data;
          }
          const_pointer operator-> () const
          {
               READ_LOCK(*iter_mutex);
               return &(operator* ());
          }
          const_iterator& operator++ ()
          {
               WRITE_LOCK(*iter_mutex);
               node = (link_type)((*node).next);
               return *this;
          }
          const_iterator operator++ (int)
          {
               const_iterator tmp = *this;
               ++*this;
               return tmp;
          }
     };
     //  construct/copy/destroy:
     //
     explicit slist (const Allocator& alloc = Allocator ())
          : value_allocator (alloc), cache ((link_type)0)
#ifdef MSIPL_MEMBER_TEMPLATE
            , slist_node_allocator (alloc)
#endif
     { 
          head = get_node (); 
     }      
   
     explicit slist (size_type n, const T& value = T (), 
                     const Allocator& alloc = Allocator ())
          : value_allocator (alloc), cache ((link_type)0)
#ifdef MSIPL_MEMBER_TEMPLATE
            , slist_node_allocator (alloc)
#endif
     { 
          head = get_node ();
          MSIPL_TRY
          {
               insert (begin (), n, value);
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clean_up ();
               slist_node_allocator.deallocate (head, 1);
               throw;
          }
		#endif
     }

#ifdef MSIPL_MEMBER_TEMPLATE
     template <class InputIterator>
     slist (InputIterator first, InputIterator last, 
            const Allocator& alloc = Allocator ())
          : value_allocator (alloc), slist_node_allocator (alloc), cache (0)
     {
          head = get_node ();
          MSIPL_TRY
          {
               insert (begin (), first, last);
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clean_up ();
               slist_node_allocator.deallocate (head, 1);
               throw;
          }
		#endif
     }
#else
     slist (const T* first, const T* last, 
            const Allocator& alloc = Allocator ())
          : value_allocator (alloc), cache (0)
     {
          head = get_node ();
          MSIPL_TRY
          {
               insert (begin (), first, last);
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clean_up ();
               slist_node_allocator.deallocate (head, 1);
               throw;
          }
		#endif
     }
     slist (const_iterator first, const_iterator last, 
            const Allocator& alloc = Allocator ())
          : value_allocator (alloc) , cache (0)
     {
          head = get_node ();
          MSIPL_TRY
          {
               insert (begin (), first, last);
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clean_up ();
               slist_node_allocator.deallocate (head, 1);
               throw;
          }
		#endif
     }
#endif 

     ~slist ()
     {
          clean_up ();
          slist_node_allocator.deallocate (head, 1);
          while (cache) {
               link_type next = (link_type)cache->next;
               slist_node_allocator.deallocate (cache, 1);
               cache = next;
          }
     }

     slist (const slist<T, Allocator>& x)
          : value_allocator (x.value_allocator), cache (0)
#ifdef MSIPL_MEMBER_TEMPLATE
            , slist_node_allocator (x.slist_node_allocator)
#endif
     {
          head = get_node ();
          MSIPL_TRY
          {
               insert (begin (), x.begin (), x.end ());
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clean_up ();
               slist_node_allocator.deallocate (head, 1);
               throw;
          }
		#endif
     }

     slist<T, Allocator>& operator= (const slist<T, Allocator>& x)
     {
          WRITE_LOCK(_mutex);
          READ_LOCK(x._mutex);
          if (this != &x)
          {
               iterator first1 = begin ();
               iterator last1 = end ();
               const_iterator first2 = x.begin ();
               const_iterator last2 = x.end ();
               for (; first1 != last1 && first2 != last2; ++first1, ++first2) 
                    *first1 = *first2;
               if (first2 == last2)
                    erase (first1, last1);
               else
                    insert (last1, first2, last2);
          }
          return *this;
     }

     allocator_type get_allocator () const 
     { 
          READ_LOCK(_mutex);
          return value_allocator; 
     }

     // 
     // Iterators:
     //

     iterator             begin ()
     {
          READ_LOCK(_mutex);
          return iterator ((link_type)(*head).next, this);
     }
     const_iterator       begin () const
     {
          READ_LOCK(_mutex);
          return const_iterator ((link_type)(*head).next, this);
     }
     iterator             end ()
     {
          READ_LOCK(_mutex);
          return iterator (head, this);
     }
     const_iterator       end () const
     {
          READ_LOCK(_mutex);
          return const_iterator (head, this);
     }

     bool      empty ()    const
     {
          READ_LOCK(_mutex);
          return (head->next == head);
     }
     size_type size () const 
     {
          READ_LOCK(_mutex); 
          return (size_type (distance (begin (), end ())));
     }
     size_type max_size () const 
     { 
          return slist_node_allocator.max_size (); 
     }

     void resize (size_type new_size, T c = T ())
     {
          WRITE_LOCK(_mutex);
          const size_type len = size ();

          if (new_size >= len)
               insert (end (), new_size-len, c);
          else 
          {
               link_type next = (link_type)head->next;
               for (size_type i = 0; i < new_size; i++)
                    next = next->next;
               iterator iter(next, this);
               erase (iter, end ());
          }
     }

     //
     //   element access:
     //
     reference         front ()       { return *begin ();   }
     const_reference   front () const { return *begin ();   }

     //
     //   modifiers
     iterator insert (iterator position, const T& x = T ())
     {
          WRITE_LOCK(_mutex);
          link_type tmp = get_node ();
          MSIPL_TRY 
          {
                value_allocator.construct (& ((*tmp).data), x);
          } 
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
             slist_node_allocator.deallocate (tmp, 1);
             throw;
          }
		#endif
          link_type next = (link_type) head->next;
          while (next->next != position.node) 
          {
               MSIPL_ASSERT(next != head)
               next = next->next;
          }
          tmp->next = position.node;
          next->next = tmp;
          return iterator (tmp, this);
     }
     
     void insert (iterator position, size_type n, const T& x)
     {
          for ( ; n > 0; --n)
              insert (position, x);
     }

#ifdef MSIPL_MEMBER_TEMPLATE
     template <class InputIterator>
     void insert (iterator position, InputIterator first, InputIterator last)
     {
          for (; first != last; ++first) 
               insert (position, *first);
     }
#else
     void insert (iterator position, const T* first, const T* last)
     {
          for (; first != last; ++first) 
               insert (position, *first);
     }
 
     void insert (iterator position, const_iterator first, const_iterator last)
     {
          for (; first != last; ++first) 
               insert (position, *first);
     }
#endif

     void push_front (const T& x) { insert (begin (), x); }
     void pop_front ()            { erase (begin ());     }

     iterator previous (const_iterator position)
     {
          READ_LOCK(_mutex);
          link_type next = (link_type) head->next;
          while (next->next != position.node) 
          {
               MSIPL_ASSERT(next != head)
               next = next->next;
          }
          return iterator (next, this);
     }

     const_iterator previous (const_iterator position) const
     {
          READ_LOCK(_mutex);
          link_type next = (link_type) head->next;
          while (next->next != position.node) 
          {
               MSIPL_ASSERT(next != head)
               next = next->next;
          }
          return const_iterator (next, this);
     }

     iterator erase (iterator position)
     {
          WRITE_LOCK(_mutex);
          link_type next = (link_type) head->next;
          while (next->next != position.node) 
          {
               MSIPL_ASSERT(next != head)
               next = next->next;
          }
          next->next = (*position.node).next;   
          iterator ret = iterator ((link_type)(*position.node).next, this);
          value_allocator.destroy (&((*position.node).data));
          (*position.node).next = cache;
          cache = (link_type)position.node;
          return ret;
     }

     iterator erase (iterator first, iterator last)
     {
          while (first != last) 
               erase (first++);
          return last;
     }

     void swap (slist<T, Allocator>& x)
     {
          WRITE_LOCK(_mutex);
          { WRITE_LOCK(x._mutex);
          MSIPLSTD::swap (value_allocator, x.value_allocator);
          MSIPLSTD::swap (slist_node_allocator, x.slist_node_allocator);
          MSIPLSTD::swap (cache, x.cache);
          MSIPLSTD::swap (head, x.head); }
     }

     void clear () { erase (begin (), end ()); }
    
     //
     // slist operations
     //
     void splice (iterator position, slist<T, Allocator>& x)
     {
          if (!x.empty () && &x != this)
               transfer (position, x.begin (), x.end ());
     }

     void splice (iterator position, slist<T, Allocator>& x, iterator i)
     {
          iterator j = i;
          transfer (position, i, ++j);
     }

     void splice (iterator position, 
                  slist<T, Allocator>& x, iterator first, iterator last)
     {
          if (first != last)
               transfer (position, first, last);
     }

	#ifdef MSIPL_MEMBER_TEMPLATE  // hh 980713 Temporarily moved into class definition to support compiler

	template <class Predicate>
	void
	remove_if (Predicate pred)
	{
	     WRITE_LOCK(_mutex);
	     iterator first = begin ();
	     iterator last = end ();
	     while (first != last)
	          if (pred (*first)) 
	               erase (first++);
	          else 
	               first++;
	}
	 
	template <class BinaryPredicate>
	void
	unique (BinaryPredicate binary_pred)
	{
	     WRITE_LOCK(_mutex);
	     iterator first = begin ();
	     iterator last = end ();
	     if (first == last) return;
	     iterator next = first;
	     while (++next != last)
	          if (binary_pred (*first, *next)) { 
	               erase (next); 
	               next =first;
	          }
	          else
	               first = next;
	}
	 
	template <class Compare>
	void
	merge (slist<T, Allocator>& x, Compare comp)
	{
	     if (&x == this) return;
	     WRITE_LOCK(_mutex);
	     iterator first1 = begin ();
	     iterator last1 = end ();
	     iterator first2 = x.begin ();
	     iterator last2 = x.end ();
	     iterator next (first2);
	     while (first1 != last1 && first2 != last2)
	          if (comp (*first2, *first1)) {
	               next = first2;
	               transfer (first1, first2, ++next);
	               first2 = next;
	          } else
	               ++first1;
	     if (first2 != last2) transfer (last1, first2, last2);
	}
	 
	template <class Compare>
	void
	sort (Compare comp)
	{
	     if (size () < 2) return;
	     WRITE_LOCK(_mutex);
	     slist<T, Allocator> carry;
	     slist<T, Allocator> counter[64];
	     int fill = 0;
	     while (!empty ()) {
	          carry.splice (carry.begin (), *this, begin ());
	          int i = 0;
	          while (i < fill && !counter[i].empty ()) {
	               counter[i].merge (carry, comp);
	               carry.swap (counter[i++]);
	          }
	          carry.swap (counter[i]);
	          if (i == fill) ++fill;
	     }
	     while (fill--) merge (counter[fill]);
	}
	 
	#endif  /* MSIPL_MEMBER_TEMPLATE */ 

     void remove (const T& value);
     void unique ();
     void merge  (slist<T, Allocator>& x);
     void sort   ();

     void reverse ();

protected:
     void transfer (iterator position, iterator first, iterator last)
     {
          if (position == first || position == last) return; 
          WRITE_LOCK(_mutex);
          link_type next = (link_type) head->next;
          while (next->next != position.node) 
          {
               MSIPL_ASSERT(next != head)
               next = next->next;
          }
          iterator tmp_pos = iterator (next, this);

          next = (*first.node).next;
          while (next->next != first.node)
               next = next->next;
          iterator tmp_first = iterator (next, this);

          next = (*last.node).next;
          while (next->next != last.node)
               next = next->next;
          iterator tmp_last = iterator (next, this);

          (*tmp_pos.node).next = (*tmp_first.node).next;
          (*tmp_first.node).next = (*tmp_last.node).next;
          (*tmp_last.node).next = position.node;
     }

     void clean_up ()
     {
          link_type next = (link_type) head->next;
          while (next != head) {
               link_type tmp = next;
               next = (link_type) next->next;
               value_allocator.destroy (&((*tmp).data));
               slist_node_allocator.deallocate (tmp, 1);
          }
          head->next = head;
     }

};

template <class T, class Allocator>
inline bool
operator== (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return x.size () == y.size () && equal (x.begin (), x.end (), y.begin ()); }
 
template <class T, class Allocator>
inline bool
operator< (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ()); }
 
template <class T, class Allocator>
inline bool
operator!= (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return ! (x == y); }
 
template <class T, class Allocator>
inline bool
operator<= (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return ! (y < x); }
 
template <class T, class Allocator>
inline bool
operator>= (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return ! (x < y); }
 
template <class T, class Allocator>
inline bool
operator> (const slist<T, Allocator>& x, const slist<T, Allocator>& y)
{ return (y < x); }

template <class T, class Allocator>
inline 
void slist<T, Allocator>::remove (const T& value)
{
     WRITE_LOCK(_mutex);
     iterator first = begin ();
     iterator last = end ();
     while (first != last)
          if (*first == value) 
               erase (first++);
          else 
               ++first;
}
 
template <class T, class Allocator>
inline
void slist<T, Allocator>::unique ()
{
     iterator first = begin ();
     iterator last = end ();
     if (first != last) {  
          WRITE_LOCK(_mutex);
          iterator next = first;
          while (++next != last) {
               if (*first == *next)
                    erase (next);
               else
                    first = next;
               next = first;
          }
     }
}
template <class T, class Allocator>
inline
void slist<T, Allocator>::merge (slist<T, Allocator>& x)
{
     if (&x == this || x.empty ()) return;
     WRITE_LOCK(_mutex);
     if (empty ()) {
          transfer (begin (), x.begin (), x.end ());
          return;
     }
     iterator first1 = begin ();
     iterator last1 = end ();
     iterator first2 = x.begin ();
     iterator last2 = x.end ();
     iterator next (first2);
     while (first1 != last1 && first2 != last2)
          if (*first2 < *first1) {
               next = first2;
               transfer (first1, first2, ++next);
               first2 = next;
          } 
          else
               ++first1;
     if (first2 != last2) 
          transfer (last1, first2, last2);
}

template <class T, class Allocator>
inline
void slist<T, Allocator>::reverse ()
{
    if (empty ()) return;
    WRITE_LOCK(_mutex);
    link_type result = head->next;
    link_type node = result;
    node = node->next;
    result->next = head;
    while (node != head) {
         link_type next = node->next;
         node->next = result;
         result = node;
         node = next;
    }
    head->next = result;
}          
 
template <class T, class Allocator> 
inline
void slist<T, Allocator>::sort ()
{
     if (size () < 2) return;
     WRITE_LOCK(_mutex);
     slist<T, Allocator> carry;
     slist<T, Allocator> counter[64];
     int fill = 0;
     while (!empty ()) {
          carry.splice (carry.begin (), *this, begin ());
          int i = 0;
          while (i < fill && !counter[i].empty ()) {
               counter[i].merge (carry);
               carry.swap (counter[i++]);
          }
          carry.swap (counter[i]);
          if (i == fill) ++fill;
     }
     while (fill--) merge (counter[fill]);
}
 
MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif

// hh 971220 fixed MOD_INCLUDE
// hh 971223 added alignment wrapper
// hh 971223 added header <iterator>
// dwa, hh 980306 added qualifier to iterator in two places
// hh 980306 removed unused argument in two places
// hh 980713 Temporarily moved member templates into class definition to support compiler
// hh 980902 #ifdef'd out exception code when ndef MSIPL_EXCEPT
