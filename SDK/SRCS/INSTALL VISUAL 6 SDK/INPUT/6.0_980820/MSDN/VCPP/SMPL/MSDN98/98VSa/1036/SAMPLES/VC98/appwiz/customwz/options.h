// options.cpp : declaration of COptions class.  This class keeps track of
//                options which affect each other (number of "new" steps
//                requested-- that is, steps other than those automatically
//                included from the standard AppWizard sequences; which, if
//                any, AppWizard sequence of steps to include; and the type
//                of the custom AppWizard).
//
// Copyright (c) 1985-1998, Microsoft Corporation. All rights reserved.
//

class COptions
{
public:
	COptions::COptions();
	void DefineDlgMacros();

	int m_nCustomType;
	UINT m_nCustomSteps;
	int m_nApwzSeq;
};

extern COptions g_options;
