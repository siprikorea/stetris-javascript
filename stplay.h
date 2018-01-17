#ifndef __STPLAY_H__
#define __STPLAY_H__

#include "stblock.h"
#include "stboard.h"
#include "stview.h"

class CStPlay
{
public:
    // Constructor
    CStPlay(CStView* pView);

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

	// Get board
	CStBoard* GetBoard();
	// Get current block
	CStBlock* GetCurrentBlock();
	// Get next block
	CStBlock* GetNextBlock();

private:
    // View
    CStView* m_pView;
    // Board
    CStBoard m_Board;
    // Current Block
    CStBlock m_CurrentBlock;
    // Next Block
    CStBlock m_NextBlock;
};

#endif

