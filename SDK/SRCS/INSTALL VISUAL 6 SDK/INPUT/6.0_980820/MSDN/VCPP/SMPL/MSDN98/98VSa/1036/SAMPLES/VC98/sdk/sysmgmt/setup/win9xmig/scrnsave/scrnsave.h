#include "miginf.h"

//
// utils.c -- reusable utilities (unrelated to screen saver code)
//

VOID
LogRegistryError (
    IN      HKEY Key,
    IN      LPCSTR ValueName
    );

HKEY
OpenRegKey (
    IN      HKEY RootKey,
    IN      LPCSTR Key
    );

HKEY
CreateRegKey (
    IN      HKEY RootKey,
    IN      LPCSTR Key
    );

VOID
CloseRegKey (
    IN      HKEY Key
    );

LPCSTR
GetRegValueString (
    IN      HKEY Key,
    IN      LPCSTR ValueName
    );

BOOL
SetRegValueString (
    HKEY Key,
    LPCSTR ValueName,
    LPCSTR ValueStr
    );

DWORD
CountStringBytes (
    IN      LPCSTR str
    );

DWORD
CountMultiStringBytes (
    IN      LPCSTR str
    );

LPSTR
CopyStringAtoB (
    OUT     LPSTR mbstrDest, 
    IN      LPCSTR mbstrStart, 
    IN      LPCSTR mbstrEnd     // ptr to the first char NOT to copy
    );

BOOL
OurGetLongPathName (
    LPCSTR ShortPath,
    LPSTR Buffer
    );

VOID
ConvertSystemToSystem32 (
    IN OUT  LPSTR Filename
    );

//
// utils.c -- helper functions specific to screen saver settings
//

VOID
GenerateFilePaths (
    VOID
    );

LPCSTR
GetScrnSaveExe (
    VOID
    );

BOOL
CreateScreenSaverParamKey (
    IN      LPCSTR ScreenSaverName,
    IN      LPCSTR Value,
    OUT     LPSTR Buffer
    );

BOOL
DecodeScreenSaverParamKey (
    IN      LPCSTR EncodedString,
    OUT     LPSTR ScreenSaverName,
    OUT     LPSTR ValueName
    );


//
// savecfg.c -- functions that save things to our working directory
//

BOOL
SaveDatFileKeyAndVal (
    IN      LPCSTR Key,
    IN      LPCSTR Val
    );

BOOL
CopyRegValueToDatFile (
    IN      HKEY RegKey,
    IN      LPCSTR ValueName
    );

BOOL
SaveControlIniSection (
    LPCSTR ControlIniSection,
    LPCSTR ScreenSaverName
    );


//
// dataconv.c -- functions that convert Win9x settings & save them on NT
//

BOOL
CopyValuesFromDatFileToRegistry (
    IN      HKEY RegKey,
    IN      LPCSTR RegKeyName,
    IN      LPCSTR ScreenSaverName,
    IN      LPCSTR ValueArray[]
    );

LPCSTR
GetSettingsFileVal (
    IN      LPCSTR Key
    );

BOOL
TranslateGeneralSetting (
    IN      HKEY RegKey,
    IN      LPCSTR Win9xSetting,
    IN      LPCSTR WinNTSetting
    );

BOOL
SaveScrName (
    IN      HKEY RegKey, 
    IN      LPCSTR KeyName
    );

BOOL
TranslateScreenSavers (
    IN      HKEY RegRoot
    );

BOOL
CopyUntranslatedSettings (
    IN      HKEY RegRoot
    );

//
// DLL globals
//

extern LPCSTR g_User;
extern LPSTR g_SettingsFile;
extern LPSTR g_MigrateDotInf;
extern LPSTR g_WorkingDirectory;
extern LPSTR g_SourceDirectories;
extern HANDLE g_hHeap;

//
// Define strings
//

#define DEFINE_LOCALIZED_STRINGS                                            \
    DEFMAC (S_HUGEDATA_ERROR,   "An invalid screen saver was detected "     \
                                "and skipped.\r\n")                         \
                                                                            \
    DEFMAC (S_DEFAULT_USER,     "Default User")                             \
                                                                            \
    DEFMAC (g_MyProductId,      "Windows 95 Screen Savers")                 \
                                                                            \
    DEFMAC (PASSWORD_ALERT,     "The current screen saver password may be " \
                                "different from the password expected by "  \
                                "Windows NT.  On Windows NT, use your "     \
                                "logon password when a screen saver "       \
                                "prompts for a password.")                  \
                                                                            \
    DEFMAC (USER_PROCESSING_ERROR, "An error occurred processing screen "   \
                                "saver settings for user %s.  The screen "  \
                                "saver will be disabled for this user.  "   \
                                "(Error: %u)\r\n")                          \
                                                                            \
    DEFMAC (DELETEFILE_SUCCESS, "Deleted Windows 95 screen saver %s\r\n")   \
                                                                            \
    DEFMAC (DELETEFILE_ERROR,   "An error occurred attempting to delete "   \
                                "the Windows 95 screen saver %s.  (Error: " \
                                "%u)\r\n")                                  \
                                                                            \
    DEFMAC (S_BEZIER_DATA_ERROR, "Some of the Bezier screen saver "         \
                                "settings are invalid and cannot be "       \
                                "transfered to Windows NT.\r\n")            \
                                                                            \
    DEFMAC (S_REGISTRY_ERROR,   "An error occurred saving the screen "      \
                                "saver settings for user %s.  (Error: %u, " \
                                "%s [%s])\r\n")                             \
                                                                            \
    


#define DEFINE_NONLOCALIZED_STRINGS                                         \
    DEFMAC (S_BOOT,             "boot")                                     \
    DEFMAC (S_SCRNSAVE_EXE,     "SCRNSAVE.EXE")                             \
    DEFMAC (S_SCRNSAVE_DOT,     "Screen Saver.")                            \
    DEFMAC (S_SCRNSAVE_MASK,    "Screen Saver.%s")                          \
    DEFMAC (S_EMPTY,            "")                                         \
    DEFMAC (S_DOUBLE_EMPTY,     "\0")                                       \
    DEFMAC (S_SETTINGS_MASK,    "%s\\settings.dat")                         \
    DEFMAC (S_MIGINF_MASK,      "%s\\migrate.inf")                          \
    DEFMAC (S_SYSTEM_INI,       "system.ini")                               \
    DEFMAC (S_CONTROL_INI,      "control.ini")                              \
    DEFMAC (S_BEZIER,           "Bezier")                                   \
    DEFMAC (S_MARQUEE,          "Marquee")                                  \
    DEFMAC (S_BEZIER_SETTINGS,  "Screen Saver.Bezier")                      \
    DEFMAC (S_MARQUEE_SETTINGS, "Screen Saver.Marquee")                     \
    DEFMAC (S_MIGRATION_PATHS,  "Migration Paths")                          \
    DEFMAC (S_CONTROL_PANEL_MASK, "Control Panel\\%s")                      \
    DEFMAC (S_LENGTH,           "Length")                                   \
    DEFMAC (S_WIDTH,            "Width")                                    \
    DEFMAC (S_LINESPEED,        "LineSpeed")                                \
    DEFMAC (S_BACKGROUND_COLOR, "BackgroundColor")                          \
    DEFMAC (S_CHARSET,          "CharSet")                                  \
    DEFMAC (S_FONT,             "Font")                                     \
    DEFMAC (S_MODE,             "Mode")                                     \
    DEFMAC (S_SIZE,             "Size")                                     \
    DEFMAC (S_SPEED,            "Speed")                                    \
    DEFMAC (S_TEXT,             "Text")                                     \
    DEFMAC (S_TEXTCOLOR,        "TextColor")                                \
    DEFMAC (S_ACTIVE1,          "Active1")                                  \
    DEFMAC (S_ACTIVE2,          "Active2")                                  \
    DEFMAC (S_CLEAN_SCREEN,     "Clean Screen")                             \
    DEFMAC (S_ENDCOLOR1,        "EndColor1")                                \
    DEFMAC (S_ENDCOLOR2,        "EndColor2")                                \
    DEFMAC (S_LINES1,           "Lines1")                                   \
    DEFMAC (S_LINES2,           "Lines2")                                   \
    DEFMAC (S_STARTCOLOR1,      "StartColor1")                              \
    DEFMAC (S_STARTCOLOR2,      "StartColor2")                              \
    DEFMAC (S_WALKRANDOM1,      "WalkRandom1")                              \
    DEFMAC (S_WALKRANDOM2,      "WalkRandom2")                              \
    DEFMAC (S_DENSITY,          "Denisty")                                  \
    DEFMAC (S_WARPSPEED,        "WarpSpeed")                                \
    DEFMAC (S_HKR,              "HKR")                                      \
    DEFMAC (S_DEFAULT_KEYSTR,   "(unknown regkey)")                         \
    DEFMAC (S_SYSTEM_DIR,       "\\system\\")                               \
    DEFMAC (S_SYSTEM32_DIR,     "\\system32\\")                             \

#define DEFINE_STRINGS DEFINE_LOCALIZED_STRINGS DEFINE_NONLOCALIZED_STRINGS

//
// Declare externs for all string variables
//

#define DEFMAC(var,str) extern CHAR var[];
DEFINE_STRINGS
#undef DEFMAC


