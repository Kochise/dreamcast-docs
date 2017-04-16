// helper.h -- 

#define CALLCONV CM_LOCAL

typedef struct {
HVM VMHandle;
PTCB ThreadHandle;
DWORD dwFlags;
} CONTBLOCK;

#define VXDLOCATION "c:\\chicddk\\custom\\callback\\messages\\appy\\callback.386"
#define DLLLOCATION "c:\\chicddk\\custom\\callback\\messages\\frontend\\16bit\\receiver\\receiver.dll"


// defines for dwFlags

#define THREAD_CREATED 0
#define VM_CREATED 1


#define VxD_Prolog \
    struct Client_Word_Reg_Struc *crRegs; \
    _asm mov eax,ebp \
    _asm mov ebp,esp  \
    _asm sub esp, __LOCAL_SIZE \
    _asm mov [crRegs],eax;

#define VxD_Epilog \
    _asm mov eax,[crRegs] \
    _asm mov esp, ebp \
    _asm mov ebp,eax \
    _asm ret;
