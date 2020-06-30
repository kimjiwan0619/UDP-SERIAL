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
	//m_nBytesSent = 0;
	//m_nBytesBufSize = 0;
	
	m_sockAddr = new SOCKADDR_IN;
	m_sockAddr->sin_family = AF_INET;
	//m_sockAddr->sin_port = htons(((CUDPEchoDlg*)m_pDlg)->m_remotePort);	
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

void CUDPSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	BYTE buf[70000];
	int nRead, addrlen=sizeof(SOCKADDR);
	
	((CUDPEchoDlg*)m_pDlg)->UpdateData(TRUE);
	stSensorData data;
	ZeroMemory(&data, sizeof(stSensorData));
	//nRead = ReceiveFrom(buf, 69999, ((CUPDClientDlg*)m_pDlg)->m_remoteIP,((CUPDClientDlg*)m_pDlg)->m_remotePort);
	nRead=ReceiveFrom(&data, sizeof(stSensorData),  (SOCKADDR*)m_sockAddr, &addrlen, 0);
	
	switch(nRead)
	{
	case 0:
		Close();
		break;
	case SOCKET_ERROR:
		if (GetLastError() != WSAEWOULDBLOCK) // WSAEWOULDBLOCK이되면 걍 나간다
		{
			if(GetLastError() != WSAEMSGSIZE)
			{   // 일반적인 받기 에러처리
				TCHAR szError[256];
				wsprintf(szError, "받기에러 : %d", GetLastError());
				AfxMessageBox(szError);
			}
			else
			{
				AfxMessageBox("데이터그램 사이즈가 너무커서 잘렸습니다.");
				CString szTemp(buf);
				((CUDPEchoDlg*)m_pDlg)->m_recvData += szTemp; // 받은데이터를 메인클래스 m_recvData에 더해준다.
				((CUDPEchoDlg*)m_pDlg)->UpdateData(FALSE);
			}
		}
		break;
	default: // 에러가 아니면
		if (nRead != SOCKET_ERROR && nRead != 0)
		{
			TCHAR szError[256];
			wsprintf(szError, "%d바이트 받음", nRead);
			if (data.SOP == 0x2599 && data.EOP == 0x1241)
			{
				if (data.SID == 1)
				{
					value[0] = data.nTemperature;
					((CUDPEchoDlg*)m_pDlg)->m_pOScope->AppendPoints(value, 0);
				}
				else if (data.SID == 2)
				{
					value[1] = data.nTemperature;
					((CUDPEchoDlg*)m_pDlg)->m_pOScope->AppendPoints(value, 1);
				}
				else if (data.SID == 3)
				{
					value[2] = data.nTemperature;
					((CUDPEchoDlg*)m_pDlg)->m_pOScope->AppendPoints(value, 2);
				}
				else if (data.SID == 4)
				{
					value[3] = data.nTemperature;
			
					((CUDPEchoDlg*)m_pDlg)->m_pOScope->AppendPoints(value, 3);
				}
				((CUDPEchoDlg*)m_pDlg)->m_arrSensorData.Add(data);
				CString strGID, strSID, strTemperature;
				strGID.Format(_T("%d"), data.GID);
				strSID.Format(_T("%d"), data.SID);
				strTemperature.Format(_T("%d"), data.nTemperature);
				((CUDPEchoDlg*)m_pDlg)->m_List.InsertItem(((CUDPEchoDlg*)m_pDlg)->m_iListcnt, strGID);
				((CUDPEchoDlg*)m_pDlg)->m_List.SetItemText(((CUDPEchoDlg*)m_pDlg)->m_iListcnt, 1, strSID);
				((CUDPEchoDlg*)m_pDlg)->m_List.SetItemText(((CUDPEchoDlg*)m_pDlg)->m_iListcnt, 2, strTemperature);
				((CUDPEchoDlg*)m_pDlg)->m_List.SetItemText(((CUDPEchoDlg*)m_pDlg)->m_iListcnt, 3, data.strGPSDATA);
				((CUDPEchoDlg*)m_pDlg)->m_iListcnt++;
				int nCount = ((CUDPEchoDlg*)m_pDlg)->m_List.GetItemCount();
				((CUDPEchoDlg*)m_pDlg)->m_List.EnsureVisible(nCount - 1, FALSE);
			}
				TRACE("SOP = %d, GID = %d, SID = %d, TEMPERATURE = %d, DATA = %s, EOP = %d\n",
					data.SOP, data.GID, data.SID, data.nTemperature, data.strGPSDATA, data.EOP);
		}
	}
	CAsyncSocket::OnReceive(nErrorCode);	
}
