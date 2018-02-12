#include <stdlib.h>
#include <time.h>
#include "stplay.h"


/************************************************************
 *	@brief		Constructor
 *	@retval		Nothing
 ************************************************************/
CStPlay::CStPlay(CStView* pView)
	: m_CurrentBlock(&m_Board),
	m_NextBlock(&m_Board)
{
    // View
    m_pView = pView;
}

/************************************************************
 *	@brief		Move left
 *	@retval		Nothing
 ************************************************************/
void CStPlay::MoveLeft()
{
    // Move left
	m_CurrentBlock.MoveLeft();
    // Update view
    m_pView->UpdateView();
}

/************************************************************
 *	@brief		Move right
 *	@retval		Nothing
 ************************************************************/
void CStPlay::MoveRight()
{
    // Move right
	m_CurrentBlock.MoveRight();
    // Update view
    m_pView->UpdateView();
}

/************************************************************
 *	@brief		Move down
 *	@retval		Nothing
 ************************************************************/
void CStPlay::MoveDown()
{
    // Move down
    if (!m_CurrentBlock.MoveDown())
    {
		// Set block to board
		SetBlockToBoard();
		// Clear complete line
		ClearCompleteLine();
		// Change block
		ChangeBlock();
    }

	// Add score
	m_Score.AddScore(10);

	// Set high score
	if (m_HighScore.GetScore() < m_Score.GetScore())
		m_HighScore.SetScore(m_Score.GetScore());

    // Update view
    m_pView->UpdateView();
}

/************************************************************
 *	@brief		Rotate
 *	@retval		Nothing
 ************************************************************/
void CStPlay::Rotate()
{
    // Rotate
    m_CurrentBlock.Rotate();
    // Update view
    m_pView->UpdateView();
}

/************************************************************
 *	@brief		Drop
 *	@retval		Nothing
 ************************************************************/
void CStPlay::Drop()
{
	// Drop
	m_CurrentBlock.Drop();
	// Set block to board
	SetBlockToBoard();
	// Clear complete line
	ClearCompleteLine();
	// Change block
	ChangeBlock();

	// Add score
	m_Score.AddScore(100);

	// Set high score
	if (m_HighScore.GetScore() < m_Score.GetScore())
		m_HighScore.SetScore(m_Score.GetScore());

    // Update view
    m_pView->UpdateView();
}

/************************************************************
 *	@brief		Get board
 *	@retval		Nothing
 ************************************************************/
CStBoard* CStPlay::GetBoard()
{
	return &m_Board;
}

/************************************************************
 *	@brief		Get current block
 *	@retval		Nothing
 ************************************************************/
CStBlock* CStPlay::GetCurrentBlock()
{
	return &m_CurrentBlock;
}

/************************************************************
 *	@brief		Get next block
 *	@retval		Nothing
 ************************************************************/
CStBlock* CStPlay::GetNextBlock()
{
	return &m_NextBlock;
}

/************************************************************
 *	@brief		Get score
 *	@retval		Nothing
 ************************************************************/
CStScore* CStPlay::GetScore()
{
	return &m_Score;
}

/************************************************************
 *	@brief		Get high score
 *	@retval		Nothing
 ************************************************************/
CStScore* CStPlay::GetHighScore()
{
	return &m_HighScore;
}

/************************************************************
 *	@brief		Set block to board
 *	@retval		Nothing
 ************************************************************/
void CStPlay::SetBlockToBoard()
{
	// Get block size
	int nXSize = m_CurrentBlock.GetXSize();
	int nYSize = m_CurrentBlock.GetYSize();

	// Set block to board
	for (int nBlockY = 0; nBlockY < nYSize; nBlockY++)
	{
		for (int nBlockX = 0; nBlockX < nXSize; nBlockX++)
		{
			if (m_CurrentBlock.GetBlock(nBlockX, nBlockY))
			{
				m_Board.SetValue(m_CurrentBlock.GetXPos() + nBlockX, m_CurrentBlock.GetYPos() + nBlockY, m_CurrentBlock.GetType());
			}
		}
	}
}

/************************************************************
 *	@brief		Clear complete line
 *	@retval		Nothing
 ************************************************************/
void CStPlay::ClearCompleteLine()
{
	// Get board size
	int nXSize = m_Board.GetXSize();
	int nYSize = m_Board.GetYSize();

	// Check if a line is completed on board
	for (int nBoardY = nYSize -1; nBoardY >= 0; )
	{
		// Count block in one line
		int nBlockCount = 0;
		for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
		{
			if (m_Board.GetValue(nBoardX, nBoardY))
			{
				nBlockCount++;
			}
		}

		// If block is completed
		if (nBlockCount == nXSize)
		{
			// Move blocks from complete block - 1 to first block
			for (int nMoveBoardY = nBoardY; nMoveBoardY > 0; nMoveBoardY--)
			{
				for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
				{
					int nValue = m_Board.GetValue(nBoardX, nMoveBoardY - 1);
					m_Board.SetValue(nBoardX, nMoveBoardY, nValue);
				}
			}

			// Clear first line
			for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
			{
				m_Board.SetValue(nBoardX, 0, 0);
			}

			// Add score
			m_Score.AddScore(1000);

			// Set high score
			if (m_HighScore.GetScore() < m_Score.GetScore())
				m_HighScore.SetScore(m_Score.GetScore());
		}
		// If block is not completed
		else
		{
			// Check next line
			nBoardY--;
		}
	}
}

/************************************************************
 *	@brief		Change block
 *	@retval		Nothing
 ************************************************************/
void CStPlay::ChangeBlock()
{
	// Set current block
	m_CurrentBlock = m_NextBlock;
	// Set next block
	CStBlock nextBlock(&m_Board);
	m_NextBlock = nextBlock;
}
