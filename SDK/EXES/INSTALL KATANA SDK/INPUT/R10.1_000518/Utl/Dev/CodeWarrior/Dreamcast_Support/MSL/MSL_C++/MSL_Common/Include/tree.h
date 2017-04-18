/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/26 18:30:18 $ 
 *  $Revision: 1.7 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1999 Metrowerks, Inc.
 *		All rights reserved.
 */

/**
 **  tree.h
 **/

#ifndef _TREE_H
#define _TREE_H

// WARNING
//
// tree.h is a non-standard, non-portable header and container.
//
// WARNING
//
//	__tree serves as the implementation of map, multimap, set and multiset.  The
//	node insertion and removal routines are based on algorithms presented in
//	Cormen, Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990).
//	Modifications to these algorithms include:
//
//	1.	Sentinel nodes are not used.  The algorithm has been modified to have
//		Sentinel nodes modled by null pointers in the leaf nodes.  Nodes represented
//		in this fashion have a color of black, and are never explicitly referenced.
//
//	2.	Point 1 is especially important in the balancing portion of the node delete
//		routine.  Here a null node is required to know it's parent and whether it is
//		a left child or right child.  This is fixed up by storing the parent of the
//		null node (instead of the null node), and a bool representing whether it is
//		a left child or right child.
//
//	3.	The orignal node delete routine called for copying one node into another.
//		This would cause non-standard behavior, so instead pointers are fixed up
//		to achieve the same effect.
//
//	4.	The "RB-Delete" and "RB-Delete-Fixup" routines are implemented as one
//		routine here:  "balance_erase".

#include <mslconfig>
#include <memory>
#include <stdexcept>
#include <iterator>
#include <string>

#include <cassert>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifndef _MSL_NO_CPP_NAMESPACE
	namespace std {
#endif

// hh 981203 **** WARNING ****  __pointer_plus_bit is not standard.
// It is used in the implementation of __tree.  It compacts a bool
// and a pointer into the space of a pointer.  The pointer must refer
// to memory with an alignment of 2 or more bytes.
// Use of this optimization can be turned off in <mslconfig> with the
// _Inhibit_Optimize_RB_bit flag.

template <class T>
class __pointer_plus_bit
{
public:
	__pointer_plus_bit(T* ptr = 0);
	__pointer_plus_bit& operator = (const __pointer_plus_bit& x);
	__pointer_plus_bit& operator = (T* x);
	operator T* () const;
	bool bit() const;
	void bit(bool b);
	T* operator -> () const;
private:
	T* ptr_;
};

template <class T>
inline
__pointer_plus_bit<T>::__pointer_plus_bit(T* ptr)
	: ptr_(ptr)
{
}

template <class T>
inline
__pointer_plus_bit<T>&
__pointer_plus_bit<T>::operator = (const __pointer_plus_bit& x)
{
	ptr_ = (T*)(((size_t)x.ptr_ & ~1) | ((size_t)ptr_ & 1));
	return *this;
}

template <class T>
inline
__pointer_plus_bit<T>&
__pointer_plus_bit<T>::operator = (T* x)
{
	ptr_ = (T*)((size_t)x | ((size_t)ptr_ & 1));
	return *this;
}

template <class T>
inline
__pointer_plus_bit<T>::operator T* () const
{
	return (T*)((size_t)ptr_ & ~1);
}

template <class T>
inline
bool
__pointer_plus_bit<T>::bit() const
{
	return bool((size_t)ptr_ & 1);
}

template <class T>
inline
void
__pointer_plus_bit<T>::bit(bool b)
{
	if (b)
		ptr_ = (T*)((size_t)ptr_ | 1);
	else
		ptr_ = (T*)((size_t)ptr_ & ~1);
}

template <class T>
inline
T*
__pointer_plus_bit<T>::operator -> () const
{
	return (T*)((size_t)ptr_ & ~1);
}

template <bool b>
class __red_black_tree
{
protected:

	enum Color {black, red};

	struct node_base;
	
	struct anchor
	{
		node_base* left_;

		anchor(node_base* left = 0) : left_(left) {}
	};

	#ifndef _Inhibit_Optimize_RB_bit

		struct node_base
			: public anchor
		{
			node_base* right_;
			__pointer_plus_bit<node_base> parent_;

			node_base(node_base* left = 0, node_base* right = 0, node_base* parent = 0) : anchor(left), right_(right), parent_(parent) {}
			Color color() const {return Color(parent_.bit());}
			void set_color(Color c) {parent_.bit(bool(c));}
		};

	#else

		struct node_base
			: public anchor
		{
			node_base* right_;
			node_base* parent_;
			Color color_;

			node_base(node_base* left = 0, node_base* right = 0, node_base* parent = 0) : anchor(left), right_(right), parent_(parent) {}
			Color color() const {return color_;}
			void set_color(Color c) {color_ = c;}
		};

	#endif

	static node_base* leftmost(node_base* x);
	static node_base* rightmost(node_base* x);
	static void increment(const node_base*& x);
	static void decrement(const node_base*& x);
	static void balance_insert(node_base* x, node_base* root);
	static void balance_erase(node_base* z, node_base* root);
private:
	static void rotate_left(node_base* x, node_base*& root);
	static void rotate_right(node_base* x, node_base*& root);
};

template <bool b>
inline
typename __red_black_tree<b>::node_base*
__red_black_tree<b>::leftmost(node_base* x)
{
	while (x->left_ != 0)
		x = x->left_;
	return x;
}

template <bool b>
inline
typename __red_black_tree<b>::node_base*
__red_black_tree<b>::rightmost(node_base* x)
{
	while (x->right_ != 0)
		x = x->right_;
	return x;
}

template <bool b>
void
__red_black_tree<b>::increment(const node_base*& x)
{
	if (x->right_ != 0)
		x = leftmost(x->right_);
	else
	{
		while (x != x->parent_->left_)
			x = x->parent_;
		x = x->parent_;
	}
}

template <bool b>
void
__red_black_tree<b>::decrement(const node_base*& x)
{
	if (x->left_ != 0)
		x = rightmost(x->left_);
	else
	{
		while (x == x->parent_->left_)
			x = x->parent_;
		x = x->parent_;
	}
}

template <bool b>
void
__red_black_tree<b>::balance_insert(node_base* x, node_base* root)
{
	x->set_color(red);
	while (x != root && x->parent_->color() == red)
	{
		if (x->parent_ == x->parent_->parent_->left_)
		{
			node_base* y = x->parent_->parent_->right_;
			if (y != 0 && y->color() == red)
			{
				x->parent_->set_color(black);
				y->set_color(black);
				x = x->parent_->parent_;
				x->set_color(red);
			}
			else
			{
				if (x == x->parent_->right_)
				{
					x = x->parent_;
					rotate_left(x, root);
				}
				x->parent_->set_color(black);
				x->parent_->parent_->set_color(red);
				rotate_right(x->parent_->parent_, root);
			}
		}
		else
		{
			node_base* y = x->parent_->parent_->left_;
			if (y != 0 && y->color() == red)
			{
				x->parent_->set_color(black);
				y->set_color(black);
				x = x->parent_->parent_;
				x->set_color(red);
			}
			else
			{
				if (x == x->parent_->left_)
				{
					x = x->parent_;
					rotate_right(x, root);
				}
				x->parent_->set_color(black);
				x->parent_->parent_->set_color(red);
				rotate_left(x->parent_->parent_, root);
			}
		}
	}
	root->set_color(black);
}

template <bool b>
void
__red_black_tree<b>::balance_erase(node_base* z, node_base* root)
{
	// Remove z from tree
	node_base* y = z;
	if (z->left_ != 0 && z->right_ != 0)
		increment(y);
	node_base* x = y->left_ != 0 ? y->left_ : y->right_;
	node_base* x_parent = y->parent_;
	if (x != 0)
		x->parent_ = x_parent;
	bool x_is_left_child;
	if (y == y->parent_->left_)
	{
		y->parent_->left_ = x;
		x_is_left_child = true;
	}
	else
	{
		y->parent_->right_ = x;
		x_is_left_child = false;
	}
	bool removed_black = y->color() == black;
	if (y != z)
	{	// Replace z with y
		y->parent_ = z->parent_;
		if (z == y->parent_->left_)
			y->parent_->left_ = y;
		else
			y->parent_->right_ = y;
		y->left_ = z->left_;
		if (y->left_ != 0)
			y->left_->parent_ = y;
		else
			x_parent = y;
		y->right_ = z->right_;
		if (y->right_ != 0)
			y->right_->parent_ = y;
		else
			x_parent = y;
		y->set_color(z->color());
		if (root == z)
			root = y;
	}
	else if (x == 0 && z == root)
		removed_black = false; // removing last node, don't balance
	if (removed_black)
	{	// Balance tree
		while (x != root && (x == 0 || x->color() == black))
		{
			if (x_is_left_child)
			{
				node_base* w = x_parent->right_;
				assert(w);
				if (w->color() == red)
				{
					w->set_color(black);
					x_parent->set_color(red);
					rotate_left(x_parent, root);
					w = x_parent->right_;
				}
				if ((w->left_  == 0 || w->left_->color()  == black) &&
					(w->right_ == 0 || w->right_->color() == black))
				{
					w->set_color(red);
					x = x_parent;
					x_parent = x->parent_;
					x_is_left_child = x == x_parent->left_;
				}
				else
				{
					if (w->right_ == 0 || w->right_->color() == black)
					{
						assert(w->left_);
						w->left_->set_color(black);
						w->set_color(red);
						rotate_right(w, root);
						w = x_parent->right_;
						assert(w);
					}
					w->set_color(x_parent->color());
					x_parent->set_color(black);
					assert(w->right_);
					w->right_->set_color(black);
					rotate_left(x_parent, root);
					x = root;
				}
			}
			else
			{
				node_base* w = x_parent->left_;
				assert(w);
				if (w->color() == red)
				{
					w->set_color(black);
					x_parent->set_color(red);
					rotate_right(x_parent, root);
					w = x_parent->left_;
				}
				if ((w->left_  == 0 || w->left_->color()  == black) &&
					(w->right_ == 0 || w->right_->color() == black))
				{
					w->set_color(red);
					x = x_parent;
					x_parent = x->parent_;
					x_is_left_child = x == x_parent->left_;
				}
				else
				{
					if (w->left_ == 0 || w->left_->color() == black)
					{
						assert(w->right_);
						w->right_->set_color(black);
						w->set_color(red);
						rotate_left(w, root);
						w = x_parent->left_;
						assert(w);
					}
					w->set_color(x_parent->color());
					x_parent->set_color(black);
					assert(w->left_);
					w->left_->set_color(black);
					rotate_right(x_parent, root);
					x = root;
				}
			}
		}
		if (x != 0)
			x->set_color(black);
	}
}

template <bool b>
void
__red_black_tree<b>::rotate_left(node_base* x, node_base*& root)
{
	node_base* y = x->right_;
	if (root == x)
		root = y;
	x->right_ = y->left_;
	if (y->left_ != 0)
		y->left_->parent_ = x;
	y->parent_ = x->parent_;
	if (x == x->parent_->left_)
		x->parent_->left_ = y;
	else
		x->parent_->right_ = y;
	y->left_ = x;
	x->parent_ = y;
}

template <bool b>
void
__red_black_tree<b>::rotate_right(node_base* x, node_base*& root)
{
	node_base* y = x->left_;
	if (root == x)
		root = y;
	x->left_ = y->right_;
	if (y->right_ != 0)
		y->right_->parent_ = x;
	y->parent_ = x->parent_;
	if (x == x->parent_->left_)
		x->parent_->left_ = y;
	else
		x->parent_->right_ = y;
	y->right_ = x;
	x->parent_ = y;
}

template <class T, class Compare, class Allocator>
class __tree
	: private __red_black_tree<true>
{
public:
	//  types:
	typedef T                                     value_type;
	typedef Compare                               value_compare;
	typedef Allocator                             allocator_type;
	typedef typename Allocator::reference         reference;
	typedef typename Allocator::const_reference   const_reference;
	class                                         iterator;
	class                                         const_iterator;
	typedef typename Allocator::size_type         size_type;
	typedef typename Allocator::difference_type   difference_type;
	typedef typename Allocator::pointer           pointer;
	typedef typename Allocator::const_pointer     const_pointer;
	typedef _STD::reverse_iterator<iterator>       reverse_iterator;
	typedef _STD::reverse_iterator<const_iterator> const_reverse_iterator;

private:

	struct node
		: public node_base
	{
		value_type data_;
	};

	typedef _MSL_REBIND (node)                     node_allocator_type;

public:

	struct debug_view
	{
		debug_view* left_;
		debug_view* right_;
		debug_view* parent_;
		value_type data_;
	};

	friend class iterator;
	class iterator
		: public _STD::iterator<bidirectional_iterator_tag, value_type, difference_type, pointer, reference>
	{
	public:
		iterator() {}
		reference operator * () const {return ptr_->data_;}
		pointer operator -> () const {return &ptr_->data_;}
		iterator& operator ++ () {increment(ptr_); return *this;}
		iterator operator ++ (int) {iterator temp(*this); increment(ptr_); return temp;}
		iterator& operator -- () {decrement(ptr_); return *this;}
		iterator operator -- (int) {iterator temp(*this); decrement(ptr_); return temp;}
		bool operator ==(const iterator& rhs) const {return bool(ptr_ == rhs.ptr_);}
		bool operator !=(const iterator& rhs) const {return bool(ptr_ != rhs.ptr_);}
	private:
		node* ptr_;

		iterator(node* ptr) : ptr_(ptr) {}

		friend class __tree;
		friend class __tree::const_iterator;
	};

	friend class const_iterator;
	class const_iterator
		: public _STD::iterator<bidirectional_iterator_tag, value_type, difference_type, const_pointer, const_reference>
	{
	public:
		const_iterator() {}
		const_iterator(const __tree::iterator& i) : ptr_(i.ptr_) {}
		const_reference operator * () const {return ptr_->data_;}
		const_pointer operator -> () const {return &ptr_->data_;}
		const_iterator& operator ++ () {increment(ptr_); return *this;}
		const_iterator operator ++ (int) {const_iterator temp(*this); increment(ptr_); return temp;}
		const_iterator& operator -- () {decrement(ptr_); return *this;}
		const_iterator operator -- (int) {const_iterator temp(*this); decrement(ptr_); return temp;}
		bool operator ==(const const_iterator& rhs) const {return bool(ptr_ == rhs.ptr_);}
		bool operator !=(const const_iterator& rhs) const {return bool(ptr_ != rhs.ptr_);}
	private:
		const node* ptr_;

		const_iterator(const node* ptr) : ptr_(ptr) {}

		friend class __tree;
	};

	//  lib.set.cons construct/copy/destroy:
	explicit __tree(const Compare& comp, const Allocator& a);
	#ifndef _MSL_NO_MEMBER_TEMPLATE
		template <class InputIterator>
			__tree(InputIterator first, InputIterator last, bool multi,
				const Compare& comp, const Allocator& a)
				: alloc_(a, 0),
				  node_alloc_(node_allocator_type(a)),
				  comp_(comp)
			{
				#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
					if ((size_t)&node_alloc_.m_ & 1)
						#ifndef _MSL_NO_EXCEPTIONS
							throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
						#else
							{
								fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
								abort();
							}
						#endif	
				#endif
				front() = (node*)&node_alloc_.m_;
				#ifndef _MSL_NO_EXCEPTIONS
				try
				{
				#endif
					if (multi)
						insert_multi(first, last);
					else
						insert_one(first, last);
				#ifndef _MSL_NO_EXCEPTIONS
				}
				catch (...)
				{
					if (root() != 0)
						destroy(root());
					throw;
				}
				#endif
			}
	#else
		__tree(const_iterator first, const_iterator last, bool multi,
			const Compare& comp, const Allocator& a);
		__tree(const value_type* first, const value_type* last, bool multi,
			const Compare& comp, const Allocator& a);
	#endif
	__tree(const __tree& x);
	~__tree();
	__tree& operator = (const __tree& x);
	allocator_type get_allocator() const;

	//  iterators:
	iterator               begin();
	const_iterator         begin() const;
	iterator               end();
	const_iterator         end() const;
	reverse_iterator       rbegin();
	const_reverse_iterator rbegin() const;
	reverse_iterator       rend();
	const_reverse_iterator rend() const;

	//  capacity:
	bool          empty() const;
	size_type     size() const;
	size_type     max_size() const;

	//  modifiers:
	pair<iterator,bool> insert_one(const value_type& x);
	iterator            insert_multi(const value_type& x);
	iterator            insert_one(iterator position, const value_type& x);
	iterator            insert_multi(iterator position, const value_type& x);
	#ifndef _MSL_NO_MEMBER_TEMPLATE
		template <class InputIterator>
			void insert_one(InputIterator first, InputIterator last)
			{
				if (first == last)
					return;
				iterator p = insert_one(*first).first;
				for (++first; first != last; ++first)
					p = insert_one(p, *first);
			}

		template <class InputIterator>
			void insert_multi(InputIterator first, InputIterator last)
			{
				if (first == last)
					return;
				iterator p = insert_multi(*first);
				for (++first; first != last; ++first)
					p = insert_multi(p, *first);
			}

	#else
		void insert_one(const_iterator first, const_iterator last);
		void insert_one(const value_type* first, const value_type* last);
		void insert_multi(const_iterator first, const_iterator last);
		void insert_multi(const value_type* first, const value_type* last);
	#endif

	void      erase(iterator position);
	size_type erase_one(const value_type& x);
	size_type erase_multi(const value_type& x);
	void      erase(iterator first, iterator last);
	void swap(__tree& x);
	void clear();

	//  observers:
	value_compare value_comp() const;

	//  set operations:
	iterator       find(const value_type& x);
	const_iterator find(const value_type& x) const;
	size_type count_one(const value_type& x) const;
	size_type count_multi(const value_type& x) const;

	iterator       lower_bound(const value_type& x);
	const_iterator lower_bound(const value_type& x) const;
	iterator       upper_bound(const value_type& x);
	const_iterator upper_bound(const value_type& x) const;
	pair<iterator, iterator>             equal_range(const value_type& x);
	pair<const_iterator, const_iterator> equal_range(const value_type& x) const;
private:
	_EmptyMemberOpt<Allocator, size_type> alloc_;  // alloc_.m_ is size_
	_EmptyMemberOpt<node_allocator_type, anchor> node_alloc_;  // node_alloc_.m_ is tail pseudo node, node_alloc_.m_.left_ is root node
	_EmptyMemberOpt<Compare, node*> comp_; // comp_.m_ is pointer to first node

	node* root() const;
	node*& root();
	void destroy(node* p);
	node* copy(const node* x);
	node* front() const;
	node*& front();
	node* insert_node_at(node* p, bool leftchild, bool is_leftmost, const value_type& x);

	bool ok() const;
	int count_black(node_base* x) const;
};

// Implementation

template <class T, class Compare, class Allocator>
__tree<T, Compare, Allocator>::__tree(const Compare& comp, const Allocator& a)
	: alloc_(a, 0),
#ifndef _MSL_NO_MEMBER_TEMPLATE
	  node_alloc_(node_allocator_type(a)),
#endif
	  comp_(comp)
{
	#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
		if ((size_t)&node_alloc_.m_ & 1)
			#ifndef _MSL_NO_EXCEPTIONS
				throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
			#else
				{
					fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
					abort();
				}
			#endif	
	#endif
	front() = (node*)&node_alloc_.m_;
}

#ifdef _MSL_NO_MEMBER_TEMPLATE

	template <class T, class Compare, class Allocator>
	__tree<T, Compare, Allocator>::__tree(const_iterator first, const_iterator last,
		bool multi, const Compare& comp, const Allocator& a)
		: alloc_(a, 0),
		  comp_(comp)
	{
		#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
			if ((size_t)&node_alloc_.m_ & 1)
				#ifndef _MSL_NO_EXCEPTIONS
					throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
				#else
					{
						fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
						abort();
					}
				#endif	
		#endif
		front() = (node*)&node_alloc_.m_;
		#ifndef _MSL_NO_EXCEPTIONS
		try
		{
		#endif
			if (multi)
				insert_multi(first, last);
			else
				insert_one(first, last);
		#ifndef _MSL_NO_EXCEPTIONS
		}
		catch (...)
		{
			if (root() != 0)
				destroy(root());
			throw;
		}
		#endif
	}

	template <class T, class Compare, class Allocator>
	__tree<T, Compare, Allocator>::__tree(const value_type* first, const value_type* last,
		bool multi, const Compare& comp, const Allocator& a)
		: alloc_(a, 0),
		  comp_(comp)
	{
		#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
			if ((size_t)&node_alloc_.m_ & 1)
				#ifndef _MSL_NO_EXCEPTIONS
					throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
				#else
					{
						fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
						abort();
					}
				#endif	
		#endif
		front() = (node*)&node_alloc_.m_;
		#ifndef _MSL_NO_EXCEPTIONS
		try
		{
		#endif
			if (multi)
				insert_multi(first, last);
			else
				insert_one(first, last);
		#ifndef _MSL_NO_EXCEPTIONS
		}
		catch (...)
		{
			if (root() != 0)
				destroy(root());
			throw;
		}
		#endif
	}

#endif

template <class T, class Compare, class Allocator>
__tree<T, Compare, Allocator>::__tree(const __tree& x)
	: alloc_(x.alloc_),
	  node_alloc_(x.node_alloc_),
	  comp_(x.comp_)
{
	#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
		if ((size_t)&node_alloc_.m_ & 1)
			#ifndef _MSL_NO_EXCEPTIONS
				throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
			#else
				{
					fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
					abort();
				}
			#endif	
	#endif
	if (x.root() != 0)
	{
		root() = copy(x.root());
		root()->parent_ = (node_base*)&node_alloc_.m_;
		front() = (node*)leftmost(root());
	}
	else
		front() = (node*)&node_alloc_.m_;
}

template <class T, class Compare, class Allocator>
inline
__tree<T, Compare, Allocator>::~__tree()
{
	if (root() != 0)
		destroy(root());
}

template <class T, class Compare, class Allocator>
__tree<T, Compare, Allocator>&
__tree<T, Compare, Allocator>::operator = (const __tree& x)
{
	if (this == &x)
		return *this;
	clear();
	if (x.root() != 0)
	{
		root() = copy(x.root());
		root()->parent_ = (node_base*)&node_alloc_.m_;
	}
	alloc_.m_ = x.alloc_.m_;
	comp_ = x.comp_;
	if (root() != 0)
		front() = (node*)leftmost(root());
	else
		front() = (node*)&node_alloc_.m_;
	return *this;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::allocator_type
__tree<T, Compare, Allocator>::get_allocator() const
{
	return alloc_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::begin()
{
	return front();
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::const_iterator
__tree<T, Compare, Allocator>::begin() const
{
	return front();
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::end()
{
	return (node*)&node_alloc_.m_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::const_iterator
__tree<T, Compare, Allocator>::end() const
{
	return (const node*)&node_alloc_.m_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::reverse_iterator
__tree<T, Compare, Allocator>::rbegin()
{
	return reverse_iterator(end());
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::const_reverse_iterator
__tree<T, Compare, Allocator>::rbegin() const
{
	return const_reverse_iterator(end());
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::reverse_iterator
__tree<T, Compare, Allocator>::rend()
{
	return reverse_iterator(begin());
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::const_reverse_iterator
__tree<T, Compare, Allocator>::rend() const
{
	return const_reverse_iterator(begin());
}

template <class T, class Compare, class Allocator>
inline
bool
__tree<T, Compare, Allocator>::empty() const
{
	return alloc_.m_ == 0;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::size() const
{
	return alloc_.m_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::max_size() const
{
	return numeric_limits<size_type>::max();
}

template <class T, class Compare, class Allocator>
pair<__tree<T, Compare, Allocator>::iterator, bool>
__tree<T, Compare, Allocator>::insert_one(const value_type& x)
{
	node* prev = 0;
	node* p = (node*)&node_alloc_.m_;
	node* n = root();
	bool leftchild = true;
	bool is_leftmost = true;
	while (n != 0)
	{
		p = n;
		if (comp_(x, n->data_))
		{
			n = (node*)n->left_;
			leftchild = true;
		}
		else
		{
			prev = p;
			n = (node*)n->right_;
			leftchild = false;
			is_leftmost = false;
		}
	}
	if (prev == 0 || comp_(prev->data_, x))
	{
		n = insert_node_at(p, leftchild, is_leftmost, x);
		return pair<iterator, bool>(n, true);
	}
	return pair<iterator, bool>(prev, false);
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::insert_multi(const value_type& x)
{
	node* p = (node*)&node_alloc_.m_;
	node* n = root();
	bool leftchild = true;
	bool is_leftmost = true;
	while (n != 0)
	{
		p = n;
		if (comp_(x, n->data_))
		{
			n = (node*)n->left_;
			leftchild = true;
		}
		else
		{
			n = (node*)n->right_;
			leftchild = false;
			is_leftmost = false;
		}
	}
	return insert_node_at(p, leftchild, is_leftmost, x);
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::insert_one(iterator position, const value_type& x)
{
	if (!empty())
	{
		if (position == end())
		{
			iterator before = end();
			--before;
			if (comp_(*before, x))
				return insert_node_at(before.ptr_, false, false, x);
		}
		else if (comp_(*position, x))
		{
			iterator after = position;
			++after;
			if (after == end() || comp_(x, *after))
			{
				node* p1 = position.ptr_;
				node* p2 = after.ptr_;
				if (p1->right_ == 0)
					return insert_node_at(p1, false, false, x);
				return insert_node_at(p2, true, false, x);
			}
		}
	}
	return insert_one(x).first;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::insert_multi(iterator position, const value_type& x)
{
	if (!empty())
	{
		if (position == end())
		{
			iterator before = end();
			--before;
			if (!comp_(x, *before))
				return insert_node_at(before.ptr_, false, false, x);
		}
		else if (!comp_(x, *position))
		{
			iterator after = position;
			++after;
			if (after == end() || !comp_(*after, x))
			{
				node* p1 = position.ptr_;
				node* p2 = after.ptr_;
				if (p1->right_ == 0)
					return insert_node_at(p1, false, false, x);
				return insert_node_at(p2, true, false, x);
			}
		}
	}
	return insert_multi(x);
}

#ifdef _MSL_NO_MEMBER_TEMPLATE

	template <class T, class Compare, class Allocator>
	void
	__tree<T, Compare, Allocator>::insert_one(const_iterator first, const_iterator last)
	{
		if (first == last)
			return;
		iterator p = insert_one(*first).first;
		for (++first; first != last; ++first)
			p = insert_one(p, *first);
	}

	template <class T, class Compare, class Allocator>
	void
	__tree<T, Compare, Allocator>::insert_one(const value_type* first, const value_type* last)
	{
		if (first == last)
			return;
		iterator p = insert_one(*first).first;
		for (++first; first != last; ++first)
			p = insert_one(p, *first);
	}

	template <class T, class Compare, class Allocator>
	void
	__tree<T, Compare, Allocator>::insert_multi(const_iterator first, const_iterator last)
	{
		if (first == last)
			return;
		iterator p = insert_multi(*first);
		for (++first; first != last; ++first)
			p = insert_multi(p, *first);
	}

	template <class T, class Compare, class Allocator>
	void
	__tree<T, Compare, Allocator>::insert_multi(const value_type* first, const value_type* last)
	{
		if (first == last)
			return;
		iterator p = insert_multi(*first);
		for (++first; first != last; ++first)
			p = insert_multi(p, *first);
	}

#endif

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::node*
__tree<T, Compare, Allocator>::insert_node_at(node* p, bool leftchild, bool is_leftmost,
	const value_type& x)
{
	if (size() > max_size() - 1)
		#ifndef _MSL_NO_EXCEPTIONS
			throw length_error("tree::insert length error");
		#else
		{
			fprintf(stderr, "tree::insert length error\n");
			abort();
		}
		#endif
	node* n = node_alloc_.allocate(1);
	#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
		if ((size_t)n & 1)
		{
			node_alloc_.deallocate(n, 1);
			#ifndef _MSL_NO_EXCEPTIONS
				throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
			#else
				fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
				abort();
			#endif
		}
	#endif
	#ifndef _MSL_NO_EXCEPTIONS
	try
	{
	#endif
		alloc_.construct(&n->data_, x);
	#ifndef _MSL_NO_EXCEPTIONS
	}
	catch (...)
	{
		node_alloc_.deallocate(n, 1);
		throw;
	}
	#endif
	n->left_ = n->right_ = 0;
	n->parent_ = p;
	if (leftchild)
		p->left_ = n;
	else
		p->right_ = n;
	++alloc_.m_;
	balance_insert(n, root());
	if (is_leftmost)
		front() = n;
	return n;
}

template <class T, class Compare, class Allocator>
void
__tree<T, Compare, Allocator>::erase(iterator position)
{
	node* z = position.ptr_;
	if (position == begin())
		front() = (++position).ptr_;
	balance_erase(z, root());
	alloc_.destroy(&z->data_);
	node_alloc_.deallocate(z, 1);
	--alloc_.m_;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::erase_one(const value_type& x)
{
	iterator i = find(x);
	if (i == end())
		return 0;
	erase(i);
	return 1;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::erase_multi(const value_type& x)
{
	pair<iterator, iterator> i = equal_range(x);
	size_type result = (size_type)distance(i.first, i.second);
	erase(i.first, i.second);
	return result;
}

template <class T, class Compare, class Allocator>
inline
void
__tree<T, Compare, Allocator>::erase(iterator first, iterator last)
{
	while (first != last)
		erase(first++);
}

template <class T, class Compare, class Allocator>
void
__tree<T, Compare, Allocator>::swap(__tree& x)
{
	if (this != &x)
	{
		_STD::swap(alloc_, x.alloc_);
		_STD::swap(node_alloc_, x.node_alloc_);
		_STD::swap(comp_, x.comp_);
		if (root() != 0)
			root()->parent_ = (node*)&node_alloc_.m_;
		if (x.root() != 0)
			x.root()->parent_ = (node*)&x.node_alloc_.m_;
	}
}

template <class T, class Compare, class Allocator>
void
__tree<T, Compare, Allocator>::clear()
{
	if (root() != 0)
	{
		destroy(root());
		alloc_.m_ = 0;
		root() = 0;
		front() = (node*)&node_alloc_.m_;
	}
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::value_compare
__tree<T, Compare, Allocator>::value_comp() const
{
	return comp_;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::find(const value_type& x)
{
	node* prev = 0;
	node* i = root();
	while (i != 0)
	{
		if (comp_(x, i->data_))
			i = (node*)i->left_;
		else
		{
			prev = i;
			i = (node*)i->right_;
		}
	}
	if (prev == 0 || comp_(prev->data_, x))
		return end();
	return prev;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::const_iterator
__tree<T, Compare, Allocator>::find(const value_type& x) const
{
	const node* prev = 0;
	const node* i = root();
	while (i != 0)
	{
		if (comp_(x, i->data_))
			i = (node*)i->left_;
		else
		{
			prev = i;
			i = (node*)i->right_;
		}
	}
	if (prev == 0 || comp_(prev->data_, x))
		return end();
	return prev;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::count_one(const value_type& x) const
{
	return size_type(!(find(x) == end()));
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::size_type
__tree<T, Compare, Allocator>::count_multi(const value_type& x) const
{
	pair<const_iterator, const_iterator> i = equal_range(x);
	return (size_type)distance(i.first, i.second);
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::lower_bound(const value_type& x)
{
	node* i = root();
	node* j = (node*)&node_alloc_.m_;
	while (i != 0)
	{
		if (!comp_(i->data_, x))
		{
			j = i;
			i = (node*)i->left_;
		}
		else
			i = (node*)i->right_;
	}
	return j;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::const_iterator
__tree<T, Compare, Allocator>::lower_bound(const value_type& x) const
{
	const node* i = root();
	const node* j = (const node*)&node_alloc_.m_;
	while (i != 0)
	{
		if (!comp_(i->data_, x))
		{
			j = i;
			i = (const node*)i->left_;
		}
		else
			i = (const node*)i->right_;
	}
	return j;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::iterator
__tree<T, Compare, Allocator>::upper_bound(const value_type& x)
{
	node* i = root();
	node* j = (node*)&node_alloc_.m_;
	while (i != 0)
	{
		if (comp_(x, i->data_))
		{
			j = i;
			i = (node*)i->left_;
		}
		else
			i = (node*)i->right_;
	}
	return j;
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::const_iterator
__tree<T, Compare, Allocator>::upper_bound(const value_type& x) const
{
	const node* i = root();
	const node* j = (const node*)&node_alloc_.m_;
	while (i != 0)
	{
		if (comp_(x, i->data_))
		{
			j = i;
			i = (const node*)i->left_;
		}
		else
			i = (const node*)i->right_;
	}
	return j;
}

template <class T, class Compare, class Allocator>
inline
pair<__tree<T, Compare, Allocator>::const_iterator, __tree<T, Compare, Allocator>::const_iterator>
__tree<T, Compare, Allocator>::equal_range(const value_type& x) const
{
	return make_pair(lower_bound(x), upper_bound(x));
}

template <class T, class Compare, class Allocator>
inline
pair<__tree<T, Compare, Allocator>::iterator, __tree<T, Compare, Allocator>::iterator>
__tree<T, Compare, Allocator>::equal_range(const value_type& x)
{
	return make_pair(lower_bound(x), upper_bound(x));
}

template <class T, class Compare, class Allocator>
void
__tree<T, Compare, Allocator>::destroy(node* p)
{
	if (p->left_ != 0)
		destroy((node*)(p->left_));
	if (p->right_ != 0)
		destroy((node*)(p->right_));
	alloc_.destroy(&p->data_);
	node_alloc_.deallocate(p, 1);
}

template <class T, class Compare, class Allocator>
typename __tree<T, Compare, Allocator>::node*
__tree<T, Compare, Allocator>::copy(const node* x)
{
	node* result = node_alloc_.allocate(1);
	#if !defined(NDEBUG) && !defined(_Inhibit_Optimize_RB_bit)
		if ((size_t)result & 1)
		{
			node_alloc_.deallocate(result, 1);
			#ifndef _MSL_NO_EXCEPTIONS
				throw invalid_argument("__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment");
			#else
				fprintf(stderr, "__pointer_plus_bit optimization failed in tree. Pointer has odd byte alignment\n");
				abort();
			#endif
		}
	#endif
	result->left_ = result->right_ = 0;
	#ifndef _MSL_NO_EXCEPTIONS
	try
	{
	#endif
		if (x->left_ != 0)
		{
			result->left_ = copy((node*)(x->left_));
			result->left_->parent_ = result;
		}
		if (x->right_ != 0)
		{
			result->right_ = copy((node*)(x->right_));
			result->right_->parent_ = result;
		}
		alloc_.construct(&result->data_, x->data_);
		result->set_color(x->color());
	#ifndef _MSL_NO_EXCEPTIONS
	}
	catch (...)
	{
		if (result->left_ != 0)
			destroy((node*)(result->left_));
		if (result->right_ != 0)
			destroy((node*)(result->right_));
		node_alloc_.deallocate(result, 1);
		throw;
	}
	#endif
	return result;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::node*&
__tree<T, Compare, Allocator>::root()
{
	return (node*&)node_alloc_.m_.left_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::node*
__tree<T, Compare, Allocator>::root() const
{
	return (node*)node_alloc_.m_.left_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::node*
__tree<T, Compare, Allocator>::front() const
{
	return (node*)comp_.m_;
}

template <class T, class Compare, class Allocator>
inline
typename __tree<T, Compare, Allocator>::node*&
__tree<T, Compare, Allocator>::front()
{
	return (node*&)comp_.m_;
}

template <class T, class Compare, class Allocator>
bool
__tree<T, Compare, Allocator>::ok() const
{
	if (root() != 0)
		assert(root()->color() == black);
	if (root() != 0)
		count_black(root());
	assert(distance(begin(), end()) == size());
	return true;
}

template <class T, class Compare, class Allocator>
int
__tree<T, Compare, Allocator>::count_black(node_base* x) const
{
	int cleft;
	int cright;
	if (x->left_ == 0)
		cleft = 1;
	else
		cleft = count_black(x->left_);
	if (x->right_ == 0)
		cright = 1;
	else
		cright = count_black(x->right_);
	assert(cleft == cright);
	if (x->color() == black)
		++cleft;
	return cleft;
}

#ifndef _MSL_NO_CPP_NAMESPACE
	} // namespace std
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif // _TREE_H

// hh 971220 fixed MOD_INCLUDE
// hh 971226 added alignment wrapper
// hh 980105 changed pointer & reference to const versions in const_iterator base class
// hh 980105 Added qualified name to iterator
// hh 980111 <stdexcept> commented out.  Not needed
// hh 980902 #ifdef'd out exception code when ndef MSIPL_EXCEPT
// hh 981130 Rewrote.
