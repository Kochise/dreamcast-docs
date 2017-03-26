#ifndef __RIARRAY_H
#define __RIARRAY_H

#include <string.h>	//for memcpy

//	An array class similar to std::vector.
// \note		Follows std::vector's naming convention (except resizeAndReallocate).
template <class Item> class Array
{
public:
	Array() : m_array(NULL), m_size(0), m_allocated(0) {}	//throws bad_alloc
	~Array()
	{
		delete [] m_array;
	}

	void		swap(Array& s)
	{
		Item* tarray = m_array;
		m_array = s.m_array;
		s.m_array = tarray;

		int tsize = m_size;
		m_size = s.m_size;
		s.m_size = tsize;

		int tallocated = m_allocated;
		m_allocated = s.m_allocated;
		s.m_allocated = tallocated;
	}

	//if more room is needed, reallocate, otherwise return
	void		reserve( int items )	//throws bad_alloc
	{
		assert( items >= 0 );
		if( items <= m_allocated )
			return;	//if there is room already, return

		assert( items > m_allocated );

		Item* newa = new Item[items];	//throws bad_alloc if runs out of memory
		for(int i=0;i<m_size;i++)
			newa[i] = m_array[i];
		delete [] m_array;
		m_array = newa;
		m_allocated = items;
		//doesn't change size
	}

	//reserve and change size
	void		resize( int items )	//throws bad_alloc
	{
		reserve( items );	//throws bad_alloc if runs out of memory
		m_size = items;
	}

	//resize and allocate exactly the correct amount of memory
	void		resizeAndReallocate( int items )	//throws bad_alloc
	{
		assert( items >= 0 );
		if( items == m_allocated )
		{
			m_size = items;
			return;
		}

		if( items == 0 )
		{
			delete [] m_array;
			m_size = 0;
			m_allocated = 0;
			return;
		}

		Item* newa = new Item[items];	//throws bad_alloc if runs out of memory
		int copySize = (m_size < items) ? m_size : items;	//min(m_size,items)
		for(int i=0;i<copySize;i++)
			newa[i] = m_array[i];
		RI_DELETE_ARRAY(m_array);
		m_array = newa;
		m_allocated = items;
		m_size = items;		//changes also size
	}
	void		clear()
	{
		m_size = 0;
	}
	void		push_back( const Item& item )	//throws bad_alloc
	{
		if( m_size >= m_allocated )
			reserve( (!m_allocated) ? 8 : m_allocated * 2 );	//by default, reserve 8. throws bad_alloc if runs out of memory
		m_array[m_size++] = item;
	}
	Item&		pop_back()	//throws bad_alloc
	{
		if( m_size > 0 )
			return m_array[--m_size];
		return m_array[0];
	}
	int			size() const				{ return m_size; }
	Item&		operator[](int i)			{ assert(i >= 0 && i < m_size); return m_array[i]; }
	const Item&	operator[](int i) const		{ assert(i >= 0 && i < m_size); return m_array[i]; }

private:
	Array(const Array& s);				//!< Not allowed.
	void operator=(const Array& s);		//!< Not allowed.

	Item*		m_array;
	int			m_size;
	int			m_allocated;
};

#endif /* __RIARRAY_H */
