#pragma once

class CSTetrisDlg : public CDialog
{
public:
	// Constructor
	CSTetrisDlg(CWnd* pParent = NULL);

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STETRIS_DIALOG };
#endif

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
	// Draw tetris
	void DrawTetris(CDC* pDC);
	// Draw board
	void DrawBoard(CDC* pDC, CRect* pRect);
	// Draw next block
	void DrawNextBlock(CDC* pDC, CRect* pRect);
	// Draw score
	void DrawScore(CDC* pDC, CRect* pRect);
protected:
	HICON m_hIcon;

};
