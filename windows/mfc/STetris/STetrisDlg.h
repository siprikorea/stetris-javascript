#pragma once

#include "../../../stview.h"
#include "../../../stplay.h"

class CSTetrisDlg : public CDialog, public CStView
{
public:
	// Constructor
	CSTetrisDlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STETRIS_DIALOG };
#endif

    // Update view
    virtual void UpdateView();

protected:
	// DDX/DDV support
	virtual void DoDataExchange(CDataExchange* pDX);
	// On initalizing dialog
	virtual BOOL OnInitDialog();
	// On painting
	afx_msg void OnPaint();
	// On querying drag icon
	afx_msg HCURSOR OnQueryDragIcon();
	// Message Map
	DECLARE_MESSAGE_MAP()

	// Draw icon
	void DrawIcon(CDC* pDC);
	// Draw all
	void DrawAll(CDC* pDC);
	// Draw background
	void DrawBackground(CDC* pDC, CRect* pRect);
	// Draw board
	void DrawBoard(CDC* pDC, CRect* pRect);
	// Draw current block
	void DrawCurrentBlock(CDC* pDC, CRect* pRect);
	// Draw next block
	void DrawNextBlock(CDC* pDC, CRect* pRect);
	// Draw score
	void DrawScore(CDC* pDC, CRect* pRect);

protected:
	// Icon
	HICON m_hIcon;
	// Background
	CBitmap m_Background;
	// Block images
	CBitmap m_BlockImages;
	// Play
	CStPlay m_Play;
};
