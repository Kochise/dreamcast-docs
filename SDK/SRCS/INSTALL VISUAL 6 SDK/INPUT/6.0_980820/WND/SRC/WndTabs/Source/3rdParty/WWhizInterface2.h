///////////////////////////////////////////////////////////////////////////////
// $Workfile: WWhizInterface2.h $
// $Archive: /WorkspaceWhiz/Src/Shared/WWhizInterface2.h $
// $Date: 2001/08/19 21:53:35 $ $Revision: 1.1 $ $Author: osolo $
///////////////////////////////////////////////////////////////////////////////
// This source file is part of the Workspace Whiz! source distribution and
// is Copyright 1997-2001 by Joshua C. Jensen.  (http://workspacewhiz.com/)
//
// The code presented in this file may be freely used and modified for all
// non-commercial and commercial purposes so long as due credit is given and
// this header is left intact.
///////////////////////////////////////////////////////////////////////////////
#pragma once

struct WWhizReg;
class WWhizProjectList;
class WWhizProject;
class WWhizFileList;
class WWhizFile;
class WWhizTagList;
class WWhizTag;
class WWhizConfig;
class XmlData;

/**
	This is the base class for several Workspace Whiz! objects that allows
	reference counting.  It should look fairly similar to COM's IUnknown.
**/
class WWhizBase
{
public:
	/**
		@return	Returns the current reference count of the object.
	**/
	virtual UINT GetRefCount() = 0;

	/**
		Increases the object's reference count by one.
		@return Returns the current reference count of the object.
	**/
	virtual UINT AddRef() = 0;

	/**
		Decreases the object's reference count by one.
		@return Returns the current reference count of the object.
	**/
    virtual UINT Release() = 0;
};


/**
	The interface to the attributes of a tag.  This class represents a single
	tag.
**/
class WWhizTag //: public WWhizBase
{
public:
	/**
		The access type of the tag.
	**/
	enum Access
	{
		PUBLIC,			//!< A public class member.
		PROTECTED,		//!< A protected class member.
		PRIVATE,		//!< A private class member.
		FRIEND,
	};

	/**
		The implementation type of the tag.
	**/
	enum ImplementationType
	{
		DEFAULT,
		ABSTRACT,
		VIRTUAL,
		PUREVIRTUAL,
	};

	/**
		The various types a tag can be.
	**/
	enum Type
	{
		CLASS,			//!< A class definition.
		DECLARATION,	//!< A tag prototype.
		DEFINE,			//!< A #define statement.
		ENUM,			//!< An enumeration.
		ENUMMEMBER,		//!< An enumeration's member.
		FILE,			//!< A file.
		FUNCTION,		//!< A function.
		MEMBER,			//!< A class or structure member.
		NAMESPACE,		//!< A namespace.
		STRUCTURE,		//!< A structure definition.
		TYPEDEF,		//!< A typedef definition.
		UNION,			//!< A union.
		VARIABLE,		//!< A variable.
		LAST_TYPE,
	};

	/**
		@return Returns the type of the tag.
	**/
	virtual Type GetType(void) const = 0;

	/**
		To facilitate faster tag lookups, every tag has a "short" identifier
		associated with it.  The short identifier is all lowercase and only
		contains alphanumeric characters.  Underscores are not included.
		Do not use GetShortIdent() for the display of the tag name.  Instead,
		use GetIdent().
		@return Returns the alphanumeric "short" name for the tag.
	**/
	virtual LPCSTR GetShortIdent(void) const = 0;

	/**
		@return Returns the true tag name, case-sensitive.
	**/
	virtual LPCSTR GetIdent(void) const = 0;

	/**
		@return Returns the filename the tag resides within.
	**/
	virtual LPCSTR GetFilename(void) const = 0;

	/**
		@return Returns the regular expression used to search for the tag.
	**/
	virtual LPCSTR GetSearchString(void) const = 0;

	/**
		To facilitate faster tag lookups, every parent tag has a "short"
		identifier associated with it.  The short identifier is all lowercase
		and only contains alphanumeric characters.  Underscores are not
		included.  Do not use GetShortParentIdent() for the display of the
		parent tag name.  Instead, use GetParentIdent().
		@return Returns the alphanumeric "short" name for the parent tag.
	**/
	virtual LPCSTR GetShortParentIdent(void) const = 0;

	/**
		@return Returns the true parent tag name, case-sensitive.
	**/
	virtual LPCSTR GetParentIdent(void) const = 0;

	/**
	**/
	virtual int GetLineNumber(void) const = 0;

	/**
		@return Returns the next matching tag, based on search criteria
			specified through the WWhizInterface::MatchTag() function.
	**/
	virtual WWhizTag* GetMatchNext(void) const = 0;

	/**
		@return Returns the previous matching tag, based on search criteria
			specified through the WWhizInterface::MatchTag() function.
	**/
	virtual WWhizTag* GetMatchPrev(void) const = 0;

	/**
		@return Returns the access of the tag if the tag is a class member.
	**/
	virtual Access GetAccess(void) const = 0;

	/**
		@return Returns the namespace, if any, of the tag.
	**/
	virtual LPCSTR GetNamespace(void) const = 0;

	/**
		Retrieves the buddy of the tag.  That is, if the tag is a declaration,
		it retrieves the definition, and vice versa.

		@return Returns the "buddy" of the tag.
	**/
	virtual WWhizTag* GetBuddy(void) const = 0;

	/**
		@return Returns the tag's implementation type.
	**/
	virtual ImplementationType GetImplementationType(void) const = 0;
};


/**
	This is the master control mechanism for anything residing in the
	WWhizInterface module.  All facilities for project information, file
	lists, and tag lists are accessible from this interface.

	Note: Any filename passed to any WWhizInterface function is passed
	through ResolveFilename().
**/
class WWhizInterface
{
public:
	/**
		For every file parsed during the creation of the tags,
		TagCallbackInfo is filled in and passed to an application-specified
		callback routine.
	**/
	struct TagCallbackInfo
	{
		void* m_userData;			//!< User data specified
		int m_curFile;				//!< The current file number being processed.
		int m_numFiles;				//!< The number of files to be processed.
		LPCTSTR m_curFilename;		//!< The filename of the file currently being processed.

		enum Type
		{
			REFRESH,
			LOAD,
			SAVE,
		};

		Type m_type;
	};

	/**
		The definition of the callback called from the tag refresh.
	**/
	typedef void (*TagRefreshCallback)(const TagCallbackInfo& info);

	/**
		Initializes the WWhizInterface.
	**/
	virtual void Reserved0() = 0;

	///////////////////////////////////////////////////////////////////////////
	// File support
	///////////////////////////////////////////////////////////////////////////
	/**
		@return Returns the list of projects considered by WWhizInterface.
			The list includes the projects from the open workspace and any
			other application-added projects, particularly through the
			registration module's ExtraFiles interface.
	**/
	virtual WWhizProjectList& GetProjectList(void) const = 0;

	/**
		@return Returns the file list corresponding to all the open
			projects.
		@see GetProjectList
	**/
	virtual WWhizFileList& GetFileList(void) const = 0;

	/**
		@return Returns the open workspace filename.
	**/
	virtual CString GetWorkspaceName(void) const = 0;

	/**
		@return Returns the open workspace location.  Note that this location
			is set through the function SetWorkspaceLocation().
		@see SetWorkspaceLocation
	**/
	virtual const CString& GetWorkspaceLocation(void) const = 0;

	/**
		DevStudio provides no function to return the location of the workspace,
		so WWhizInterface provides this functionality.

		SetWorkspaceLocation() obtains the workspace location through the
		WWhizInterfaceHelper.pkg file, installed via the WWhizInterfaceInstaller.
		If this is unavailable, then SetWorkspaceLocation() works by obtaining
		the current working directory when the workspace opens.  This is best
		done by calling WWhizInterface's SetWorkspaceLocation() through the
		DevStudio automation function:
		
		HRESULT CCommands::XApplicationEvents::WorkspaceOpen();

		If the WWhizInterface facilities are being used without DevStudio's
		assistance, then set the current working directory to the directory
		containing the workspace and call SetWorkspaceLocation().

		@code
		_chdir("c:/Projects/MyProject");
		g_wwhizInterface->SetWorkspaceLocation();
		g_wwhizInterface->AddProject("c:/Projects/MyProject/MyProject.dsw");
		@endcode

		Note: A call to SetWorkspaceLocation() is required, because Workspace
		Whiz! files, such as ExtraFiles.WW and Tags.WW, are stored in the
		directory returned via GetWorkspaceLocation().
	**/
	virtual void SetWorkspaceLocation(void) = 0;

	/**
		@return Returns the full path to the ExtraFiles.WW file.
	**/
	virtual const CString& GetExtraFilename(void) = 0;

	/**
		@param filename A reference to a CString where the currently active
			file's full path will be stored.  If DevStudio is not running,
			filename will be an empty string.
		@return Returns true if a filename was able to be retrieved.  False,
			otherwise.
	**/
	virtual bool GetCurrentFilename(CString& filename) const = 0;

	/**
		@return When running DevStudio, returns the WWhizProject interface to
			the currently active project in the workspace.
	**/
	virtual WWhizProject* GetCurrentProject() const = 0;

	/**
		Resolves the filename when it contains environment variables and relative paths.
		Any filename can contain environment variables.  This is especially true of
		DevStudio.

		Filenames containing environment variables are of the form:

		$(MYPROJECTS)\CoolProject\Cool.dsw

		@param rootDir The root directory to be attached to the beginning of
			[filename] if [filename] is a relative path.  If the root
			directory is empty, no string is prepended.
		@param filename The reference to the filename to be resolved.  The
			resolved filename is stored back into this variable.
	**/
	virtual void ResolveFilename(const CString& rootDir, CString& filename) = 0;

	/**
		It is wise to refresh the file list before using any file or tag
		commands.  This is especially true when running in DevStudio.  Since
		DevStudio provides no COM method of retrieving the list of files in
		a project, WWhizInterface is only able to retrieve its file list by
		parsing .dsp files.  This has at least one primary disadvantage.  If
		a change is made to the project in DevStudio, the project MUST be
		saved before WWhizInterface can process the change.

		RefreshFileList() does a scan of .dsp files to determine if
		updates are necessary.  This scan is very quick, so it is advised the
		application calls RefreshFileList() before each set of file or tag
		commands.

		When in DevStudio, RefreshFileList() automatically adds any projects
		in the open workspace.

		If the Workspace Whiz! registration interface is available, ExtraFiles
		are added, also.

		
	**/
	virtual bool RefreshFileList(void) = 0;

	/**
		Adds a project to the list of WWhizInterface projects.  Projects (.dsp)
		or workspaces (.dsw) are the only file types that can be added.

		@param projectName The path to the project or workspace file to be added.
	**/
	virtual void AddProject(CString projectName) = 0;

	/**
		Performs a full cleanup of the WWhizInterface internal structures.
	**/
	virtual void RemoveAllFiles(void) = 0;

	/**
	**/
	virtual void Reserved1() = 0;

	///////////////////////////////////////////////////////////////////////////
	// Tag support
	///////////////////////////////////////////////////////////////////////////
	/**
		@return After performing a tag match through the MatchTag() function,
			GetTagMatchHead() returns the first found WWhizTag.
	**/
	virtual const WWhizTag* GetTagMatchHead(void) const = 0;

	/**
		@return After performing a tag match through the MatchTag() function,
			GetTagMatchTail() returns the last found WWhizTag.
	**/
	virtual const WWhizTag* GetTagMatchTail(void) const = 0;

	/**
		@return Returns the total number of matched tags found through the
			MatchTag() function.
	**/
	virtual int GetTagMatchCount(void) const = 0;

	/**
		@return If the WWhizReg registration interface exists, returns the
			last tag moved to through GotoTag().
	**/
	virtual const WWhizTag* GetLastMatchedTag(void) const = 0;

	/**
		@return Retrieves the list of tags corresponding to all of the files
			in GetFileList().
	**/
	virtual const WWhizTagList& GetTagList(void) const = 0;

	/**
		Performs a full cleanup of the WWhizInterface internal tag structures.
	**/
	virtual void RemoveAllTags(void) = 0;

	/**
		Matches [name] against a tag list.  The list of matched tags can be
		retrieved through GetTagMatchHead(), GetTagMatchTail(), and
		GetTagMatchCount().  Additionally, WWhizTag::GetMatchNext() and 
		WWhizTag::GetMatchPrev() may be used for traversal.

		@param tags The tag list to match against.
		@param name [name] is of the format described in the Find Tag Workspace
			Whiz! documentation.
	**/
	virtual void MatchTag(const WWhizTagList& tags, LPCTSTR name, WWhizTag::Type forceType = WWhizTag::LAST_TYPE) const = 0;

	/**
		If the WWhizReg registration interface exists and DevStudio is loaded,
		the appropriate source file is opened and the caret is positioned.

		@param tag The tag to go to.
	**/
	virtual bool GotoTag(const WWhizTag* tag) const = 0;

	/**
		Before calling RefreshTagList(), a tag callback may be set through this
		function.

		@param callback The callback function.
		@param userData User-specified data.
	**/
	virtual void SetTagCallback(TagRefreshCallback callback, void* userData) = 0;

	/**
		Refreshes the tag list.  If WWhizConfig::GetAutoRefreshTags() is not
		set and [forceRefresh] is not set, then the tags aren't refreshed.

		@param forceRefresh Forces a tag refresh.
	**/
	virtual void RefreshTagList(bool forceRefresh = false, bool forceSave = false) = 0;

	/**
		Loads a list of saved tags from the disk.
	**/
	virtual void LoadTags() = 0;

	/**
		Saves the list of tags to the disk.  The tags are saved to the file
		Tags.WW in the directory specified by GetWorkspaceLocation().
	**/
	virtual void SaveTags() = 0;

	/**
		@param The tag type to query.
		@return Returns whether the specified tag type is considered for the
			MatchTag() search.
	**/
	virtual bool GetTagUseType(WWhizTag::Type type) = 0;

	/**
		Sets the tag types considered for the MatchTag() routine.  By default,
		all tag types are on.

		@param type The tag type to turn on/off.
		@param use Set to true if the tag type should be considered for the
			search, false otherwise.
	**/
	virtual void SetTagUseType(WWhizTag::Type type, bool use) = 0;

	// Global files
	/**
		@return Retrieves the global file list, which is the list of files
			queried from the global include directories.  (In DevStudio,
			they are found under Tools->Options->Directories->Include Files.)
	**/
	virtual WWhizFileList& GetGlobalFileList(void) const = 0;

	/**
		Refreshes the global file list.
	**/
	virtual bool RefreshGlobalFileList(void) = 0;
	
	// Misc
	/**
		@return Retrieves the WWhizConfig interface.
	**/
	virtual WWhizConfig& GetConfig() = 0;

	// More stuff appended to the end.
	/**
		@return Retrieves the last time RefreshFileList() found new files.
	**/
	virtual CTime GetLastFileRefreshTime() const = 0;

	/**
		@return Returns the last time RefreshTagList() found new tags.
	**/
	virtual CTime GetLastTagRefreshTime() const = 0;

	/**
		Sets a pointer to the Workspace Whiz! registration module.

		@param wwhizReg The pointer to the WWhizReg.mod.
	**/
	virtual void SetWWhizReg(WWhizReg* wwhizReg) = 0;

	/**
		@return Returns the file list corresponding to all the open
			active projects.
		@see GetProjectList
	**/
	virtual WWhizFileList& GetActiveFileList(void) const = 0;

	/**
		@return Returns the version of the WWhizInterface library.
			Bits 24-31 = Major version.  Bits 16-23 = Minor version.  Bits 0-15 = Build.
		@see GetProjectList
	**/
	virtual DWORD GetVersion(void) const = 0;

	/**
		For better efficiency, WWhizInterface maintains a list of files to check
		for tag changes.  If a file is modified, it should be added to WWhizInterface
		via the AddChangedFile() function.

		@param filename The full pathname of the file that changed.
	**/
	virtual void AddChangedFile(CString filename) = 0;

	/**
		After calling CheckActiveFilesForChanges(), the next tag refresh will
		check every file in the workspace for changes.
	**/
	virtual void CheckActiveFilesForChanges() = 0;

	/**
		Retrieves the tag whose scope contains the specified line number.

		@param filename The name of the file where the tag resides.
		@param lineNumber The line number to match a tag's scope with.
		@return Returns the tag whose scope contains lineNumber or NULL if no
			tag is matched.
	**/
	virtual const WWhizTag* GetTagScope(const CString& filename, UINT lineNumber) = 0;

	/**
		@return Returns the open workspace filename.
	**/
	virtual const CString& GetWorkspaceFullPath(void) const = 0;
};


/**
	WWhizInterface configuration information.
**/
class WWhizConfig
{
public:
	///////////////////////////////////////////////////////////////////////////
	// Files extension list.
	///////////////////////////////////////////////////////////////////////////
	/**
		\internal Resets the file extension list to the defaults:

		cpp, c, cxx, cc, h, hpp, hh, inl

		Currently, the list of file extensions is only used by the registration
		module's header flip.
	**/
	virtual void FilesExtReset() = 0;

	/**
		\internal Remove all extensions in the extension list.
	**/
	virtual void FilesExtRemoveAll() = 0;

	/**
		\internal Adds a new file extension.
	**/
	virtual void FilesExtAdd(CString ext) = 0;

	/**
		\internal Removes a file extension.
	**/
	virtual void FilesExtRemove(int index) = 0;

	/**
		\internal Gets a file extension from the list.
	**/
	virtual const CString& FilesExtGet(int index) = 0;

	/**
		\internal Retrieves the number of registered file extensions.
	**/
	virtual int FilesExtGetCount() = 0;

	///////////////////////////////////////////////////////////////////////////
	// Tags extension list.
	///////////////////////////////////////////////////////////////////////////
	/**
		Resets the tag extension list to the defaults:

		cpp, c, cxx, cc, h, hpp, hh, inl

		The list of tag extensions is used when considering which files should
		be processed by CTags.
	**/
	virtual void TagsExtReset() = 0;

	/**
		Remove all extensions in the extension list.
	**/
	virtual void TagsExtRemoveAll() = 0;

	/**
		Adds a new tag file extension.
	**/
	virtual void TagsExtAdd(CString ext) = 0;

	/**
		Removes a tag file extension.
	**/
	virtual void TagsExtRemove(int index) = 0;

	/**
		@return Retrieves the number of registered tag file extensions.
	**/
	virtual int TagsExtGetCount() = 0;

	/**
		@param index The tag extension index to retrieve.
		@return Retrieves a tag extension from the list.
	**/
	virtual const CString& TagsExtGet(int index) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Misc.
	///////////////////////////////////////////////////////////////////////////
	/**
		The tags are automatically packed every x tag refreshes.

		@return Retrieves the number of tag refreshes that must occur before
			the tags are packed.
	**/
	virtual UINT GetTagAutoPackAmount() = 0;

	/**
		The tags are automatically packed every x tag refreshes.

		@param amount The number of tag refreshes that must occur before
			the tags are packs.
	**/
	virtual void SetTagAutoPackAmount(UINT amount) = 0;

	/**
		@return Retrieves whether tags are automatically force refreshed every
			time WWhizInterface::RefreshTagList() is called.
	**/
	virtual bool GetAutoRefreshTags() = 0;

	/**
		@param autoRefresh Sets whether tags are automatically force refreshed every
			time WWhizInterface::RefreshTagList() is called.
	**/
	virtual void SetAutoRefreshTags(bool autoRefresh) = 0;

	/**
		@return Retrieves whether files are automatically date/time checked
			after a task switch has occurred.
	**/
	virtual bool GetScanFilesTaskSwitch() = 0;

	/**
		@param scanFiles Sets whether files are automatically date/time checked
			after a task switch has occurred.
	**/
	virtual void SetScanFilesTaskSwitch(bool scanFiles) = 0;
	
	///////////////////////////////////////////////////////////////////////////
	// Tokens to ignore.
	///////////////////////////////////////////////////////////////////////////
	/**
		Resets the token ignore list to the defaults:

		_AFXWIN_INLINE

		The list of tokens to ignore is used when files are processed by CTags.
	**/
	virtual void IgnoreTokensReset() = 0;

	/**
		Remove all tokens in the token ignore list.
	**/
	virtual void IgnoreTokensRemoveAll() = 0;

	/**
		Adds a new token to ignore.
	**/
	virtual void IgnoreTokensAdd(CString ext) = 0;

	/**
		Removes a token to ignore.
	**/
	virtual void IgnoreTokensRemove(int index) = 0;

	/**
		@return Retrieves the number of registered tag file extensions.
	**/
	virtual int IgnoreTokensGetCount() = 0;

	/**
		@param index The tag extension index to retrieve.
		@return Retrieves a tag extension from the list.
	**/
	virtual const CString& IgnoreTokensGet(int index) = 0;

	///////////////////////////////////////////////////////////////////////////
	// Misc.
	///////////////////////////////////////////////////////////////////////////
	/**
		The tags are automatically saved after there have been x file saves.

		@return Retrieves the number of file saves that must occur before
			the tags are saved.
	**/
	virtual UINT GetTagAutoSaveAmount() = 0;

	/**
		The tags are automatically saved after there have been x file saves.

		@param amount The number of files saves that must occur before
			the tags are saved.
	**/
	virtual void SetTagAutoSaveAmount(UINT amount) = 0;
};


/**
	WWhizProjectList represents the list of projects contained within
	WWhizInterface.
**/
class WWhizProjectList
{
public:
	/**
		@return Retrieves the number of projects in the list.
	**/
	virtual int GetProjectCount() const = 0;

	/**
		@param index The index of the project to retrieve.
		@return Returns the WWhizProject at [index].
	**/
	virtual WWhizProject* GetProjectByIndex(int index) const = 0;

	/**
		Finds a project by full path name.

		@param projectName The full path name to the project.
		@return Returns the WWhizProject matching [projectName].
	**/
	virtual WWhizProject* Find(CString projectName) const = 0;
};


/**
	Represents a single project.
**/
class WWhizProject
{
public:
	/**
		@return Retrieves the full path name to the project.
	**/
	virtual const CString& GetName(void) const = 0;

	/**
		@return Returns whether the project is active.
	**/
	virtual bool IsActive(void) const = 0;

	/**
		@return Retrieves the time stamp of the project file when it was read
			in.
	**/
	virtual const CTime& GetTimeStamp(void) const = 0;

	/**
		@return Retrieves the project's file list.
	**/
	virtual WWhizFileList& GetFileList(void) const = 0;

	/**
		@return Retrieves the project's tag list.
	**/
	virtual WWhizTagList& GetTagList(void) const = 0;

	/**
		@return Returns true if the project is part of the active workspace,
			false otherwise.
	**/
	virtual bool IsWorkspaceProject(void) const = 0;

	/**
		Sets whether the project is active or not.  Be sure to call
		WWhizInterface::RefreshFileList() after making this call.

		@param active The new active state of the project.
	**/
	virtual void SetActive(bool active = true) = 0;

	/**
		Retrieve the XML data representing the project.

		@return Returns a pointer to the XmlData object representing the project.
	**/
	virtual XmlData& GetXmlData() = 0;
};


/**
	Represents a file list, usually sorted.  Only contains unique filenames.
**/
class WWhizFileList
{
public:
	/**
		@return Retrieves the count of files in the file list.
	**/
	virtual int GetCount(void) const = 0;

	/**
		@param index The index of the WWhizFile to retrieve.
		@return Retrieves the file at [index].
	**/
	virtual WWhizFile* Get(int index) const = 0;

	/**
		Searches for a file matching [fullName].

		@param fullName The full path name of the file to find, case sensitive.
		@return Returns the WWhizFile of the found file.  If the file was not
			found, returns NULL.
	**/
	virtual WWhizFile* Find(CString fullName) const = 0;

	/**
		Based on an existing WWhizFile, FindExact() finds the index
		corresponding to that file.

		@param An existing WWhizFile, obtained via WWhizFileList::Get() or
			WWhizFileList::Create().
		@return Returns the found index or -1 if not found.
	**/
	virtual int FindExact(WWhizFile& file) const = 0;

	/**
		Based on an existing WWhizFile, FindExact() finds the next index
		corresponding to an approximate file match.

		@param An existing WWhizFile, obtained via WWhizFileList::Get() or
			WWhizFileList::Create().
		@return Returns the found index or -1 if not found.
	**/
	virtual int FindNext(int startPos, WWhizFile& file) const = 0;

	/**
		Based on an existing WWhizFile, FindPrevious() finds the previous 
		index corresponding to an approximate file match.

		@param An existing WWhizFile, obtained via WWhizFileList::Get() or
			WWhizFileList::Create().
		@return Returns the found index or -1 if not found.
	**/
	virtual int FindPrevious(int startPos, WWhizFile& file) const = 0;

	/**
		Based on a filename, Create() returns a new WWhizFile object that
		has a reference count of 1.  The application is responsible for
		calling Release() on the file when done.

		@param filename The filename to create a WWhizFile object from.
		@return A WWhizFile describing [filename].
	**/
	virtual WWhizFile& Create(const CString& filename) = 0;
};


/**
	Represents a file.
**/
class WWhizFile : public WWhizBase
{
public:
	/**
		@return Returns the lowercase version of the full path name.
	**/
	virtual const CString& GetFullName() const = 0;

	/**
		@return Returns the case-sensitive version of the full path name, as it
			appears on disk.
	**/
	virtual CString GetCaseFullName() const = 0;

	/**
		To facilitate faster file lookups, every file has a "short" title
		associated with it.  The short name is all lowercase and only
		contains alphanumeric characters.  Underscores are not included.
		Do not use GetShortName() for the display of the file title.  Instead,
		use GetTitle().

		@return Returns the alphanumeric "short" title for the file.
	**/
	virtual const CString& GetShortName(void) const = 0;

	/**
		@return Returns the case-sensitive file title.
	**/
	virtual const CString& GetTitle(void) const = 0;

	/**
		@return Returns the lowercase file extension.
	**/
	virtual const CString& GetExt(void) const = 0;

	/**
		@return Returns the case-sensitive path name.
	**/
	virtual const CString& GetPath(void) const = 0;

	/**
		@return Returns the file stamp of the file the last time
			WWhizInterface::RefreshFileList() was called.
	**/
	virtual const CTime& GetTimeStamp(void) const = 0;

	/**
		@return Returns the tag list associated with this file.
	**/
	virtual WWhizTagList& GetTagList(void) const = 0;


	/**
		Sets the short name of the file.  Only use this function on file's
		returned via WWhizFileList::Create().

		@param shortName The new short name for the file.
	**/
	virtual void SetShortName(const CString& shortName) = 0;

	/**
		Sets the file title of the file.  Only use this function on file's
		returned via WWhizFileList::Create().

		@param title The new title for the file.
	**/
	virtual void SetTitle(const CString& title) = 0;

	/**
		Sets the extension of the file.  Only use this function on file's
		returned via WWhizFileList::Create().

		@param ext The new extension for the file.
	**/
	virtual void SetExt(const CString& ext) = 0;

	/**
		Sets the path of the file.  Only use this function on file's
		returned via WWhizFileList::Create().

		@param ext The new path for the file.
	**/
	virtual void SetPath(const CString& path) = 0;

	/**
		Sets the time stamp of the file.  Only use this function on file's
		returned via WWhizFileList::Create().

		@param ext The new time stamp for the file.
	**/
	virtual void SetTimeStamp(CTime timeStamp) = 0;

	/**
		@return Retrieves a non sorted tag list, ordered according their position
		within the file.
	**/
	virtual WWhizTagList& GetOrderedTagList(void) const = 0;

	/**
		@return Returns whether this file is a member of the workspace or not.
	**/
	virtual bool IsWorkspaceFile(void) const = 0;
};


/**
	Represents a sorted tag list.
**/
class WWhizTagList
{
public:
	/**
		@return Retrieves the count of tags in the tag list.
	**/
	virtual int GetCount(void) const = 0;

	/**
		@param index The index of the WWhizTag to retrieve.
		@return Retrieves the tag at [index].
	**/
	virtual WWhizTag* Get(int index) const = 0;
};


