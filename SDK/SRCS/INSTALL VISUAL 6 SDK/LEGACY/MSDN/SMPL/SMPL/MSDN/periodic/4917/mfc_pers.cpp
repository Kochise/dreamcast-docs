#include "mfc_pers.h"

/*virtual*/ size_t persistent_CFile::write( const void *buffer,
												size_t size, size_t count)
{
	// Throws a CFileException on a write error, which is unrecoverable
	// becuase there's no way to determine how many bytes were written
	// before the problem occured.

	fp->Write( buffer, size * count );
	return size * count;
}
//----------------------------------------------------------------------
/*virtual*/ size_t persistent_CFile::read( void *buffer,
												size_t size, size_t count)
{
	return fp->Read( buffer, size * count );
}
