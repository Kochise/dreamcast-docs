////////////////////////////////////////////////////////////////////////////
// Implémentation de la classe TextJump 
//
// Classe permettant de stocker du texte et des données d'URL dans une seule classe
//
// Ceci fait partie des exemples SDK d'Internet Information Server
// Copyright (C) 1997 Microsoft Corporation
// Tous droits réservés.
//
// Ce code source est un complément du matériel de référence Software 
// Development Kit Reference et de la documentation électronique connexe.
//
////////////////////////////////////////////////////////////////////////////

class TextJump 
{
	private String	m_strURL;
	private String	m_strText;

	TextJump(String strURL,String strText)
	{
		m_strURL = strURL;
		m_strText = strText;
	}

	public String getString()	{ return m_strText; }
	public String getURL()		{ return m_strURL; }
}

