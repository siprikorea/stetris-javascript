#define MAX_BOARD_X 10
#define MAX_BOARD_Y 20

class stboard
{
    public:
        // constructor
        stboard();
        // clear board
        void clear();
        // set block
        void set_block(int x, int y, int** block);
    private:
        // board
        int m_board[MAX_BOARD_X][MAX_BOARD_Y];
};

