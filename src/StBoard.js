define(() => {
    return class StBoard {
        static get ST_MAX_BOARD_X() { return 10; }
        static get ST_MAX_BOARD_Y() { return 20; }

        // Constructor
        constructor() {
            // Board
            this.board = new Array(StBoard.ST_MAX_BOARD_Y);
            for (let boardY = 0; boardY < this.board.length; boardY++) {
                this.board[boardY] = new Array(StBoard.ST_MAX_BOARD_X).fill(0);
            }
        }

        // Get X size
        getXSize() {
            return StBoard.ST_MAX_BOARD_X;
        }

        // Get Y size
        getYSize() {
            return StBoard.ST_MAX_BOARD_Y;
        }

        // Get block
        getBlock(x, y) {
            if (x < 0 || x >= StBoard.ST_MAX_BOARD_X)
                return 0;

            if (y < 0 || y >= StBoard.ST_MAX_BOARD_Y)
                return 0;

            return this.board[y][x];
        }

        // Set block
        setBlock(x, y, block) {
            if (x < 0 || x >= StBoard.ST_MAX_BOARD_X)
                return;

            if (y < 0 || y >= StBoard.ST_MAX_BOARD_Y)
                return;

            this.board[y][x] = block;
        }

        // Clear complete lines
        clearCompleteLines() {
            let complete_lines = 0;

            for (let boardY = 0; boardY < StBoard.ST_MAX_BOARD_Y; boardY++) {
                let block_count = 0;

                // Count the number of block
                for (let boardX = 0; boardX < StBoard.ST_MAX_BOARD_X; boardX++) {
                    if (this.board[boardY][boardX]) {
                        block_count++;
                    }
                }

                // The line of board is full of block
                if (block_count == this.board[boardY].length) {
                    // Delete line of board
                    this.board.splice(boardY, 1);
                    // Add line to the beginning of the board
                    this.board.unshift(new Array(StBoard.ST_MAX_BOARD_X).fill(0));
                    complete_lines++;
                }
            }

            return complete_lines;
        }
    }
});