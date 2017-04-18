#include "stdafx.h"
#include "cemf.h"

//////////////////////////////////////////////////////////////////////////
//constructor
CEMF::CEMF()
{
  m_pEMFHdr = NULL;
  m_pDescStr = NULL;
  m_pPal = NULL;
  m_hemf = NULL;
  m_pLogPal = NULL;
  m_hPal = NULL;
}

//////////////////////////////////////////////////////////////////////////
//destructor
CEMF::~CEMF()
{
  if (m_pEMFHdr)
    free(m_pEMFHdr);
  if (m_pDescStr)
    free(m_pDescStr);
  if (m_pPal)
    free(m_pPal);
  if (m_pLogPal)
    free (m_pLogPal);
  if (m_hPal)
    DeleteObject(m_hPal);
  if (m_hemf)
    DeleteEnhMetaFile(m_hemf);
}

//////////////////////////////////////////////////////////////////////////
//Load()
BOOL CEMF::Load(const char *szFileName)
{
  UINT uiSig;
  //save the filename
  m_szPathName = szFileName;

  //check the file signature to see if this is an enhanced metafile
  CFile cfEMF;
  cfEMF.Open(m_szPathName, CFile::modeRead | CFile::shareDenyWrite);
  cfEMF.Read(&uiSig, sizeof(UINT));
  cfEMF.Close();

  //if this is an EMF then obtain a handle to it
  if (uiSig == EMR_HEADER)
  {
    m_hemf = GetEnhMetaFile(m_szPathName);
	GetEMFCoolStuff();
	LoadPalette();
  }
  else
    m_hemf = NULL;

  //return success
  return ((m_hemf) ? TRUE : FALSE);
}

//////////////////////////////////////////////////////////////////////////
//Draw()
BOOL CEMF::Draw(CDC *pdc, RECT *pRect)
{
  ASSERT(m_hemf);

  BOOL fRet = FALSE;
  CRect crect;
  CPalette *cpalOld = NULL;

  if (m_hemf)
  {
    if (m_hPal) 
	{
      CPalette cpal;
      if ((cpalOld = pdc->SelectPalette(cpal.FromHandle(m_hPal), FALSE)))
	    pdc->RealizePalette();
	}
    fRet = pdc->PlayMetaFile(m_hemf, pRect);

	if (cpalOld)
	  pdc->SelectPalette(cpalOld, FALSE);
  }
  return (fRet);
}

//////////////////////////////////////////////////////////////////////////
//GetEMFCoolStuff()
BOOL CEMF::GetEMFCoolStuff()
{
	if (m_hemf)
	{
	  //
	  //obtain the sizes of the emf header, description string and palette
	  //
	  UINT uiHdrSize = ::GetEnhMetaFileHeader(m_hemf, 0, NULL);
	  UINT uiDescStrSize = ::GetEnhMetaFileDescription(m_hemf, 0, NULL);
	  UINT uiPalEntries = ::GetEnhMetaFilePaletteEntries(m_hemf, 0, NULL);
	  //
	  //if these are lengths > 0 then allocate memory to store them
	  //
	  if (uiHdrSize)
	    m_pEMFHdr = (LPENHMETAHEADER)malloc(uiHdrSize);
	  if (uiDescStrSize)
	    m_pDescStr = (LPTSTR)malloc(uiDescStrSize);
	  if (uiPalEntries)
	    m_pPal = (LPPALETTEENTRY)malloc(uiPalEntries * sizeof(PALETTEENTRY));
	  //
	  //so far the emf seems to be valid so continue
	  //
	  if (uiHdrSize)
	  {
  	    //
	    //get the actual emf header and description string
	    //
	    if (!::GetEnhMetaFileHeader(m_hemf, uiHdrSize, m_pEMFHdr))
          return (FALSE);
		else
		{
		  //
		  //get the description string if it exists
		  //
		  if (uiDescStrSize)
		    ::GetEnhMetaFileDescription(m_hemf, uiDescStrSize, m_pDescStr);
		  //
		  //get the palette if it exists
		  //
		  if (uiPalEntries)
		  {
		    ::GetEnhMetaFilePaletteEntries(m_hemf, uiPalEntries, m_pPal);
		    m_palNumEntries = uiPalEntries;
		  }
		}
      }
   }
   return (TRUE);
}

//////////////////////////////////////////////////////////////////////////
//LoadPalette()
BOOL CEMF::LoadPalette()
{
  if (m_pPal)
  {
     m_pLogPal = (LPLOGPALETTE) malloc(sizeof(LOGPALETTE) +(sizeof (PALETTEENTRY) * m_palNumEntries));
     m_pLogPal->palVersion = 0x300;
     m_pLogPal->palNumEntries = m_palNumEntries;
 
     //copy palette entries into palentry array
     for (int i = 0; i < m_pLogPal->palNumEntries; i++)
       m_pLogPal->palPalEntry[i] = *m_pPal++;

     //position the ptr back to the beginning should we call this
     //code again
     m_pPal -= m_pLogPal->palNumEntries;

     //create the palette
     if ((m_hPal = ::CreatePalette((LPLOGPALETTE)m_pLogPal)))
	   return TRUE;
  } 
  return FALSE;
}
