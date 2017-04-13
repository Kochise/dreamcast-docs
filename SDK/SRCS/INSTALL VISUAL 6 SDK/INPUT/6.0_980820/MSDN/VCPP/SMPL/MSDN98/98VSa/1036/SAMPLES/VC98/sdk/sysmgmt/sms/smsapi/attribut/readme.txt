    SMS API Example: attribute filters. (attribut.exe)
    ==================================================

This sample illustrates the use of the Attribute filter that is
applied to a site container in order to enumerate specified
properties of a machine (architecture: Personal Computer).

Applying an attribute filter in order to enumerate machines is
faster than setting group filters and then retrieving specified
machine group scalars (machine properties). This is due to the
nature of the SQL operations that have to be performed.
This filter is also useful in the respect that only the information
that is requested will be returned.

This program opens a site container, constructs and applies an
attribute filter composed of three tokens:
    a) Name scalar        (from MICROSOFT|IDENTIFICATION|1.0 group).
    b) SMSLocation scalar (from MICROSOFT|IDENTIFICATION|1.0 group).
    c) NetCardID scalar   (from MICROSOFT|IDENTIFICATION|1.0 group).

Two other filters are applied to the container:
1. Site filter: to instruct the container to retrieve the root site.
2. Architecture filter: to specify that we want machines of the
   Personal Computer architecture.

After populating the container, which will cause the container to
contain only a site folder for the root site, we open the folder
and then close the container.
Closing the container is an important step since the container
increments a use count that is held for all descendant folders. If
the container is not closed as soon as possible we will never be
able to free the resources for any descendant folder. This would
cause us to exceed virtual memory very quickly for a database of
any size.

We then enter a loop to deal with any folders contained in the
site container. Although, by definition, there can only be one
folder in the site container, this loop is an example of the
general procedure to be followed in folder enumeration involving
the SMS API set.

The function DisplayFolder does most of the work.
It is passed a handle to the folder currently under examination,
at this stage all he is aware of is that this is a handle to a
folder. No mention is made yet as to what type of folder this is.

For display purposes we retrieve the ID of the folder. We then
discovers the folder's properties; these are:
1. the folder's type, and
2. the number of scalars and sub-folders contained in this folder.

The scalars are then displayed.

For each folder we will open each of its child sub-folders, storing
the handles away in a temporary list, and then close the folder.
This is identical to what we did above for the container.


Turning our attention now to the DisplayScalars function we see
that this consists of a simple loop that repeatedly tries to
retrieve a scalar from the folder. The loop terminates when there
are no more scalars in the folder.
Careful note should be taken of the use of the SCALAR structure.
This is composed (currently - expect minor modifications here) of
six fields, two of which are pointers to memory that must be
allocated by the application.
When retrieving a scalar we set the pszName and pszValue pointers
to buffers. The pszName buffer will receive the name of the scalar,
no indication is given by the API as to what size that buffer
should be. However, a size of 256 (see SMS_DATA_BUFF_SIZE define)
is guaranteed to be sufficient.
The pszValue field is used when retrieving string data. For binary
data the pvalue field is used.
Associated with this is a length field. Prior to retrieving a
scalar, you must set the length field to the size of this buffer.
If the scalar is a string or binary, then the actual size of the
data will be returned here. If the buffer was too small then the
return code from the API will be SMS_MORE_DATA.

Once this API has been called, we execute a switch statement to
find out what the type of the scalar is. For integer and time
scalars the value will be in the dwValue member of the SCALAR
structure. The time value can be converted to a string by using
one of the standard C library routines, or a CTime object from
MFC.


