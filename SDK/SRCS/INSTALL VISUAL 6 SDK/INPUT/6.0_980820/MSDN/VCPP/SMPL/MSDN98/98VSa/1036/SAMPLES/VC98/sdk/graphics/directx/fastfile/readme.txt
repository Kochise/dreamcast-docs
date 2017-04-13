FastFile
--------
FastFile provides a way to create a very fast way to access large numbers
of files.

You use FFCREATE.EXE to create a single flat file.   Just run FFCREATE in
the directory that contains all of the files you wish to access.   A file
will be created at the root (RESULT.FF) that is the FastFile.  (you can 
specify a filename on the command line to override the default of RESULT.FF;
if you do so, make sure that the result file is NOT generated in the
current directory).

Once you have created your FastFile, you can use the FastFile routines to
access it:

BOOL FastFileInit( LPSTR fname, int max_handles ):
Call to initialize access to a FastFile.
    fname      : name of FastFile
    max_handles: maximum number of file handles you want to have open at the
		 same time.
    returns TRUE if succeeds, FALSE otherwise

void FastFileFini( void ):
Call when you are finished accessing your FastFile

HFASTFILE FastFileOpen( LPSTR name ):
Call to open an individual file in a FastFile (read-only access is supported)
    name: name if individual file
    returns a handle, or NULL if fail
    
BOOL FastFileClose( HFASTFILE hff ):
Call to close an individual file 
    hff: handle to an individual file
    returns TRUE if succeeded, FALSE otherwise
    
BOOL FastFileRead( HFASTFILE hff, LPVOID ptr, int size )
Call to read from an individual file
    hff:  handle to an individual file
    ptr:  buffer to copy data
    size: size of data to copy
    returns TRUE if succeeded, FALSE otherwise
    
BOOL FastFileSeek( HFASTFILE hff, int off, int type )
Call to seek to an offset in an individual file
    hff:  handle to an individual file
    off:  offset to seek to
    type: seek type: SEEK_SET (from start), SEEK_CUR (from current pos),
    	  or SEEK_END (from end)
    returns TRUE if succeeded, FALSE otherwise
    
long FastFileTell( HFASTFILE hff )
Call to get the current position in an individual file
    hff:  handle to an individual file
    returns current position if succeeded, -1 otherwise
