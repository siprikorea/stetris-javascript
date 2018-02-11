#include "stdafx.h"
#include "stmemdc.h"

/************************************************************
 *	@brief		Constructor
 *	@retval		Nothing
 ************************************************************/
CStMemDC::CStMemDC(CDC* pDC, CRect* pRect)
	: m_pDC(pDC),
	m_Rect(*pRect)
{
	CreateCompatibleDC(m_pDC);
}

/************************************************************
 *	@brief		Destructor
 *	@retval		Nothing
 ************************************************************/
CStMemDC::~CStMemDC()
{
	m_pDC->BitBlt(0, 0, m_Rect.Width(), m_Rect.Height(), this, 0, 0, SRCCOPY);
}
