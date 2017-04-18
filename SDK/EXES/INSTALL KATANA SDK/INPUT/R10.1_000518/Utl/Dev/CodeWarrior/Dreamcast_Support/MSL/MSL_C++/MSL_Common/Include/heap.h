/*  Metrowerks Standard Library  */

/*  $Date: 1999/01/23 00:25:39 $ 
 *  $Revision: 1.6 $ 
 *  $NoKeywords: $ 
 *
 *		Portions Copyright © 1995-1998 Metrowerks, Inc.
 *		All rights reserved.
 */
 
/**
 **  heap.h
 **
 **  Lib++  : The Modena C++ Standard Library,
 **           Version 2.4, October 1997
 **
 **  Copyright (c) 1995-1997 Modena Software Inc.
 **/

#ifndef MSIPL_HEAP_H
#define MSIPL_HEAP_H

#include <mcompile.h>

#pragma options align=native
#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import on
#endif

#ifdef MSIPL_USING_NAMESPACE
	namespace std {
#endif

// For implementation of class priority_queue and Heap operations

// Section 25.3.6 -- Heap operations

// hh 980611 Rewrote to achieve modest performance gains

//	Low level heap helper:
//	Given heap with a hole at holeIndex (typically at the top (0)),
//	bubble down the tree until temp fits, and put temp in there.
//	temp must not be a reference in [first, first+len)
template <class RandomAccessIterator, class Distance, class Value>
void
__insert_heap_down(RandomAccessIterator first, Distance len, Distance holeIndex,
                   const Value& temp)
{
	Distance child = (holeIndex + 1) * 2;
	while (child <= len)
	{
		if (child == len || *(first + child) < *(first + child - 1))
			--child;
		if (!(temp < *(first + child)))
			break;
		*(first + holeIndex) = *(first + child);
		holeIndex = child;
		++child;
		child *= 2;
	}
	*(first + holeIndex) = temp;
}

template <class RandomAccessIterator, class Distance, class Value, class Compare>
void
__insert_heap_down(RandomAccessIterator first, Distance len, Distance holeIndex,
                   const Value& temp, Compare comp)
{
	Distance child = (holeIndex + 1) * 2;
	while (child <= len)
	{
		if (child == len || comp(*(first + child), *(first + child - 1)))
			--child;
		if (!comp(temp, *(first + child)))
			break;
		*(first + holeIndex) = *(first + child);
		holeIndex = child;
		++child;
		child *= 2;
	}
	*(first + holeIndex) = temp;
}

//	Exchange *first and *exchange, and then bubble the new item
//	in the heap down to where it fits.
template <class RandomAccessIterator1, class RandomAccessIterator2>
void
__replace_heap(RandomAccessIterator1 first, RandomAccessIterator1 last,
               RandomAccessIterator2 exchange)
{
	typedef typename iterator_traits<RandomAccessIterator1>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator1>::value_type Value;
	Distance len = last - first;
	if (len < 1)
		return;
	else if (len == 1)
	{
		iter_swap(first, exchange);
		return;
	}
	Value temp(*exchange);
	*exchange = *first;
	__insert_heap_down(first, len, Distance(0), temp);
}

template <class RandomAccessIterator1, class RandomAccessIterator2, class Compare>
void
__replace_heap(RandomAccessIterator1 first, RandomAccessIterator1 last,
               RandomAccessIterator2 exchange, Compare comp)
{
	typedef typename iterator_traits<RandomAccessIterator1>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator1>::value_type Value;
	Distance len = last - first;
	if (len < 1)
		return;
	else if (len == 1)
	{
		iter_swap(first, exchange);
		return;
	}
	Value temp(*exchange);
	*exchange = *first;
	__insert_heap_down(first, len, Distance(0), temp, comp);
}

//	Like __replace_heap, but *first is discarded.
template <class RandomAccessIterator, class T>
void
__replace_heap_copy(RandomAccessIterator first, RandomAccessIterator last,
               const T& temp)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 1)
		return;
	else if (len == 1)
	{
		*first = temp;
		return;
	}
	__insert_heap_down(first, len, Distance(0), temp);
}

template <class RandomAccessIterator, class T, class Compare>
void
__replace_heap_copy(RandomAccessIterator first, RandomAccessIterator last,
               const T& temp, Compare comp)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 1)
		return;
	else if (len == 1)
	{
		*first = temp;
		return;
	}
	__insert_heap_down(first, len, Distance(0), temp, comp);
}

// Section 25.3.6.1 -- push_heap

template <class RandomAccessIterator>
void
push_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance holeIndex = last - first;
	if (holeIndex < 2)
		return;
	--holeIndex;
	Distance parent = (holeIndex - 1) / 2;
	if (*(first + parent) < *(first + holeIndex))
	{
		Value temp(*(first + holeIndex));
		do
		{
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			--parent;
			parent /= 2;
		} while (holeIndex > 0 && *(first + parent) < temp);
		*(first + holeIndex) = temp;
	}
}

template <class RandomAccessIterator, class Compare>
void
push_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance holeIndex = last - first;
	if (holeIndex < 2)
		return;
	--holeIndex;
	Distance parent = (holeIndex - 1) / 2;
	if (comp(*(first + parent), *(first + holeIndex)))
	{
		Value temp(*(first + holeIndex));
		do
		{
			*(first + holeIndex) = *(first + parent);
			holeIndex = parent;
			--parent;
			parent /= 2;
		} while (holeIndex > 0 && comp(*(first + parent), temp));
		*(first + holeIndex) = temp;
	}
}

// Section 25.3.6.2 -- pop_heap

template <class RandomAccessIterator>
void
pop_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 2)
		return;
	else if (len == 2)
	{
		iter_swap(first, last-1);
		return;
	}
	--last;
	--len;
	Value temp(*last);
	*last = *first;
	__insert_heap_down(first, len, Distance(0), temp);
}

template <class RandomAccessIterator, class Compare>
void
pop_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 2)
		return;
	else if (len == 2)
	{
		iter_swap(first, last-1);
		return;
	}
	--last;
	--len;
	Value temp(*last);
	*last = *first;
	__insert_heap_down(first, len, Distance(0), temp, comp);
}

// Section 25.3.6.3 -- make_heap

template <class RandomAccessIterator>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 2)
		return;
	Distance parent = (len - 2)/2;
	Distance child2 = (parent + 1) * 2;
	Distance child1 = child2 - 1;
	Distance max_child = child2;
	if (child2 == len || *(first + child2) < *(first + child1))
		max_child = child1;
	if (*(first + parent) < *(first + max_child))
	{
		Value temp(*(first + parent));
		*(first + parent) = *(first + max_child);
		__insert_heap_down(first, len, max_child, temp);
	}
	for (--parent; parent >= 0; --parent)
	{
		child2 -= 2;
		child1 -= 2;
		max_child = child2;
		if (*(first + child2) < *(first + child1))
			max_child = child1;
		if (*(first + parent) < *(first + max_child))
		{
			Value temp(*(first + parent));
			*(first + parent) = *(first + max_child);
			__insert_heap_down(first, len, max_child, temp);
		}
	}
}

template <class RandomAccessIterator, class Compare>
void
make_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	typedef typename iterator_traits<RandomAccessIterator>::difference_type Distance;
	typedef typename iterator_traits<RandomAccessIterator>::value_type Value;
	Distance len = last - first;
	if (len < 2)
		return;
	Distance parent = (len - 2)/2;
	Distance child2 = (parent + 1) * 2;
	Distance child1 = child2 - 1;
	Distance max_child = child2;
	if (child2 == len || comp(*(first + child2), *(first + child1)))
		max_child = child1;
	if (comp(*(first + parent), *(first + max_child)))
	{
		Value temp(*(first + parent));
		*(first + parent) = *(first + max_child);
		__insert_heap_down(first, len, max_child, temp, comp);
	}
	for (--parent; parent >= 0; --parent)
	{
		child2 -= 2;
		child1 -= 2;
		max_child = child2;
		if (comp(*(first + child2), *(first + child1)))
			max_child = child1;
		if (comp(*(first + parent), *(first + max_child)))
		{
			Value temp(*(first + parent));
			*(first + parent) = *(first + max_child);
			__insert_heap_down(first, len, max_child, temp, comp);
		}
	}
}

// Section 25.3.6.4 -- sort_heap
 
template <class RandomAccessIterator>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last)
{
	while (last - first > 1)
		pop_heap(first, last--);
}

template <class RandomAccessIterator, class Compare>
void
sort_heap(RandomAccessIterator first, RandomAccessIterator last, Compare comp)
{
	while (last - first > 1)
		pop_heap(first, last--, comp);
}

#ifdef MSIPL_USING_NAMESPACE
	} // namespace std
#endif

#if defined(__CFM68K__) && !defined(__USING_STATIC_LIBS__)
	#pragma import reset
#endif
#pragma options align=reset

#endif /* MSIPL_HEAP_H */

// hh 971222 added alignment wrapper
