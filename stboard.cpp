#include "stboard.h"

// Constructor
CStBoard::CStBoard()
{
    // X Size
    m_XSize = ST_MAX_BOARD_X;
    // Y Size
    m_YSize = ST_MAX_BOARD_Y;
    // Clear
    Clear();
}

// Clear
void CStBoard::Clear()
{
	for (int x = 0; x < m_XSize; x++)
	{
		for (int y = 0; y < m_YSize; y++)
		{
			m_Board[x][y] = 0;
		}
	}
}

// Get X size
int CStBoard::GetXSize()
{
    return m_XSize;
}

// Get Y size
int CStBoard::GetYSize()
{
    return m_YSize;
}

// Get value
int CStBoard::GetValue(int nX, int nY)
{
    return m_Board[nX][nY];
}

// Set value
void CStBoard::SetValue(int nX, int nY, int nValue)
{
    m_Board[nX][nY] = nValue;
}
