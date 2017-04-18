/****************************************************************************\
* FUNCTION PROTOTYPES
\****************************************************************************/

extern "C" {

VOID ExamineAccessToken(HANDLE hAccessToken);
BOOL ExamineSD    (PSECURITY_DESCRIPTOR psdSD);
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask);
BOOL ExamineACL   (PACL paclACL,              LPTSTR lpszOldIndent);
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask);
VOID ExamineMask  (ACCESS_MASK amMask,        LPTSTR lpszOldIndent);
//                   KINDS_OF_ACCESSMASKS_DECODED kamKindOfMask);
BOOL LookupSIDName(PSID psidSID,              LPTSTR lpszOldIndent);
BOOL SIDStringName(PSID psidSID, LPTSTR lpszSIDStringName);
VOID InitializeWellKnownSIDs(VOID);

};
