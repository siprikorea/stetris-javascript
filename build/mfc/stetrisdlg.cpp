#include "stdafx.h"
#include "stetris.h"
#include "stetrisdlg.h"
#include "stmemdc.h"
#include "afxdialogex.h"
#include <atlimage.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define ST_WINDOW_WIDTH			1024
#define ST_WINDOW_HEIGHT		768

#define ST_BLOCK_WIDTH			30
#define ST_BLOCK_HEIGHT			30

#define ST_BOARD_POS_X			400
#define ST_BOARD_POS_Y			30

#define ST_NEXT_BLOCK_POS_X		600
#define ST_NEXT_BLOCK_POS_Y		150

#define ST_SCORE_POS_X			750
#define ST_SCORE_POS_Y			30

#define ST_HIGHSCORE_POS_X		600
#define ST_HIGHSCORE_POS_Y		30

BEGIN_MESSAGE_MAP(CSTetrisDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_KEYDOWN()
	ON_WM_TIMER()
	ON_WM_DESTROY()
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
	__super::DoDataExchange(pDX);
}

/************************************************************
 *	@brief		On initalizing dialog
 *	@retval		TRUE
 *	@retval		FALSE
 ************************************************************/
BOOL CSTetrisDlg::OnInitDialog()
{
	__super::OnInitDialog();

	SetIcon(m_hIcon, TRUE);
	SetIcon(m_hIcon, FALSE);

	// Load high score
	int nHighScore = theApp.GetProfileInt(_T(""), _T("High Score"), 0);
	m_Play.GetHighScore()->SetScore(nHighScore);

	// Change dialog size
	SetWindowPos(NULL, -1, -1, 1024, 760, SWP_NOMOVE | SWP_NOACTIVATE | SWP_NOZORDER);

	// Set timer
	SetTimer(0, 1000, NULL);

	return TRUE;
}

/************************************************************
 *	@brief		PreTranslateMessage
 *	@retval		Nothing
 ************************************************************/
BOOL CSTetrisDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch (pMsg->wParam)
		{
		case VK_LEFT:
			m_Play.MoveLeft();
			break;
		case VK_RIGHT:
			m_Play.MoveRight();
			break;
		case VK_DOWN:
			m_Play.MoveDown();
			break;
		case VK_UP:
			m_Play.Rotate();
			break;
		case VK_SPACE:
			m_Play.Drop();
			break;
		case VK_RETURN:
			return TRUE;
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return __super::PreTranslateMessage(pMsg);
}

/************************************************************
 *	@brief		On destroy
 *	@retval		TRUE
 *	@retval		FALSE
 ************************************************************/
void CSTetrisDlg::OnDestroy()
{
	// Save high score
	int nHighScore = m_Play.GetHighScore()->GetScore();
	theApp.WriteProfileInt(_T(""), _T("High Score"), nHighScore);

	__super::OnDestroy();
}

/************************************************************
 *	@brief		On timer
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::OnTimer(UINT_PTR nIDEvent)
{
	// Move down
	m_Play.MoveDown();

	__super::OnTimer(nIDEvent);
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
	CStMemDC MemDC(pDC, &rect);

	// Create memory bitmap
	CBitmap MemBM;
	MemBM.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	// Select memory bitmap
	MemDC.SelectObject(&MemBM);

	// Draw background
	DrawBackground(&MemDC, &rect);

	// Draw board
	CRect boardRect(CPoint(rect.left + ST_BOARD_POS_X, rect.top + ST_BOARD_POS_Y),
		CSize(ST_BLOCK_WIDTH * ST_MAX_BOARD_X, ST_BLOCK_HEIGHT * ST_MAX_BOARD_Y));
	DrawBoard(&MemDC, &boardRect);

	// Draw current block
	DrawBlock(&MemDC, &boardRect, m_Play.GetCurrentBlock());

	// Draw next block
	CRect nextBlockRect(CPoint(rect.left + ST_NEXT_BLOCK_POS_X, rect.top + ST_NEXT_BLOCK_POS_Y),
		CSize(ST_BLOCK_WIDTH * ST_MAX_BLOCK_X, ST_BLOCK_HEIGHT * ST_MAX_BLOCK_Y));
	DrawBlock(&MemDC, &nextBlockRect, m_Play.GetNextBlock());

	// Draw score
	CRect scoreRect(CPoint(rect.left + ST_SCORE_POS_X, rect.top + ST_SCORE_POS_Y),
		CSize(ST_BLOCK_WIDTH * 7, ST_BLOCK_HEIGHT * 2));
	DrawScore(&MemDC, &scoreRect);

	// Draw high score
	CRect highScoreRect(CPoint(rect.left + ST_HIGHSCORE_POS_X, rect.top + ST_HIGHSCORE_POS_Y),
		CSize(ST_BLOCK_WIDTH * 7, ST_BLOCK_HEIGHT * 2));
	DrawHighScore(&MemDC, &highScoreRect);
}

/************************************************************
 *	@brief		Draw background
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawBackground(CDC * pDC, CRect* pRect)
{
	// Create memory DC
	CStMemDC MemDC(pDC, pRect);
	
	// Select background
	MemDC.SelectObject(&m_Background);
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

	// Get block width and height
	int nBlockWidth = bmBlockImages.bmHeight;
	int nBlockHeight = bmBlockImages.bmHeight;

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

	// Draw board
	for (int nBoardY = 0; nBoardY < nYSize; nBoardY++)
	{
		for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
		{
			CRect rect(CPoint(pRect->left + nBoardX * nBlockWidth, pRect->top + nBoardY * nBlockHeight), CSize(nBlockWidth, nBlockHeight));
			pDC->BitBlt(rect.left, rect.top, nBlockWidth, nBlockHeight, &MemDC, nBlockWidth * pBoard->GetValue(nBoardX, nBoardY), 0, SRCCOPY);
		}
	}
}

/************************************************************
 *	@brief		Draw block
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@param[in]	pBlock			Block
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawBlock(CDC* pDC, CRect* pRect, CStBlock* pBlock)
{
	BITMAP bmBlockImages;
	m_BlockImages.GetBitmap(&bmBlockImages);

	// Get block width and height
	int nBlockWidth = bmBlockImages.bmHeight;
	int nBlockHeight = bmBlockImages.bmHeight;

	// Create memory DC
	CDC MemDC;
	MemDC.CreateCompatibleDC(pDC);
	
	// Select block images
	MemDC.SelectObject(&m_BlockImages);

	// Get block size
	int nXSize = pBlock->GetXSize();
	int nYSize = pBlock->GetYSize();

	// Draw block
	for (int nBlockY = 0; nBlockY < nYSize; nBlockY++)
	{
		for (int nBlockX = 0; nBlockX < nXSize; nBlockX++)
		{
			if (pBlock->GetBlock(nBlockX, nBlockY))
			{
				int nXPos = pRect->left + (pBlock->GetXPos() + nBlockX) * nBlockWidth;
				int nYPos = pRect->top + (pBlock->GetYPos() + nBlockY) * nBlockHeight;
				CRect rect(CPoint(nXPos, nYPos), CSize(nBlockWidth, nBlockHeight));
				pDC->BitBlt(rect.left, rect.top, nBlockWidth, nBlockHeight, &MemDC, nBlockWidth * pBlock->GetType(), 0, SRCCOPY);
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
	// Set background mode
	SetBkMode(*pDC, TRANSPARENT);
	// Set text color
	SetTextColor(*pDC, RGB(0, 255, 0));

	// Set font
	CFont font;
	font.CreatePointFont(150, _T("Arial"), pDC);
	pDC->SelectObject(font);

	// Draw title
	CRect titleRect(CPoint(pRect->left, pRect->top), CSize(pRect->Width(), pRect->Height() / 2));
	pDC->DrawText(_T("SCORE"), &titleRect, DT_RIGHT | DT_VCENTER);

	// Draw score
	CString strScore;
	strScore.Format(_T("%u"), m_Play.GetScore()->GetScore());
	CRect scoreRect(CPoint(pRect->left, titleRect.bottom), CSize(pRect->Width(), pRect->Height() / 2));
	pDC->DrawText(strScore, &scoreRect, DT_RIGHT | DT_VCENTER);
}

/************************************************************
 *	@brief		Draw high score
 *	@param[in]	pDC				Device context
 *	@param[in]	pRect			Rectangle
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::DrawHighScore(CDC * pDC, CRect* pRect)
{
	// Set background mode
	SetBkMode(*pDC, TRANSPARENT);
	// Set text color
	SetTextColor(*pDC, RGB(0, 255, 0));

	// Set font
	CFont font;
	font.CreatePointFont(150, _T("Arial"), pDC);
	pDC->SelectObject(font);

	// Draw title
	CRect titleRect(CPoint(pRect->left, pRect->top), CSize(pRect->Width(), pRect->Height() / 2));
	pDC->DrawText(_T("HIGH SCORE"), &titleRect, DT_RIGHT | DT_VCENTER);

	// Draw high score
	CString strHighScore;
	strHighScore.Format(_T("%u"), m_Play.GetHighScore()->GetScore());
	CRect highScoreRect(CPoint(pRect->left, titleRect.bottom), CSize(pRect->Width(), pRect->Height() / 2));
	pDC->DrawText(strHighScore, &highScoreRect, DT_RIGHT | DT_VCENTER);
}

/************************************************************
 *	@brief		Update view
 *	@retval		Nothing
 ************************************************************/
void CSTetrisDlg::UpdateView()
{
	Invalidate(FALSE);
}


