// plist.h -- implements a class for retrieving performance counter data


#define INDEX_STR_LEN       10


#define PN_PROCESS                          TEXT("Process")
/*
#define PN_PROCESS_CPU                      TEXT("% Processor Time")
#define PN_PROCESS_PRIV                     TEXT("% Privileged Time")
#define PN_PROCESS_USER                     TEXT("% User Time")
#define PN_PROCESS_WORKING_SET              TEXT("Working Set")
#define PN_PROCESS_PEAK_WS                  TEXT("Working Set Peak")
#define PN_PROCESS_PRIO                     TEXT("Priority Base")
#define PN_PROCESS_ELAPSE                   TEXT("Elapsed Time")
*/
#define PN_PROCESS_ID                       TEXT("ID Process")
/*
#define PN_PROCESS_PRIVATE_PAGE             TEXT("Private Bytes")
#define PN_PROCESS_VIRTUAL_SIZE             TEXT("Virtual Bytes")
#define PN_PROCESS_PEAK_VS                  TEXT("Virtual Bytes Peak")
#define PN_PROCESS_FAULT_COUNT              TEXT("Page Faults/sec")

*/
#define PN_THREAD                           TEXT("Thread")
/*
#define PN_THREAD_CPU                       TEXT("% Processor Time")
#define PN_THREAD_PRIV                      TEXT("% Privileged Time")
#define PN_THREAD_USER                      TEXT("% User Time")
#define PN_THREAD_START                     TEXT("Start Address")
#define PN_THREAD_SWITCHES                  TEXT("Context Switches/sec")
#define PN_THREAD_PRIO                      TEXT("Priority Current")
#define PN_THREAD_BASE_PRIO                 TEXT("Priority Base")
#define PN_THREAD_ELAPSE                    TEXT("Elapsed Time")

#define PN_THREAD_DETAILS                   TEXT("Thread Details")
#define PN_THREAD_PC                        TEXT("User PC")

#define PN_IMAGE                            TEXT("Image")
#define PN_IMAGE_NOACCESS                   TEXT("No Access")
#define PN_IMAGE_READONLY                   TEXT("Read Only")
#define PN_IMAGE_READWRITE                  TEXT("Read/Write")
#define PN_IMAGE_WRITECOPY                  TEXT("Write Copy")
#define PN_IMAGE_EXECUTABLE                 TEXT("Executable")
#define PN_IMAGE_EXE_READONLY               TEXT("Exec Read Only")
#define PN_IMAGE_EXE_READWRITE              TEXT("Exec Read/Write")
#define PN_IMAGE_EXE_WRITECOPY              TEXT("Exec Write Copy")


#define PN_PROCESS_ADDRESS_SPACE            TEXT("Process Address Space")
#define PN_PROCESS_PRIVATE_NOACCESS         TEXT("Reserved Space No Access")
#define PN_PROCESS_PRIVATE_READONLY         TEXT("Reserved Space Read Only")
#define PN_PROCESS_PRIVATE_READWRITE        TEXT("Reserved Space Read/Write")
#define PN_PROCESS_PRIVATE_WRITECOPY        TEXT("Reserved Space Write Copy")
#define PN_PROCESS_PRIVATE_EXECUTABLE       TEXT("Reserved Space Executable")
#define PN_PROCESS_PRIVATE_EXE_READONLY     TEXT("Reserved Space Exec Read Only")
#define PN_PROCESS_PRIVATE_EXE_READWRITE    TEXT("Reserved Space Exec Read/Write")
#define PN_PROCESS_PRIVATE_EXE_WRITECOPY    TEXT("Reserved Space Exec Write Copy")


#define PN_PROCESS_MAPPED_NOACCESS          TEXT("Mapped Space No Access")
#define PN_PROCESS_MAPPED_READONLY          TEXT("Mapped Space Read Only")
#define PN_PROCESS_MAPPED_READWRITE         TEXT("Mapped Space Read/Write")
#define PN_PROCESS_MAPPED_WRITECOPY         TEXT("Mapped Space Write Copy")
#define PN_PROCESS_MAPPED_EXECUTABLE        TEXT("Mapped Space Executable")
#define PN_PROCESS_MAPPED_EXE_READONLY      TEXT("Mapped Space Exec Read Only")
#define PN_PROCESS_MAPPED_EXE_READWRITE     TEXT("Mapped Space Exec Read/Write")
#define PN_PROCESS_MAPPED_EXE_WRITECOPY     TEXT("Mapped Space Exec Write Copy")


#define PN_PROCESS_IMAGE_NOACCESS           TEXT("Image Space No Access")
#define PN_PROCESS_IMAGE_READONLY           TEXT("Image Space Read Only")
#define PN_PROCESS_IMAGE_READWRITE          TEXT("Image Space Read/Write")
#define PN_PROCESS_IMAGE_WRITECOPY          TEXT("Image Space Write Copy")
#define PN_PROCESS_IMAGE_EXECUTABLE         TEXT("Image Space Executable")
#define PN_PROCESS_IMAGE_EXE_READONLY       TEXT("Image Space Exec Read Only")
#define PN_PROCESS_IMAGE_EXE_READWRITE      TEXT("Image Space Exec Read/Write")
#define PN_PROCESS_IMAGE_EXE_WRITECOPY      TEXT("Image Space Exec Write Copy")






*/


class CPerfData
{ private:
	int iCount;
	TCHAR           m_szProcessStrings[2*INDEX_STR_LEN];

  public:
    CPerfData();
	~CPerfData();
    BOOL Initialize(CPView *cpTarget);
/*
	int GetCount();
    BOOL FindProcessName(LPSTR lpBuf, int iIndex);
*/    BOOL KillProcessEntry(int iID);

};
