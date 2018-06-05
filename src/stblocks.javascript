const ST_MAX_BLOCK_CNT = 7;
const ST_MAX_BLOCK_ROT = 4;
const ST_MAX_BLOCK_X = 4;
const ST_MAX_BLOCK_Y = 4;

// block structure
class ST_BLOCK {
    xSize;
    ySize;
    block[ST_MAX_BLOCK_ROT][ST_MAX_BLOCK_Y][ST_MAX_BLOCK_X];
};

// blocks
const ST_BLOCK g_StBlocks[ST_MAX_BLOCK_CNT];

