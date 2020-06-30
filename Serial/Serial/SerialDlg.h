
// SerialDlg.h : 헤더 파일
//

#pragma once
#include "afxwin.h"
#include "PYH_Comm.h"

// CSerialDlg 대화 상자
class CSerialDlg : public CDialogEx
{
// 생성입니다.
public:
	CSerialDlg(CWnd* pParent = NULL);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	DECLARE_MESSAGE_MAP()
public:
	void OnRecieve();
	CComboBox m_comboComport;
	void getSerialPort();
	afx_msg void OnBnClickedCancel();
	CPYH_Comm* m_Comm;
protected:
	afx_msg LRESULT OnReceive(WPARAM wParam, LPARAM lParam);
};
