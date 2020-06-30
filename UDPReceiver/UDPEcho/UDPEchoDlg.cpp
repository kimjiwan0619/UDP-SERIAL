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
	DDX_Control(pDX, IDC_LIST1, m_List);
	DDX_Control(pDX, IDC_CHARTCTRL, m_chart);
	DDX_Control(pDX, IDC_MAP, m_map);
	DDX_Control(pDX, IDC_BUTTON_RECEIVE, m_btnReceive);
	DDX_Control(pDX, IDC_BUTTON_SAVE, m_btnSave);
	DDX_Control(pDX, IDC_BUTTON_Load, m_btnLoad);
	DDX_Control(pDX, IDC_BUTTON_SHOW, m_btnShow);
	DDX_Control(pDX, IDC_BUTTON_RESET, m_btnReset);
}

BEGIN_MESSAGE_MAP(CUDPEchoDlg, CDialog)
	//{{AFX_MSG_MAP(CUDPEchoDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CUDPEchoDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_Load, &CUDPEchoDlg::OnBnClickedButtonLoad)
	ON_BN_CLICKED(IDC_BUTTON_RECEIVE, &CUDPEchoDlg::OnBnClickedButtonReceive)
	ON_BN_CLICKED(IDC_BUTTON_RESET, &CUDPEchoDlg::OnBnClickedButtonReset)
	ON_BN_CLICKED(IDC_BUTTON_SHOW, &CUDPEchoDlg::OnBnClickedButtonShow)
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

	//
	ShowWindow(SW_MAXIMIZE);

	// control  position setting
	int width = GetSystemMetrics(SM_CXSCREEN);
	int height = GetSystemMetrics(SM_CYSCREEN);
	m_map.MoveWindow(width / 100, height / 50, (width * 97) / 200, height / 2 - height / 50);
	m_List.MoveWindow(width / 2 + width / 200, height / 50, (width * 97) / 200, height / 2 - height / 50);
	m_chart.MoveWindow(width / 100, height / 2 + height / 50, width - width / 50, (height * 2) / 5);

	//m_btnReset()
	m_btnReceive.MoveWindow(width / 2 + width * 3 / 25, height * 93 / 100, width / 25, height / 40);
	m_btnSave.MoveWindow(width / 2 + width * 3 /25 + width * 2 / 25, height * 93 / 100, width / 25, height / 40);
	m_btnLoad.MoveWindow(width / 2 + width * 3 / 25 + width * 4 / 25, height * 93 / 100, width / 25, height / 40);
	m_btnShow.MoveWindow(width / 2 + width * 3 / 25 + width * 6 / 25, height * 93 / 100, width / 25, height / 40);
	m_btnReset.MoveWindow(width / 2 + width * 3 /25 + width * 8 / 25, height * 93 / 100, width / 25, height / 40);



	//Oscope
	CRect rtGraph;
	GetDlgItem(IDC_CHARTCTRL)->GetWindowRect(rtGraph);

	ScreenToClient(rtGraph);
	m_pOScope = new COScopeCtrl(4);
	m_pOScope->Create(WS_VISIBLE | WS_CHILD, rtGraph, this, IDC_CHARTCTRL);
	m_iRangeLow = -50;
	m_iRangeHigh = 50;
	m_pOScope->SetRanges(m_iRangeLow, m_iRangeHigh);
	m_pOScope->autofitYscale = true;
	m_pOScope->SetYUnits("Temperature");
	m_pOScope->SetXUnits("Time");
	m_pOScope->SetLegendLabel("SID1", 0);
	m_pOScope->SetLegendLabel("SID2", 1);
	m_pOScope->SetLegendLabel("SID3", 2);
	m_pOScope->SetLegendLabel("SID4", 3);
	m_pOScope->SetPlotColor(RGB(255, 0, 0), 0);
	m_pOScope->SetPlotColor(RGB(0, 255, 0), 1);
	m_pOScope->SetPlotColor(RGB(0, 0, 255), 2);
	m_pOScope->SetPlotColor(RGB(255, 255, 255), 3);
	m_pOScope->InvalidateCtrl();
	SetTimer(1000, 1000, NULL);

	//listctrl
	CRect rect;
	m_List.GetClientRect(&rect);

	m_List.InsertColumn(0, _T("GID"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(1, _T("SID"), LVCFMT_CENTER, 50);
	m_List.InsertColumn(2, _T("TEMPERATURE"), LVCFMT_CENTER, 110);
	m_List.InsertColumn(3, _T("GPSDATA"), LVCFMT_LEFT, rect.Width() - 210);

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
		AfxMessageBox("소켓생성이 실패 하였습니다");
		return;
	}
	/*ZeroMemory(m_pUDPSocket->m_sendBuf, sizeof(m_pUDPSocket->m_sendBuf));
	m_pUDPSocket->m_nBytesSent = 0;
	m_pUDPSocket->m_nBytesBufSize = 0;*/

	//소켓을 생성
	if (!m_pUDPSocket->Create(m_port, SOCK_DGRAM))
	{ // 소켓 생성이 실패하면
		wsprintf((LPSTR)m_szError, "소켓 생성실패-> %d", m_pUDPSocket->GetLastError());
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
		m_remoteIP = _T("");
		m_pUDPSocket->Close();
		delete m_pUDPSocket;
		m_pUDPSocket = NULL;
	}
}

void CUDPEchoDlg::ShowLoad()
{
	if (m_arrSensorDataRead[m_iLoadCnt].SOP == 0x2599 && m_arrSensorDataRead[m_iLoadCnt].EOP == 0x1241)
	{
		if (m_arrSensorDataRead[m_iLoadCnt].SID == 1)
		{
			value[0] = m_arrSensorDataRead[m_iLoadCnt].nTemperature;
			m_pOScope->AppendPoints(value, 0);
		}
		else if (m_arrSensorDataRead[m_iLoadCnt].SID == 2)
		{
			value[1] = m_arrSensorDataRead[m_iLoadCnt].nTemperature;
			m_pOScope->AppendPoints(value, 1);
		}
		else if (m_arrSensorDataRead[m_iLoadCnt].SID == 3)
		{
			value[2] = m_arrSensorDataRead[m_iLoadCnt].nTemperature;
			m_pOScope->AppendPoints(value, 2);
		}
		else if (m_arrSensorDataRead[m_iLoadCnt].SID == 4)
		{
			value[3] = m_arrSensorDataRead[m_iLoadCnt].nTemperature;
			m_pOScope->AppendPoints(value, 3);
		}
		CString strGID, strSID, strTemperature;
		strGID.Format(_T("%d"), m_arrSensorDataRead[m_iLoadCnt].GID);
		strSID.Format(_T("%d"), m_arrSensorDataRead[m_iLoadCnt].SID);
		strTemperature.Format(_T("%d"), m_arrSensorDataRead[m_iLoadCnt].nTemperature);
		m_List.InsertItem(m_iLoadListCnt, strGID);
		m_List.SetItemText(m_iLoadListCnt, 1, strSID);
		m_List.SetItemText(m_iLoadListCnt, 2, strTemperature);
		m_List.SetItemText(m_iLoadListCnt, 3, m_arrSensorDataRead[m_iLoadCnt].strGPSDATA);
		int nCount = m_List.GetItemCount();
		m_List.EnsureVisible(nCount - 1, FALSE);
	}
	m_iLoadListCnt++;
	m_iLoadCnt++;
	if (m_iLoadCnt == m_arrSensorDataRead.GetCount())
	{
		KillTimer(1234);
		m_bisLoading = FALSE;
		m_iLoadCnt = 0;
		m_iLoadListCnt = 0;
	}
}

void CUDPEchoDlg::OnDestroy()
{
	CDialog::OnDestroy();

	delete m_pOScope;
	// TODO: Add your message handler code here
}

void CUDPEchoDlg::OnBnClickedButtonSave()
{
	CFileDialog dlg(FALSE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		CStdioFile file;
		CString m_strPath;
		m_strPath = dlg.GetPathName();
		file.Open(m_strPath, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite | CFile::typeBinary);
		for (int i = 0; i < m_arrSensorData.GetCount(); i++)
		{
			file.Write(&m_arrSensorData[i], sizeof(stSensorData));
		}
		file.Close();
	}
}


void CUDPEchoDlg::OnBnClickedButtonLoad()
{
	CFileDialog dlg(TRUE, _T("*.txt"), NULL, OFN_FILEMUSTEXIST | OFN_OVERWRITEPROMPT, _T("TXT Files(*.txt)|*.txt|"), NULL);
	if (dlg.DoModal() == IDOK)
	{
		m_arrSensorDataRead.RemoveAll();
		CStdioFile file;
		CString m_strPath;
		m_strPath = dlg.GetPathName();
		if(file.Open(m_strPath, CFile::modeRead | CFile::typeBinary))
			m_bisLoaded = TRUE;
		for (int i = 0; i < file.GetLength() / 200; i++)
		{
			file.Read(&m_sensorDataRecv, sizeof(stSensorData));
			m_arrSensorDataRead.Add(m_sensorDataRecv);
			TRACE("SOP = %d, GID = %d, SID = %d, TEMPERATURE = %d, DATA = %s, EOP = %d\n",
				m_sensorDataRecv.SOP, m_sensorDataRecv.GID, m_sensorDataRecv.SID, m_sensorDataRecv.nTemperature, m_sensorDataRecv.strGPSDATA, m_sensorDataRecv.EOP);
		}
		file.Close();
	}
}

void CUDPEchoDlg::OnBnClickedButtonReceive()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bisOpened)
	{
		//Socket Create
		m_remoteIP = "192.168.0.34";
		m_port = 0x5245;
		CreateSocket();
		m_bisOpened = TRUE;
		SetDlgItemText(IDC_BUTTON_RECEIVE, "Stop");
	}
	else
	{
		CloseSocket();
		m_bisOpened = FALSE;
		SetDlgItemText(IDC_BUTTON_RECEIVE, "Receive");
	}
}


void CUDPEchoDlg::OnBnClickedButtonReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	if (!m_bisOpened && !m_bisLoading)
	{
		m_pOScope->Reset();
		m_List.DeleteAllItems();
		m_iListcnt = 0;
		m_iLoadListCnt = 0;
	}
}

void CUDPEchoDlg::OnBnClickedButtonShow()
{
	if (!m_bisLoading && m_bisLoaded)
	{
		SetTimer(1234, 100, 0);
		m_bisLoading = TRUE;
		SetDlgItemText(IDC_BUTTON_SHOW, "Stop");
	}
	else
	{
		KillTimer(1234);
		m_bisLoading = FALSE;
		SetDlgItemText(IDC_BUTTON_SHOW, "Show");
	}
	
}

void CUDPEchoDlg::OnTimer(UINT nIDEvent)
{
	if (nIDEvent == 1234)
	{
		ShowLoad();
	}
}


