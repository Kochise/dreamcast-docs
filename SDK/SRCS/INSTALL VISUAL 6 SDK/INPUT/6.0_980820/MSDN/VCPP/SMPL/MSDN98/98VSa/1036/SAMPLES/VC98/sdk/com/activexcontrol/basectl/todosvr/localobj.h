//=--------------------------------------------------------------------------=
// LocalObj.H
//=--------------------------------------------------------------------------=
// Copyright 1995-1997 Microsoft Corporation.  All Rights Reserved.
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF 
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A 
// PARTICULAR PURPOSE.
//=--------------------------------------------------------------------------=
//
// this file is used by automation servers to delcare things that their objects
// need other parts of the server to see.
//
#ifndef _LOCALOBJ_H_

//=--------------------------------------------------------------------------=
// these constants are used in conjunction with the g_ObjectInfo table that
// each inproc server defines.  they are used to identify a given  object
// within the server.
//
// **** ADD ALL NEW OBJECTS TO THIS LIST ****
//

#define OBJECT_TYPE_CTLTODO 0
#define OBJECT_TYPE_PPGTODOGENERAL 1

#define _LOCALOBJ_H_
#endif // _LOCALOBJ_H_
