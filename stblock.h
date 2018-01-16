#ifndef __STBLOCK_H__
#define __STBLOCK_H__

#define ST_MAX_BLOCK_ROT 4
#define ST_MAX_BLOCK_X 4
#define ST_MAX_BLOCK_Y 4

#include "stboard.h"

class CStBlock
{
public:
    // Constructor
    CStBlock();

    // Set board
    int SetBoard(CStBoard* pBoard);
    // Get type
    int GetType();
    // Get X size
    int GetXSize();
    // Get Y size
    int GetYSize();

    // Rotate
    bool Rotate();
    // Move left
    bool MoveLeft();
    // Move right
    bool MoveRight();
    // Move down
    bool MoveDown();
    // Drop
    void Drop();
    
    // Check for movement
    bool CheckForMovement();

protected:
    // Board
    CStBoard* m_pBoard;
    // Type
    int m_Type;
    // X size
    int m_XSize;
    // Y size
    int m_YSize;
    // Current X position
    int m_CurrentXPos;
    // Current Y position
    int m_CurrentYPos;
    // Current rotation
    int m_CurrentRotation;
    // Current block
    int m_CurrentBlock[ST_MAX_BLOCK_X][ST_MAX_BLOCK_Y];
    // Temp X position
    int m_TempXPos;
    // Temp Y position
    int m_TempYPos;
    // Temp rotation
    int m_TempRotation;
    // Temp block
    int m_TempBlock[ST_MAX_BLOCK_X][ST_MAX_BLOCK_Y];
};

#endif 
