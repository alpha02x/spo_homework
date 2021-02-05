
// MFCApplication2_individualPart.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CMFCApplication2individualPartApp:
// See MFCApplication2_individualPart.cpp for the implementation of this class
//

class CMFCApplication2individualPartApp : public CWinApp
{
public:
	CMFCApplication2individualPartApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CMFCApplication2individualPartApp theApp;
