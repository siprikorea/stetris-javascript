#include "../include/stboard.h"


// constructor
stboard::stboard()
{
    clear();
}

// clear
void stboard::clear()
{
	for (int x = 0; x < MAX_BOARD_X; x++)
	{
		for (int y = 0; y < MAX_BOARD_Y; y++)
		{
			m_board[x][y] = 0;
		}
	}
}

// check block
bool stboard::checkBlock(int x, int y, stblock* block)
{
    for (int xCnt = 0; xCnt < block->getXSize(); xCnt++)
    {
        for (int yCnt = 0; yCnt < block->getYSize(); yCnt++)
        {
            if (*block[xCnt][yCnt])
            {
                if ((x + xCnt) >= MAX_BOARD_X || (y + yCnt) >= MAX_BOARD_Y)
                {
                    return false;
                }
                if (m_board[x + xCnt] || m_board[y + yCnt])
                {
                    return false;
                }
            }
        }
    }

    return true;
}

// set block
void stboard::setBlock(int x, int y, stblock* block)
{
    for (int xCnt = 0; xCnt < block->getXSize(); xCnt++)
    {
        for (int yCnt = 0; yCnt < block->getYSize(); yCnt++)
        {
            m_board[x + xCnt][y + yCnt] = *block[xCnt][yCnt];
        }
    }
}

