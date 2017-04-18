#include "stdafx.h"
#include "Serial.h"

#include "SerialDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//------------------------------------------------
IMPLEMENT_SERIAL( Employee,	CObject,	1 );
IMPLEMENT_SERIAL( Manager,	Employee,	1 );
IMPLEMENT_SERIAL( Peon,		Employee,	1 );
IMPLEMENT_SERIAL( Division, CObject,	1 );

//------------------------------------------------
/*virtual*/ void Employee::Dump( CDumpContext &dc ) const
{
	dc << "id=" << employee_id ;
}
//------------------------------------------------
/*virtual*/ void Peon::Dump( CDumpContext &dc ) const
{
	Employee::Dump(dc);
	dc << "(Peon) works for: " ;
	boss->Employee::Dump( dc );	// just prints id
	dc << "\n";
}
//------------------------------------------------
/*virtual*/ void Manager::Dump( CDumpContext &dc ) const
{
	Employee::Dump(dc);
	dc << "(Manager) group is: " ;

	for( int i = 0; i < group_size; ++i )
	{
		group[i]->Employee::Dump( dc );
		dc << ", ";
	}
	dc << "\n";
}
//------------------------------------------------
/*virtual*/ void Division::Dump( CDumpContext &dc ) const
{
	dc << "division size = " << size << ", members:\n" ;
	for( int i = 0; i < size; ++i )
		workers[i]->Dump(dc);
		dc << "\n";
	dc << "\n";
}
//------------------------------------------------
/*virtual*/ void Employee::Serialize( CArchive &ar )
{
	if( ar.IsStoring() )
		ar << employee_id;
	else
		ar >> employee_id;
}
//------------------------------------------------
/*virtual*/ void Peon::Serialize( CArchive &ar )
{
	Employee::Serialize( ar );
	// There's nothing else to serialize at this
	// level, but if there was, you'd do it here.
}
//------------------------------------------------
/*virtual*/ void Manager::Serialize( CArchive &ar )
{
	Employee::Serialize( ar );

	int	*cur = group_ids;
	if( ar.IsStoring() )
	{
		ar << group_size;
		for( int i = group_size; --i >= 0 ;)
			ar << *cur++;
	}
	else
	{
		ar >> group_size;
		for(int i = group_size; --i >= 0 ;)
			ar >> *cur++;
	}
}
//------------------------------------------------
/*virtual*/ void Division::Serialize( CArchive &ar )
{
	Employee **cur = workers;
	int i = 0;
	if( ar.IsStoring() )
	{
		ar << size;
		for(i = size; --i >= 0 ;)
			ar << *cur++;
	}
	else
	{
		// Must load the entire division before you
		// can set up the pointers in any of the workers.

		ar >> size;
		for(i = size; --i >= 0 ;)
			ar >> *cur++;

		cur = workers;
		for(i = size; --i >= 0 ;)
			if( dynamic_cast<Manager *>(*cur) )	// If it's a manager
				(*cur++)->set_up_pointers(*this);
	}
}
//------------------------------------------------
/*virtual*/ void Manager::set_up_pointers ( const Division &division )
{	
	// When called, the id array has been initialied by
	// the group array has not. For every id, ask the division
	// for the associated employee and put a pointer to it
	// in the group array.

	int	i = group_size;
	while( --i >= 0 )
	{
		Employee *emp = division.give_me_worker_with_this_id( group_ids[i] );
		Peon *peon = dynamic_cast<Peon *>(emp);
		ASSERT( peon );

		peon->you_work_for_me( this );
		group[i] = peon;
	}
}
//------------------------------------------------
Employee *Division::give_me_worker_with_this_id( Employee::Id id ) const
{
	Employee *const *cur = workers;
	for( int i = size; --i >= 0 ;)
	{
		if( (*cur)->is_this_you( id ) )
			return *cur;
		++cur;
	}
	return NULL;
}
//------------------------------------------------
void Division::hire( Employee *emp )
{
	ASSERT( size <= Max_workers );
	workers[size++] = emp;
}
