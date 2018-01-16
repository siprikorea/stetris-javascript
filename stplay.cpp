#include "../include/stplay.h"
#include "../include/stblocks.h"
#include <stdlib.h>
#include <time.h>


// constructor
stplay::stplay()
    : m_block(rand() % MAX_BLOCK_CNT),
    m_nextBlock(rand() % MAX_BLOCK_CNT)
{
    // initialize random seed
    srand((unsigned int)time(NULL));

    // block
    m_block = 0;
    // block X position
    m_blockXPos = 0;
    // block Y position
    m_blockYPos = 0;
    // next block
    m_nextBlock = 0;
}

// start
void stplay::start()
{
}

// stop
void stplay::stop()
{
}

// pause
void stplay::pause()
{
}

// resume
void stplay::resume()
{
}

// move left
void stplay::moveLeft()
{
    int blockXPos = m_blockXPos - 1;

    if (m_board.checkBlock(blockXPos, m_blockYPos, &m_block))
    {
        m_blockXPos = blockXPos;
    }
}

// move right
void stplay::moveRight()
{
    int blockXPos = m_blockXPos + 1;

    if (m_board.checkBlock(blockXPos, m_blockYPos, &m_block))
    {
        m_blockXPos = blockXPos;
    }
}

// move down
void stplay::moveDown()
{
    int blockYPos = m_blockYPos + 1;

    if (m_board.checkBlock(m_blockXPos, blockYPos, &m_block))
    {
        m_blockYPos = blockYPos;
    }
}

// rotate
void stplay::rotate()
{
    // rotate block
    stblock block(m_block);
    block.rotate();

    // check block
    if (m_board.checkBlock(m_blockXPos, m_blockYPos, &block))
    {
        m_block = block;
    }
}

// drop
void stplay::drop()
{
    while (1)
    {
        int blockYPos = m_blockYPos + 1;

        if (m_board.checkBlock(m_blockXPos, blockYPos, &m_block))
        {
            m_blockYPos = blockYPos;
        }
        else
        {
            break;
        }
    }
}

// get board
void stplay::getBoard(stboard* board)
{
    *board = m_board;
}

// get block X pos
int stplay::getBlockXPos()
{
    return m_blockXPos;
}

// get block Y pos
int stplay::getBlockYPos()
{
    return m_blockYPos;
}

// get block
void stplay::getBlock(stblock* block)
{
    *block = m_block;
}

// get next block
void stplay::getNextBlock(stblock* block)
{
    *block = m_nextBlock;
}

