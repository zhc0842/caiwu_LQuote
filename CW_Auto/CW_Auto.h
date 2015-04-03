
// CW_Auto.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CCW_AutoApp:
// See CW_Auto.cpp for the implementation of this class
//

class CCW_AutoApp : public CWinApp
{
public:
	CCW_AutoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()

};

extern CCW_AutoApp theApp;