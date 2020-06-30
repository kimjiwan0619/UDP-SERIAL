// UDPEchoDlg.h : header file
//

#if !defined(AFX_UDPECHODLG_H__80DCC4B6_BF97_4297_95E6_4CA3CC3C1073__INCLUDED_)
#define AFX_UDPECHODLG_H__80DCC4B6_BF97_4297_95E6_4CA3CC3C1073__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "UDPSocket.h"
/////////////////////////////////////////////////////////////////////////////
// CUDPEchoDlg dialog
#include "UDPEchoDlg.h"
#include <ctime>

class CUDPSocket;
#pragma pack(push, 1) 
typedef struct
{
	unsigned short int SOP;
	unsigned short int GID;
	unsigned short int SID;
	short int nTemperature;
	char strGPSDATA[190];
	unsigned short int EOP;
}stSensorData;
#pragma pack(pop) 

class CUDPEchoDlg : public CDialog
{
// Construction
public:
	CUDPEchoDlg(CWnd* pParent = NULL);	// standard constructor
	
	CUDPSocket* m_pUDPSocket;
	stSensorData m_sensorData1;
	stSensorData m_sensorData2;
	stSensorData m_sensorData3;
	stSensorData m_sensorData4;
	void CreateSocket();
	void CloseSocket();

	UINT m_port;           // 내포트
	UINT m_remotePort;     // 상대편 포트
	CString m_sendData;  // 보낼 데이터
	CString m_recvData;  // 받을 데이터
	CString m_remoteIP;  // 상대방 IP
	int m_iCount1 = 0;
	int m_iCount2 = 0;
	int m_iCount3 = 0;
	int m_iCount4 = 0;
	int cnt = 0;
	BOOL m_b1 = TRUE;
	BOOL m_b2 = TRUE;
	BOOL m_b3 = TRUE;
	BOOL m_b4 = TRUE;

// Dialog Data
	//{{AFX_DATA(CUDPEchoDlg)
	enum { IDD = IDD_UDPECHO_DIALOG };
	CEdit	m_edt;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CUDPEchoDlg)


	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CUDPEchoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnDestroy();
	void OnTimer(UINT_PTR nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPECHODLG_H__80DCC4B6_BF97_4297_95E6_4CA3CC3C1073__INCLUDED_)
