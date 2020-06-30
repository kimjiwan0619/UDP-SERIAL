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
#include "OScopeCtrl.h"
#include "afxcmn.h"
#include "afxwin.h"
class CUDPSocket;

#pragma pack(push, 1) 
typedef struct
{
	unsigned short int SOP;
	unsigned short int GID;
	unsigned short int SID;
	short int nTemperature;
	CHAR strGPSDATA[190];
	unsigned short int EOP;
}stSensorData;
#pragma pack(pop) 

class CUDPEchoDlg : public CDialog
{
// Construction
public:
	CUDPEchoDlg(CWnd* pParent = NULL);	// standard constructor

	CArray<stSensorData, const stSensorData&> m_arrSensorData;
	CArray<stSensorData, const stSensorData&> m_arrSensorDataRead;

	CUDPSocket* m_pUDPSocket;
	stSensorData m_sensorData;
	stSensorData m_sensorDataRecv;
	void CreateSocket();
	void CloseSocket();
	void ShowLoad();
	UINT m_port;           // 내포트
	CString m_recvData;  // 받을 데이터
	CString m_remoteIP;  // 상대방 IP

	COScopeCtrl* m_pOScope;

	int m_iRangeLow;
	int m_iRangeHigh;
	int m_iLoadCnt = 0;
	int m_iLoadListCnt = 0;
	int m_iListcnt = 0;
	double value[4] = { 0 };

	BOOL m_bisOpened = FALSE;
	BOOL m_bisLoading = FALSE;
	BOOL m_bisLoaded = FALSE;

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
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_List;
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonLoad();
	afx_msg void OnBnClickedButtonReceive();
	afx_msg void OnBnClickedButtonReset();
	afx_msg void OnBnClickedButtonShow();
	void OnTimer(UINT nIDEvent);
	CStatic m_chart;
	CStatic m_map;
	CButton m_btnReceive;
	CButton m_btnSave;
	CButton m_btnLoad;
	CButton m_btnShow;
	CButton m_btnReset;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_UDPECHODLG_H__80DCC4B6_BF97_4297_95E6_4CA3CC3C1073__INCLUDED_)
