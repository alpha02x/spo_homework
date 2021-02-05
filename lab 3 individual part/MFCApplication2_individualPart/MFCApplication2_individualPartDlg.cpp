// MFCApplication2_individualPartDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication2_individualPart.h"
#include "MFCApplication2_individualPartDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	void DoDataExchange(CDataExchange* pDX) override; // DDX/DDV support

	// Implementation
protected:
DECLARE_MESSAGE_MAP()
public:
	//	afx_msg void OnHelpAbout();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//	ON_COMMAND(ID_HELP_ABOUT, &CAboutDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CMFCApplication2individualPartDlg dialog


CMFCApplication2individualPartDlg::CMFCApplication2individualPartDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION2_INDIVIDUALPART_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication2individualPartDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, listControl);
	DDX_Control(pDX, IDC_RADIO1, adminRadio);
	DDX_Control(pDX, IDC_RADIO2, userRadio);
	DDX_Control(pDX, IDC_RADIO3, guestRadio);
	DDX_Control(pDX, IDC_EDIT1, userNameTextBox);
	DDX_Control(pDX, IDC_BUTTON1, addButton);
	DDX_Control(pDX, IDC_BUTTON2, removeUserButton);
}

BEGIN_MESSAGE_MAP(CMFCApplication2individualPartDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplication2individualPartDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplication2individualPartDlg::OnBnClickedButton2)
	ON_COMMAND(ID_HELP_ABOUT, &CMFCApplication2individualPartDlg::OnHelpAbout)
END_MESSAGE_MAP()


// CMFCApplication2individualPartDlg message handlers

BOOL CMFCApplication2individualPartDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	listControl.InsertColumn(0, L"userName", LVCFMT_LEFT, 200);
	listControl.InsertColumn(1, L"group", LVCFMT_LEFT, 100);
	//
	CImageList* myImageList = new CImageList;
	myImageList->Create(32, 32, ILC_COLOR32, 0, 2);
	myImageList->Add(AfxGetApp()->LoadIcon(IDI_ICONADMIN));
	myImageList->Add(AfxGetApp()->LoadIcon(IDI_ICONUSER));
	myImageList->Add(AfxGetApp()->LoadIcon(IDI_ICONGUEST));
	listControl.SetImageList(myImageList, LVSIL_SMALL);
	// TODO: Add extra initialization here

	return TRUE; // return TRUE  unless you set the focus to a control
}

void CMFCApplication2individualPartDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMFCApplication2individualPartDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication2individualPartDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCApplication2individualPartDlg::OnBnClickedButton1()
{
	wchar_t* username = new wchar_t[1024];
	userNameTextBox.GetWindowTextW(username, MAXINT32);
	if (adminRadio.GetCheck() == 1)
	{
		auto added_item = listControl.InsertItem(0, username, 0);
		listControl.SetItemText(added_item, 1, L"admin");
	}
	if (userRadio.GetCheck() == 1)
	{
		auto added_item = listControl.InsertItem(0, username, 1);
		listControl.SetItemText(added_item, 1, L"user");
	}
	if (guestRadio.GetCheck() == 1)
	{
		auto added_item = listControl.InsertItem(0, username, 2);
		listControl.SetItemText(added_item, 1, L"guest");
	}
}


void CMFCApplication2individualPartDlg::OnBnClickedButton2()
{
	for (int nItem = 0; nItem < listControl.GetItemCount();)
	{
		if (listControl.GetItemState(nItem, LVIS_SELECTED) == LVIS_SELECTED)
			listControl.DeleteItem(nItem);
		else
			nItem++;
	}
}


void CMFCApplication2individualPartDlg::OnHelpAbout()
{
	CAboutDlg about_dlg;
	about_dlg.DoModal();
}
