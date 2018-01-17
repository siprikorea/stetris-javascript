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
	: CDialog(IDD_STETRIS_DIALOG, pParent),
	m_Play(this)
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
		DrawAll(&dc);
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

void CSTetrisDlg::DrawAll(CDC * pDC)
{
	// Get client rect
	CRect rect;
	GetClientRect(&rect);
	
	// Create memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);

	// Create memory bitmap
	CBitmap MemBM;
	MemBM.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	// Select memory bitmap
	MemDC.SelectObject(&MemBM);

	// Draw background
	DrawBackground(&MemDC, &rect);

	// Draw board
	CRect boardRect(CPoint(rect.left + 50, rect.top + 50), CSize(400, 600));
	DrawBoard(&MemDC, &boardRect);

	// Draw current block
	DrawCurrentBlock(&MemDC, &boardRect);

	// Draw next block
	CRect nextBlockRect(CPoint(rect.left + 500, rect.top + 50), CSize(100, 100));
	DrawNextBlock(&MemDC, &nextBlockRect);

	// Draw score
	CRect scoreRect(CPoint(rect.left + 700, rect.top + 50), CSize(200, 50));
	DrawScore(&MemDC, &scoreRect);

	// Bitblt
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
}

void CSTetrisDlg::DrawBackground(CDC * pDC, CRect* pRect)
{
	CBrush brush(RGB(0, 0, 0));
	pDC->FillRect(pRect, &brush);
}

void CSTetrisDlg::DrawBoard(CDC * pDC, CRect* pRect)
{
	CBrush brush(RGB(255, 255, 255));
	pDC->FillRect(pRect, &brush);

	// Get board
	CStBoard* pBoard = m_Play.GetBoard();

	// Get board size
	int nXSize = pBoard->GetXSize();
	int nYSize = pBoard->GetYSize();

	// Get board width and height
	int nWidth = pRect->Width() / nXSize;
	int nHeight = pRect->Height() / nYSize;

	// Draw board
	for (int x = 0; x < nXSize; x++)
	{
		for (int y = 0; y < nYSize; y++)
		{
			CRect rect(CPoint(x * nWidth, y * nHeight), CSize(nWidth, nHeight));
		}
	}
}

void CSTetrisDlg::DrawCurrentBlock(CDC* pDC, CRect* pRect)
{
}

void CSTetrisDlg::DrawNextBlock(CDC * pDC, CRect* pRect)
{
	CBrush brush(RGB(255, 255, 255));
	pDC->FillRect(pRect, &brush);

	// Get next block
	CStBlock* pBlock = m_Play.GetNextBlock();

	// Get board width and height
	int nWidth = pRect->Width() / ST_MAX_BLOCK_X;
	int nHeight = pRect->Height() / ST_MAX_BLOCK_Y;

	// Draw board
	for (int x = 0; x < ST_MAX_BLOCK_X; x++)
	{
		for (int y = 0; y < ST_MAX_BLOCK_Y; y++)
		{
			if (pBlock->GetBlock(x, y))
			{
				CRect rect(CPoint(pRect->left + x * nWidth, pRect->top + y * nHeight), CSize(nWidth, nHeight));
				CBrush brushBlock(RGB(255, 127, 0));
				pDC->FillRect(rect, &brushBlock);
			}
		}
	}
}

void CSTetrisDlg::DrawScore(CDC * pDC, CRect* pRect)
{
	CBrush brush(RGB(255, 255, 255));
	pDC->FillRect(pRect, &brush);
}

void CSTetrisDlg::UpdateView()
{
	Invalidate();
}
