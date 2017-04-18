// RegDB.h -- Defines the registry interface used by this application.
//            The registry database conventions are described in
//            RegDb.c.

#define COMPANY_NAME        "Microsoft"            // Registry path
#define APPLICATION_NAME    "RegMPad32"            //   elements...
#define VERSION_NUMBER      "1.0"

#define KEY_VALUE_INSTALL_NAME "Installed by:"     //
#define KEY_VALUE_INSTALL_ORG  "Installed for:"    //

#define DEFAULTS_PATH	    "Default"              // Global subnode for
                                                   //   application defaults

#define WORD_WRAP_DEFAULT   "Word Wrap Default"    // Value names for
#define LAST_FILE_SET	    "Last File Set"        //   profile data

#define REG_INSTALLED       "Installed"            // Last value written during
                                                   // application installation.

#define GLOBAL_WORD_WRAP_DEFAULT    TRUE           // Global default for
                                                   // word wrap profile value.
#define ACL_BUFFER_SIZE     1024

extern HKEY hkGlobal;
extern HKEY hkPerUser;

extern BOOL fTextWrapDefault;

BOOL StoreAppConfig(HWND hwnd, PSZ pszPathBuff, PSZ pszInstallName,
                    PSZ pszInstallOrg,
                    BOOL fTextWrapDefault
                   );

BOOL CreateAppKeys();

BOOL LoadConfiguration();

BOOL SaveConfiguration();
