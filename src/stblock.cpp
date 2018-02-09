#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "stblock.h"
#include "stblocks.h"

/************************************************************
 *	@brief		Constructor
 *	@retval		Nothing
 ************************************************************/
CStBlock::CStBlock(CStBoard* pBoard)
	: m_pBoard(pBoard)
{
    // Initialize random seed
    srand((unsigned int)time(NULL));

    // Type
    m_Type = (rand() % ST_MAX_BLOCK_CNT) + 1;
    // X Size
    m_XSize = g_StBlocks[m_Type-1].x_size;
    // Y Size
    m_YSize = g_StBlocks[m_Type-1].y_size;
    // X Position
    m_XPos = (pBoard->GetXSize() / 2) - (m_XSize / 2);
    // Y Position
    m_YPos = 0;
    // Rotation
    m_Rotation = 0;
    // Block
    memcpy(m_Block, &g_StBlocks[m_Type-1].block[m_Rotation], sizeof(m_Block));
}

/************************************************************
 *	@brief		Get type
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetType()
{
    return m_Type;
}

/************************************************************
 *	@brief		Get X size
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetXSize()
{
    return m_XSize;
}

/************************************************************
 *	@brief		Get Y size
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetYSize()
{
    return m_YSize;
}

/************************************************************
 *	@brief		Get X position
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetXPos()
{
    return m_XPos;
}

/************************************************************
 *	@brief		Get Y position
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetYPos()
{
    return m_YPos;
}

/************************************************************
 *	@brief		Get block
 *	@retval		Nothing
 ************************************************************/
int CStBlock::GetBlock(int nX, int nY)
{
	if (nX < 0 || nX >= ST_MAX_BLOCK_X)
		return 0;

	if (nY < 0 || nY >= ST_MAX_BLOCK_Y)
		return 0;

    return m_Block[nY][nX];
}

/************************************************************
 *	@brief		Rotate
 *	@retval		Nothing
 ************************************************************/
bool CStBlock::Rotate()
{
    // Set temp rotation
    int nTempRotation = (m_Rotation + 1) % ST_MAX_BLOCK_ROT;
    // Set temp block
    int TempBlock[ST_MAX_BLOCK_Y][ST_MAX_BLOCK_X];
    memcpy(TempBlock, &g_StBlocks[m_Type-1].block[nTempRotation], sizeof(TempBlock));

    // Check for movement
    if (CheckForMovement(m_XPos, m_YPos, TempBlock))
    {
        // Set current rotation
        m_Rotation = (m_Rotation + 1) % ST_MAX_BLOCK_ROT;
        // Set current block
        memcpy(m_Block, TempBlock, sizeof(m_Block));
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************
 *	@brief		Move left
 *	@retval		Nothing
 ************************************************************/
bool CStBlock::MoveLeft()
{
    // Check for movement
    if (CheckForMovement(m_XPos - 1, m_YPos, m_Block))
    {
        // Set current X position
        m_XPos = m_XPos - 1;
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************
 *	@brief		Move right
 *	@retval		Nothing
 ************************************************************/
bool CStBlock::MoveRight()
{
    // Check for movement
    if (CheckForMovement(m_XPos + 1, m_YPos, m_Block))
    {
        // Set current X position
        m_XPos = m_XPos + 1;
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************
 *	@brief		Move down
 *	@retval		Nothing
 ************************************************************/
bool CStBlock::MoveDown()
{
    // Check for movement
    if (CheckForMovement(m_XPos, m_YPos + 1, m_Block))
    {
        // Set current Y position
        m_YPos = m_YPos + 1;
        return true;
    }
    else
    {
        return false;
    }
}

/************************************************************
 *	@brief		Drop
 *	@retval		Nothing
 ************************************************************/
void CStBlock::Drop()
{
    while (1)
    {
        // Check for movement
        if (CheckForMovement(m_XPos, m_YPos + 1, m_Block))
        {
            // Set current Y position
            m_YPos = m_YPos + 1;
        }
        else
        {
            break;
        }
    }
}

/************************************************************
 *	@brief		Check for movement
 *	@retval		Nothing
 ************************************************************/
bool CStBlock::CheckForMovement(int nMoveX, int nMoveY, int MoveBlock[ST_MAX_BLOCK_Y][ST_MAX_BLOCK_X])
{
    // Get board size
    int nBoardXSize = m_pBoard->GetXSize();
    int nBoardYSize = m_pBoard->GetYSize();

    // Get value of board
    for (int nBlockY = 0; nBlockY < m_YSize; nBlockY++)
    {
        for (int nBlockX = 0; nBlockX < m_XSize; nBlockX++)
        {
            // Check if block is empty
            if (!MoveBlock[nBlockY][nBlockX])
            {
                continue;
            }

            // Check X position of block
            if ((nMoveX + nBlockX) < 0 || (nMoveX + nBlockX) >= nBoardXSize)
            {
                return false;
            }

            // Check Y position of block
            if ((nMoveY + nBlockY) < 0 || (nMoveY + nBlockY) >= nBoardYSize)
            {
                return false;
            }

            // Check if block is already exist
            if (m_pBoard->GetValue(nMoveX + nBlockX, nMoveY + nBlockY))
            {
                return false;
            }
        }
    }

    return true;
}
