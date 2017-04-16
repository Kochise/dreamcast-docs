#include <afx.h>
#include <stdio.h>
#include "errmsg.h"


/******************************************************/
// Error messages
/******************************************************/

ERRSPEC gaErrMsgs[] = 
{
	// File errors (reported by CFileException::m_cause)

	errNone,				"Error: No error occurred.",
	errGeneric,				"Error: An unspecified file access error occurred.",
	errFileNotFound,		"Error: The file could not be located.",
	errBadPath,				"Error: All or part of the path is invalid.",
	errTooManyOpenFiles,	"Error: The permitted number of open files was exceeded.",
	errAccessDenied,		"Error: The file could not be accessed.",
	errInvalidFile,			"Error: There was an attempt to use an invalid file handle.",
	errRemoveCurrentDir,	"Error: The current working directory cannot be removed.",
	errDirectoryFull,		"Error: There are no more directory entries.",
	errBadSeek,				"Error: There was an error trying to set the file pointer.",
	errHardIO,				"Error: There was a hardware error.",
	errSharingViolation,	"Error: The file is being used by another application.",
	errLockViolation,		"Error: There was an attempt to lock a region that was already locked.",
	errDiskFull,			"Error: The disk is full.",
	errEndOfFile,			"Error: The end of file was reached.",

    errBadFieldRef     ,    "Error: Bad field reference in format string",
    errCantAppend     ,     "Error: Cannot find end of existing RTF file to append. ",
    errCantDeduceOutput ,   "Error: Cannot deduce a default output filename; use the /O option to specify.",
    errCmdSyntaxDefine,	    "Error: Invalid /D option; use /D \"name=constant string\"",
    errCmdSyntaxExpectedFlagFollowup, "Error: Expected entry following command flag",
    errCmdSyntaxHelp,		"",
    errCmdSyntaxTab,		"Error: Expected number following /T command option.",
    errCmdSyntaxUnknownFlag,"Error: Unknown command line option.",
    errLogDuplicate,        "Error: Duplicate topic name; cannot add to log",
    errLogMismatchedQuotes ,"Error: Cannot read entry from %s (mismatched quotes).",
    errMemory   ,           "Error: Out of memory",
    errMismatchedResponseQuotes, "Error: Mismatched quotes in response file.",
    errMultilineOverflow  , "Error: Multiline source element is too large to read.",
    errNoFiles         ,    "Error: No files specified\n",
    errTagTooBig     ,      "Error: Tag is too large. Truncating to %d characters.",
    errTopicCtxTooLong ,    "Error: Context string is too long, truncating to %s.",
    errTopicNameTooLong ,   "Error: Topic name is too long, truncating to %s.",
    exprerrDocTokenTooLong,      "Error: Token in expression exceeds maximum of 64 characters.",
    exprerrExpectedExprArgument, "Error: Expected an extraction tag (alphanumeric) or parenthesized expression.",
    exprerrExpectedExprOperator, "Error: Expected operator - use & (AND) or | (OR)",
    exprerrExprMismatchedParens, "Error: Mismatched parentheses in extraction expression.",
    fmterrBadEntryCount,    "Error: Wrong number of fields in format file entry. Fields are comma-separated.",
    fmterrBadFilenameExtension,     "Error: Invalid filename extension.",
    fmterrBadFieldCount,    "Error: Invalid tag field count; must be 0-6",
    fmterrBadFieldReference, "Error: Invalid tag field reference: must be 1-6",
    fmterrBadFmtEntry,      "Error: Unknown format-file entry name.",
    fmterrBadIfExpression,  "Error: Invalid if statement.",
	fmterrBadMapFieldReference, "Error: Para-to-topic map entries should be of form \"$n\" or \"$<topicname>.n\".",
    fmterrBadSection,       "Error: Unknown format-file section name.",
    fmterrBadSrcParse,      "Error: Invalid source parsing type.",
    fmterrBadSrcType,       "Error: Unknown source type; use C for C/C++; ASM for assembly; BAS for Basic.",
    fmterrBadTagName,       "Error: Invalid tag name; use alphanumerics, max length 64.",
    fmterrBadTokenCode,     "Error: Invalid token code; use a single character or ^p or ^t.",
    fmterrDuplicateEntry,   "Error: Duplicate format file entry; must define a new tag first.",
    fmterrExpectedCloseParen, "Error: Expected to find a close parenthesis.",
    fmterrExpectedComma,    "Error: Expected to find a comma.",
    fmterrExpectedEol,      "Error: Unexpected text at the end of the entry.",
    fmterrExpectedEqual,    "Error: Expected to find an equal sign.",
    fmterrExpectedExtension, "Error: Expected to find a filename extension",
    fmterrExpectedFieldCount, "Error: Expected a tag field count, 1-6",
    fmterrExpectedFieldNum, "Error: Expected tag field reference, 1-6",
    fmterrExpectedName,     "Error: Expected tag name.",
    fmterrExpectedOpenParen, "Error: Expected to find an open parenthesis.",
    fmterrExpectedPeriod,   "Error: Expected period (.).",
	fmterrExpectedTokenName, "Error: Expected a valid token name (paragraph | tab | escape).",
    fmterrFieldReferenceRange, "Error: Field reference out of range for tag.",
    fmterrNameBadSpec,      "Error: Invalid topic name mask.",
    fmterrNameCount,        "Error: Too many tokens in topic name mask; max is 12.",
    fmterrNoTagName,        "Error: Tag names must start with a letter.",
    fmterrNoTokenDefinitions, "Error: No [tokens] entry found for the specified output type.",
    fmterrOrphanedTag,      "Error: A parent tag needs to be defined before this tag.",
    fmterrParaExpectedExFlag, "Error: Expected to find an example tag flag (0 or 1)",
    fmterrParaExpectedLevel, "Error: Expected to find a tag level number.",
    fmterrTooManyIfs,       "Error: Too many .IF statements for the tag - maximum is 6.", 
    fmterrTopicExpectedSortWeight, "Error: Expected a topic sort weight number.",
    warnBadConstantReference,   "Warning: Invalid constant reference; should use the form $(constant_name)",
    warnBadContextReference,    "Warning: Context string reference not followed by a field number.",
    warnBadDiagramReference,    "Warning: Invalid diagram reference; should use the form $[diagram:name]",
    warnBadFieldReference ,     "Warning: Format string referenced an invalid or missing field.",
    warnBadFmtEscapeSequence,   "Warning: Format string contains an invalid escape sequence (^ code).",
    warnBadIndexReference,      "Warning: Invalid index reference; should use the format $[index:tagname filters:docflag filters]",
    warnBadTopicFieldReference, "Warning: Format string references an invalid or missing topic type.",
    warnCantTransferAux,		"Warning: Can't transfer fields from paragraph tag to attached topic tag.",
    warnFileTypeUnknown ,       "Warning: Unregistered filename extension; assuming C/C++.",
    warnMissingTextTagTerminator  , "Warning: Missing terminator for type formatting",
    warnNoConstFormat,          "Warning: Can't find a matching constant format; skipping.",
    warnNoDiagramFormat,        "Warning: Can't find a matching diagram format; skipping.",
    warnNoIndexFormat,          "Warning: Can't find a matching index format; skipping.",
    warnNoParaFormat,		    "Warning: Can't find a matching paragraph tag format; skipping.",
    warnNoPendingFields ,       "Warning: Tag is missing fields, and no source data is available for extraction.",
    warnNoTextFormat,           "Warning: Can't find a matching text tag format; skipping.",
    warnNoTopicFormat,		    "Warning: Can't find a matching topic tag format; skipping.",
	warnOrphanedAuxPara,		"Warning: Found paragraph tag for auxiliary topic, but no aux topic.",
    warnSrcFieldsUnavailable ,  "Warning: Can't complete tag: can't find a source line to parse.",
	warnSrcFieldsIncomplete,    "Warning: Can't complete tag: can't find expected source element.",
	warnSrcFieldsMultiline,	    "Warning: Can't complete tag: can't parse multiline statement.",
    warnTagExclSyntax ,         "Warning: Invalid syntax specifying extraction flags in tag. Use @tag:(FLAG FLAG ...)",
    warnTagFieldUnavailable,    "Warning: Format string references local tag field, but no tag is available.",
    warnTagFieldUnavailableForDiagram,    "Warning: Diagram requires an attached topic; skipping the diagram.",
    warnTooManyFields  ,        "Warning: Tag has too many fields.",
    warnTooManyTextFields  ,    "Warning: Too many fields in text tag.",
    warnTopicFieldUnavailable,  "Warning: Format string references topic field, but no topic is available.",
    warnUnknownBuildConstant,   "Warning: Unrecognized build constant in formatting string; skipping the reference.",
    warnUnknownParaTag     ,    "Warning: Unrecognized paragraph tag; paragraph was skipped.",
    warnUnknownTopicTag    ,    "Warning: Unrecognized topic tag; topic was skipped.",
    warnWantTopicTag ,          "Warning: Topic must begin with topic tag.",
    warnWrongNumFields ,        "Warning: Wrong number of fields for tag.",
    warnWrongNumTextFields ,    "Warning: Wrong number of fields in text tag.",
    0,                          "Unknown error.",
};


//@func Print an error message

void PrintError(
	const char *szFilename,		//@parm Name of file in which error occurred
	long lLine, 				//@parm Line number (can be NO_LINE)
	int nError)					//@parm Error message
{
    int iErr;
        
    if(szFilename)
    	fprintf(stdout, "%s", szFilename);

	if(lLine != NO_LINE)
		fprintf(stdout, "(%ld)", lLine);
		
	if(szFilename)
	    fputs(": ", stdout);

    for(iErr = 0; gaErrMsgs[iErr].iTag != -1 && gaErrMsgs[iErr].iTag != nError; iErr++);
    
    ASSERT(gaErrMsgs[iErr].szText);
    
    fputs(gaErrMsgs[iErr].szText, stdout);

	fputc('\n', stdout);
}


