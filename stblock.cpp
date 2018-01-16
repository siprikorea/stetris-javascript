#include "../include/stblock.h"
#include "../include/stblocks.h"
#include <stdlib.h>
#include <string.h>

// constructor
CStBlock::CStBlock(CStBoard* pBoard)
{
    // Board
    m_pBoard = pBoard;
    // Type
    m_Type = rand() % ST_MAX_BLOCK_CNT;
    // X Size
    m_XSize = g_StBlocks[m_Type].x_size;
    // Y Size
    m_YSize = g_StBlocks[m_Type].y_size;
    // Current X Position
    m_CurrentXPos = 0;
    // Current Y Position
    m_CurrentYPos = 0;
    // Current Rotation
    m_CurrentRotation = 0;
    // Current Block
    memcpy(m_CurrentBlock, &g_StBlocks[m_Type].block[m_CurrentRotation], sizeof(m_CurrentBlock));
    // Temp X Position
    m_TempXPos = 0;
    // Temp Y Position
    m_TempYPos = 0;
    // Temp Rotation
    m_TempRotation = 0;
    // Temp Block
    memcpy(m_TempBlock, &g_StBlocks[m_Type].block[m_TempRotation], sizeof(m_TempBlock));
}

// Get type
int CStBlock::GetType()
{
    return m_Type;
}

// Get X size
int CStBlock::GetXSize()
{
    return m_XSize;
}

// Get Y size
int CStBlock::GetYSize()
{
    return m_YSize;
}

// Rotate
void CStBlock::Rotate()
{
    // Set temp rotation
    m_TempRotation = m_CurrentRotation + 1;
    // Set temp block
    memcpy(m_TempBlock, &g_StBlocks[m_Type].block[m_TempRotation], sizeof(m_TempBlock));

    // Check for movement
    if (CheckForMovement())
    {
        // Set current rotation
        m_CurrentRotation = m_CurrentRotation + 1;
        // Set current block
        memcpy(m_CurrentBlock, m_TempBlock, sizeof(m_CurrentBlock));
    }
}

// Move left
void CStBlock::MoveLeft()
{
    // Set temp X position
    m_TempXPos = m_CurrentXPos - 1;
    // Set current block
    memcpy(m_TempBlock, m_CurrentBlock, sizeof(m_TempBlock));

    // Check for movement
    if (CheckForMovement())
    {
        // Set current X position
        m_CurrentXPos = m_CurrentXPos - 1;
    }
}

// Move right
void CStBlock::MoveRight()
{
    // Set temp X position
    m_TempXPos = m_CurrentXPos + 1;
    // Set current block
    memcpy(m_TempBlock, m_CurrentBlock, sizeof(m_TempBlock));

    // Check for movement
    if (CheckForMovement())
    {
        // Set current X position
        m_CurrentXPos = m_CurrentXPos + 1;
    }
}

// Move down
void CStBlock::MoveDown()
{
    // Set temp Y position
    m_TempYPos = m_CurrentYPos + 1;
    // Set current block
    memcpy(m_TempBlock, m_CurrentBlock, sizeof(m_TempBlock));

    // Check for movement
    if (CheckForMovement())
    {
        // Set current Y position
        m_CurrentYPos = m_CurrentYPos + 1;
    }
}

// Drop
void CStBlock::Drop()
{
    while (1)
    {
        // Set temp Y position
        m_TempYPos = m_CurrentYPos + 1;
        // Set current block
        memcpy(m_TempBlock, m_CurrentBlock, sizeof(m_TempBlock));

        // Check for movement
        if (CheckForMovement())
        {
            // Set current Y position
            m_CurrentYPos = m_CurrentYPos + 1;
        }
        else
        {
            break;
        }
    }
}

// Check for movement
bool CStBlock::CheckForMovement()
{
    // Get X size of board
    int nBoardXSize = m_pBoard->GetXSize();
    // Get Y size of board
    int nBoardYSize = m_pBoard->GetYSize();

    // Check X position of block
    if (m_TempXPos < 0 || m_TempXPos > nBoardXSize)
    {
        return false;
    }

    // Check Y position of block
    if (m_TempYPos < 0 || m_TempYPos > nBoardYSize)
    {
        return false;
    }

    // Get value of board
    for (int nBlockX = 0; nBlockX < m_XSize; nBlockX++)
    {
        for (int nBlockY = 0; nBlockY < m_YSize; nBlockY++)
        {
            // Check if block is empty
            if (!m_TempBlock[nBlockX][nBlockY])
            {
                continue;
            }

            // Check X position of block
            if ((m_TempXPos + nBlockX) < 0 || (m_TempXPos + nBlockX) > nBoardXSize)
            {
                return false;
            }

            // Check Y position of block
            if ((m_TempYPos + nBlockY) < 0 || (m_TempYPos + nBlockY) > nBoardYSize)
            {
                return false;
            }

            // Check if block is already exist
            if (m_pBoard->GetValue(m_TempXPos + nBlockX, m_TempXPos + nBlockY))
            {
                return false;
            }
        }
    }

    return true;
}

