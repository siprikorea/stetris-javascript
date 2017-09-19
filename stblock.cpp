#include <stblock.h>

int stblocks[MAX_BLOCK_CNT][MAX_BLOCK_X][MAX_BLOCK_Y] = {
    {
        { 1, 0, 0, 0 },
        { 1, 1, 1, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 0, 2, 0 },
        { 2, 2, 2, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 3, 3, 0, 0 },
        { 3, 3, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 4, 4, 0 },
        { 4, 4, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 0, 5, 0, 0 },
        { 5, 5, 5, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 6, 6, 0, 0 },
        { 0, 6, 6, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
    {
        { 7, 7, 7, 7 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 },
        { 0, 0, 0, 0 }
    },
};

// constructor
stblock::stblock(int block_no)
{
    m_no = block_no;
}

void stblock::get_block(int** block)
{
    for (int x=0; x<MAX_BLOCK_X; x++)
    {
        for (int y=0; y<MAX_BLOCK_Y; y++)
        {
            block[x][y] = m_block[x][y];
        }
    }

}

// rotate block
void stblock::rotate()
{
    // find max size
    int max_size = -1;

    for (int x=0; x<MAX_BLOCK_X; x++)
    {
        for (int y=0; y<MAX_BLOCK_Y; y++)
        {
            if (m_block[x][y] && max_size < x)
                max_size = x;

            if (m_block[x][y] && max_size < y)
                max_size = y;
        }
    }

    // rotate the matrix by 90 degree
    for (int x=0; x<max_size/2; x++)
    {
        for (int y=0; y<(max_size+1)/2; y++)
        {
            int temp = m_block[x][y];
            m_block[x][y] = m_block[max_size-1-y][x];
            m_block[max_size-1-y][x] = m_block[max_size-1-x][max_size-1-y];
            m_block[max_size-1-x][max_size-1-y] = m_block[y][max_size-1-x];
            m_block[y][max_size-1-x] = temp;
        }
    }
}

