#ifndef __STPLAY_H__
#define __STPLAY_H__

#include "stblock.h"
#include "stboard.h"

class CStPlay
{
public:
    // Constructor
    CStPlay();

    // Start
    void Start();
    // Stop
    void Stop();
    // Pause
    void Pause();
    // Resume
    void Resume();

    // Move left
    void MoveLeft();
    // Move right
    void MoveRight();
    // Move down
    void MoveDown();
    // Rotate
    void Rotate();
    // Drop
    void Drop();

private:
    // Board
    CStBoard m_Board;
    // Current Block
    CStBlock m_CurrentBlock;
    // Next Block
    CStBlock m_NextBlock;
};

#endif

