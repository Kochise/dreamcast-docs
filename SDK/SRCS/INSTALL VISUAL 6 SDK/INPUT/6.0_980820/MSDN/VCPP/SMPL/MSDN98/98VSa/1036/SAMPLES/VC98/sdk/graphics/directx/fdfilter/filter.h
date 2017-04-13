#ifndef __FILTER_H__
#define __FILTER_H__



class CFilter
    {
    public:
	virtual HRESULT Transform( PBYTE, int, PBYTE );
	virtual HRESULT SetFormat( PWAVEFORMATEX );
    };


class CGargle : public CFilter
    {
    public:
	CGargle( int nFreq = 0, int nChannels = 0, int nBytesPerSample = 0 );
	~CGargle();
	virtual HRESULT Transform( PBYTE, int, PBYTE );
	virtual HRESULT SetFormat( PWAVEFORMATEX );

    protected:
	enum Shape { SHAPE_TRIANGLE, SHAPE_SQUARE };

	int m_nPhase, m_nGargleRate;
	int m_nBytesPerSample, m_nSamplesPerSec, m_nChannels;

	Shape	m_Shape;

	void MessItAbout( PBYTE, DWORD, PBYTE );
    };


class C3DPosition : public CFilter
    {
    public:
	virtual HRESULT Transform( PWAVEHDR );

    protected:
//	GetPosition( D3DVECTOR * );
    };


#endif	//__FILTER_H__


