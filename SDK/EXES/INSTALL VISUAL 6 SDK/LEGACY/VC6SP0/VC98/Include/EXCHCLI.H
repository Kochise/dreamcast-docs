/* Microsoft Exchange. Copyright 1986 - 1998, Microsoft Corporation -
   All Rights Reserved */

/*
 * E X C H C L I . H
 * Client-side Exchange programmability interfaces
 *
 * This file contains interfaces to the following Exchange features:
 *	Enterprise-wide forms registry
 *	Conflict resolution interfaces for forms
 *	Custom actions on inbox management rules
 *
 * Information in this document is subject to change without notice and does
 * not represent a commitment on the part of Microsoft Corporation.
 */

#ifndef _EXCHCLI_H_
#define _EXCHCLI_H_


/* Parameter to IMAPIFormMgr::OpenFormContainer
   denoting the Exchange Enterprise Forms Registry */

#if defined(HFRMREG_DEFAULT)
#define HFRMREG_ENTERPRISE 4
#endif


/* The GUID for Exchange's form extension properties. */

#if !defined(INITGUID) || defined(USES_GUID_ExchangeFormExts)
DEFINE_GUID (
	GUID_ExchangeFormExts,
	0x77f69534, 0x6b7d, 0x101b, 0x9f, 0x0d, 0x00, 0xaa, 0x00, 0x3b, 0xa9, 0x05);
#endif
#define IDFEXT_ExchangeResolvesConflict 0


/*
	Interfaces for "custom actions," the client rule extensions.

	Exchange rules are evaluated against each message on the server,
	where matches result in the server executing one or more actions
	against the message.  For purposes of performance and robustness
	the server offers a fixed set of actions.
	However, some actions must necessarily execute on a client machine.
	To allow this, the server encodes the desired action in a message
	(known as a DAM, or Deferred Action Message), then waits for a client
	to open the mailbox and process these client-side action requests.
	Client side actions include popup alerts, cross-store moves and copies,
	and CUSTOM ACTIONS.

	Custom actions are the sole rule extensibility mechanism available
	to clients.  A user installs a DLL containing a custom action on
	his workstation, then writes a rule naming this DLL as its action.
	When the server finds a match for the rule, it generates a DAM
	specifying the action named.  Subsequently the client reads the DAM
	and executes the action by invoking the proper DLL.

	A custom action DLL very much resembles a Capone super-extension in
    its gross structure.  One installs it on 16 bit platforms by creating
    a section [Custom Actions] in exchng.ini, there adding a key
    "tag=4.0;DLL;ordinal" just as for a superextension.  On 32 bit platforms
    the custom action is specified in the Registry as a name/value pair
    under the registry key:

    \\HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Exchange\Client\Custom Actions

    The name/value pair is identical to that used on the 16 bit platform,
    where the 'name' is the 'tag' mentioned above, and the value is the
    DLL entry point information in the form: "4.0;DLL;ordinal".

    The tag should be suitable for display, as the Inbox Assistant will
    use it to represent the custom action for selection in its UI.  DLL
    should contain a fully qualified path to the DLL.  Ordinal is an
    integer denoting the ordinal of the extension entry point; it defaults
    to 1.

	That entry point is of type LPFNEXCHANGERULEEXTENTRY: it must allocate
	and return an instance of an IUnknown, off of which the Exchange
	client will QueryInterface the IExchangeRulesExt interface.  All
	subsequent calls will take place through this returned interface.
	Hence a custom action may easily reside in the same DLL as a super
	extension.

	Some methods of IExchangeRuleExt are passed an instance of the
	interface IExchangeRuleExtCallback.  This will return the extension
	information about the running Exchange client, including its MAPI
	session (off of which the extension may make calls) and a window
	handle (off of which to parent UI of its own).

	After the initial sequence of IUnknown methods, Exchange will
	invoke IExchangeRuleExt::Install.  This informs the extension into which
	context it is being invoked: either ERCONTEXT_INFO, that of the
	Inbox Assistant dialog, in which case it will be called upon to
	get new commands and translate existing commands; or else ERCONTEXT_EXEC,
	that of the client rule execution engine, in which case it will be
	called upon to execute the actual extension commands on a message.
	Return S_FALSE to abort installation or further processing.

		HRESULT IExchangeRuleExt::Install(
			LPEXCHANGERULEEXTCALLBACK percb,
				- an instance of IExchangeRuleExtCallback
			ULONG ulContext
				- one of ERCONTEXT_INFO or ERCONTEXT_EXEC
			)

    The QueryRelease() method is reserved for future use.  For now all rule
    extensions should return S_OK in response to a call on this method.

		HRESULT IExchangeRuleExt::QueryRelease()

	When a user selects the extension's tag from the Inbox Assistant,
	that extension is queried via IExchangeRuleExt::GetCommand for the
	command encoding it wishes to use.  This is an opportunity for it
	to present further UI refining the user's selection or specifying
	options if necessary.  The extension should return both an
	encoding of the command and a display string suitably representing
	the command to the user.  Return S_OK or S_FALSE as per the user's
	Ok or Cancel to any secondary UI.

		HRESULT IExchangeRuleExt::GetCommand(
			LPEXCHANGERULEEXTCALLBACK percb,
				- an instance of IExchangeRuleExtCallback
			TCHAR FAR* pszCommand, ULONG cchCommand,
                - an IN/OUT buffer in which to return the encoded command,
                  the buffer may be pre-initialized with a previously
                  existing command for this provider.
				  together with the length of the buffer given
			TCHAR FAR* pszDisplayName, ULONG cchDisplayName
                - IN/OUT, as the previous buffer, but for the display string
			)

	When the Inbox Assistant is invoked to edit an existing rule which
	specifies a custom action, it queries the appropriate extension
	via IExchangeRuleExt::QueryCommandDisplayName for the display string
	corresponding to the encoded command.  This should match the
	display string originally returned from GetCommand.  (Note that
	Exchange does not save the display string when saving the rule.)

		HRESULT IExchangeRuleExt::QueryCommandDisplayName(
			LPEXCHANGERULEEXTCALLBACK percb,
				- an instance of IExchangeRuleExtCallback
			LPCTSTR pszCommand,
				- the encoded command for which we want the display string
			TCHAR FAR* pszDisplayName, ULONG cchDisplayName
				- a buffer in which to return the display string,
				  together with the length of the buffer given
			)

	At the time that Exchange processes client-side rule actions, any
	custom actions invoked will result in their extensions receiving
	IExchangeRuleExt::Command calls.

		HRESULT IExchangeRuleExt::Command(
			LPEXCHANGERULEEXTCALLBACK percb,
				- an instance of IExchangeRuleExtCallback
			LPCTSTR pszCommand,
				- the encoded command to execute
			ULONG cb, LPENTRYID peid
				- the entryid of the message on which to execute
			)

*/

/* Extensibility contexts used with IExchangeRuleExt::Install */

#define ERCONTEXT_INFO (0x00000001)
#define ERCONTEXT_EXEC (0x00000002)


#undef INTERFACE
#define INTERFACE   IExchangeRuleExtCallback

DECLARE_INTERFACE_(IExchangeRuleExtCallback, IUnknown)
{
	BEGIN_INTERFACE
    /* IUnknown methods */
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR* lppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS)  PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

	/* IExchangeRuleExtCallback methods */
	STDMETHOD(GetVersion) (THIS_ ULONG FAR* pulVersion, ULONG ulFlags) PURE;
    STDMETHOD(GetWindow) (THIS_ HWND FAR* phwnd) PURE;
    STDMETHOD(GetSession) (THIS_ LPMAPISESSION FAR* ppses) PURE;
};
typedef IExchangeRuleExtCallback FAR * LPEXCHANGERULEEXTCALLBACK;

#undef INTERFACE
#define INTERFACE   IExchangeRuleExt

DECLARE_INTERFACE_(IExchangeRuleExt, IUnknown)
{
    /* IUnknown methods */
    STDMETHOD(QueryInterface) (THIS_ REFIID riid, LPVOID FAR * lppvObj) PURE;
    STDMETHOD_(ULONG,AddRef) (THIS) PURE;
    STDMETHOD_(ULONG,Release) (THIS) PURE;

    /* IExchangeRuleExt methods */
    STDMETHOD(Install) (THIS_
    	LPEXCHANGERULEEXTCALLBACK percb, ULONG ulContext) PURE;
    STDMETHOD(QueryRelease) (THIS) PURE;

	STDMETHOD(GetCommand)(THIS_
		LPEXCHANGERULEEXTCALLBACK percb,
		TCHAR FAR* pszCommand, ULONG cchCommand,
		TCHAR FAR* pszDisplayName, ULONG cchDisplayName) PURE;
	STDMETHOD(QueryCommandDisplayName) (THIS_
		LPEXCHANGERULEEXTCALLBACK percb,
		LPCTSTR pszCommand,
		TCHAR FAR* pszDisplayName, ULONG cchDisplayName) PURE;

	STDMETHOD(Command) (THIS_
		LPEXCHANGERULEEXTCALLBACK percb,
		LPCTSTR pszCommand,
		ULONG cb, LPENTRYID peid ) PURE;
};
typedef IExchangeRuleExt FAR* LPEXCHANGERULEEXT;


/* Type of function called by rules to load a provider */
typedef LPUNKNOWN (CALLBACK * LPFNEXCHANGERULEEXTENTRY)(VOID);

#define DEFINE_RULEEXTGUID(name, b) \
    DEFINE_GUID(name, 0x00020E00 | (b), 0, 0, 0xC0,0,0,0,0,0,0,0x46)

DEFINE_RULEEXTGUID(IID_IExchangeRuleExtCallback,			0x10);
DEFINE_RULEEXTGUID(IID_IExchangeRuleExt,					0x11);

#endif /* end of file exchcli.h */
