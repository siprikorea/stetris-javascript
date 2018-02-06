#include <stdlib.h>
#include <time.h>
#include "stplay.h"
#include "thread/thread.h"


// Constructor
CStPlay::CStPlay(CStView* pView)
{
    // View
    m_pView = pView;
    // Set board
    m_CurrentBlock.SetBoard(&m_Board);
	// Thread
	ThreadObject::New(CStPlay::Play, this, &m_pThread, "Play");
}

// Play
void CStPlay::Play(void *pPlay)
{
	((CStPlay*)pPlay)->Play();
}

#include <Windows.h>

// Play
void CStPlay::Play()
{
	while (1)
	{
		Sleep(500);
//		MoveDown();
	}
}

// Move left
void CStPlay::MoveLeft()
{
    // Move left
	m_CurrentBlock.MoveLeft();
    // Update view
    m_pView->UpdateView();
}

// Move right
void CStPlay::MoveRight()
{
    // Move right
	m_CurrentBlock.MoveRight();
    // Update view
    m_pView->UpdateView();
}

// Move down
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

    // Update view
    m_pView->UpdateView();
}

// Rotate
void CStPlay::Rotate()
{
    // Rotate
    m_CurrentBlock.Rotate();
    // Update view
    m_pView->UpdateView();
}

// Drop
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

    // Update view
    m_pView->UpdateView();
}

// Get board
CStBoard* CStPlay::GetBoard()
{
	return &m_Board;
}

// Get current block
CStBlock* CStPlay::GetCurrentBlock()
{
	return &m_CurrentBlock;
}

// Get next block
CStBlock* CStPlay::GetNextBlock()
{
	return &m_NextBlock;
}

// Set block to board
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

// Clear complete line
void CStPlay::ClearCompleteLine()
{
	// Get board size
	int nXSize = m_Board.GetXSize();
	int nYSize = m_Board.GetYSize();

	for (int nBoardY = nYSize; nBoardY >= 0; nBoardY--)
	{
		int nBlockCount = 0;
		for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
		{
			if (m_Board.GetValue(nBoardX, nBoardY))
			{
				nBlockCount++;
			}
		}

		if (nBlockCount == m_Board.GetXSize())
		{
			for (int nMoveBoardY = nBoardY; nMoveBoardY >= 0; nMoveBoardY--)
			{
				for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
				{
					int nValue = m_Board.GetValue(nBoardX, nMoveBoardY - 1);
					m_Board.SetValue(nBoardX, nMoveBoardY, nValue);
				}
			}

			for (int nBoardX = 0; nBoardX < nXSize; nBoardX++)
			{
				m_Board.SetValue(nBoardX, 0, 0);
			}
		}
	}
}

// Change block
void CStPlay::ChangeBlock()
{
	// Set current block
	m_CurrentBlock = m_NextBlock;
	// Set board
	m_CurrentBlock.SetBoard(&m_Board);
	// Set next block
	CStBlock nextBlock;
	m_NextBlock = nextBlock;
}
