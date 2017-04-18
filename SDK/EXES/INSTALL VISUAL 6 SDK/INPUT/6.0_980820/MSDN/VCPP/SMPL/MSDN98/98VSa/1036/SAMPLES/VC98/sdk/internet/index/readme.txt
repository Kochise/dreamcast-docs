Index Server sample code
------------------------

Content Indexing is a service in Windows NT version 5.  It provides very fast
full text search over material that has been indexed (typically files or web
pages) at the expense of disk space (for storing the catalogs).  For more
information, see the "Index Server" section in the SDK documentation.

The programmatic interface to the index server is via OLEDB.  The following
samples demonstrate this interface:

  SIMPLE - create a query, submit it, and print the results.
  ADVQUERY - allow a more complex query and avoid the use of CICreateCommand().
  CATQ - GUI tool for searching the SDK; will start the index server if needed.

The index server relies on "filters" (registered implementations of the
IFilter interface) to parse different file formats.  The following sample
shows how such a filter DLL is built.

  IFILTER - implementation of the IFilter interface for HTML files.
