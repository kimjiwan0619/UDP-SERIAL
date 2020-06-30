// UDPEcho.h : main header file for the UDPECHO application
//

#if !defined(AFX_UDPECHO_H__89206F80_3D68_4C7D_B7C7_DD1E1D94BBDD__INCLUDED_)
#define AFX_UDPECHO_H__89206F80_3D68_4C7D_B7C7_DD1E1D94BBDD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CUDPEchoApp:
// See UDPEcho.cpp for the implementation of this class
//

class CUDPEchoApp : public CWinApp
{
public:
	CUDPEchoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPEchoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CUDPEchoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPECHO_H__89206F80_3D68_4C7D_B7C7_DD1E1D94BBDD__INCLUDED_)
