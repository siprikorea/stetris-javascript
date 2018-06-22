define(['StBlock', 'StBoard'], (StBlock, StBoard) => {
    return class StPlay {
        static get ST_NOTIFY_LEFT() { return "NOTIFY_LEFT"; }
        static get ST_NOTIFY_RIGHT() { return "NOTIFY_RIGHT"; }
        static get ST_NOTIFY_DOWN() { return "NOTIFY_DOWN"; }
        static get ST_NOTIFY_DROP() { return "NOTIFY_DROP"; }
        static get ST_NOTIFY_ROTATE() { return "NOTIFY_ROTATE"; }
        static get ST_NOTIFY_CLEAR() { return "NOTIFY_CLEAR"; }
        static get ST_NOTIFY_TETRISOVER() { return "NOTIFY_TETRISOVER"; }

        // Constructor
        constructor(notify) {
            // Board
            this.board = new StBoard();
            // Current block
            this.currentBlock = new StBlock();
            this.currentBlock.setXPos(Math.floor((this.board.getXSize() - this.currentBlock.getXSize()) / 2));
            this.currentBlock.setYPos(- this.currentBlock.getYSize());
            // Next block
            this.nextBlock = new StBlock();
            // Notify
            this.notify = notify;
        }

        // Get board
        getBoard() {
            return this.board;
        }

        // Get current block
        getCurrentBlock() {
            return this.currentBlock;
        }

        // Get next block
        getNextBlock() {
            return this.nextBlock;
        }

        // Move left
        moveLeft() {
            // Is block movable
            if (this.isMovable(this.currentBlock, this.currentBlock.getXPos() - 1, this.currentBlock.getYPos(), this.currentBlock.getRotation())) {
                // Set current X position to left
                this.currentBlock.setXPos(this.currentBlock.getXPos() - 1);
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_LEFT);
            }
        }

        // Move right
        moveRight() {
            // Is block movable
            if (this.isMovable(this.currentBlock, this.currentBlock.getXPos() + 1, this.currentBlock.getYPos(), this.currentBlock.getRotation())) {
                // Set current X position to right
                this.currentBlock.setXPos(this.currentBlock.getXPos() + 1);
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_RIGHT);
            }
        }

        // Move down
        moveDown() {
            // Is block movable
            if (this.isMovable(this.currentBlock, this.currentBlock.getXPos(), this.currentBlock.getYPos() + 1, this.currentBlock.getRotation())) {
                // Set current Y position to down
                this.currentBlock.setYPos(this.currentBlock.getYPos() + 1);
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_DOWN);
            }
            // Block is not movable
            else {
                // Set current block to board
                this.setCurrentBlockToBoard();
                // Change current block
                this.changeCurrentBlock();
                // Clear completed line
                let cleared_lines = this.board.clearCompleteLines();
                if (cleared_lines) {
                    // Notify
                    this.notify.notify(StPlay.ST_NOTIFY_CLEAR, { cleared_lines : cleared_lines });
                }
                // Tetris is over
                if (this.isTetrisOver()) {
                    // Notify
                    this.notify.notify(StPlay.ST_NOTIFY_TETRISOVER);
                }
            }
        }

        // Drop
        drop() {

            while (true) {
                // Block is movable
                if (this.isMovable(this.currentBlock, this.currentBlock.getXPos(), this.currentBlock.getYPos() + 1, this.currentBlock.getRotation())) {
                    // Set current Y position to down
                    this.currentBlock.setYPos(this.currentBlock.getYPos() + 1);
                }
                // Block is not movable
                else {
                    // Notify
                    this.notify.notify(StPlay.ST_NOTIFY_DROP);
                    break;
                }
            }

            // Set current block to board
            this.setCurrentBlockToBoard();
            // Change current block
            this.changeCurrentBlock();
            // Clear completed line
            let cleared_lines = this.board.clearCompleteLines();
            if (cleared_lines) {
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_CLEAR, { cleared_lines : cleared_lines });
            }
            // Tetris is over
            if (this.isTetrisOver()) {
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_TETRISOVER);
            }
        }

        // Rotate
        rotate() {
            // Is block movable
            if (this.isMovable(this.currentBlock, this.currentBlock.getXPos(), this.currentBlock.getYPos(), this.currentBlock.getRotation() + 1)) {
                // Rotate
                this.currentBlock.setRotation(this.currentBlock.getRotation() + 1);
                // Notify
                this.notify.notify(StPlay.ST_NOTIFY_ROTATE);
            }
        }

        // Is movable
        isMovable(block, xPos, yPos, rotation) {

            // Create block to check and set value to check
            let checkBlock = new StBlock(block);
            checkBlock.setXPos(xPos);
            checkBlock.setYPos(yPos);
            checkBlock.setRotation(rotation);

            // Get value of board
            for (let blockX = 0; blockX < checkBlock.getXSize(); blockX++) {
                for (let blockY = 0; blockY < checkBlock.getYSize(); blockY++) {

                    // Check if block to check is empty
                    if (checkBlock.getBlock(blockX, blockY) == 0) {
                        continue;
                    }

                    let boardX = checkBlock.getXPos() + blockX;
                    let boardY = checkBlock.getYPos() + blockY;

                    // Check X position of block to check
                    if (boardX < 0 || boardX >= this.board.getXSize()) {
                        return false;
                    }

                    // Check Y position of block to check
                    if (boardY >= this.board.getYSize()) {
                        return false;
                    }

                    // Check if block is already exist
                    if (this.board.getBlock(boardX, boardY) != 0) {
                        return false;
                    }
                }
            }

            return true;
        }

        // Set current block to board
        setCurrentBlockToBoard() {
            // Set current block to board
            for (let blockX = 0; blockX < this.currentBlock.getXSize(); blockX++) {
                for (let blockY = 0; blockY < this.currentBlock.getYSize(); blockY++) {
                    if (this.currentBlock.getBlock(blockX, blockY) != 0) {
                        this.board.setBlock(this.currentBlock.getXPos() + blockX, this.currentBlock.getYPos() + blockY, this.currentBlock.getType());
                    }
                }
            }
        }

        // Check if tetris is over
        isTetrisOver() {
            let isTetrisOver = false;
            for (let boardX = 0; boardX < this.board.getXSize(); boardX++) {
                if (this.board.getBlock(boardX, 0) != 0) {
                    isTetrisOver = true;
                    break;
                }
            }
            return isTetrisOver;
        }

        // Change current block
        changeCurrentBlock() {
            // Set next block to current block
            this.currentBlock = this.nextBlock;
            this.currentBlock.setXPos(Math.floor((this.board.getXSize() - this.currentBlock.getXSize()) / 2));
            this.currentBlock.setYPos(- this.currentBlock.getYSize());
            // Set next block
            this.nextBlock = new StBlock();
        }
    }
});