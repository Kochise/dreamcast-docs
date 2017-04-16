#ifndef MFC_PERSIST_H__
#define MFC_PERSIST_H__

#include "persist.h"
#include <afxwin.h>         // MFC core and standard components

class persistent_CFile: public persistent_store
{
	CFile *fp;
public:
	persistent_CFile( CFile *stream ) : fp(stream)			{}
	persistent_CFile( CArchive &ar  ) : fp(ar.GetFile())	{}

	virtual size_t write( const void *buffer, size_t size, size_t count);
	virtual size_t read ( void		 *buffer, size_t size, size_t count);
};

#endif // MFC_PERSIST_H__
  
