#include "../include/stblock.h"
#include "../include/stblocks.h"


// constructor
stblock::stblock(int number)
{
    m_number = number;
    m_x_size = stblocks[m_number].x_size;
    m_y_size = stblocks[m_number].y_size;
    m_rotation = 0;
    m_block = (int***)stblocks[m_number].block;
}

// rotate
void stblock::rotate()
{
    m_rotation = (m_rotation + 1) % MAX_BLOCK_ROT;
}

// operator []
int* stblock::operator[](int x)
{
    return m_block[m_rotation][x];
}

// get X size
int stblock::getXSize()
{
    return m_x_size;
}

// get Y size
int stblock::getYSize()
{
    return m_y_size;
}
