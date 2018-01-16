#include <stdlib.h>
#include <time.h>
#include "stplay.h"


// Constructor
CStPlay::CStPlay(CStView* pView)
{
    // View
    m_pView = pView;
    // Set board
    m_CurrentBlock.SetBoard(&m_Board);
}

// Start
void CStPlay::Start()
{
}

// Stop
void CStPlay::Stop()
{
}

// Pause
void CStPlay::Pause()
{
}

// Resume
void CStPlay::Resume()
{
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
        // Set current block
        m_CurrentBlock = m_NextBlock;
        // Set next block
        CStBlock nextBlock;
        m_NextBlock = nextBlock;
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
    // Set current block
    m_CurrentBlock = m_NextBlock;
    // Set next block
    CStBlock nextBlock;
    m_NextBlock = nextBlock;
    // Update view
    m_pView->UpdateView();
}

