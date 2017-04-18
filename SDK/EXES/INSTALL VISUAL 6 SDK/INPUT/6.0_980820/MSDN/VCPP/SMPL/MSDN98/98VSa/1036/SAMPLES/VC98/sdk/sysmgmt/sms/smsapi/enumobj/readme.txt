    SMS API Example: object enumeration. (enumobj.exe)
    ==================================================

This sample illustrates the use of the SMS object enumeration APIs.
The objects involved here are currently Architectures and Platforms,
and their descendent objects.

The API draws a distinction between 'first-class' and 'secondary objects.
A 'first-class' object is one that can be described by SMS without any
prior knowledge. The first-class objects that are known to the system
is returned by calling SmsEnumObjectTypes. Calling this will currently
result in two object-types being returned: Architectures and Platforms.
In order to determine what Architectures exist the user then calls
SmsEnumObjects, passing "Architectures" as the types of object that we
are interested in. What is returned from this call depends on the
individual database. The set of architectures will certainly include:
        Personal Computer
        SMSEvents
        SNMP Traps      (SMS 1.2 and above)
        PackageLocation
        UserGroups
        etc.
These are all secondary objects whose type is "Architecture".

It is now possible to determine what objects each of these contain.
For instance, every object of type 'Architecture' will contain one or
more object of type 'Group', such as "MICROSOFT|IDENTIFICATION|1.0".
Note that it is impossible to determine what groups exist without first
knowing what architecture the user is interested in. Similarly, while a
Group object contains Attribute objects, it is impossible to know what
Attributes exist without knowing what group we are talking about.
This is why the SmsEnumObjects API has the notion of a predecessor list.

The data type used by the API to describe an object that it returns
is known as OBJDESCRIPTOR. Looking at the definition for this data type
(see smsapi.h) we see that there are the following fields:
        
    DWORD objType                Type of this object.

    SMSBUFF szName               Object name (eg 'Personal Computer')

    SMSBUFF szFriendlyName       Friendly name. Only used in groups
                                 where szName would be, eg,
                                 'MICROSOFT|IDENTIFICATION|1.0', the
                                 friendly name would be 'Identification'.

    BOOL bGotFriendlyName        TRUE if we have a friendly name.

    DWORD dwRelopMin             For attributes, indicates range of
    DWORD dwRelopMax             relational operators that can be used
                                 for this attribute.

    BOOL bGotRelops              TRUE if we have the relops fields set.


The 'objType' parameter is one of the set of OT_ defines (also in smsapi.h).
This tells the user what type of object is described by this OBJDESCRIPTOR.

'szName' provides the name for this object (eg 'Personal Computer', 'SMSID').

'szFriendlyName' if this is not null then it gives a user-friendly name for
the object (see above). This is only used in the case of Group objects, but
the 'bGotFriendlyName' datum will indicate whether this field is present
or not.

'dwRelopMin' and 'dwRelopMax' are used by attributes. They inform the caller
what the range of operators are for the attribute in question. 'bGotRelops'
is TRUE if these fields are present.
The values of these relational operators is from the file qrycodes.h.


Note that this example operates in a recursive manner in order to enumerate
all objects that are known to the API set.
A different use would of the APIs would be something like: given a specific
architecture and a specific group, what attributes exist. Code for this would
be something like:
        (where Architecture is Personal Computer, and Group is MICROSOFT|
         VIDEO|1.0)


    SMSBUFF aPreds[10];
    strcpy( aPreds[0], "Architectures" );
    strcpy( aPreds[1], "MICROSOFT|VIDEO|1.0 );
    strcpy( aPreds[2], "MICROSOFT|VIDEO|1.0 );

    SmsEnumObjects( hConnect,   // Handle to datasource connection.
                    pszObj,     // Attribute.
                    pPreds,     // see above.
                    ctPreds,    // 3: Architectures, PC, MS|VIDEO|1.0
                    Objects,    // filled in by API.
                    &ctObjs );  // filled in by API.

This would return, in 'Objects', all attributes for the video group.    


