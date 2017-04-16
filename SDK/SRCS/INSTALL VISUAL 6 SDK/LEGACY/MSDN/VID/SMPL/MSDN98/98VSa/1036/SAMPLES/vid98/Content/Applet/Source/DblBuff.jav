////////////////////////////////////////////////////////////////////////////
// Implémentation de la classe DoubleBuffer
//
// Encapsule simplement les données requises pour stocker les images hors champ.
// 
// Ceci fait partie des exemples SDK d'Internet Information Server
// Copyright (C) 1997 Microsoft Corporation
// Tous droits réservés.
//
// Ce code source est un complément du matériel de référence Software 
// Development Kit Reference et de la documentation électronique connexe.
//
////////////////////////////////////////////////////////////////////////////

import java.applet.*;
import java.awt.*;

class DoubleBuffer 
{
	private Image		m_imgBuff;				
    private Graphics	m_gBuff;			
	private Rectangle	m_rect;
	private Applet		m_app;

	//////////////////////////////////////////////////////////////////////////////////
	DoubleBuffer(Applet app, Rectangle rect)
	{
		m_rect = rect;
		m_app = app;

		// génère un tampon pour l'image hors champ
		m_imgBuff = m_app.createImage(rect.width,rect.height);
		m_gBuff = m_imgBuff.getGraphics();
	}

	//////////////////////////////////////////////////////////////////////////////////
	public Rectangle getSize()		{ return m_rect; }
	public Image getImage()			{ return m_imgBuff; }
	public Graphics getGraphics()	{ return m_gBuff; }
}

