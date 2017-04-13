You have to have the ODBC drivers installed on your machine for this 
sample to work.  Also, the sample abstract in the documents is wrong.
You don't edit stdafx.h with the path of msado10.dll.  Ignore items 4 
and 5 in the "To run the sample" section.  Instead, put the path to 
msado10.dll in Tools.Options.Directories.Include Files.  There is a 
#pragma message in the source that tells the programmer to do that.

The projects in this sample must be built in the following order:

1. server\adosamp.dsw
2. runado\runado.dsw


