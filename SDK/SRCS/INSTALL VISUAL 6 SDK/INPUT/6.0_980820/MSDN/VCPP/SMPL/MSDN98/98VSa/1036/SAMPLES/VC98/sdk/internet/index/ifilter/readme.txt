The IFilter interface was designed primarily to provide a uniform mechanism to extract character streams from formatted data. The goal was to provide ISVs with an interface that extracts text as the initial step in content indexing document data. IFilter can be implemented over any document format and the ISV can choose any API or interface to read the data format.  For example, a content filter can be written that reads data using the Win32 file APIs or uses the OLE storage interfaces.

Any software author who stores textual data should consider implementing a content filter for the document format to allow content indexing systems to extract text.

The sample filter in this directory will extract text and properties from HTML pages.  In addition to raw content, headings (level 1 to 6), title and anchors are emitted as pseudo-properties.  Title is also published as a full property available via IFilter::GetValue.

To compile and link the filter, i.e., htmlfilt.dll:

1) Make sure the Lib and Include environment variables for libraries and include files are set correctly.

2) Make sure the CPU environment variable is set correctly.

3) Enter the command 'nmake'.
