/*  Metrowerks Standard Library  Version 2.4  1998 March 10  */

/*  $Date: 1999/03/02 17:35:11 $ 
 *  $Revision: 1.8 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/**
 **  hashtbl.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_HASH_TABLE_H
#define MSIPL_HASH_TABLE_H

#ifndef _No_Floating_Point

#include <mcompile.h>

#include <cstdlib>     // hh 971220 fixed MOD_C_INCLUDE

#include <iosfwd>      // hh 971220 fixed MOD_INCLUDE
#include <iterator>    // hh 971220 fixed MOD_INCLUDE
#include <functional>  // hh 971220 fixed MOD_INCLUDE
#include <algobase.h>  // hh 971220 fixed MOD_INCLUDE
#include <vector>      // hh 971220 fixed MOD_INCLUDE

#ifdef MSIPL_ANSI_HEADER
#include <stdexcept>   // hh 971220 fixed MOD_INCLUDE
#else
#include <mexcept.h>   // hh 971220 fixed MOD_INCLUDE
#endif

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

MSIPL_STD_BEGIN
#define HT_TEMPLATE template <class Key, class Value, class KeyOfValue, class HashFunction, class KeyEqual, class Allocator>
#define HT_TYPE hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual, Allocator>

HT_TEMPLATE
class hash_table {

public:
    struct hash_node;
    class iterator; friend class iterator;
    class const_iterator; friend class const_iterator;
    
    typedef size_t                               size_type;
    typedef Key                                  key_type;
    typedef Value                                value_type;
    typedef HashFunction                         hash_function;
    typedef ptrdiff_t                            difference_type;
    typedef value_type&                          reference;
    typedef const value_type&                    const_reference;
    typedef value_type*                          pointer;
    typedef const value_type*                    const_pointer;
    typedef ALLOC_BIND(hash_node)                hash_node_allocator_type;
    typedef ALLOC_BIND(value_type)               value_allocator_type;
    typedef pair<iterator, bool>                 pair_iterator_bool;
    typedef pair<iterator, iterator>             pair_iterator_iterator;
    typedef pair<const_iterator, const_iterator> pair_citerator_citerator;
    typedef typename hash_node_allocator_type::pointer    link_type;
    typedef ALLOC_BIND(link_type)                         allocator_link_type;

    struct hash_node {
        value_type val;
        link_type  next;
    };

public:
    class iterator 
    : public MSIPLSTD::iterator <forward_iterator_tag, Value, difference_type,
                                 pointer, reference>
    {
        friend class const_iterator;
        friend class hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual,
                                Allocator>;
    protected:
        HT_TYPE*   ht;       // hast table to which the iterator is pointing 
        link_type  cur;      // Pointer to the current element in the bucket

    public:
        iterator (link_type ptr, const HT_TYPE* ht)
        :  ht ((HT_TYPE*)ht), cur (ptr) {}
  
        iterator () : ht (0), cur (0) { }
    
        ~iterator () {}
    
        bool operator== (const iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur == rhs.cur); }
  
        bool operator!= (const iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur != rhs.cur); }
  
        bool operator== (const const_iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur == rhs.cur); }
  
        bool operator!= (const const_iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur != rhs.cur); }
  
        reference operator* () { READ_LOCK(ht->_mutex); return cur->val; }

        pointer operator-> () { READ_LOCK(ht->_mutex); return &(operator* ()); }

        iterator& operator++ () 
        {
            WRITE_LOCK(ht->_mutex);
            link_type old = cur;
            cur = cur->next;
            if (!cur) {
                size_type bucket = ht->bkt_num (old->val);
                while (!cur && ++bucket < ht->buckets.size ())
                    cur = ht->buckets[bucket];
            }
            return *this;
        }
    
        iterator operator++ (int) 
        {
            iterator tmp = *this;
            ++*this;
            return tmp;
        }
    };   // end class iterator
  
    class const_iterator
    : public MSIPLSTD::iterator <forward_iterator_tag, Value, difference_type,
                                 pointer, reference>
    {
        friend class hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual,
                                Allocator>::iterator;  // hh 980109 added qualified name
        friend class hash_table<Key, Value, KeyOfValue, HashFunction, KeyEqual,
                                Allocator>;
    protected:
        HT_TYPE*  ht;        // hast table to which the iterator is pointing
        link_type  cur;      // Pointer to the current element in the bucket

    public:
        const_iterator (link_type ptr, const HT_TYPE*  ht)
        :  ht ((HT_TYPE*)ht), cur (ptr) { }

        const_iterator () : ht (0),  cur (0) { }

        const_iterator (const hash_table<Key, Value, KeyOfValue, HashFunction, // hh 980109 added qualified name
        	KeyEqual, Allocator>::iterator& x) : ht (x.ht), cur (x.cur) { }

        ~const_iterator () {}

        bool operator== (const hash_table<Key, Value, KeyOfValue, HashFunction, // hh 980109 added qualified name
        	KeyEqual, Allocator>::iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur == rhs.cur); }

        bool operator!= (const hash_table<Key, Value, KeyOfValue, HashFunction, // hh 980109 added qualified name
        	KeyEqual, Allocator>::iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur != rhs.cur); }

        bool operator== (const const_iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur == rhs.cur); }

        bool operator!= (const const_iterator& rhs) const
        { READ_LOCK(ht->_mutex); return (cur != rhs.cur); }

        const_reference operator* () 
        { 
             READ_LOCK(ht->_mutex); 
             return cur->val; 
        }

        const_pointer operator-> () 
        { 
             READ_LOCK(ht->_mutex); 
             return &(operator* ()); 
        }

        const_iterator& operator++ ()
        {
            WRITE_LOCK(ht->_mutex);
            link_type old = cur;
            cur = cur->next;
            if (!cur) {
                size_type bucket = ht->bkt_num(old->val);
                while (!cur && ++bucket < ht->buckets.size())
                    cur = ht->buckets[bucket];
            }
            return *this;
        }

        const_iterator operator++ (int)
        {
            const_iterator tmp = *this;
            ++*this;
            return tmp;
        }
    };   // end class const_iterator

private:
    
#define _MN_(size) if (n < size) return size;
    inline unsigned long __stl_next_prime(unsigned long n) const
   {
        _MN_(53)  _MN_(97)  _MN_(193)  _MN_(389)  _MN_(769)  _MN_(1543) 
        _MN_(3079)  _MN_(6151)  _MN_(12289)  _MN_(24593)  _MN_(49157) 
        _MN_(98317)  _MN_(196613)  _MN_(393241)  _MN_(786433)  
        _MN_(1572869)  _MN_(3145739)  _MN_(6291469)  _MN_(12582917)  
        _MN_(25165843)  _MN_(50331653)  _MN_(100663319)  
        _MN_(201326611)  _MN_(402653189) 
        _MN_(805306457)  _MN_(1610612741)  _MN_(3221225473)  
        return 4294967291;
   }
#undef _MN_
    
     void copy_from (const HT_TYPE& ht)
     {
          WRITE_LOCK(_mutex);
          buckets.reserve (ht.buckets.size ());
          buckets.insert (buckets.end (), ht.buckets.size (), NULL);
          MSIPL_TRY
          {
               for (size_type i = 0; i < ht.buckets.size (); ++i) {
                    if (link_type cur = ht.buckets[i]) {
                         link_type copy = new_node (cur->val);
                         buckets[i] = copy;

                         for (link_type next = cur->next; next; cur = next, next = cur->next) {
                              copy->next = new_node (next->val);
                              copy = copy->next;
                         }
                         copy->next = NULL;
                    }
               }
               num_elements = ht.num_elements;
          }
		#ifdef MSIPL_EXCEPT // hh 980902 added
          MSIPL_CATCH
          {
               clear (true);
               throw;
          } 
		#endif
     }

    void erase_bucket (const size_type n, link_type first, link_type last)
    {
        WRITE_LOCK (_mutex);
        link_type cur = buckets[n];
        if (cur == first)
            erase_bucket (n, last);
        else {
            link_type next;
            for (next = cur->next; next != first; cur = next, next = cur->next)
                ;
            while (next) {
                cur->next = next->next;
                put_node (next);
                next = cur->next;
                --num_elements;
            }
        }
    }

    void erase_bucket (const size_type n, link_type last)
    {
        WRITE_LOCK(_mutex);
        link_type cur = buckets[n];
        while (cur != last) {
            link_type next = cur->next;
            put_node (cur);
            cur = next;
            buckets[n] = cur;
            --num_elements;
        }
    }

    link_type get_node ()
    {
       WRITE_LOCK(_mutex);
       link_type tmp = free_list;
       if (tmp)
           free_list = free_list->next;  // hh 990225
       else
           tmp = hash_node_allocator.allocate (1);
       return tmp;
    }

    link_type new_node (const value_type& obj)
    {
        link_type n = get_node ();
        MSIPL_TRY 
        {
            value_allocator.construct (&(n->val), obj);
        }
		#ifdef MSIPL_EXCEPT // hh 980902 added
        MSIPL_CATCH
        {
            hash_node_allocator.deallocate (n, 1);
            throw;
        }
		#endif
        return n;
    }

    void delete_node (link_type n)
    {
        value_allocator.destroy (&(n->val));
        hash_node_allocator.deallocate (n, 1);
    }

    void put_node(link_type n)
    {
        if (n)
        {
            value_allocator.destroy (&(n->val));
            n->next = free_list;
            free_list = n;
        }
    }

    void clear (bool delete_it = false)
    {
        for (size_type i = 0; i < buckets.size (); ++i) {
            link_type cur = buckets[i];
            while (cur != 0) {
                link_type next = cur->next;
                if (delete_it)
                    delete_node (cur);
                else
                    put_node (cur);
                cur = next;
            }
            buckets[i] = 0;
        }
        if (delete_it) {
            link_type tmp;
            while(free_list) { 
                tmp = free_list; 
                free_list = free_list->next;
                hash_node_allocator.deallocate (tmp, 1);
            }
        }
        num_elements = 0;
    }

    size_type next_size(size_type n) const { return __stl_next_prime (n); }

    size_type bkt_num_key (const key_type& key) const
    {
        return bkt_num_key (key, buckets.size ());
    }

    size_type bkt_num (const value_type& obj) const
    {
        return bkt_num_key(get_key (obj));
    }

    size_type bkt_num_key(const key_type& key, size_t n) const
    {
        return hash(key) % n;
    }

    size_type bkt_num(const value_type& obj, size_t n) const
    {
        return bkt_num_key(get_key(obj), n);
    }

protected:
    HashFunction  hash;           // Actual hash function being used
    KeyEqual      equals;         // Function object used to compare keys
    size_type     num_elements;   // Keeps track of the # of elements
    KeyOfValue    get_key;
    link_type     free_list;
    hash_node_allocator_type hash_node_allocator;
    value_allocator_type value_allocator;
    vector<link_type, allocator_link_type> buckets;
    DEC_OBJ_LOCK(_mutex)

public:

    // allocation - deallocation    
    hash_table (size_type initSize,
                const HashFunction& hf = HashFunction (),
                const KeyEqual& equal  = KeyEqual (),
                const KeyOfValue& ext  = KeyOfValue())
    : num_elements (0), buckets (next_size (initSize)),  hash (hf), 
      equals (equal), get_key (ext), free_list (0)
    { }
    
    hash_table (const value_type* first,
                const value_type* last, 
                size_type initSize,
                const HashFunction& hf = HashFunction (), 
                const KeyEqual& equal  = KeyEqual (),
                const KeyOfValue& ext  = KeyOfValue())
    : num_elements (0),  hash (hf), equals (equal), 
      buckets (next_size (initSize)), get_key(ext), free_list(0)
    { insert_equal (first, last); }
    
    // copying, assignment, swap
    //
    hash_table (const HT_TYPE& ht)
    : num_elements (0), hash (ht.hash), equals (ht.equals),
      get_key (ht.get_key), free_list (0)
    { copy_from (ht); }
    
    HT_TYPE& operator= (const HT_TYPE& ht)
    {
        if (&ht != this) {
            WRITE_LOCK(_mutex);
            hash = ht.hash;
            equals = ht.equals;
            get_key = ht.get_key;
            clear();
            buckets.erase (buckets.begin (), buckets.end ());
            copy_from (ht);
        }
        return *this;
    }

    
    void swap (HT_TYPE& ht)
    {
        if (&ht != this) {
            WRITE_LOCK(_mutex);
            {WRITE_LOCK(ht._mutex);
            MSIPLSTD::swap(hash, ht.hash);
            MSIPLSTD::swap(equals, ht.equals);
            MSIPLSTD::swap(get_key, ht.get_key);
            MSIPLSTD::swap(free_list, ht.free_list);
            MSIPLSTD::swap(num_elements, ht.num_elements);
            buckets.swap( ht.buckets );}
        }
    }

    bool operator==(const HT_TYPE& ht)
    {
        if(this != &ht)
        {
            READ_LOCK(_mutex);
            if (buckets.size() != ht.buckets.size())
                return false;
            for (size_type n = 0; n < buckets.size(); ++n) {
                link_type cur1 = buckets[n];
                link_type cur2 = ht.buckets[n];
                for ( ; cur1 && cur2 && cur1->val == cur2->val;
                        cur1 = cur1->next, cur2 = cur2->next)
                {}
                if (cur1 || cur2)
                    return false;
            }
        }
        return true;
    }

    bool operator!=(const HT_TYPE& ht)
    {
         return !(*this == ht); 
    }

    ~hash_table()               
    { 
        clear (true);            // delete nodes aswell.
    }

    size_type size ()     const 
    { 
        READ_LOCK (_mutex); 
        return  (num_elements); 
    }

    size_type max_size () const 
    { 
        return size_type(-1);   
    }

    bool      empty ()    const 
    { 
        READ_LOCK (_mutex); 
        return  (size () == 0); 
    }

    // accessors
    KeyEqual           key_comp ()    const 
    { 
        READ_LOCK (_mutex); 
        return equals;           
    }
    hash_function      hash_funct ()  const 
    { 
        READ_LOCK (_mutex); 
        return hash;             
    }

    size_type bucket_count() const 
    { 
        return buckets.size(); 
    }

    // iterators
    iterator begin()
    {
        READ_LOCK (_mutex); 
        for (size_type n = 0; n < buckets.size(); ++n)
            if (buckets[n])
                return iterator(buckets[n], this);
        return end();
    }

    iterator end() 
    { 
        READ_LOCK (_mutex); 
        return iterator(0, this); 
    }

    const_iterator begin() const
    {
        READ_LOCK (_mutex); 
        for (size_type n = 0; n < buckets.size(); ++n)
            if (buckets[n])
                return const_iterator(buckets[n], this);
        return end();
    }

    const_iterator end() const 
    { 
        READ_LOCK (_mutex); 
        return const_iterator(0, this); 
    }

    size_type max_bucket_count() const
    { 
        return 4294967291;
    }

    size_type elems_in_bucket(size_type bucket) const
    {
        READ_LOCK (_mutex); 
        size_type result = 0;
        for (link_type cur = buckets[bucket]; cur; cur = cur->next)
            result += 1;
        return result;
    }

    pair_iterator_bool insert_unique(const value_type& obj)
    {
        resize(num_elements + 1);
        return insert_unique_noresize(obj);
    }

    iterator insert_equal(const value_type& obj)
    {
        resize(num_elements + 1);
        return insert_equal_noresize(obj);
    }

    reference find_or_insert(const value_type& obj);

    iterator find(const key_type& key)
    {
        READ_LOCK(_mutex); 
        size_type n = bkt_num_key (key);
        link_type first;
        for ( first = buckets[n];
              first && !equals (get_key(first->val), key);
              first = first->next) {}
        return iterator (first, this);
    }
    
    const_iterator find (const key_type& key) const
    {
        READ_LOCK (_mutex); 
        size_type n = bkt_num_key (key);
        link_type first;
        for ( first = buckets[n];
              first && !equals(get_key (first->val), key);
              first = first->next) {}
        return const_iterator (first, this);
    }

    size_type count(const key_type& key) const
    {
        READ_LOCK(_mutex); 
        const size_type n = bkt_num_key (key);
        size_type result = 0;
        for (link_type cur = buckets[n]; cur; cur = cur->next)
            if (equals(get_key (cur->val), key))
                ++result;
        return result;
    }

    size_type erase(const key_type& key);
    void erase(const iterator& it);
    void erase(iterator first, iterator last);
    void erase(const const_iterator& it);
    void erase(const_iterator first, const_iterator last);

    void resize(size_type num_elements_hint);

    pair<iterator, bool> insert_unique_noresize(const value_type& obj);
    iterator insert_equal_noresize(const value_type& obj);

#ifdef MSIPL_MEMBER_TEMPLATE
    template <class InputIterator>
    void insert_unique(InputIterator f, InputIterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_unique_noresize(*f);
    }

    template <class InputIterator>
    void insert_equal(InputIterator f, InputIterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_equal_noresize(*f); 
    }
#else
    void insert_unique(const value_type* f, const value_type* l)
    {
        size_type n = l - f;
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_unique_noresize(*f);
    }

    void insert_equal(const value_type* f, const value_type* l)
    {
        size_type n = l - f;
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_equal_noresize(*f);
    }

    void insert_unique(const_iterator f, const_iterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_unique_noresize(*f);
    }

    void insert_equal(const_iterator f, const_iterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_equal_noresize(*f);
    }

    void insert_unique(iterator f, iterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_unique_noresize(*f);
    }

    void insert_equal(iterator f, iterator l)
    {
        size_type n = distance(f, l);
        resize(num_elements + n);
        for ( ; n > 0; --n, ++f)
            insert_equal_noresize(*f);
    }
#endif

    iterator lower_bound (const key_type& key)
    {
        READ_LOCK (_mutex);
        link_type first = buckets[bkt_num_key(key)];
        for (; first; first = first->next)
            if (equals(get_key(first->val), key)) 
                return iterator(first, this);
        return iterator(0, this);
    }

    const_iterator lower_bound (const key_type& key) const
    {
        READ_LOCK (_mutex);
        link_type first = buckets[bkt_num_key(key)];
        for (; first; first = first->next) 
            if (equals(get_key(first->val), key)) 
                return const_iterator(first, this);
        return const_iterator(0, this);
    }

    iterator upper_bound (const key_type& key)
    {
        READ_LOCK (_mutex);
        const size_type n = bkt_num_key(key);
        for (link_type first = buckets[n]; first; first = first->next) {
            if (equals(get_key(first->val), key)) {
                for (link_type cur = first->next; cur; cur = cur->next)
                    if (!equals(get_key(cur->val), key))
                        return iterator(cur, this);
                for (size_type m = n + 1; m < buckets.size(); ++m)
                    if (buckets[m])
                        return iterator(buckets[m], this);
                return iterator(0, this);
            }
        }
        return iterator(0, this);
    }

    const_iterator upper_bound (const key_type& key) const
    {
        READ_LOCK (_mutex);
        const size_type n = bkt_num_key(key);
        for (link_type first = buckets[n]; first; first = first->next) {
            if (equals(get_key(first->val), key)) {
                for (link_type cur = first->next; cur; cur = cur->next)
                    if (!equals(get_key(cur->val), key))
                        return const_iterator(cur, this);
                for (size_type m = n + 1; m < buckets.size(); ++m)
                    if (buckets[m])
                        return const_iterator(buckets[m], this);
                return const_iterator(0, this);
            }
        }
        return const_iterator(0, this);
    }

    pair_iterator_iterator equal_range (const key_type& key)
    {
        READ_LOCK (_mutex); 
        typedef pair_iterator_iterator pii;
        const size_type n = bkt_num_key(key);
        for (link_type first = buckets[n]; first; first = first->next) {
            if (equals(get_key(first->val), key)) {
                for (link_type cur = first->next; cur; cur = cur->next)
                    if (!equals(get_key(cur->val), key))
                        return pii(iterator(first, this), iterator(cur, this));
                for (size_type m = n + 1; m < buckets.size(); ++m)
                    if (buckets[m])
                        return pii(iterator(first, this), 
                                   iterator(buckets[m], this));
                return pii(iterator(first, this), end());
            }
        }
        return pii(end(), end());
    }

    pair_citerator_citerator equal_range (const key_type& key) const
    {
        READ_LOCK (_mutex); 
        typedef pair_citerator_citerator pii;
        const size_type n = bkt_num_key(key);
        for (link_type first = buckets[n]; first; first = first->next) {
            if (equals(get_key(first->val), key)) {
                for (link_type cur = first->next; cur; cur = cur->next)
                    if (!equals(get_key(cur->val), key))
                        return pii(const_iterator(first, this), const_iterator(cur, this));
                for (size_type m = n + 1; m < buckets.size(); ++m)
                    if (buckets[m])
                        return pii(const_iterator(first, this),
                                   const_iterator(buckets[m], this));
                return pii(const_iterator(first, this), end());
            }
        }
        return pii(end(), end());
    }

};  // end class hash_table;

HT_TEMPLATE inline typename HT_TYPE::pair_iterator_bool
HT_TYPE::insert_unique_noresize(const typename HT_TYPE::value_type& obj)
{
    const size_type n = bkt_num(obj);
    link_type first = buckets[n];
    for (link_type cur = first; cur; cur = cur->next)
        if (equals(get_key(cur->val), get_key(obj)))
            return pair<iterator, bool>(iterator(cur, this), false);
    link_type tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return pair<iterator, bool>(iterator(tmp, this), true);
}

HT_TEMPLATE inline typename HT_TYPE::iterator
HT_TYPE::insert_equal_noresize(const typename HT_TYPE::value_type& obj)
{
    WRITE_LOCK (_mutex); 
    const size_type n = bkt_num(obj);
    link_type first = buckets[n];
    for (link_type cur = first; cur; cur = cur->next)
        if (equals(get_key(cur->val), get_key(obj))) {
            link_type tmp = new_node(obj);
            tmp->next = cur->next;
            cur->next = tmp;
            ++num_elements;
            return iterator(tmp, this);
        }
    link_type tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return iterator(tmp, this);
}

HT_TEMPLATE inline typename HT_TYPE::reference
HT_TYPE::find_or_insert(const typename HT_TYPE::value_type& obj)
{
    WRITE_LOCK (_mutex); 
    resize(num_elements + 1);
    size_type n = bkt_num(obj);
    link_type first = buckets[n];
    for (link_type cur = first; cur; cur = cur->next)
        if (equals(get_key(cur->val), get_key(obj)))
            return cur->val;
    link_type tmp = new_node(obj);
    tmp->next = first;
    buckets[n] = tmp;
    ++num_elements;
    return tmp->val;
}

HT_TEMPLATE inline typename HT_TYPE::size_type
HT_TYPE::erase(const typename HT_TYPE::key_type& key)
{
    WRITE_LOCK (_mutex); 
    const size_type n = bkt_num_key(key);
    link_type first = buckets[n];
    size_type erased = 0;
    if (first) {
        link_type cur = first;
        link_type next = cur->next;
        while (next) {
            if (equals(get_key(next->val), key)) {
                cur->next = next->next;
                put_node (next);
                next = cur->next;
                ++erased;
            }
            else {
            cur = next;
            next = cur->next;
            }
        }
        if (equals(get_key(first->val), key)) {
            buckets[n] = first->next;
            put_node (first);
            ++erased;
        }
    }
    num_elements -= erased;
    return erased;
}

HT_TEMPLATE inline void
HT_TYPE::erase(const typename HT_TYPE::iterator& it)
{
    WRITE_LOCK (_mutex); 
    link_type const p = it.cur;
    if (p) {
        const size_type n = bkt_num(p->val);
        link_type cur = buckets[n];
        if (cur == p) {
            buckets[n] = cur->next;
            put_node (cur);
            --num_elements;
        }
        else {
            link_type next = cur->next;
            while (next) {
                if (next == p) {
                    cur->next = next->next;

                    put_node (next);
                    --num_elements;
                    break;
                }
                else {
                cur = next;
                next = cur->next;
                }
            }
        }
    }
}

HT_TEMPLATE inline void
HT_TYPE::erase(typename HT_TYPE::iterator first, typename HT_TYPE::iterator last)
{
    WRITE_LOCK (_mutex); 
    size_type f_bucket = first.cur ? bkt_num(first.cur->val) : buckets.size();
    size_type l_bucket = last.cur ? bkt_num(last.cur->val) : buckets.size();
    if (first.cur == last.cur)
        return;
    else if (f_bucket == l_bucket)
        erase_bucket(f_bucket, first.cur, last.cur);
    else {
        erase_bucket(f_bucket, first.cur, 0);
        for (size_type n = f_bucket + 1; n < l_bucket; ++n)
            erase_bucket(n, 0);
        if (l_bucket != buckets.size())
            erase_bucket(l_bucket, last.cur);
    }
}

HT_TEMPLATE inline void
HT_TYPE::erase(typename HT_TYPE::const_iterator first, 
               typename HT_TYPE::const_iterator last)
{
    WRITE_LOCK (_mutex);
    size_type f_bucket = first.cur ? bkt_num(first.cur->val) : buckets.size();
    size_type l_bucket = last.cur ? bkt_num(last.cur->val) : buckets.size();
    if (first.cur == last.cur)
        return;
    else if (f_bucket == l_bucket)
        erase_bucket(f_bucket, first.cur, last.cur);
    else {
        erase_bucket(f_bucket, first.cur, 0);
        for (size_type n = f_bucket + 1; n < l_bucket; ++n)
            erase_bucket(n, 0);
        if (l_bucket != buckets.size())
            erase_bucket(l_bucket, last.cur);
    }
}

HT_TEMPLATE inline void
HT_TYPE::erase(const typename HT_TYPE::const_iterator& it)
{
    WRITE_LOCK (_mutex);
    link_type const p = it.cur;
    if (p) {
        const size_type n = bkt_num(p->val);
        link_type cur = buckets[n];
        if (cur == p) {
            buckets[n] = cur->next;
            put_node (cur);
            --num_elements;
        }
        else {
            link_type next = cur->next;
            while (next) {
                if (next == p) {
                    cur->next = next->next;

                    put_node (next);
                    --num_elements;
                    break;
                }
                else {
                cur = next;
                next = cur->next;
                }
            }
        }
    }
}

HT_TEMPLATE inline void
HT_TYPE::resize(size_type num_elements_hint)
{
    WRITE_LOCK (_mutex); 
    const size_type old_n = buckets.size();
    if (num_elements_hint > old_n) {
        const size_type n = next_size(num_elements_hint);
        if (n > old_n) {
            HT_TYPE tmp(n-1); // hh 980809 Put in -1.  The constructor calls next_size on the argument
            for (size_type bucket = 0; bucket < old_n; ++bucket) {
                link_type first = buckets[bucket];
                while (first) {
                    size_type new_bucket = bkt_num(first->val, n);
                    buckets[bucket] = first->next;
                    first->next = tmp.buckets[new_bucket];
                    tmp.buckets[new_bucket] = first;
                    first = buckets[bucket];

                }
            }
            buckets.clear();
            buckets.swap(tmp.buckets);
        }
    }
}

MSIPL_STD_END

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* #ifndef _No_Floating_Point */

#endif /* MSIPL_HASH_TABLE_H */

// 970723 scm  wrapped file in #ifndef _No_Floating_Point
// hh 971220 fixed MOD_INCLUDE and MOD_C_INCLUDE
// hh 971222 added alignment wrapper
// hh 980109 added qualified name to iterator in const_iterator
// hh 980809 Put in -1 in resize.  The constructor calls next_size on the argument
// hh 980902 #ifdef'd out exception code when ndef MSIPL_EXCEPT
// hh 990225 fixed bug in get_node with free_list
