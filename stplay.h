#ifndef __STPLAY_H__
#define __STPLAY_H__

#include "stblock.h"
#include "stboard.h"

class stplay
{
    public:
        // constructor
        stplay();

        // start
        void start();
        // stop
        void stop();
        // pause
        void pause();
        // resume
        void resume();

        // move left
        void moveLeft();
        // move right
        void moveRight();
        // move down
        void moveDown();
        // rotate
        void rotate();
        // drop
        void drop();

        // get board
        void getBoard(stboard* board);
        // get block X pos
        int getBlockXPos();
        // get block Y pos
        int getBlockYPos();
        // get block
        void getBlock(stblock* block);
        // get next block
        void getNextBlock(stblock* block);

    private:
        // board
        stboard m_board;
        // block
        stblock m_block;
        // block X position
        int m_blockXPos;
        // block Y position
        int m_blockYPos;
        // next block
        stblock m_nextBlock;
};

#endif

