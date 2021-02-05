// MFCApplication1Dlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "MFCApplication1.h"
#include "MFCApplication1Dlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCApplication1Dlg dialog


CMFCApplication1Dlg::CMFCApplication1Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCAPPLICATION1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplication1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplication1Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()

COLORREF figures_color;
POINT triangle_vertices[3] = {{100, 50}, {150, 150}, {50, 150}};
int ellipse_coordinates[4] = {100, 200, 200, 300};
int drag_mode = 0;
CPoint last_point;
int ontop = 1;

// CMFCApplication1Dlg message handlers

BOOL CMFCApplication1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE); // Set big icon
	SetIcon(m_hIcon, FALSE); // Set small icon

	CColorDialog color_dialog;
	color_dialog.DoModal();
	figures_color = color_dialog.GetColor();

	return TRUE; // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.


void CMFCApplication1Dlg::OnPaint()
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
		Invalidate();
		PAINTSTRUCT pn;
		CDC* pDC = BeginPaint(&pn);
		CBrush cbrush((figures_color));
		pDC->SelectObject(&cbrush);
		if (drag_mode == 1)
		{
			pDC->Ellipse(ellipse_coordinates[0], ellipse_coordinates[1], ellipse_coordinates[2], ellipse_coordinates[3]);
			pDC->Polygon(triangle_vertices, 3);
		}
		else
		{
			pDC->Polygon(triangle_vertices, 3);
			pDC->Ellipse(ellipse_coordinates[0], ellipse_coordinates[1], ellipse_coordinates[2], ellipse_coordinates[3]);
		}
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMFCApplication1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool belongs_to_triangle(CPoint point)
{
	return ((point.x - triangle_vertices[0].x) * (triangle_vertices[1].y - triangle_vertices[0].y) - (point.y - triangle_vertices[0].y) * (triangle_vertices[1].x -
			triangle_vertices[0].x)) * ((triangle_vertices[2].x - triangle_vertices[0].x) * (triangle_vertices[1].y - triangle_vertices[0].y) - (triangle_vertices[2].y -
			triangle_vertices[0].y) * (triangle_vertices[1].x - triangle_vertices[0].x)) >= 0 &&
		((point.x - triangle_vertices[1].x) * (triangle_vertices[2].y - triangle_vertices[1].y) - (point.y - triangle_vertices[1].y) * (triangle_vertices[2].x -
			triangle_vertices[1].x)) * ((triangle_vertices[0].x - triangle_vertices[1].x) * (triangle_vertices[2].y - triangle_vertices[1].y) - (triangle_vertices[0].y -
			triangle_vertices[1].y) * (triangle_vertices[2].x - triangle_vertices[1].x)) >= 0 &&
		((point.x - triangle_vertices[2].x) * (triangle_vertices[0].y - triangle_vertices[2].y) - (point.y - triangle_vertices[2].y) * (triangle_vertices[0].x -
			triangle_vertices[2].x)) * ((triangle_vertices[1].x - triangle_vertices[2].x) * (triangle_vertices[0].y - triangle_vertices[2].y) - (triangle_vertices[1].y -
			triangle_vertices[2].y) * (triangle_vertices[0].x - triangle_vertices[2].x)) >= 0;
}

bool belongs_to_ellipse(CPoint point)
{
	int center_x = ellipse_coordinates[0] + 50;
	int center_y = ellipse_coordinates[1] + 50;

	double distance = sqrt(pow(point.x - center_x, 2) + pow(point.y - center_y, 2));
	return distance < 50;
}

void CMFCApplication1Dlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (belongs_to_ellipse(point) && belongs_to_triangle(point))
	{
		drag_mode = ontop;
		last_point = {point.x, point.y};

		return;
	}

	if (belongs_to_triangle(point))
	{
		drag_mode = 1;
		last_point = {point.x, point.y};
	}

	if (belongs_to_ellipse(point))
	{
		drag_mode = 2;
		last_point = {point.x, point.y};
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}


void CMFCApplication1Dlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	ontop = drag_mode;
	drag_mode = 0;
	CDialogEx::OnLButtonUp(nFlags, point);
}

void CMFCApplication1Dlg::OnMouseMove(UINT nFlags, CPoint point)
{
	CPoint offset = {point.x - last_point.x, point.y - last_point.y};
	if (drag_mode == 1)
	{
		triangle_vertices[0] = {triangle_vertices[0].x + offset.x, triangle_vertices[0].y + offset.y,};
		triangle_vertices[1] = {triangle_vertices[1].x + offset.x, triangle_vertices[1].y + offset.y,};
		triangle_vertices[2] = {triangle_vertices[2].x + offset.x, triangle_vertices[2].y + offset.y,};

		OnPaint();
		last_point = point;
	}
	if (drag_mode == 2)
	{
		ellipse_coordinates[0] = ellipse_coordinates[0] + offset.x;
		ellipse_coordinates[1] = ellipse_coordinates[1] + offset.y;
		ellipse_coordinates[2] = ellipse_coordinates[2] + offset.x;
		ellipse_coordinates[3] = ellipse_coordinates[3] + offset.y;

		OnPaint();
		last_point = point;
	}
	Sleep(15);
	CDialogEx::OnMouseMove(nFlags, point);
}
