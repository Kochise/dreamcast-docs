
#define BOOL int
#define FALSE 0

#define OK_ALLOCATED(obj) \
   ((obj!=(void *)0) && NT_SUCCESS((obj)->m_status))

void * __cdecl operator new(unsigned int nSize, POOL_TYPE iType);


class CUString 
{ 
  private : unsigned char m_bType;
  public: UNICODE_STRING m_String;
          NTSTATUS m_status;
  public:
    CUString(int);
	CUString(PWCHAR);
	CUString(int,int);
	~CUString();
	void Append(UNICODE_STRING *);
    void CUString::CopyTo(CUString *pTarget);
	BOOL operator==(CUString cuArg);
	int inline GetLength() { return m_String.Length; };
	PWCHAR inline GetString() { return m_String.Buffer; };
	void inline SetLength(int i) { m_String.Length = i; };
};

class CRegistry 
{ 
  private: PRTL_QUERY_REGISTRY_TABLE m_pTable;
  public: NTSTATUS m_status;
  public: CRegistry(int iSize);
          ~CRegistry();
		  BOOL QueryDirect(CUString *location,CUString *key, void **pReceiveBuffer, ULONG uType);
          BOOL QueryWithCallback(PRTL_QUERY_REGISTRY_ROUTINE callback,ULONG RelativeTo,PWSTR Path,PVOID Context, PVOID Environment);
          BOOL WriteString(ULONG relativeTo, CUString *pBuffer, CUString *pPath, CUString *pKey);
          BOOL WriteDWord(ULONG relativeTo, void *pBuffer,CUString *pPath,CUString *pKey);

};


class CErrorLogEntry
{
  private: PIO_ERROR_LOG_PACKET m_pPacket;
  public: CErrorLogEntry(PVOID,ULONG,USHORT,ULONG,NTSTATUS,ULONG *,UCHAR);
          ~CErrorLogEntry();
};

