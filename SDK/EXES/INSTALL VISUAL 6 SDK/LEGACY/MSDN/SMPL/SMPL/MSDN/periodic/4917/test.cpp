
//======================================================================
// Test and demo routine
//======================================================================
#include <stdio.h>
#include <share.h>
#include <stdlib.h>
#include "persist.h"
//----------------------------------------------------------------------
// The report macro works much like an ASSERT, except that int prints
// an "okay" message if the condition is true and prints an ERROR message
// (and goes to the debugger---that's the _asm int 3) if something
// is wrong. This makes it easy to test the code: A string of okays means
// that everything's fine, but an error gets you into the debugger at the
// point of error. Note that since this is a macro, the debugger will
// be positioned at the REPORT invocation, not up here in the macro
// definition. When you're not debugging, all REPORT statments just
// disappear (or to be more accurate, they expand to empty strings).

#ifndef NDEBUG
	#define REPORT( condition, str )\
		if( condition )\
			printf("okay: " #condition "\n" );\
		else\
		{\
			printf("***ERROR*** %s\n", str);\
			_asm int 3\
		}
#else
	#define REPORT(c,s) // empty
#endif
//----------------------------------------------------------------------
// Define a base class and a few derived classes to test things.

class base
{
public:
	virtual ~base(){}
	// base(){ printf("creating %s\n", typeid(*this).name()); }
};

class derived : public base
{
public:
	virtual ~derived(){} 
	// derived(){ printf("creating %s\n", typeid(*this).name()); }
};

template <class t>
class templ
{
public:
	virtual ~templ(){}
	// templ(){ printf("creating %s\n", typeid(*this).name()); }
};
//----------------------------------------------------------------------
// Template factories must either be declared at the global level or
// allocated from new.

dynamic::factory< templ<int> > f;

void test_dynamic_creation( void )
{
	dynamic::factory< derived >		f2;
	{
		dynamic::factory< base >	f1;

		base *bp = (base *)dynamic::create( "class base" );
		
		REPORT( bp,							"Couldn't create base");
		REPORT( dynamic_cast<base*>(bp),	"base not RTTI identifiable");
		REPORT( !dynamic_cast<derived*>(bp),"base incorrectly identifed "\
											"as derived");
	}

	base *bp = (base *)dynamic::create( "class base" ); // should fail
	REPORT( !bp, "Was able to create an object when no factory exists" );

	bp = (derived *) dynamic::create("class derived");
	REPORT( bp,							"Couldn't create derived");
	REPORT( dynamic_cast<derived*>(bp), "derived not RTTI identifiable");
	REPORT( dynamic_cast<base*>(bp),	"derived not RTTI identifiable "\
										"as base");

	templ<int> *tp = (templ<int> *) dynamic::create("class templ<int>");
	REPORT( tp,								"Couldn't create templ<int>");
	REPORT( dynamic_cast< templ<int>* >(tp),"templ<int> not RTTI "\
											"identifiable");
}
//======================================================================
class persistent_base : public persistent
{
	char buf[32];

	virtual version_t version( void	) const
	{
		return 1;
	}
	
protected:
	virtual persistent::error serialize( persistent_store &stream,
												direction am_flushing )
	{
		if( am_flushing )
			stream.write( buf, sizeof(buf), 1 );
		else
			stream.read( buf, sizeof(buf), 1 );
		
		return persistent::success;
	}
public:
	persistent_base()
	{
		memset(buf, '-', sizeof(buf) );
		strcpy(buf, "Base-class obj/" );
	}
	virtual int check_ok( void )
	{
		return strcmp(buf,"Base-class obj/")==0;
	}
};
//----------------------------------------------------------------------
class persistent_derived: public persistent_base
{
	char buf[32];

	virtual persistent::error serialize(persistent_store &stream,
												direction am_flushing)
	{
		persistent::error err = persistent::success;

		if( !(err = persistent_base::serialize(stream, am_flushing)) )
		{
			if( am_flushing )
				stream.write( buf, sizeof(buf), 1 );
			else
				stream.read( buf, sizeof(buf), 1 );
		}
		return err;
	}

	virtual version_t version( void	) const
	{
		return 2;
	}
public:
	persistent_derived()
	{
		memset(buf, '=', sizeof(buf) );
		strcpy(buf, "Derived-class obj/" );
	}
	virtual int check_ok( void )
	{
		return strcmp(buf,"Derived-class obj/")==0
									? persistent_base::check_ok()
									: 0;
	}
};
//----------------------------------------------------------------------
template <class t>
class persistent_templ: public persistent
{
	t a_field;
public:
	persistent_templ(void): a_field(0xabcd) {}
	int check_ok( void ){ return a_field == 0xabcd; }

	virtual ~persistent_templ(){}
	virtual persistent::error serialize(persistent_store &stream,
												direction am_flushing)
	{
		if( am_flushing )
			stream.write( &a_field, sizeof(t), 1 );
		else
			stream.read( &a_field, sizeof(t), 1 );

		return persistent::success;
	}
};
//----------------------------------------------------------------------
dynamic::factory<persistent_derived>	 d_factory;
dynamic::factory<persistent_templ<int> > t_factory;
//----------------------------------------------------------------------
void test_persistence( void )
{
	persistent_derived		derived_obj;
	persistent_templ<int>   template_obj;

	FILE *fp = _fsopen( "test", "w", _SH_DENYNO );
	REPORT( fp, "Couldn't open test file\n" );
	
	REPORT(!derived_obj.flush(	persistent_file(fp)	), "flush derived" );
	REPORT(!template_obj.flush(	persistent_file(fp)	), "flush template" );
	fclose( fp );

	fp = _fsopen( "test", "r", _SH_DENYNO );
	REPORT( fp, "Couldn't reopen test file\n" );

	persistent::error err;
	persistent *p = persistent::load( persistent_file(fp), &err);
	REPORT( p, "Persistent load failed" );
	
	persistent_derived	*dp = dynamic_cast<persistent_derived*>(p);
	REPORT( dp, "Couldn't do dynamic cast to derived type\n");
	REPORT( dp->check_ok(), "Dynamically-loaded object corrupt\n");
	delete dp;

	p = persistent::load( persistent_file(fp), &err);
	REPORT( p, "Persistent load failed" );
	
	persistent_templ<int> *tp = dynamic_cast<persistent_templ<int>*>(p);
	REPORT( tp, "Couldn't do dynamic cast to template type\n");
	REPORT( tp->check_ok(), "Dynamically-loaded object corrupt\n");
	delete tp;
}
//----------------------------------------------------------------------
void main( void )
{
	test_dynamic_creation();
	test_persistence();

	printf("Press ENTER to terminate\n");
	getchar();

	exit( 0 );
}
