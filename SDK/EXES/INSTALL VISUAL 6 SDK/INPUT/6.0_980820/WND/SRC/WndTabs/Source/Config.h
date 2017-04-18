/***************************************************************************/
/* NOTE:                                                                   */
/* This document is copyright (c) by Oz Solomonovich, and is bound by the  */
/* MIT open source license (www.opensource.org/licenses/mit-license.html). */
/* See License.txt for more information.                                   */
/***************************************************************************/


// Config.h : header file
//

#ifndef __CONFIG_H__
#define __CONFIG_H__

#ifndef CFG_VAR
#define CFG_VAR(name, type, var, defval) extern type var;
#define CFG_STR(name, var, defval)       extern CString var;
#endif

void CfgSetRegSection(LPCTSTR pszSection);
void CfgGetRegSection(LPCTSTR *ppszSection);

void GetConfiguration();
void WriteConfiguration();

#endif // __CONFIG_H__

#include "CfgVars.h"
