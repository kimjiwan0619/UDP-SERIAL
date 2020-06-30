
// SerialTestSenderDlg.h : ��� ����
//

#pragma once
#include "CommThread.h"
#include "afxwin.h"

// CSerialTestSenderDlg ��ȭ ����
typedef struct
{
	unsigned short int SOP;
	unsigned short int GID;
	unsigned short int SID;
	short int nTemperature;
	char strGPSDATA[190];
	unsigned short int EOP;
}stSensorData;
class CSerialTestSenderDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSerialTestSenderDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.
	CCommThread m_commThread;
// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIALTESTSENDER_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �����Դϴ�.


// �����Դϴ�.
protected:
	HICON m_hIcon;

	// ������ �޽��� �� �Լ�
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonOpen();
	afx_msg void OnBnClickedButtonStart();
	BOOL m_bIsOpened;
	void getCommport();

	stSensorData m_sensorData;

	int m_icnt = 0;
	int m_iCount1 = 0;
	int m_iCount2 = 0;
	int m_iCount3 = 0;
	int m_iCount4 = 0;

	BOOL m_b1 = TRUE;
	BOOL m_b2 = TRUE;
	BOOL m_b3 = TRUE;
	BOOL m_b4 = TRUE;
	CComboBox m_comboCommport;
};
