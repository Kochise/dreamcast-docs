#ifndef PERSIST_H__
#define PERSIST_H__

#include "dynamic.h"

//----------------------------------------------------------------------
// Support for persistance. For any given persistant type, a factory<t>
// must exist before the object can be loaded from the disk. The
// factory<t> can be a local variable in the function that does the
// loading, however.

class persistent_store
{
public:
	virtual ~persistent_store(){}

	virtual size_t write( const void *buffer, size_t size, size_t count)=0;
	virtual size_t read	( void		 *buffer, size_t size, size_t count)=0;
};
//----------------------------------------------------------------------
class persistent_file: public persistent_store
{
	FILE *fp;
public:
	persistent_file( FILE *stream = stdout ) : fp(stream) {}

	virtual size_t write( const void *buffer, size_t size, size_t count);
	virtual size_t read ( void		 *buffer, size_t size, size_t count);
};
//----------------------------------------------------------------------
class persistent
{
private:
	enum direction { loading = 0, flushing = 1 };
	enum           { name_size = 126	// max size of a class name
				   };
	typedef short version_t;

public:
	enum error
	{
		success = 0,
		bad_version,
		cannot_create_dynamically,
		file_error,
		file_corrupt,
		internal_error,
		serialize_error
	};

	static persistent	*load( persistent_store &stream, error *err	);
	error 				flush( persistent_store &stream	) const;

	virtual error serialize( persistent_store &stream,
												direction am_flushing	);
	virtual version_t version  ( void ) const;
};

#endif // PERSIST_H__
