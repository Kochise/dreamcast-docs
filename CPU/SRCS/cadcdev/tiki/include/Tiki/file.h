/*
   Tiki
        
   file.h

   Copyright (C)2003,2004,2005 Cryptic Allusion, LLC
*/

#ifndef __TIKI_FILE_H
#define __TIKI_FILE_H

#include "Tiki/refcnt.h"

namespace Tiki {

// Encapsulates an open file and auto-closes it if necessary when the
// object is destructed. We wrap stdio streams here.
class File {
public:
	File();
	File(const string & fn, const char * access);
	virtual ~File();
	
	// Open a file
	bool	open(const string & fn, const char * access);

	// Is the file valid and opened?
	bool	isValid() const;

	// Close the file.
	void	close();

	// Read from the file.
	int	read(void * out, int size);

	// Write to the file.
	int	write(const void * src, int size);

	// Read cnt 16-bit little-endian words from the file.
	bool	readle16(void * out, int cnt);
	
	// Read cnt 32-bit little-endian words from the file.
	bool	readle32(void * out, int cnt);

	// Write cnt 16-bit little-endian words to the file.
	bool	writele16(uint16 * in, int cnt);

	// Write cnt 32-bit little-endian words to the file.
	bool	writele32(uint32 * in, int cnt);

	
	// Seek in the file.
	int	seek(int where, int whence);

	// Return the current position of the file.
	int	tell();

	// Return the total size of the file, or -1 if not possible.
	int	total();

	// Return a FILE * referring to the open file, or NULL if none.
	FILE *	getFile() const;

private:
	class FileFD : public RefCnt {
	public:
		FileFD() { m_fd = NULL; }
		FileFD(FILE *f) { m_fd = f; }
		virtual ~FileFD() {
			if (m_fd)
				fclose(m_fd);
		}
		
		FILE	* m_fd;
	};

	RefPtr<FileFD>	m_fd;
};

}

#endif	// __TIKI_FILE_H

