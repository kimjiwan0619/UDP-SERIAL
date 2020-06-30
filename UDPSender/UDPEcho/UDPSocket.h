#if !defined(AFX_UDPSOCKET_H__FEA35E6A_5F19_4A53_82EC_1BD577CEB369__INCLUDED_)
#define AFX_UDPSOCKET_H__FEA35E6A_5F19_4A53_82EC_1BD577CEB369__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// UDPSocket.h : header file
//
/////////////////////////////////////////////////////////////////////////////
// CUDPSocket command target
#include "UDPEchoDlg.h"
class CUDPEchoDlg;

class CUDPSocket : public CAsyncSocket
{
// Attributes
public:
	CDialog *m_pDlg;
	//CString m_sendBuf;
	BYTE m_sendBuf[70000];
	int m_nBytesSent;
	int m_nBytesBufSize;
	SOCKADDR_IN *m_sockAddr;
	void SendData();

	
// Operations
public:
	CUDPSocket();
	CUDPSocket(CDialog* pDlg);
	virtual ~CUDPSocket();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPSocket)
	public:
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CUDPSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPSOCKET_H__FEA35E6A_5F19_4A53_82EC_1BD577CEB369__INCLUDED_)
