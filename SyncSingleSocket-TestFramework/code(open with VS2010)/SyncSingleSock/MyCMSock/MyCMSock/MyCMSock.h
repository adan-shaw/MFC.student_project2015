
// MyCMSock.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'stdafx.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// MyCMSockApp:
// See MyCMSock.cpp for the implementation of this class
//

class MyCMSockApp : public CWinApp
{
public:
	MyCMSockApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern MyCMSockApp theApp;