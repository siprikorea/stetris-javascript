#ifndef __STVIEW_H__
#define __STVIEW_H__

#include "stplay.h"

class stview
{
    public:
        // constructor
        stview();
        // destructor
        virtual ~stview();
        
        // draw board
        virtual void drawBoard();
        // draw block
        virtual void drawBlock();
        // draw next block
        virtual void drawNextBlock();
};

#endif
