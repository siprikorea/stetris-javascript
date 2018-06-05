import "stblock.javascript"
import "stboard.javascript"
import "stscore.javascript"
import "stview.javascript"

class CStPlay
{
    // Constructor
    constructor(CStView* pView);

    // Move left
    MoveLeft();
    // Move right
    MoveRight();
    // Move down
    MoveDown();
    // Rotate
    Rotate();
    // Drop
    Drop();

	// Get board
	GetBoard();
	// Get current block
	GetCurrentBlock();
	// Get next block
	GetNextBlock();
	// Get score
	GetScore();
	// Get high score
	GetHighScore();

	// Set block to board
	SetBlockToBoard();
	// Clear complete line
	ClearCompleteLine();
	// Change block
	ChangeBlock();

    // View
    m_pView;
    // Board
    m_Board;
    // Current Block
    m_CurrentBlock;
    // Next Block
    m_NextBlock;
	// Score
	m_Score;
	// High Score
	m_HighScore;
};
