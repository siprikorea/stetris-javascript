const ST_MAX_BOARD_X = 10;
const ST_MAX_BOARD_Y = 20;

class CStBoard
{
    // Constructor
    constructor();

    // Clear
    Clear();

    // Get X size
    GetXSize();
    // Get Y size
    GetYSize();
    // Get value
    GetValue(int nX, int nY);
    // Set value
    SetValue(int nX, int nY, int nValue);

    // X Size
    m_XSize;
    // Y Size
    m_YSize;
    // Board
    m_Board[ST_MAX_BOARD_Y][ST_MAX_BOARD_X];
};
