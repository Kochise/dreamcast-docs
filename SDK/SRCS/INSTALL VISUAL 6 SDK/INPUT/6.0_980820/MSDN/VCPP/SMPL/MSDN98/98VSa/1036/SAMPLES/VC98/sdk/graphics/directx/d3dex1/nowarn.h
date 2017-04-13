/*
 * Shut that bloody bouzouki up!
 * Disable the benign /W4 warnings generate when including system
 * header files from .c source files.
 *
 * W4201 = nameless struct/union.
 * W4214 = nonstandard extension used : bit field types other than int
 * W4209 = nonstandard extension used : benign typedef redefinition
 * W4001 = nonstandard extension used : 'single line comment' was used
 * W4115 = named type definition in parantheses
 * W4699 = Note: Creating precomplied header
 * W4514 = Note: Creating new precomplied header
 * W4127 = conditional expression is constant
 */
#pragma warning(disable:4201)
#pragma warning(disable:4214)
#pragma warning(disable:4209)
#pragma warning(disable:4001)
#pragma warning(disable:4115)
#pragma warning(disable:4699)
#pragma warning(disable:4514)
#pragma warning(disable:4127)

