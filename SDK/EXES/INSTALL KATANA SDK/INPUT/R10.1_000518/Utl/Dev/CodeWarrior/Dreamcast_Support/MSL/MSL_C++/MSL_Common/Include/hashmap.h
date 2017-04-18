/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/**
 **  hashmap.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_HASH_MAP_H
#define MSIPL_HASH_MAP_H

#ifndef _No_Floating_Point

#include <mcompile.h>

#include <hashtbl.h>    // hh 971220 fixed MOD_INCLUDE

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN

template <class Key, class T, class HashFunction, class KeyEqual>
class hash_map {
public:
    //
    // typedefs:
    //
    typedef Key                  key_type;
    typedef pair<M_CONST Key, T> value_type;
    typedef HashFunction         hash_function;
    typedef KeyEqual             key_equal;

    class value_compare
        : public binary_function<value_type, value_type, bool> {
 
        friend class hash_map<Key, T, HashFunction, KeyEqual>;
    protected :
 
        KeyEqual comp;
        value_compare (KeyEqual c) : comp (c) {}
 
    public:
 
        bool operator () (const value_type& x, const value_type& y) const
        {
            return comp (x.first, y.first);
        }
    };

private:

    typedef hash_table<key_type, value_type,
                       select1st<value_type, key_type>,
                       hash_function, key_equal, allocator<value_type> >        rep_type;
    rep_type ht;  // hash_table representing hash_map

public:

    typedef typename rep_type::reference          reference;
    typedef typename rep_type::const_reference    const_reference;
    typedef typename rep_type::iterator           iterator;
    typedef typename rep_type::const_iterator     const_iterator;
    typedef typename rep_type::size_type          size_type;
    typedef typename rep_type::difference_type    difference_type;
    typedef pair<iterator, iterator>             pair_iterator_iterator; 
    typedef pair<const_iterator, const_iterator> pair_citerator_citerator; 

    //
    // allocation/deallocation
    //
    hash_map (size_type initSize     = 10007,
              const HashFunction& hf = HashFunction (),
              const KeyEqual& equal  = KeyEqual ()) 
    : ht (initSize, hf, equal) {}

    hash_map (const value_type* first,
              const value_type* last,
              size_type initSize       = 10007,
              const HashFunction& hf   = HashFunction (),
              const KeyEqual& equal    = KeyEqual ()) 
    : ht (first, last, initSize, hf, equal) {}

    //
    // copying, assignment, swap
    //
    hash_map (const hash_map<Key, T, HashFunction, KeyEqual>& x) 
    : ht (x.ht) {}

    hash_map<Key,T,HashFunction,KeyEqual>& 
    operator= (const hash_map<Key, T, HashFunction, KeyEqual>& x)
    {
     ht = x.ht;
     return *this; 
    }

    void
    swap (hash_map<Key, T, HashFunction, KeyEqual>& x){ ht.swap (x.ht); }
    //
    // accessors:
    //
    key_equal            key_comp   () const { return ht.key_comp ();   }
    value_compare        value_comp () const 
    { 
        return value_compare (key_comp()); 
    }

    hash_function        hash_funct () const { return ht.hash_funct (); }

    iterator             begin      ()       { return ht.begin ();      }
    const_iterator       begin      () const { return ht.begin ();      }
    iterator             end        ()       { return ht.end ();        }
    const_iterator       end        () const { return ht.end ();        }

    bool                 empty      () const { return ht.empty ();      }
    size_type            size       () const { return ht.size ();       }
    size_type            max_size   () const { return ht.max_size ();   }

    typename allocator<T>::reference operator[] (const key_type& k) 
    {
     return (*((insert (value_type (k, T ()))).first)).second;
    }

    //
    // insert/erase
    //

    // typedef done to get around compiler bug
    typedef pair<iterator, bool> pair_iterator_bool; 

    pair_iterator_bool insert (const value_type& x) 
    {
     return ht.insert_unique (x);
    }

#ifdef MSIPL_MEMBER_TEMPLATE 

    template <class InputIterator>
    void insert (InputIterator first, InputIterator last)
    {
        ht.insert_unique (first, last);
    }
 
#else

    void insert (const_iterator first, const_iterator last)
    {
        ht.insert_unique (first, last);
    }

    void insert (const value_type* first, const value_type* last) 
    {
     ht.insert_unique (first, last);
    }

#endif

    void      erase (iterator position)         { ht.erase (position);   }
    size_type erase (const key_type& x)         { return (ht.erase (x)); }
    void      erase (iterator beg_, iterator end_)
    { ht.erase (beg_, end_); }

    void clear ()                               { erase (begin (), end ()); }
    //
    // search operations:
    //
    iterator       find (const key_type& x)       { return ht.find (x); }
    const_iterator find (const key_type& x) const { return ht.find (x); }

    size_type count (const key_type& x) const { return ht.count (x); }


    pair_iterator_iterator
    equal_range (const key_type& x)       { return ht.equal_range (x); }

    pair_citerator_citerator
    equal_range (const key_type& x) const { return ht.equal_range (x); }

    //
    // hash_map operations:
    //

    iterator lower_bound (const key_type& x) { return ht.lower_bound (x); }
    const_iterator lower_bound (const key_type& x) const
    {
        return ht.lower_bound (x);
    }
 
    iterator upper_bound (const key_type& x) { return ht.upper_bound (x); }
    const_iterator upper_bound (const key_type& x) const 
    { 
        return ht.upper_bound (x);
     }
};

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator== (const hash_map<Key, T, HashFunction, KeyEqual>& x, 
                  const hash_map<Key, T, HashFunction, KeyEqual>& y) 
{ return (x.size () == y.size () &&
             equal (x.begin (), x.end (), y.begin ())); }

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator< (const hash_map<Key, T, HashFunction, KeyEqual>& x,
                       const hash_map<Key, T, HashFunction, KeyEqual>& y)
{ return lexicographical_compare (x.begin (), x.end (), y.begin (), y.end ()); }

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator!= (const hash_map<Key, T, HashFunction, KeyEqual>& x, 
                  const hash_map<Key, T, HashFunction, KeyEqual>& y) 
{ return !(x == y); }

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator<= (const hash_map<Key, T, HashFunction, KeyEqual>& x,
                       const hash_map<Key, T, HashFunction, KeyEqual>& y)
{ return !(y < x); }

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator>= (const hash_map<Key, T, HashFunction, KeyEqual>& x, 
                  const hash_map<Key, T, HashFunction, KeyEqual>& y) 
{ return !(x < y); }

template <class Key, class T, class HashFunction, class KeyEqual>
inline bool operator> (const hash_map<Key, T, HashFunction, KeyEqual>& x,
                       const hash_map<Key, T, HashFunction, KeyEqual>& y)
{ return (y < x); }

#undef Allocator

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* #ifndef _No_Floating_Point */

#endif /* MSIPL_HASH_MAP_H */

// 970723 sm wrapped entire file in #ifndef _No_Floating_Point
// hh 971220 fixed MOD_INCLUDE
// hh 971222 added alignment wrapper
