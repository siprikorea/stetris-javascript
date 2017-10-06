class stblock
{
    public:
        // constructor
        stblock(int number);
        // rotate
        void rotate();
        // operator []
        int* operator[](int x);
        // get X size
        int getXSize();
        // get Y size
        int getYSize();

    private:
        // block number
        int m_number;
        // X size
        int m_x_size;
        // X size
        int m_y_size;
        // rotation
        int m_rotation;
        // block
        int*** m_block;
};

