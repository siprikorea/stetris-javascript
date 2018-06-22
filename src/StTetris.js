define(['StPlay', 'StScore'], function(StPlay, StScore) {
    return class StTetris {

        static get ST_WINDOW_WIDTH() { return 800; }
        static get ST_WINDOW_HEIGHT() { return 600; }
        static get ST_BLOCK_WIDTH() { return 30; }
        static get ST_BLOCK_HEIGHT() { return 30; }
        static get ST_BOARD_POS_X() { return 200; }
        static get ST_BOARD_POS_Y() { return 0; }
        static get ST_NEXT_BLOCK_POS_X() { return 650; }
        static get ST_NEXT_BLOCK_POS_Y() { return 150; }
        static get ST_SCORE_POS_X() { return 550; }
        static get ST_SCORE_POS_Y() { return 30; }
        static get ST_HIGHSCORE_POS_X() { return 650; }
        static get ST_HIGHSCORE_POS_Y() { return 30; }
        static get ST_BLOCK_COLOR() { return ["#000000", "#C71585", "#FFA500","#FFD700",  "#228B22",  "#1E90FF",  "#483D8B",  "#9932CC"]; }
        static get ST_BACKGROUND_COLOR() { return "#FFFFFF"; }

        // Constructor
        constructor(canvas) {
            // Canvas
            this.canvas = canvas;
            this.canvas.width = StTetris.ST_WINDOW_WIDTH;
            this.canvas.height = StTetris.ST_WINDOW_HEIGHT;
            // Context of canvas
            this.ctx = this.canvas.getContext("2d");

            // Play
            this.play = new StPlay(this);
            // Score
            this.score = new StScore();
            // High Score
            this.highScore = new StScore();
            // Load high score
            let highScore = sessionStorage.getItem("highscore");
            if (highScore) {
                // Set high score
                this.highScore.setScore(highScore);
            }
            // Play interval
            this.playInterval = 500;
            // Play interval handle
            this.playIntervalHandle = null;

        }

        // Start
        start() {
            // Set interval
            this.playIntervalHandle = setInterval(() => {
                this.play.moveDown() },
                this.playInterval);

            // Key down event listener
            this.onKeyDown = (e) => {
                switch (e.code) {
                    case "ArrowLeft":
                        this.play.moveLeft();
                        break;
                    case "ArrowRight":
                        this.play.moveRight();
                        break;
                    case "ArrowDown":
                        this.play.moveDown();
                        break;
                    case "ArrowUp":
                        this.play.rotate();
                        break;
                    case "Space":
                        this.play.drop();
                        break;
                }
            };

            // Add event listener
            window.addEventListener('keydown', this.onKeyDown);
        }

        // Stop
        stop() {
            // Clear interval
            clearInterval(this.playIntervalHandle);
            // Remove event listener
            window.removeEventListener('keydown', this.onKeyDown);
        }

        // Notify
        notify(message, param) {
            switch (message) {
                case StPlay.ST_NOTIFY_LEFT:
                case StPlay.ST_NOTIFY_RIGHT:
                case StPlay.ST_NOTIFY_ROTATE:
                    break;
                case StPlay.ST_NOTIFY_DOWN:
                case StPlay.ST_NOTIFY_DROP:
                    this.score.setScore(this.score.getScore() + 100);
                    break;
                case StPlay.ST_NOTIFY_CLEAR:
                    this.score.setScore(this.score.getScore() + param.cleared_lines * 1000);
                    break;
                case StPlay.ST_NOTIFY_TETRISOVER:
                    this.stop();
                    return;
            }

            // Update high score
            if (this.highScore.getScore() < this.score.getScore()) {
                this.highScore.setScore(this.score.getScore());
                sessionStorage.setItem("highscore", this.highScore.getScore());
            }

            this.drawTetris(this.ctx);
        }

        // Draw tetris
        drawTetris(ctx) {

            // Draw background
            var rect = {
                x: 0,
                y: 0,
                width: StTetris.ST_WINDOW_WIDTH,
                height: StTetris.ST_WINDOW_HEIGHT };
            this.drawBackground(this.ctx, rect);

            // Draw board
            var boardRect = {
                x: StTetris.ST_BOARD_POS_X,
                y: StTetris.ST_BOARD_POS_Y,
                width: StTetris.ST_BLOCK_WIDTH * this.play.getBoard().getXSize(),
                height: StTetris.ST_BLOCK_HEIGHT * this.play.getBoard().getYSize() };
            this.drawBoard(ctx, boardRect, this.play.getBoard());

            // Draw current block
            this.drawBlock(ctx, boardRect, this.play.getCurrentBlock());

            // Draw next block
            var nextBlockRect = {
                x: StTetris.ST_NEXT_BLOCK_POS_X,
                y: StTetris.ST_NEXT_BLOCK_POS_Y,
                width: StTetris.ST_BLOCK_WIDTH * StTetris.ST_MAX_BLOCK_X,
                height: StTetris.ST_BLOCK_HEIGHT * StTetris.ST_MAX_BLOCK_Y };
            this.drawBlock(ctx, nextBlockRect, this.play.getNextBlock());

            // Draw score
            var scoreRect = {
                x: StTetris.ST_SCORE_POS_X,
                y: StTetris.ST_SCORE_POS_Y,
                width: StTetris.ST_BLOCK_WIDTH * 7,
                height: StTetris.ST_BLOCK_HEIGHT * 2 };
            this.drawScore(ctx, scoreRect, "SCORE", this.score);

            // Draw high score
            var highScoreRect = {
                x: StTetris.ST_HIGHSCORE_POS_X,
                y: StTetris.ST_HIGHSCORE_POS_Y,
                width: StTetris.ST_BLOCK_WIDTH * 7,
                height: StTetris.ST_BLOCK_HEIGHT * 2 };
            this.drawScore(ctx, highScoreRect, "HIGH SCORE", this.highScore);
        }

        // Draw background
        drawBackground(ctx, rect) {
            ctx.fillStyle = StTetris.ST_BACKGROUND_COLOR;
            ctx.fillRect(rect.x, rect.y, rect.width, rect.height);
        }

        // Draw board
        drawBoard(ctx, rect, board) {

            // Draw board
            for (let boardY = 0; boardY < board.getYSize(); boardY++) {
                for (let boardX = 0; boardX < board.getXSize(); boardX++) {
                    var rectBlock = {
                        x: rect.x + boardX * StTetris.ST_BLOCK_WIDTH,
                        y: rect.y + boardY * StTetris.ST_BLOCK_HEIGHT,
                        width: StTetris.ST_BLOCK_WIDTH,
                        height: StTetris.ST_BLOCK_HEIGHT };
                    ctx.fillStyle = StTetris.ST_BLOCK_COLOR[this.play.getBoard().getBlock(boardX, boardY)];
                    ctx.fillRect(rectBlock.x, rectBlock.y, rectBlock.width, rectBlock.height);
                }
            }
        }

        // Draw block
        drawBlock(ctx, rect, block) {

            // Draw block
            for (let blockY = 0; blockY < block.getYSize(); blockY++) {
                for (let blockX = 0; blockX < block.getXSize(); blockX++) {
                    if (block.getBlock(blockX, blockY)) {
                        var rectBlock = {
                            x: rect.x + (block.getXPos() + blockX) * StTetris.ST_BLOCK_WIDTH,
                            y: rect.y + (block.getYPos() + blockY) * StTetris.ST_BLOCK_HEIGHT,
                            width: StTetris.ST_BLOCK_WIDTH,
                            height: StTetris.ST_BLOCK_HEIGHT };
                        ctx.fillStyle = StTetris.ST_BLOCK_COLOR[block.getBlock(blockX, blockY)];
                        ctx.fillRect(rectBlock.x, rectBlock.y, rectBlock.width, rectBlock.height);
                    }
                }
            }
        }

        // Draw score
        drawScore(ctx, rect, title, score) {
            // Draw title
            ctx.textAligh = "right";
            ctx.fillStyle = "red";
            ctx.fillText(title, rect.x, rect.y);

            // Draw score
            ctx.fillText(score.getScore(), rect.x, rect.y + rect.height / 2);
        }
    }
}); 