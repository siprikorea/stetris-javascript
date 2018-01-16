#ifndef __STBLOCKS_H__
#define __STBLOCKS_H__

#define MAX_BLOCK_CNT 7
#define MAX_BLOCK_ROT 4
#define MAX_BLOCK_X 4
#define MAX_BLOCK_Y 4

// block structure
typedef struct _ST_BLOCK
{
    int x_size;
    int y_size;
    int block[MAX_BLOCK_ROT][MAX_BLOCK_X][MAX_BLOCK_Y];
}ST_BLOCK, *PST_BLOCK;

// block informations
extern ST_BLOCK stblocks[MAX_BLOCK_CNT];

#endif
