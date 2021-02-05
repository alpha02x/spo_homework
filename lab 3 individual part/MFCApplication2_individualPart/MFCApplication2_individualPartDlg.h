
// MFCApplication2_individualPartDlg.h : header file
//

#pragma once


// CMFCApplication2individualPartDlg dialog
class CMFCApplication2individualPartDlg : public CDialogEx
{
// Construction
public:
	CMFCApplication2individualPartDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATION2_INDIVIDUALPART_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl listControl;
	CButton adminRadio;
	CButton userRadio;
	CButton guestRadio;
	CEdit userNameTextBox;
	CButton addButton;
	afx_msg void OnBnClickedButton1();
	CButton removeUserButton;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnHelpAbout();
};
