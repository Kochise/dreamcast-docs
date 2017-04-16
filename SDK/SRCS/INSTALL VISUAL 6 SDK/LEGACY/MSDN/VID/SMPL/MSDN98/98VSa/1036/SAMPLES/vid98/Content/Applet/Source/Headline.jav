////////////////////////////////////////////////////////////////////////////
// Implementatation of CoolHeadLines class
//
// The main applet.
// 
// This is a part of the Internet Information Server SDK Samples
// Copyright (C) 1997 Microsoft Corporation
// All rights reserved.
//
// This source code is only intended as a supplement to the Software 
// Development Kit Reference and related electronic documentation provided.
//
////////////////////////////////////////////////////////////////////////////

import java.applet.*;
import java.awt.*;
import java.util.*;
import java.net.*;
import TextJump;
import DoubleBuffer;

public class CoolHeadLines extends Applet implements Runnable
{
	// constants to gather data from <param> tags
	private final String	PARAM_BackColor = "BackColor";
	private final String	PARAM_TextColor = "TextColor";
	private final String	PARAM_HiliteTextColor = "HiliteTextColor";
	private final String	PARAM_ScrollDelay = "ScrollDelay";
	private final String	PARAM_MessageDelay = "MessageDelay";
	private final String	PARAM_NumItems = "NumItems";
	private final String	PARAM_URLPrefix = "URLPrefix";

	// data from <param> tags
	private Color			m_colBackColor;
	private Color			m_colTextColor;
	private Color			m_colHiliteTextColor;
	private int				m_iScrollDelay = 10;
	private int				m_iMessageDelay = 4;
	private int				m_iNumItems;
	private String			m_strURLPrefix;

	private Thread			m_CoolHeadLines = null;				// worker thread
	private Dimension		m_dimAppletSize;					// size of the containing applet
	private Vector			m_vectData=null;					// vector of TextJump objects
	private Font			m_font;								// font to draw text with
	private FontMetrics		m_fm;								// size of the font
	private int				m_iFontHeight;						// maximum height of font
	private DoubleBuffer	m_buff=null;						// off-screen buffer
	private boolean			m_fStoppedScrolling = false;		// has the image stopped scrolling (when true mouse-clicks are active)
	private int				m_iCurrentMessage = -1;				// what's the current message at the bottom of the screen?
	private int				m_iMaxMessage=0;						// how many messages can the applet display at once?
	private int				m_iOldMessageSelected = -1;			// what was the last message the mouse moved over?
	private int				m_iOldMessageSelectedYOffset = -1;	// what was the last message location on screen?

	////////////////////////////////////////////////////////////////////////////
	// ctor
	public CoolHeadLines()
	{
		// set some default colors
		m_colBackColor =	   new Color(255,255,128);
		m_colTextColor = 	   new Color(0,0,0);
		m_colHiliteTextColor = new Color(255,0,0);
	}

	////////////////////////////////////////////////////////////////////////////
	// getAppletInfo
	// info about this applet
	public String getAppletInfo()
	{
		return "Name: CoolHeadLines\r\n" +
		       "Author: Michael Howard (mikehow@microsoft.com)\r\n" +
		       "Created with Microsoft Visual J++ Version 1.1";
	}

	////////////////////////////////////////////////////////////////////////////
	// getParameterInfo
	// <param> info
	public String[][] getParameterInfo()
	{
		String[][] info =
		{
			{ PARAM_BackColor,			"String",	"Background Color" },
			{ PARAM_TextColor,			"String",	"Text Color" },
			{ PARAM_HiliteTextColor,	"String",	"Hilited Text Color" },
			{ PARAM_ScrollDelay,		"int",		"msec delay between each scroll" },
			{ PARAM_MessageDelay,		"int",		"sec delay between each message" },
			{ PARAM_NumItems,			"int",		"Number of items" },
			{ PARAM_URLPrefix,			"String",	"Prefix for all .htm or .asp files" },
		};

		return info;		
	}

	////////////////////////////////////////////////////////////////////////////
	// init
	// initialize the applet
	public void init()
	{
		String param;

		// background color
		param = getParameter(PARAM_BackColor);
		if (param != null)
			m_colBackColor = getColorFromRGB(param);

		// text color
		param = getParameter(PARAM_TextColor);
		if (param != null)
			m_colTextColor = getColorFromRGB(param);

		// high-lighted text color
		param = getParameter(PARAM_HiliteTextColor);
		if (param != null)
			m_colHiliteTextColor = getColorFromRGB(param);

		// scroll delay in msec
		param = getParameter(PARAM_ScrollDelay);
		if (param != null)
			m_iScrollDelay = Integer.parseInt(param);

		// pause between messages in seconds
		param = getParameter(PARAM_MessageDelay);
		if (param != null)
			m_iMessageDelay = Integer.parseInt(param);

		// number of items to be displayed
		param = getParameter(PARAM_NumItems);
		if (param != null)
			m_iNumItems = Integer.parseInt(param);

		// path for .htm and .asp files
		param = getParameter(PARAM_URLPrefix);
		if (param != null)
			m_strURLPrefix = param;

		// various vars
		m_dimAppletSize = size();
		m_font			= new Font("Helvetica",Font.PLAIN,12);
		m_fm			= getFontMetrics(m_font);
		m_iFontHeight	= m_fm.getMaxDescent() + m_fm.getLeading() + m_fm.getMaxAscent();
		Rectangle r		= new Rectangle(0,0,m_dimAppletSize.width,m_dimAppletSize.height + m_iFontHeight);
		m_buff			= new DoubleBuffer(this,r);

		// fill in the background of the off-screen buffer and the applet
		m_buff.getGraphics().setColor(m_colBackColor);
		m_buff.getGraphics().fillRect(r.x, r.y, r.width, r.height);
		setBackground(m_colBackColor);

		// maximum number of messages
		m_iMaxMessage = 1 +( m_dimAppletSize.height / m_iFontHeight);

		// get all the headlines from the <param> tags
		m_vectData = new Vector();
		for (int i=0; i<m_iNumItems; i++)
		{
			String strText = new String();
			strText = getParameter("Text"+i);

			String strURL = new String();
			strURL = getParameter("URL"+i);
			m_vectData.addElement(new TextJump(strURL,strText));
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// getColorFromRGB
	// converts an RGB triplet (such as "255 255 255") to a Color object
	public Color getColorFromRGB(String strRGB)
	{
		StringTokenizer st  = new StringTokenizer(strRGB);
		int iRed   = Integer.parseInt(st.nextToken());
		int iGreen = Integer.parseInt(st.nextToken());
		int iBlue  = Integer.parseInt(st.nextToken());
		return new Color(iRed,iGreen,iBlue);
	}

	////////////////////////////////////////////////////////////////////////////
	// start
	public void start()
	{
		if (m_CoolHeadLines == null)
		{
			m_CoolHeadLines = new Thread(this);
			m_CoolHeadLines.start();
		}
		else
		{
			// This is so we get a quick refresh when we move back to the homepage
			drawHeadlines();
		}
	}
	
	////////////////////////////////////////////////////////////////////////////
	// stop
	public void stop()
	{
		if (m_CoolHeadLines != null)
		{
			m_CoolHeadLines.stop();
			m_CoolHeadLines = null;
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// run
	// most of the work is done here, essentially loops until the applet dies
	public void run()
	{
		while (true)
		{
			try
			{
				// the applet is about to scroll
				m_fStoppedScrolling = false;

				// there is no old message because we are about to 
				// scroll which invalidates the last message
				m_iOldMessageSelected=-1;
				m_iOldMessageSelectedYOffset=-1;

				// re-draw the headlines
				drawHeadlines();

				// ok, we've stopped scrolling, we can now accept mouse input
				m_fStoppedScrolling = true;

				// ZZZzzzz...
				Thread.sleep(m_iMessageDelay * 1000);
			}
			catch (InterruptedException e)
			{
				stop();
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////
	// drawHeadlines
	// draws the headlines on the screen
	private void drawHeadlines()
	{
		// get the next message and loop round to message #0 
		// if we reach the last message
		m_iCurrentMessage++;
		m_iCurrentMessage %= m_vectData.size();

		// if we are about to display the first message then clear the screen
		if (m_iCurrentMessage == 0)
			for (int i=0; i<m_iMaxMessage; i++)
				scrollOneLine();

		// write in the text in the off-screen buffer. 
		// note the text is drawn BELOW the bottom of the applet so when it
		// gets scrolled it appears to rise from nowhere
		drawString(m_buff.getGraphics(),
				   m_iCurrentMessage,
				   0,
				   m_buff.getSize().height-m_fm.getDescent(),
				   m_colTextColor);

		// scroll one line
		scrollOneLine();
	}

	////////////////////////////////////////////////////////////////////////////
	// drawString
	// draw a string at a given location and place a 'dot' at the start
	private void drawString(Graphics g,String str, int x, int y, Color col)
	{
		int iFontWidth = m_fm.charWidth('W');
		int iOvalWidth = Math.min(iFontWidth/2,m_iFontHeight/2);
		g.setFont(m_font);
		g.setColor(col);
		g.drawString(str,x + iFontWidth,y);
		g.fillOval(x + iOvalWidth/2,y-iOvalWidth-2,iOvalWidth,iOvalWidth);
	}

	////////////////////////////////////////////////////////////////////////////
	// drawString
	// draw a string at a given location and place a 'dot' at the start
	// this version takes an index into the vector to get the string
	private void drawString(Graphics g,int iMsg, int x, int y, Color col)
	{
		drawString(g,getStringFromVector(iMsg),x,y,col);
	}

	////////////////////////////////////////////////////////////////////////////
	// getStringFromVector
	// returns a string from the vector of TextJumps. 
	private String getStringFromVector(int iIndex)
	{
		TextJump t = (TextJump)m_vectData.elementAt(iIndex);
		return (String)t.getString();
	}

	////////////////////////////////////////////////////////////////////////////
	// scrollOneLine
	// 
	private void scrollOneLine()
	{
		// smoothly draw the off-screen buffer
		for (int j=0; j < m_iFontHeight; j++)
		{
			getGraphics().drawImage(m_buff.getImage(),0,-j,this);
			try { Thread.sleep(m_iScrollDelay);}
			catch (InterruptedException e) { }
		}

		Graphics g = m_buff.getGraphics();

		// move image up one-line inside the off-screen buffer
		g.drawImage(m_buff.getImage(),0,-m_iFontHeight,this);

		// erase old text at bottom of image
		g.setColor(m_colBackColor);
		g.fillRect(0,
				   m_dimAppletSize.height,
				   m_dimAppletSize.width,
				   m_dimAppletSize.height+m_iFontHeight);
	}

	////////////////////////////////////////////////////////////////////////////
	// getYOffset
	// based on a mouse y-location determine which text row we are on
	private int getYOffset(int y)
	{
		int iY = (m_dimAppletSize.height - y) / m_iFontHeight;
		return iY;
	}

	////////////////////////////////////////////////////////////////////////////
	// mouseMove
	// highlights a row of text as we move over it
	public boolean mouseMove(Event evt, int x, int y)
	{
		// if the image is still scrolling then bail
		if (!m_fStoppedScrolling)
			return true;

		// get the message we must be over
		int iYOffset = getYOffset(y);
		int iWhichMsg = m_iCurrentMessage - iYOffset;

		// if we are still over the same message then don't do anything
		if (m_iOldMessageSelected == iWhichMsg)
			return true;

		// if there was an old message we were over then re-draw it in it's non-highlighted color
		if (m_iOldMessageSelected >= 0)
		{
			drawString(getGraphics(),
					   m_iOldMessageSelected,
					   0,
					   m_dimAppletSize.height - (m_iOldMessageSelectedYOffset * m_iFontHeight) - m_fm.getDescent() + 1,
					   m_colTextColor);

			if (iWhichMsg < 0)
				m_iOldMessageSelected=-1;
		}

		// if we are over a valid message then draw it in a highlighted color
		if (iWhichMsg >= 0)
		{
			// set the old message to be this message
			m_iOldMessageSelected = iWhichMsg;
			m_iOldMessageSelectedYOffset = iYOffset;

			drawString(getGraphics(),
					   iWhichMsg,
					   0,
					   m_dimAppletSize.height - (iYOffset * m_iFontHeight) - m_fm.getDescent() + 1,
					   m_colHiliteTextColor);

			// put the string on the status line
			String strStatusMsg = getStringFromVector(iWhichMsg) + 
								  " at " + m_strURLPrefix + 
								  "/" + 
								  (((TextJump)m_vectData.elementAt(iWhichMsg)).getURL());
			getAppletContext().showStatus(strStatusMsg);
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////
	// mouseExit
	// if we move the mouse out of the applet and there was an old message
	// highlighted then redraw it as a non-highlighted message
	public boolean mouseExit(Event evt, int x, int y)
	{
		if (!m_fStoppedScrolling)
			return true;

		if (m_iOldMessageSelected >= 0)
		{
			drawString(getGraphics(),
					   m_iOldMessageSelected,
					   0,
					   m_dimAppletSize.height - (m_iOldMessageSelectedYOffset * m_iFontHeight) - m_fm.getDescent() + 1,
					   m_colTextColor);

			m_iOldMessageSelected=-1;
		}

		return true;
	}

	////////////////////////////////////////////////////////////////////////////
	// mouseDown
	// user is interested in a message
	public boolean mouseDown(Event evt, int x, int y)
	{
		// if the image is still scrolling then bail
		if (!m_fStoppedScrolling)
			return true;

		// get the message we must be over
		int iYOffset = getYOffset(y);
		int iWhichMsg = m_iCurrentMessage - iYOffset;

		try
		{
			m_CoolHeadLines.suspend();

 			// Build the url for the sample
			String strSampleURL = m_strURLPrefix + "/" + (((TextJump)m_vectData.elementAt(iWhichMsg)).getURL());
			showStatus(strSampleURL);
			getAppletContext().showDocument(new URL(strSampleURL));

		} catch(MalformedURLException e) { }

		return true;
	}
}
