// MFCApplication2_commonPartDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2_commonPartDlg.h"
#include "afxdialogex.h"
#include "resource.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication2commonPartDlg dialog


CMFCApplication2commonPartDlg::CMFCApplication2commonPartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_COMMONPART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2commonPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, edit_box);
	DDX_Control(pDX, IDC_BUTTON2, button2);
	DDX_Control(pDX, IDC_BUTTON3, button3);
}

BEGIN_MESSAGE_MAP(CMFCApplication2commonPartDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2commonPartDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2commonPartDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplication2commonPartDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMFCApplication2commonPartDlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMFCApplication2commonPartDlg message handlers

BOOL CMFCApplication2commonPartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	// TODO: Add extra initialization here
	button2.EnableWindow(false);

	return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2commonPartDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

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
		PAINTSTRUCT pn;
		CDC* pDC = BeginPaint(&pn);
		CBrush cbrush(RGB(0, 0, 255));
		pDC->SelectObject(&cbrush);
		pDC->Ellipse(0, 0, 50, 50);

		LOGFONT logfont;
		logfont.lfHeight = 16;
		logfont.lfWidth = 12;
		logfont.lfItalic = 1;
		logfont.lfStrikeOut = 0;
		logfont.lfUnderline = 0;
		wcscpy_s(logfont.lfFaceName, L"Courier");
		CFont font;
		font.CreateFontIndirect(&logfont);

		pDC->SelectObject(&font);
		pDC->TextOutW(50, 25, L"50");
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication2commonPartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2commonPartDlg::OnBnClickedButton1()
{
	CString sWindowText;
	edit_box.GetWindowText(sWindowText);
	this->SetWindowTextW(sWindowText);
}


void CMFCApplication2commonPartDlg::OnBnClickedButton2()
{
	button2.EnableWindow(false);
	button3.EnableWindow(true);
}


void CMFCApplication2commonPartDlg::OnBnClickedButton3()
{
	this->GetDlgItem(IDC_BUTTON2)->EnableWindow(true);
	this->GetDlgItem(IDC_BUTTON3)->EnableWindow(false);
}


void CMFCApplication2commonPartDlg::OnBnClickedButton4()
{
	auto button = this->GetDlgItem(IDC_BUTTON4);
	CRect sizes_rc;
	button->GetWindowRect(&sizes_rc);
	button->MoveWindow(rand() % 100 + 100, rand() % 100 + 100, sizes_rc.Width(), sizes_rc.Height());
}
