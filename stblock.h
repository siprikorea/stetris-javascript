#define MAX_BLOCK_CNT 7
#define MAX_BLOCK_X 4
#define MAX_BLOCK_Y 4

class stblock
{
    public:
        // constructor
        stblock(int no);
        // rotate block
        void rotate();
        // get block
        void get_block(int** block);

    private:
        // block number
        int m_no;
        // blocks
        int m_block[MAX_BLOCK_Y][MAX_BLOCK_X];
};

