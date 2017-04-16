/* @doc
 *
 * @module OLECOM.D - Some OLE COM Examples |
 *
 * This module shows how to code Autoduck tags for OLE COM objects.
 * The .D extension denotes an "Autoduck-Only" file.
 *
 * Autoduck example by Eric Artzt (erica@microsoft.com)
 */

/*
@object MyObject | The @object topic describes a COM object.

@supint IMyObject | Primary interface for <o MyObject>.

@xref <i IMyObject> <om .Method1> <op .Property1>

**************************************************************

@interface IMyObject | The @interface topic describes a COM interface,
and includes descriptions of the properties and methods implemented
for the interface.

@meth HRESULT | Method1 | The @meth tag provides a summary description
of a COM interface method.

@prop ULONG | Property1 | The @prop tag provides a summary description
of a COM interface property.

***************************************************************

@method HRESULT | IMyObject | Method1 | The @method topic describes a COM
interface method.

@parm ULONG | lParam1 | A parameter description.

@rdesc Returns a result code.

@xref <i IMyObject> <op .Property1> <om IMyOtherObject.Method1>

***************************************************************

@property ULONG | IMyObject | Property1 | The @property topic
describes a COM interface property.

@xref <i IMyObject> <om .Method1> <op IMyOtherObject.Property1>

*/

