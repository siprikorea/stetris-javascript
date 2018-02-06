#include "stdafx.h"
#include "STetris.h"
#include "STetrisDlg.h"
#include "afxdialogex.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ST_WINDOW_WIDTH			1024
#define ST_WINDOW_HEIGHT		768

#define ST_BOARD_POS_X			400
#define ST_BOARD_POS_Y			30
#define ST_BOARD_WIDTH			300
#define ST_BOARD_HEIGHT			600

#define ST_NEXT_BLOCK_POS_X		850
#define ST_NEXT_BLOCK_POS_Y		200
#define ST_NEXT_BLOCK_WIDTH		100
#define ST_NEXT_BLOCK_HEIGHT	100

#define ST_SCORE_POS_X			850
#define ST_SCORE_POS_Y			30
#define ST_SCORE_WIDTH			150
#define ST_SCORE_HEIGHT			50

BEGIN_MESSAGE_MAP(CSTetrisDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
END_MESSAGE_MAP()

/************************************************************
 *	@brief		Constructor
 *	@retval		Nothing
 ************************************************************/
CSTetrisDlg::CSTetrisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_STETRIS_DIALOG, pParent),
	m_Play(this)
{
	// Icon
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	// Background
	m_Background.LoadBitmapW(IDB_STETRIS_BACKGROUND);
	// Block images
	m_BlockImages.LoadBitmapW(IDB_STETRIS_BLOCK);
}

/************************************************************
 *	@brief		DDX/DDV support
 *	@param[in]	pDX				DDX
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

/************************************************************
 *	@brief		On initalizing dialog
 *	@retval		TRUE
 *	@retval		FALSE
 ************************************************************/
BOOL CSTetrisDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Change dialog size
	SetWindowPos(NULL, -1, -1, 1024, 760, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	return TRUE;
}

/************************************************************
 *	@brief		On painting
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::OnPaint()
{
	CPaintDC dc(this);

	if (IsIconic())
		DrawIcon(&dc);
	else
		DrawAll(&dc);
}

/************************************************************
 *	@brief		On quering drag icon
 *	@retval		HCURSOR			Cursor handle
 ************************************************************/
HCURSOR CSTetrisDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

/************************************************************
 *	@brief		Draw icon
 *	@param[in]	pDC				Device context
 *	@retval		Nothing
 ************************************************************/
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

/************************************************************
 *	@brief		Draw all
 *	@param[in]	pDC				Device context
 *	@retval		Nothing
 ************************************************************/
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
	CRect boardRect(CPoint(rect.left + ST_BOARD_POS_X, rect.top + ST_BOARD_POS_Y), CSize(ST_BOARD_WIDTH, ST_BOARD_HEIGHT));
	DrawBoard(&MemDC, &boardRect);

	// Draw current block
	DrawCurrentBlock(&MemDC, &boardRect);

	// Draw next block
	CRect nextBlockRect(CPoint(rect.left + ST_NEXT_BLOCK_POS_X, rect.top + ST_NEXT_BLOCK_POS_Y), CSize(ST_NEXT_BLOCK_WIDTH, ST_NEXT_BLOCK_HEIGHT));
	DrawNextBlock(&MemDC, &nextBlockRect);

	// Draw score
	CRect scoreRect(CPoint(rect.left + ST_SCORE_POS_X, rect.top + ST_SCORE_POS_Y), CSize(ST_SCORE_WIDTH, ST_SCORE_HEIGHT));
	DrawScore(&MemDC, &scoreRect);

	// Bitblt
	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);
}

/************************************************************
 *	@brief		Draw background
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawBackground(CDC * pDC, CRect* pRect)
{
	// Get bitmap
	BITMAP bmBackground;
	m_BlockImages.GetBitmap(&bmBackground);

	// Create memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	// Select background
	MemDC.SelectObject(&m_Background);

	// Draw image
	pDC->BitBlt(pRect->left, pRect->top, 1024, 768, &MemDC, 0, 0, SRCCOPY);
}

/************************************************************
 *	@brief		Draw board
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawBoard(CDC * pDC, CRect* pRect)
{
	BITMAP bmBlockImages;
	m_BlockImages.GetBitmap(&bmBlockImages);

	// Create memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	// Select block images
	MemDC.SelectObject(&m_BlockImages);

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
			CRect rect(CPoint(pRect->left + x * nWidth, pRect->top + y * nHeight), CSize(nWidth, nHeight));
			pDC->BitBlt(rect.left, rect.top, bmBlockImages.bmHeight, bmBlockImages.bmHeight, &MemDC, pBoard->GetValue(x, y) * bmBlockImages.bmHeight, 0, SRCCOPY);
		}
	}
}

/************************************************************
 *	@brief		Draw current block
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawCurrentBlock(CDC* pDC, CRect* pRect)
{
}

/************************************************************
 *	@brief		Draw next block
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawNextBlock(CDC * pDC, CRect* pRect)
{
	BITMAP bmBlockImages;
	m_BlockImages.GetBitmap(&bmBlockImages);

	// Create memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	// Select block images
	MemDC.SelectObject(&m_BlockImages);

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
				pDC->BitBlt(rect.left, rect.top, bmBlockImages.bmHeight, bmBlockImages.bmHeight, &MemDC, pBlock->GetType() * bmBlockImages.bmHeight, 0, SRCCOPY);
			}
		}
	}
}

/************************************************************
 *	@brief		Draw score
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawScore(CDC * pDC, CRect* pRect)
{
	CBrush brush(RGB(255, 255, 255));
	pDC->FillRect(pRect, &brush);
}

/************************************************************
 *	@brief		Update view
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::UpdateView()
{
	Invalidate();
}
