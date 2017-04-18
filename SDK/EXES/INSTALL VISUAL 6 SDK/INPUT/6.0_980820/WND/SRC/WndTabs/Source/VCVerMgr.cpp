/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/

#include "stdafx.h"
#include "WndTabs.h"

#include <initguid.h>
#define WT_INITGUID
#include "VCVerMgr.h"
#include "AddInComm\AICLoader.h"


////////////////////////////////////////////////////////////////////////////
// IID_IDocuments

// {FB7FDAE3-89B8-11CF-9BE8-00A0C90A632C}
DEFINE_GUID(IID_IDocuments_VC,
0xFB7FDAE3L,0x89B8,0x11CF,0x9B,0xE8,0x00,0xA0,0xC9,0x0A,0x63,0x2C);

// {9093b40f-e2db-44a0-9caa-ed14c73ffdc5}
DEFINE_GUID(IID_IDocuments_EVC3,
0x9093b40fL,0xe2db,0x44a0,0x9c,0xaa,0xed,0x14,0xc7,0x3f,0xfd,0xc5);

// {C3E4138A-0F5E-4CBF-A6B8-65D710B34BEA}
DEFINE_GUID(IID_IDocuments_EVC4,
0xC3E4138AL,0x0F5E,0x4CBF,0xA6,0xB8,0x65,0xD7,0x10,0xB3,0x4B,0xEA);


////////////////////////////////////////////////////////////////////////////
// IID_IGenericDocument

// {FB7FDAE1-89B8-11cf-9BE8-00A0C90A632C}
DEFINE_GUID(IID_IGenericDocument_VC,
0xfb7fdae1L, 0x89b8, 0x11cf, 0x9b, 0xe8, 0x0, 0xa0, 0xc9, 0xa, 0x63, 0x2c);

// {c41998bd-f7b1-49bf-874b-b48d6ce99f12}
DEFINE_GUID(IID_IGenericDocument_EVC3,
0xc41998bdL, 0xf7b1, 0x49bf, 0x87, 0x4b, 0xb4, 0x8d, 0x6c, 0xe9, 0x9f, 0x12);

// {28B45BBB-666C-4950-9F2D-9F271F30AB47}
DEFINE_GUID(IID_IGenericDocument_EVC4,
0x28B45BBBL, 0x666C, 0x4950, 0x9F, 0x2D, 0x9F, 0x27, 0x1F, 0x30, 0xAB, 0x47);


////////////////////////////////////////////////////////////////////////////
// IID_ITextDocument

// {2A6DF201-8240-11CF-AB59-00AA00C091A1}
DEFINE_GUID(IID_ITextDocument_VC,
0x2A6DF201L,0x8240,0x11CF,0xAB,0x59,0x00,0xAA,0x00,0xC0,0x91,0xA1);

// {ae0914db-ac28-4834-9361-6dead7a1adad}
DEFINE_GUID(IID_ITextDocument_EVC3,
0xae0914dbL,0xac28,0x4834,0x93,0x61,0x6d,0xea,0xd7,0xa1,0xad,0xad);

// {4164B30C-8537-4688-9672-EDE6B1957A5F}
DEFINE_GUID(IID_ITextDocument_EVC4,
0x4164B30CL, 0x8537,0x4688,0x96,0x72,0xED,0xE6,0xB1,0x95,0x7A,0x5F);


VC_Versions g_VCVer = Unknown;
const char *g_pszVCExeName = "Unknown";

static const char *s_pszVCExeNames[] = 
{
    "MSDEV.EXE", "EVC.EXE", "CEPB.EXE", "DFDEV.EXE"
};


static struct VerInit
{
    VerInit()
    {
        for (int i = 0; i < countof(s_pszVCExeNames); ++i)
        {
            if (GetModuleHandle(s_pszVCExeNames[i]) != 0)
            {
                g_VCVer = VC_Versions(i);
                g_pszVCExeName = s_pszVCExeNames[i];
                break;
            }
        }

		if (g_VCVer == eVC3)
		{
			// maybe it's eVC4
			char ver[256];
			if(aiclGetModuleVersion("EVC.EXE", (LPSTR)ver))
			{
				if (ver[0] == '4')
				{
					g_VCVer = eVC4;
				}
			}
		}

        switch (g_VCVer)
        {
            case CEPB:
            case VC:
            case VF:
                memcpy(&IID_IDocuments_Resolved, 
                       &IID_IDocuments_VC, sizeof(GUID));
                memcpy(&IID_IGenericDocument_Resolved, 
                       &IID_IGenericDocument_VC, sizeof(GUID));
                memcpy(&IID_ITextDocument_Resolved, 
                       &IID_ITextDocument_VC, sizeof(GUID));
                break;

            case eVC3:
			{
                memcpy(&IID_IDocuments_Resolved, 
                       &IID_IDocuments_EVC3, sizeof(GUID));
                memcpy(&IID_IGenericDocument_Resolved, 
                       &IID_IGenericDocument_EVC3, sizeof(GUID));
                memcpy(&IID_ITextDocument_Resolved, 
                       &IID_ITextDocument_EVC3, sizeof(GUID));
                break;
			}

            case eVC4:
			{
                memcpy(&IID_IDocuments_Resolved, 
                       &IID_IDocuments_EVC4, sizeof(GUID));
                memcpy(&IID_IGenericDocument_Resolved, 
                       &IID_IGenericDocument_EVC4, sizeof(GUID));
                memcpy(&IID_ITextDocument_Resolved, 
                       &IID_ITextDocument_EVC4, sizeof(GUID));
                break;
			}

            default:
                break;
        }
    }
    
} init;
