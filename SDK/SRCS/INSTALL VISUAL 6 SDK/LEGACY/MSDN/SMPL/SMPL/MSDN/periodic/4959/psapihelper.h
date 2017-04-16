BOOL GetModuleNameAndSectionInfo(
        HANDLE  hProcess,           // IN
        PVOID   p,                  // IN
        PSTR    pszModuleName,      // OUT
        DWORD   cbModuleName,       // IN
        PSTR    pszSectionName,     // OUT
        DWORD   cbSectionName,      // IN
        PDWORD  puSectionNum );     // OUT
