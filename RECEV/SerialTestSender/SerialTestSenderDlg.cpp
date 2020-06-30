
// SerialTestSenderDlg.cpp : 구현 파일
//

#include "stdafx.h"
#include "SerialTestSender.h"
#include "SerialTestSenderDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.


class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CSerialTestSenderDlg 대화 상자



CSerialTestSenderDlg::CSerialTestSenderDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_SERIALTESTSENDER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSerialTestSenderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO1, m_comboCommport);
}

BEGIN_MESSAGE_MAP(CSerialTestSenderDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OPEN, &CSerialTestSenderDlg::OnBnClickedButtonOpen)
	ON_BN_CLICKED(IDC_BUTTON_START, &CSerialTestSenderDlg::OnBnClickedButtonStart)
END_MESSAGE_MAP()


// CSerialTestSenderDlg 메시지 처리기

BOOL CSerialTestSenderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.
	getCommport();

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CSerialTestSenderDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 응용 프로그램의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CSerialTestSenderDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 그리기를 위한 디바이스 컨텍스트입니다.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 클라이언트 사각형에서 아이콘을 가운데에 맞춥니다.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 아이콘을 그립니다.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CSerialTestSenderDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSerialTestSenderDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1000)
	{
		m_commThread.ReadComm((BYTE*)&m_sensorData, sizeof(stSensorData));
		TRACE("SOP = %d, GID = %d, SID = %d, TEMPERATURE = %d, DATA = %s, EOP = %d\n",
			m_sensorData.SOP, m_sensorData.GID, m_sensorData.SID, m_sensorData.nTemperature, m_sensorData.strGPSDATA, m_sensorData.EOP);
	}
}

void CSerialTestSenderDlg::OnBnClickedButtonOpen()
{
	UpdateData(TRUE);
	CString str, strV, strC;
	if (!m_bIsOpened) {
		GetDlgItemText(IDC_COMBO1, str);
		CString com = "\\\\.\\" + str;
		if (m_commThread.OpenPort(com, "19200", "8", "NO", "NO", "1")) {
			m_bIsOpened = TRUE;
			SetDlgItemText(IDC_BUTTON_OPEN, "Close");
		}
	}
	else if (m_bIsOpened) {
		m_commThread.ClosePort();
		m_bIsOpened = FALSE;
		SetDlgItemText(IDC_BUTTON_OPEN, "Open");
	}
}

void CSerialTestSenderDlg::getCommport()
{
	//HKEY_LOCAL_MACHINE\HARDWARE\DEVICEMAP\SERIALCOMM 에  시리얼포트 번호들이 등록되어 있음.  
	HKEY hKey;

	//오픈할 레지스터 키에 대한 기본키 이름  
	//오픈할 레지스터 서브키 이름  
	//레지스터키에 대한 핸들  
	RegOpenKey(HKEY_LOCAL_MACHINE, TEXT("HARDWARE\\DEVICEMAP\\SERIALCOMM"), &hKey);

	TCHAR szData[20], szName[100];
	DWORD index = 0, dwSize = 100, dwSize2 = 20, dwType = REG_SZ;
	m_comboCommport.ResetContent();
	memset(szData, 0x00, sizeof(szData));
	memset(szName, 0x00, sizeof(szName));
	//hKey - 레지스터키 핸들  
	//index - 값을 가져올 인덱스.. 다수의 값이 있을 경우 필요  
	//szName - 항목값이 저장될 배열  
	//dwSize - 배열의 크기  
	while (ERROR_SUCCESS == RegEnumValue(hKey, index, szName, &dwSize, NULL, NULL, NULL, NULL))
	{
		index++;
		//szName-레지터스터 항목의 이름  
		//dwType-항목의 타입, 여기에서는 널로 끝나는 문자열  
		//szData-항목값이 저장될 배열  
		//dwSize2-배열의 크기  
		RegQueryValueEx(hKey, szName, NULL, &dwType, (LPBYTE)szData, &dwSize2);
		m_comboCommport.AddString(CString(szData));
		memset(szData, 0x00, sizeof(szData));
		memset(szName, 0x00, sizeof(szName));
		dwSize = 100;
		dwSize2 = 20;
	}
	RegCloseKey(hKey);
}



void CSerialTestSenderDlg::OnBnClickedButtonStart()
{
	SetTimer(1000, 1000, 0);
}
