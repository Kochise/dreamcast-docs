#error You must re-compile the supplied IDL files using your MIDL compiler.

/*
    The Microsoft Smart Card system utilizes IDL files to describe its COM-based
    interfaces.  However, due to differences between MIDL compilers on the
    various platforms, it is necessary that you compile these IDL files with the
    MIDL compiler that corresponds to your development platform.

    To resolve this problem, execute the following commands in this file's
    directory:

        midl scarddat.idl
        midl scardsrv.idl
        midl scardmgr.idl
        midl sspsidl.idl

    Depending on your platform, you may have to specify the default SDK include
    directory.  For example, if you are using Microsoft Visual Studio 97 with
    the default installation options, you may have to modify the above commands
    as follows:

        midl -I "C:\Program Files\DevStudio\VC\include" scarddat.idl
        midl -I "C:\Program Files\DevStudio\VC\include" scardsrv.idl
        midl -I "C:\Program Files\DevStudio\VC\include" scardmgr.idl
        midl -I "C:\Program Files\DevStudio\VC\include" sspsidl.idl

    It is possible that you will get warnings of the form,

        warning MIDL2039 : interface does not conform to [oleautomation]
                           attribute : ...

    These warnings may be safely ignored.
*/

