// UDPEchoDlg.cpp : implementation file
//

#include "stdafx.h"
#include "UDPEcho.h"
#include "UDPEchoDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

	// Dialog Data
		//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPEchoDlg dialog

CUDPEchoDlg::CUDPEchoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CUDPEchoDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CUDPEchoDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CUDPEchoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CUDPEchoDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CUDPEchoDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPEchoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CUDPEchoDlg::OnBnClickedButton1)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CUDPEchoDlg message handlers

BOOL CUDPEchoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_remoteIP = "127.0.0.1";
	m_remotePort = 0x5245;
	m_port = 9000;
	CreateSocket();
	// ������ �ֱ������� ������ ���� Ÿ�̸�(�����) 
	SetTimer(1000, 100, 0);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CUDPEchoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CUDPEchoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM)dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CUDPEchoDlg::OnQueryDragIcon()
{
	return (HCURSOR)m_hIcon;
}

void CUDPEchoDlg::CreateSocket()
{
	BYTE m_szError[255];

	m_pUDPSocket = new CUDPSocket(this);
	if (m_pUDPSocket == NULL)
	{
		AfxMessageBox("���ϻ����� ���� �Ͽ����ϴ�");
		return;
	}
	ZeroMemory(m_pUDPSocket->m_sendBuf, sizeof(m_pUDPSocket->m_sendBuf));
	m_pUDPSocket->m_nBytesSent = 0;
	m_pUDPSocket->m_nBytesBufSize = 0;

	//������ ����
	if (!m_pUDPSocket->Create(0, SOCK_DGRAM))
	{ // ���� ������ �����ϸ�
		wsprintf((LPSTR)m_szError, "���� ��������-> %d", m_pUDPSocket->GetLastError());
		delete m_pUDPSocket;
		m_pUDPSocket = NULL;
		CString szTemp(m_szError);
		AfxMessageBox(szTemp);
		return;
	}
}
void CUDPEchoDlg::CloseSocket()
{
	if (m_pUDPSocket)
	{
		m_recvData = _T("");
		m_sendData = _T("");
		m_remoteIP = _T("");
		m_pUDPSocket->Close();
		delete m_pUDPSocket;
		m_pUDPSocket = NULL;
		KillTimer(1000);
	}
}

void CUDPEchoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here

}


void CUDPEchoDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1000)
	{
		ZeroMemory(&m_sensorData1, sizeof(stSensorData));
		ZeroMemory(&m_sensorData2, sizeof(stSensorData));
		ZeroMemory(&m_sensorData3, sizeof(stSensorData));
		ZeroMemory(&m_sensorData4, sizeof(stSensorData));
		SYSTEMTIME t;
		GetLocalTime(&t);
		CString strData;
		strData.Format(_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"), t.wYear, t.wMonth, t.wDay, t.wHour, t.wMinute, t.wSecond, t.wMilliseconds);
		if (cnt == 0)
		{
			m_sensorData1.SOP = 0x2599;
			m_sensorData1.GID = 0x01;
			m_sensorData1.SID = 0x01;
			m_sensorData1.nTemperature = m_iCount1 - 40;
			memcpy(m_sensorData1.strGPSDATA, strData, strData.GetLength());
			m_sensorData1.EOP = 0x1241;
			memcpy(m_pUDPSocket->m_sendBuf, &m_sensorData1, sizeof(stSensorData));
			m_pUDPSocket->m_nBytesBufSize = sizeof(stSensorData);
			m_pUDPSocket->SendData();
			if (m_b1)
				m_iCount1++;
			else
				m_iCount1--;
			if (m_iCount1 - 40 == 40)
				m_b1 = FALSE;
			if (m_iCount1 - 40 == -40)
				m_b1 = TRUE;
		}
		
		if (cnt == 1)
		{
			m_sensorData2.SOP = 0x2599;
			m_sensorData2.GID = 0x02;
			m_sensorData2.SID = 0x02;
			m_sensorData2.nTemperature = m_iCount2 - 30;
			memcpy(m_sensorData2.strGPSDATA, strData, strData.GetLength());
			m_sensorData2.EOP = 0x1241;
			memcpy(m_pUDPSocket->m_sendBuf, &m_sensorData2, sizeof(stSensorData));
			m_pUDPSocket->m_nBytesBufSize = sizeof(stSensorData);
			m_pUDPSocket->SendData();
			if (m_b2)
				m_iCount2++;
			else
				m_iCount2--;
			if (m_iCount2 - 30 == 30)
				m_b2 = FALSE;
			if (m_iCount2 - 30 == -30)
				m_b2 = TRUE;
		}
		if (cnt == 2)
		{
			m_sensorData3.SOP = 0x2599;
			m_sensorData3.GID = 0x02;
			m_sensorData3.SID = 0x03;
			m_sensorData3.nTemperature = m_iCount3 - 20;
			memcpy(m_sensorData3.strGPSDATA, strData, strData.GetLength());
			m_sensorData3.EOP = 0x1241;
			memcpy(m_pUDPSocket->m_sendBuf, &m_sensorData3, sizeof(stSensorData));
			m_pUDPSocket->m_nBytesBufSize = sizeof(stSensorData);
			m_pUDPSocket->SendData();
			if (m_b3)
				m_iCount3++;
			else
				m_iCount3--;
			if (m_iCount3 - 20 == 20)
				m_b3 = FALSE;
			if (m_iCount3 - 20 == -20)
				m_b3 = TRUE;
		}
		if (cnt == 3)
		{
			m_sensorData4.SOP = 0x2599;
			m_sensorData4.GID = 0x03;
			m_sensorData4.SID = 0x04;
			m_sensorData4.nTemperature = m_iCount4 - 10;
			memcpy(m_sensorData4.strGPSDATA, strData, strData.GetLength());
			m_sensorData4.EOP = 0x1241;
			memcpy(m_pUDPSocket->m_sendBuf, &m_sensorData4, sizeof(stSensorData));
			m_pUDPSocket->m_nBytesBufSize = sizeof(stSensorData);
			m_pUDPSocket->SendData();
			
			if (m_b4)
				m_iCount4++;
			else
				m_iCount4--;
			if (m_iCount4 - 10 == 10)
				m_b4 = FALSE;
			if (m_iCount4 - 10 == -10)
				m_b4 = TRUE;
		}
		cnt++;
		if (cnt == 4)cnt = 0;
	}
}

void CUDPEchoDlg::OnBnClickedButton1()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CloseSocket();
}
