
#ifndef __CCTLREG_H__
#define __CCTLREG_H__

class CCtlReg {
	public:
		CCtlReg(CString PathName) ;
		~CCtlReg() ;
		
		BOOL Register() ;
		BOOL Unregister() ;

	protected:
		BOOL SupportsSelfRegister();

	protected:
		CString m_strPathName ;
	
};
	
#endif //__CCTLREG_H__
