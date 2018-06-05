const ST_MAX_BLOCK_ROT = 4;
const ST_MAX_BLOCK_X = 4;
const ST_MAX_BLOCK_Y = 4;

import "stboard.js"

class CStBlock
{
    // Constructor
    constructor(CStBoard board) {
        // Type
        type = (Math.rand() % ST_MAX_BLOCK_CNT) + 1;
        // X Size
        xSize = g_StBlocks[m_Type-1].x_size;
        // Y Size
        ySize = g_StBlocks[m_Type-1].y_size;
        // X Position
        xPos = (pBoard->GetXSize() / 2) - (m_XSize / 2);
        // Y Position
        yPos = 0;
        // Rotation
        rotation = 0;
        // Block
        block = g_StBlocks[type-1].block[rotation];
    }

    // Get type
    getType() {
        return type;
    }
    // Get X size
    getXSize() {
        return xSize;
    }
    // Get Y size
    getYSize() {
        return ySize;
    }
    // Get X position
    getXPos() {
        return xPos;
    }
    // Get Y position
    getYPos() {
        return xPos;
    }
	// Get block
	getBlock(x, y) {
        if (x < 0 || x >= ST_MAX_BLOCK_X)
            return 0;

        if (y < 0 || y >= ST_MAX_BLOCK_Y)
            return 0;

        return block[y][x];
    }

    // Rotate
    rotate();
    // Move left
    moveLeft();
    // Move right
    moveRight();
    // Move down
    moveDown();
    // Drop
    drop();

    // Check bounds
    checkBounds(moveX, moveY, moveBlock);

    // Board
    CStBoard board;
    // Type
    type;
    // X size
    xSize;
    // Y size
    ySize;
    // X position
    xPos;
    // Y position
    yPos;
    // Rotation
    rotation;
    // Block
    block;
};

