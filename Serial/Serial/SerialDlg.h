
// SerialDlg.h : ��� ����
//

#pragma once
#include "afxwin.h"
#include "PYH_Comm.h"

// CSerialDlg ��ȭ ����
class CSerialDlg : public CDialogEx
{
// �����Դϴ�.
public:
	CSerialDlg(CWnd* pParent = NULL);	// ǥ�� �������Դϴ�.

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERIAL_DIALOG };
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
