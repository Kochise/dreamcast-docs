#include "persist.h"
#include <stdlib.h>
//----------------------------------------------------------------------
/*virtual*/ size_t persistent_file::write( const void *buffer,
												size_t size, size_t count)
{
	return fwrite( buffer, size, count, fp );
}
//----------------------------------------------------------------------
/*virtual*/ size_t persistent_file::read( void *buffer,
												size_t size, size_t count)
{
	return fread( buffer, size, count, fp );
}
//======================================================================
/*virtual*/ persistent::error persistent::serialize( persistent_store &stream,
							persistent::direction am_flushing_to_disk )
{
	// Do nothing, it's here only to allow the user to chain
	// to it in a rote sort of way.
	return success;
}
//----------------------------------------------------------------------
/*virtual*/ persistent::version_t  persistent::version( void ) const
{
	return 0;
}
//----------------------------------------------------------------------
persistent::error persistent::flush( persistent_store &stream ) const
{
	char  buf[ name_size ];
	version_t ver = version();

	memset( buf, 0, name_size );
	strncpy( buf, typeid(*this).name(), sizeof(buf)		);

	if(	stream.write( buf, name_size, 1 ) != 1	)
		return file_error;

	if( stream.write( &ver, sizeof(ver), 1 ) != 1	)
		return file_error;

	// the  ((persistent *)this)-> is necessary because the
	// serialize function cannot be const because we want load()
	// to call it. Nonetheless, we want the flush()	function to be const.
	// because it doesn't modify the flushed object.

	if( ((persistent *)this)->serialize( stream, flushing ) != success)
		return serialize_error;
	
	return success;
}
//----------------------------------------------------------------------
/*static*/ persistent *persistent::load( persistent_store &stream,
										 error *err )
{
	// Loads a persistent object from the disk without having to know the
	// objects actual class. Returns false (which has the value
	// persistant::success) on success and loads *obj_ptr with a
	// pointer to the newly-created object (which can be destroyed
	// by passing it to delete). *obj_ptr is not modified if an
	// error is returned.

	char cls_name[name_size], *p = cls_name;
	persistent *the_object = NULL;
	version_t version_number;

	*err = internal_error;

	if( stream.read( cls_name, name_size, 1 ) != 1 )
		*err == file_error;
	
	else if( *cls_name == '\0' )
		*err = file_corrupt;
	
	else if( !(the_object = (persistent *) dynamic::create( cls_name )) )
		*err = cannot_create_dynamically;

	else if( stream.read(&version_number, sizeof(version_number), 1) != 1 )
		*err = file_error;

	else if(version_number != the_object->version())
		*err = bad_version;

	else if( the_object->serialize( stream, loading ) != success )
		*err = serialize_error;
	else
		*err = success;


	if( *err != success && the_object )
	{
		delete the_object;
		the_object = NULL;
	}
	return the_object;
}
