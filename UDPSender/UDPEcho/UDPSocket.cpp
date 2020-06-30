// UDPSocket.cpp : implementation file
//

#include "stdafx.h"
#include "UDPEcho.h"
#include "UDPSocket.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket

CUDPSocket::CUDPSocket()
{
	
}

CUDPSocket::CUDPSocket(CDialog* pDlg)
{
	m_pDlg = pDlg;
	ZeroMemory(m_sendBuf, sizeof(m_sendBuf));
	m_nBytesSent = 0;
	m_nBytesBufSize = 0;
	
	m_sockAddr = new SOCKADDR_IN;
	m_sockAddr->sin_family = AF_INET;
	m_sockAddr->sin_port = htons(((CUDPEchoDlg*)m_pDlg)->m_remotePort);	
	m_sockAddr->sin_addr.s_addr = htonl(INADDR_ANY);
}
CUDPSocket::~CUDPSocket()
{
	free(m_sockAddr);
	//free(m_pDlg);
	//delete m_pDlg;
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CUDPSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CUDPSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CUDPSocket member functions



void CUDPSocket::SendData()
{
	while(m_nBytesSent < m_nBytesBufSize)
	{
		int dwBytes;
		/*wchar_t *sendBuf = (wchar_t *)m_sendBuf.GetBuffer(0);
		wchar_t *remoteIP = (wchar_t *)(((CUDPEchoDlg*)m_pDlg)->m_remoteIP.GetBuffer(0));
		wchar_t sendTemp[100] = { 0 };
		wchar_t recvTemp[100] = { 0 };*/

		dwBytes = SendTo(m_sendBuf, m_nBytesBufSize - m_nBytesSent,
			((CUDPEchoDlg*)m_pDlg)->m_remotePort, ((CUDPEchoDlg*)m_pDlg)->m_remoteIP.GetBuffer(0));
		// SendTo(보낼메시지, 메시지사이즈, 받을포트, 받을IP)
/*		dwBytes = SendTo(sendBuf + m_nBytesSent, m_nBytesBufSize - m_nBytesSent,
			((CUDPEchoDlg*)m_pDlg)->m_remotePort, remoteIP);
*/		if(dwBytes == SOCKET_ERROR)
		{
			if (GetLastError() ==  WSAEWOULDBLOCK) break;
			else
			{
				TCHAR szError[256];
				wsprintf(szError, "메시지 전송실패-> %d", GetLastError());
				Close();
				AfxMessageBox(szError);
				break;
			}
		}
		else // 에러가 안나면
			m_nBytesSent += dwBytes;
	}
	
	if (m_nBytesSent == m_nBytesBufSize)
	{
		m_nBytesSent = m_nBytesBufSize = 0;
		ZeroMemory(m_sendBuf,sizeof(m_sendBuf));
	}
}
