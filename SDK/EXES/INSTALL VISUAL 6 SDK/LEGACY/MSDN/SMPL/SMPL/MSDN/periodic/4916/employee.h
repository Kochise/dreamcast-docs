
#include <iostream.h>
//------------------------------------------------
class Division; // declared below
class Peon;		// declared below

class Employee : public CObject
{
	DECLARE_SERIAL( Employee );
public:
	typedef int	Id;
private:
	Id		employee_id;
public:
	enum { id_none = 0 };	// number that's not a valid id

	virtual void Serialize( CArchive &ar	 );
	virtual	void Dump	  ( CDumpContext &dc ) const;

	virtual 
	~Employee(){}
	 Employee( Id id = id_none ) : employee_id(id) {}
	//...
	int			 is_this_you	 ( Id	id				   ) const;
	virtual void set_up_pointers ( const Division &division){ASSERT(0);}
};
//------------------------------------------------
inline int Employee::is_this_you(Id id) const
{
	return employee_id == id;
}
//------------------------------------------------
class Manager : public Employee
{
	DECLARE_SERIAL( Manager );

	enum{ max_group_size = 64 };

	Peon			*group	 [ max_group_size ];
	Employee::Id	group_ids[ max_group_size ];
	int				group_size;

	virtual void set_up_pointers( const Division &division );

	virtual void Serialize( CArchive &ar	 );
	virtual	void Dump	  ( CDumpContext &dc ) const;
public:
	void i_work_for_you( Peon *peon, Employee::Id id )
	{
		group	 [group_size  ] = peon;
		group_ids[group_size++] = id;	
	}

	virtual
	~Manager( void ){}
	 Manager( Employee::Id id = Employee::id_none )
									: Employee(id)
									, group_size(0)
	{}
};
//------------------------------------------------
class Peon : public Employee
{
	DECLARE_SERIAL( Peon );

	Manager	*boss;
	virtual void Serialize( CArchive &ar	 );
	virtual	void Dump	  ( CDumpContext &dc ) const;

public:
	void you_work_for_me( Manager *b ){ boss = b; }

	virtual
	~Peon( void ){}
	 Peon( Employee::Id id	 = Employee::id_none,
		   Manager *the_boss = NULL );
};
//------------------------------------------------
inline Peon::Peon( Employee::Id id, Manager *the_boss )
						: Employee(id)
						, boss    (the_boss)
{
	if( the_boss )
		the_boss->i_work_for_you( this, id );
}
//------------------------------------------------
class Division : public CObject
{
	DECLARE_SERIAL( Division );
	enum{ Max_workers = 1024 };

	Employee *workers[ Max_workers ];	// workers in the division
	int		 size;						// number of workers in division

	virtual void Serialize( CArchive &ar	 );
	virtual void Dump	  ( CDumpContext &dc ) const;

public:
	Employee *give_me_worker_with_this_id( Employee::Id id ) const;

	Division( void ) : size(0)
	{}

	~Division( void )
	{
		while( --size >= 0 )
			delete workers[size];
	}

	void hire( Employee *emp );
};