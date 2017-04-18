THIS TOOL IS NOT SUPPORTED BY MICROSOFT CORPORATION. IT IS PROVIDED "AS
IS" BECAUSE WE BELIEVE IT MAY BE USEFUL TO YOU. WE REGRET THAT
MICROSOFT IS UNABLE TO SUPPORT OR ASSIST YOU SHOULD YOU HAVE PROBLEMS
USING THIS TOOL.

There is no licensing fee or arrangement. You can use and copy Autoduck 
freely - if you distribute it, please distribute the entire release
directory or .ZIP file, including documentation, source code, etc.


AUTODUCK
=======

To install Autoduck, copy AUTODUCK.EXE and AUTODUCK.FMT to a directory 
referenced by your PATH environment variable. You can also copy the
CONTENTS.D file, which provides a "template" help contents page.

See AUTODUCK.HLP or AUTODUCK.DOC for documentation.

The EXAMPLE subdirectory contains a sample development project. The
makefile is only set up for Autoduck; you can use it as a template.



Autoduck Release Notes

----------------------------------------------------------------------------
Release 2.08
----------------------------------------------------------------------------
  * New parsing type "meth" to allow automatic source parsing of OLE
    method declarations via @meth paragraph tag.

----------------------------------------------------------------------------
Release 2.07
----------------------------------------------------------------------------
  * New @union tag with parsing support for C++ style union decls.

----------------------------------------------------------------------------
Release 2.04
----------------------------------------------------------------------------
Bug fix release for 2.00. One new feature:

  * @parmopt tag for parameters with values:

      @parmopt type | name | default value | description

    Includes autoparsing support, use it the same way you use @parm.

----------------------------------------------------------------------------
Release 2.0
----------------------------------------------------------------------------
Huge new release with many new features. See the help file for details.
Highlights:

  * Numerous fixes to source parser.

  * Visual Basic source parsing support for subs, functions, types.

  * Support for class enumeration and class structure definitions, via
    @menum and @mstruct topic tags. See help file topic "Nesting Topics
    Inside Topics" for details.

  * The log file is no longer required, assuming all topics referenced
    in the build are included in the build. In other words, you don't
    have to run Autoduck in two passes to generate hypertext links. See
    MAKEDOCS.MAK in the example project for the new model.

  * Topic lists (indexes/tables of contents) can now be inserted in 
    any topic and no longer need to reside in the format file. A new 
    index file, CONTENTS.D, has been added to replace the index definition 
    formerly contained in the [FILE] section of the format file. To 
    generate a table of contents topic for your help file, include
    CONTENTS.D in your build.

  * Extraction sets can now be specified using simple expressions
    including OR (|), AND (&), and parentheses.

  * Unified format-string model now; you can use the format string
    constructs anywhere in the format file.

  * New format-string codes $!c and $!n for referencing topic 
    context string and name, respectively.

  * New [TOKENS] section for defining output tokens for a given output
    type... this should break the hard-coding of RTF as an output type,
    and allow alternate formats such as HTML... if some enterprising
    individual would be interested in writing an HTML format file...

----------------------------------------------------------------------------
Release 1.11.04 
----------------------------------------------------------------------------
Bug fixes:
  * Failing to read [EXTENSIONS] section across supplemental format
    file.

  * Failing to properly read multiline class member declarations.

  * Improperly handling @doc extraction flags enclosed within a single
    line /* */ comment block.
  
  Format file:

  * Adjusted @access, @cmember tags so Class Member headings are output
    in correct order when @access is present.

New features:
  Format file:

  * Added <bmp > textw tag for inserting bitmaps inline.

----------------------------------------------------------------------------
Release 1.11 
----------------------------------------------------------------------------
New features:
  * Added [EXTENSIONS] section to FMT file to define source types of
    various filename extensions.

  * Changed directory search behavior for FMT files - if a full path or
    relative path is not specified, Autoduck searches the current
    directory, AUTODUCK.EXE directory, and search path for the specified
    format file.

  Format file:

  * Added @base paragraph tag implementation for use in COM @interface
    topics.

Bug fixes:
  * Reading past end of line when reading log entry at end of file
  * Tweaked the comment extraction code to allow single-line /* */ style
    comments.
  * Preserve indenting of example code within /* */ comment blocks.

----------------------------------------------------------------------------
Release 1.10.03 Jan. 23, 1995 
----------------------------------------------------------------------------
Bug fixes:
  * Bug in /S supplemental format file - uninitialized structure caused
    problems in DOS version.

  * Index lookup was failing when supplemental fmt file used.

  * @const tag was omitted from fmt file
  
  * Parsing problems w/@cmember parsing in operator functions.

  * Improper parsing of C++ destructor members using the @cmember tag.


----------------------------------------------------------------------------
Release 1.10    Jan. 9, 1995 
----------------------------------------------------------------------------
New features:
  * Response files now supported on command line. Input files and options
    can be specified in a file - reference the file with @FILE, e.g.
    AUTODUCK /v @files.lst

  * New support for supplemental format files. Now, you can define 
    deltas to the standard format file, rather than editing the
    AUTODUCK.FMT file each new release. There are two ways to do this:

        - Use the /S command line option to specify a supplemental 
          formatting file. Tags defined there override (or add to) 
          those in the main formatting file.

        - Sections can be repeated in the format file - for example, 
          supplemental paragraph tag definitions can be inserted at the
          front of the standard formatting file.

  * New tags:

        @CONST topic tag with parsing of C++ constant declarations.
        @GLOBALV paragraph tag for documenting global variables
        @CONSUMES paragraph tag for identifying interfaces that an
         object consumes.

Bug fixes:
  * Syntax warnings now output to STDOUT.
  * Log files can now exceed 64K in the 32-bit version only.

----------------------------------------------------------------------------
Release 1.09.07  Nov. 21w, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Removed references to MSGRIDA1.DOT in format file.
  * Fixed invalid memory reference bug.

----------------------------------------------------------------------------
Release 1.09.03  Nov. 15, 1994
----------------------------------------------------------------------------
New features:
  * New @parmvar tag for documenting variable parameter lists. See help
    for details.
  * Changed weird header text in print output - you can now customize
    the header by overriding the "doc_header" constant on the command
    line, e.g.:
    
        autoduck /d "doc_header=My Header Text" ...

Bug fixes:
  * Problems parsing assorted C++ template constructs were fixed.

----------------------------------------------------------------------------
Release 1.091   Nov. 6, 1994
----------------------------------------------------------------------------
New features:
  * Format file updates for OLE tags:

    @method:    added interface name as field
    @property:  added interface name as field
    @event:     new topic tag for OLE events
    @abstract:  new topic tag for OLE abstract objects (an object that
                defines a standard set of interfaces to support)
    <om >:      added interface name as field
    <op >:      added interface name as field
    <oe >:      new text tag for OLE events

  * C++ tags now support templates.

  * New tags for defining template arguments:

    @tcarg      template class argument
    @tfarg      template function argument

  * Cool new @cmember tag - replacement for @member - automatically
    parses C++ members from the class header. New "classmember" parsing
    type defined for .PARSESOURCE entry in format file.
    
  * The @enum tag now parses the enumeration type name from the definition
    immediately following the tag comment block. New "enum" parsing
    type for .PARSESOURCE entry in format file.
     
  * New topic-name token $<n - references the "nth" tag field and
    strips out a templae specifier if present.

  * Changed TAGEXISTS() statement (.IF) to check topic tag as well
    as paragraph tags - can now use to determine the containing
    topic type.

  * The .IF statement can now be used up to six times within a
    paragraph, text, or diagram tag definition. The multiple
    conditions have an implied OR relationship.

  * Changed format of error messages for compatibility with VC 2.0
    (you can now set up Autoduck as a tool in VC, redirect Autoduck 
    output to the output window and use F4 to move from one Autoduck 
    syntax error to the next).

Bug fixes:
  * Fixed bug in which context string for topic (.CONTEXT=) was not 
    being constructed or written to log file correctly.
  * Fixed FIELDEMPTY() bug (used in .IF=) in which statement was
    referring to topic tag fiels instead of the current tag (paragraph
    or text tag).
  * Changing parsing behavior to allow a macro to be used as a return
    value in a function.
  * Last character in example fields was being lopped off.

----------------------------------------------------------------------------
Release 1.08    Sept. 12, 1994
----------------------------------------------------------------------------
New features:
  * New conditional testing added to .IF statement in format file;
    cleans up many "empty field" warnings for C++ constructors and
    destructors.

Bug fixes:
  * Made the C++ class parsing a little smarter (but not much :-).

----------------------------------------------------------------------------
Release 1.071   July 8, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Fix problem parsing function pointer parameters.
  * Back out change to default EXISTS behavior made in 1.07.

----------------------------------------------------------------------------
Release 1.07    July 7, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Second eof test in extraction to avoid double extraction of last 
    comment line in file.
  * Correctly handle extended ASCII (8-bit) characters; convert to \'nn
    RTF code.
  * Remove restriction that text tags need to be confined to a single
    line in a comment block.
  * For better backward compatibility, log file EXISTS expressions in
    formatting file (.if=exists($1)) default to TRUE if no log file was
    specified on the command line.
  * Formatting file parser now flags tags that specify an illegal
    number of fields (max 6 fields per tag).

New features:
  * New /A command line option to append RTF and log file output
    to existing file.
  * New /D command line option defines string constants to override or
    add to constants specified in the formatting file. Used to insert
    build-specific string constants into RTF.
  * New formatting string codes to output source filename, line number,
    and build date in RTF ($!P, $!F, $!L, $!D).

Format file updates:
  * Fix to @access formatting string.
  * New @consumes tag for listing interfaces consumed by an object
  * Most topic tags now output the name of the source filename for the 
    comment block, and build date now output in contents screen for Help.
  * Contents screen includes replaceable title; to use, define a TITLE
    constant using the /D command line option, for example:
       
        autoduck /rh /d "TITLE=Autoduck User Guide" ...

----------------------------------------------------------------------------
Release 1.05     May 13, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Fix memory overwrite in log file creation.
  * Streamline extraction and output processing.
  * Tempfile usage: now creates only one temp file with unique name.
  * Allow escaped @ sign (only needed in first column position).

New features:
  * Added /N option to suppress RTF output. Useful when generating a
    log file on a first pass.

  * Can now specify a context string for topics. Context string is used
    in log file (to identify topic) and when outputting topic lists in
    Help. Use the context string to create a unique identifier for
    topics that may have the same name (e.g., OLE properties and
    methods). For more information, see Help discussion of .CONTEXT
    formatting file keyword.

  * Extraction tags can now be specified for individual paragraphs.
    See Conditional Extraction topic in the Help file for more information.

Formatting file updates:
  * Added .CONTEXT tags for OLE @property and @method tags.
  * Misc bug fixes.

----------------------------------------------------------------------------
Release 1.03     March 31, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Fix improper extraction of comment text across multiple comment
    blocks.

New features:
  * Temporary files are placed in the TEMP directory rather than the
    current directory.

  * Formatting file now allows .IF statement in paragraph tags as well
    as text tags.

  * Topic log feature added (see help file for details).

  * Command line parser now accepts flags following input filenames.

  * New /N flag that extracts but creates no output .RTF file.

Formatting file updates:
  * I have cleaned up the standard tagset defined in AUTODUCK.FMT. I
    added new tags for OLE2 COM, changed the name of a couple C tags
    for clarity (@types now @struct, @typee now @enum), and removed
    some duplicate or little-used tags. The old formatting file is
    still available as OLD.FMT. From this release forward, the
    tagset defined in AUTODUCK.FMT will be subject to change, to
    accomodate the needs of the Multimedia Document Architecture (MDA)
    group.

----------------------------------------------------------------------------
Release 1.00     February 7, 1994
----------------------------------------------------------------------------
Bug fixes:
  * Fix improper source-parsing of C++ overloaded operator member 
    functions.

  * Change source parsing behavior of C++ classes. In rel. 99, Autoduck
    parsed both a class name and base class name. This parsing did not
    handle multiple inheritance properly. In rel 1.00, class source
    parsing just grabs the class name and deposits it in the first
    field position for the tag. Base class names are no longer
    extracted.

  * Fixed PARSESOURCE=FIELD so it actually works.

  * Fix C++ member function parser to correctly parse member functions
    with class enumeration type return values e.g.:
    
        CFooBar::MyEnum CFooBar::MyFunc();

  * Fixed a bug in the .IF processing for text types.

New features:
  * Change context-string generation to be a little more discerning.
    Before, any illegal character in a topic name was converted to an 
    underscore. This causes collisions in C++: operator++, operator--
    etc. all get the same context string. The new context string
    generation follows these rules:

    - Alphanumerics, periods, and underscores are used as is.
    - Spaces and colons are converted to underscores.
    - All other characters are converted to a period, followed by the
      hexadecimal representation of the character (for example, .2b for
      a plus sign.

    For example, a topic with name "operator++" is converted to
    "operator.2b.2b".

  * New "emem" source-parsing option, for parsing identifiers for 
    enumeration members. Add the "parsesource=emem" entry to the format
    file for the "emem" tag. See the Help file for details.


----------------------------------------------------------------------------
Release 099     October 22, 1993
----------------------------------------------------------------------------
Bug fixes:
    Fix source-parsing bug manifested when a parameter declaration is
    not followed by a separator or paren on the same line.

New features:
  * Add a .PARSESOURCE=FIELD entry for parsing fields. (This was
    supported before via .PARSESRC=PARAMETER; however, this makes
    the format file a little easier to read.)

  * Formatting string references to out-of-tag fields ($tagname.1) now
    search both the topic tag and the list of paragraph tags. Returns 
    the field value for the first paragraph tag encountered.

----------------------------------------------------------------------------
Release 098     September 23, 1993
----------------------------------------------------------------------------

Bug fixes:
    Fixed HPJ outputting error in which [files] section entry
    incorrectly included the directory path.
    
New features:
  * New .PARSESOURCE= statement for formatting file enables the following
    source-parsing capabilities for topic and paragraph tags:

    - Extract data type and name information from parameters & structure
      fields
    - Extract return type and name from function header
    - Extract class name and base class name from class declaration
    - Extract return type, class name, and member function name from
      member function

    Note: The .PARSESOURCE= statement MUST be added to your formatting file
    to activate this feature. I am not updating the standard AUTODUCK.FMT
    file.

  * New .ORDER= statement for formatting file lets you specify the order
    in which paragraph tags are output within a topic

  * An .OUTPUT= statement has been added to the [CONSTANT] section of the
    formatting file. This lets you associate an output type with a
    constant, so you can have help/doc constants that share the same name.
    This is mostly useful for eliminating duplicate specification of
    paragraph tags in the formatting file.

  * Autoduck topics can now span multiple comment blocks. All Autoduck
    paragraph tags following a topic tag are appended to that topic, until
    a new topic tag is encountered in the file.
    
  * The @DOC tag no longer needs to be specified for each comment block.
    Topics use the extraction flags specified in the preceding @DOC tag (in
    the current comment block or a previous comment block). You can still
    use multiple @DOC tags within a source file (the old format is still
    supported).

  * Comment blocks no longer need to begin in the first column. They can
    begin following source text.

  * Can specify unsorted output within a group of topics by specifying
    a negative sorting value.


----------------------------------------------------------------------------
Release 097     August 12, 1992
----------------------------------------------------------------------------

Bug fixes:
    Improved "no topic tag found in block" warning message so it 
        actually says that, also changed line number to be more
        accurate.
    Fixed "constant not found" error message to reference correct tag
        name.
    Fixed paragraph tag post-text output bug.
    Fixed incorrect @doc tag parsing.
    Increased extraction buffer size & added error message to warn of
        buffer overflow.
    
Format file changes:
    Added "mf" text-formatting tag for member functions.
    Added "reg" tag for documenting registers.


----------------------------------------------------------------------------
Release 096     June 24, 1993
----------------------------------------------------------------------------

Bug fixes:
    Numerous bug fixes to formatting specification file, especially in
      C++ tags

New features:
    Add .CANCELIFPRESENT entry to format file. Allows cancellation of 
      diagram generation if a certain paragraph tag is present in topic
    Allow paragraph/text formatting strings to refer to fields in the
      topic-level tag.
    Add @memberl paragraph tag (like @member, but generates link).


----------------------------------------------------------------------------
Release 095     May 13, 1993
----------------------------------------------------------------------------

Important!  Beginning with the 0.95 release, Autoduck requires a format
    information file. A default format file, AUTODUCK.FMT, is included 
    in the release. Copy this file to a directory on your PATH.

New Features:
    Autoduck now generates output based on a format information file.
    The format file is a separate ASCII text file which allows
    users to add new tags and specify the formatting for tags. See
    the AUTODUCK.HLP help file for details on the Autoduck format file.

----------------------------------------------------------------------------
Release 094     April 15, 1993
----------------------------------------------------------------------------

Bug Fixes:
    Handle comment blocks that begin with leading whitespace.
    Use case-insensitive string compare to sort topics.
    Increase topic buffer size from 8K to 16K.
    Properly report warning line numbers in multi-topic comment blocks.
    Treat leading consecutive asterisk characters as noise (strip).

----------------------------------------------------------------------------
Release 093     March 12, 1993
----------------------------------------------------------------------------

Bug Fixes:
    Fixed parser problem with tags such as @public that have no fields.
    Fixed out-of-memory errors resulting in assertions.

New Features:
    Generation of Help RTF is fully supported.
    Progress indicator.

Other Changes:
    Updates for latest MSGRIDA1.DOT template (2/10/93 version).
    Latest versions of MSGRIDA1.DOT and MSGRIDWH.DOT are included.

Notes:
    To properly format Help RTF, load the RTF file generated by Autoduck
    into Word and then save it as an RTF file (with same name). You must
    do this before compiling the Help file. Be sure both of the Word
    templates included in this release are copied to your Word template
    directory.

----------------------------------------------------------------------------
Release 092     March 5, 1993
----------------------------------------------------------------------------

Bug Fixes:
    Fixed extractor problem with // comments preceeding @doc block.
    Report error for topic name overflow.

Other Changes:
    Do not generate output for unrecognized tags.


----------------------------------------------------------------------------
Release 091     March 5, 1993
----------------------------------------------------------------------------

Bug Fixes:
    Properly ignores directories instead of trying to open as files.

    Properly formats example code for @ex tag. Example code can now be
        be dropped into Autoduck verbatim! You don't have to escape
        _any_ characters.

New Features:
    Ignores ";Internal" keywords. This allows Autoduck to be stripped
        from public header files before release using the standard
        tools Development uses for this purpose.

    Ignores any lines beginning with "//" comment characters to allow
        comments to the Autoduck source (or whatever). There can be
        no whitespace preceeding the comment characters, else the
        line will be processed.

    New command line option, \t[0-9], allows you to specify the tab
        size used in your example source for @ex tag. The default
        is tabs = 8.

Other Changes:
    Outputs @todo and @devnote text in red for easy visibility in WinWord.

----------------------------------------------------------------------------
