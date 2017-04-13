#ifndef __PARAMS_H
#define __PARAMS_H

class ATL_NO_VTABLE CParameter
{
public:

	CParameter(DWORD iParam) { m_iParam = iParam; }
	DWORD   Index() { return m_iParam; }

	virtual BOOL    FToVariant(VARIANT& varDest) = 0;
	virtual ~CParameter()
	{
	}

	DWORD   m_iParam;
};

#if 0
class CBoundParam : public CParameter
{
public:
	CBoundParam();

	CBoundParam(SWORD fParamType, SWORD fCType, SWORD fSqlType,
				UDWORD cbColDef,  SWORD ibScale, PTR rgbValue,
				SDWORD cbValueMax, SDWORD* pcbValue, DWORD iParam);

	virtual ~CBoundParam();

	virtual BOOL    FToVariant(VARIANT& varDest);

	SWORD   m_fParamType;
	SWORD   m_fCType;
	SWORD   m_fSqlType;
	UDWORD  m_cbColDef;
	SWORD   m_ibScale;
	PTR     m_rgbValue;
	SDWORD  m_cbValueMax;
	SDWORD* m_pcbValue;
};
#endif

class CByValParameter : public CParameter
{
public:

	CByValParameter(DWORD iParam, LPTSTR szParam) : CParameter(iParam)
	{
		m_szParameter = szParam;
	}

	virtual BOOL    FToVariant(VARIANT& varDest);
	virtual ~CByValParameter();

	LPTSTR m_szParameter;
};

#endif //__PARAMS_H
