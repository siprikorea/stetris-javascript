#include <stblock.h>

#define MAX_BOARD_X 10
#define MAX_BOARD_Y 20

class stboard
{
    public:
        // constructor
        stboard();
        // clear
        void clear();
        // check block
        bool checkBlock(int x, int y, stblock* block);
        // set block
        void setBlock(int x, int y, stblock* block);

    private:
        // board
        int m_board[MAX_BOARD_X][MAX_BOARD_Y];
};

