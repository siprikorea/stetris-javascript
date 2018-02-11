#pragma once

/************************************************************
 *	@brief		Memory DC
 ************************************************************/
class CStMemDC : public CDC
{
public:
	// Constructor
	CStMemDC(CDC* pDC, CRect* pRect);
	// Destructor
	virtual ~CStMemDC();

protected:
	// DC
	CDC* m_pDC;
	// Rect
	CRect m_Rect;
};
