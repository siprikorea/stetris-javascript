#include "stdafx.h"
#include "STetris.h"
#include "STetrisDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BEGIN_MESSAGE_MAP(CSTetrisDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

CSTetrisDlg::CSTetrisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STETRIS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BOOL CSTetrisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Change dialog size
	SetWindowPos(NULL, -1, -1, 1024, 760, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	return TRUE;
}

void CSTetrisDlg::OnPaint()
{
	CPaintDC dc(this);

	if (IsIconic())
		DrawIcon(&dc);
	else
		DrawTetris(&dc);
}

HCURSOR CSTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CSTetrisDlg::DrawIcon(CDC * pDC)
{
	SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(pDC->GetSafeHdc()), 0);

	int cxIcon = GetSystemMetrics(SM_CXICON);
	int cyIcon = GetSystemMetrics(SM_CYICON);
	CRect rect;
	GetClientRect(&rect);
	int x = (rect.Width() - cxIcon + 1) / 2;
	int y = (rect.Height() - cyIcon + 1) / 2;

	pDC->DrawIcon(x, y, m_hIcon);
}

void CSTetrisDlg::DrawTetris(CDC * pDC)
{
	// Get client rect
	CRect rect;
	GetClientRect(&rect);

	// Draw background
	CBrush brush(RGB(0, 0, 0));
	pDC->FillRect(&rect, &brush);

	// Draw board
	CPoint boardPoint(rect.left + 50, rect.top + 50);
	CSize boardSize(400, 600);
	CRect boardRect(boardPoint, boardSize);
	DrawBoard(pDC, &boardRect);

	// Draw next block
	CRect nextBlockRect = rect;
	DrawNextBlock(pDC, &nextBlockRect);

	// Draw score
	CRect scoreRect = rect;
	DrawScore(pDC, &scoreRect);
}

void CSTetrisDlg::DrawBoard(CDC * pDC, CRect* pRect)
{
	// Draw background
	CBrush brush(RGB(255, 255, 255));
	pDC->FillRect(pRect, &brush);
}

void CSTetrisDlg::DrawNextBlock(CDC * pDC, CRect* pRect)
{
}

void CSTetrisDlg::DrawScore(CDC * pDC, CRect* pRect)
{
}
