#ifndef ILEVELGETTER_H
#define ILEVELGETTER_H

// {BCB53641-F630-11d0-A25F-000000000000}
static const IID IID_ILevelGetter = 
{ 0xbcb53641, 0xf630, 0x11d0, { 0xa2, 0x5f, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 } };

interface ILevelGetter : public IUnknown
{
//first add the three canonical methods
    virtual HRESULT STDMETHODCALLTYPE 
		QueryInterface(REFIID riid, LPVOID* ppvObj) = 0;
    virtual ULONG STDMETHODCALLTYPE AddRef()  = 0;
	virtual ULONG STDMETHODCALLTYPE Release() = 0;
//now add methods for this custom interface
	virtual HRESULT STDMETHODCALLTYPE 
		GetCurrentLevel(long* plCurrentLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE
		GetHighestPossibleSafeLevel(long* plHighestSafeLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE
		GetLowestPossibleSafeLevel(long* plLowestSafeLevel) = 0;
	virtual HRESULT STDMETHODCALLTYPE
		GetTextMessage(BSTR* ppbstrMessage) = 0;
};


#endif

