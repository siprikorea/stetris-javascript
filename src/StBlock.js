define(() => {
    return class StBlock {
        // Blocks
        static get blocks() {
            return [ [
                    [
                        [ 1, 0, 0 ],
                        [ 1, 1, 1 ],
                        [ 0, 0, 0 ]
                    ], [
                        [ 0, 1, 0 ],
                        [ 0, 1, 0 ],
                        [ 1, 1, 0 ]
                    ], [
                        [ 0, 0, 0 ],
                        [ 1, 1, 1 ],
                        [ 0, 0, 1 ]
                    ], [
                        [ 0, 1, 1 ],
                        [ 0, 1, 0 ],
                        [ 0, 1, 0 ]
                    ]
                ], [
                    [
                        [ 0, 0, 2 ],
                        [ 2, 2, 2 ],
                        [ 0, 0, 0 ]
                    ], [
                        [ 2, 2, 0 ],
                        [ 0, 2, 0 ],
                        [ 0, 2, 0 ]
                    ], [
                        [ 0, 0, 0 ],
                        [ 2, 2, 2 ],
                        [ 2, 0, 0 ]
                    ], [
                        [ 0, 2, 0 ],
                        [ 0, 2, 0 ],
                        [ 0, 2, 2 ]
                    ]
                ], [
                    [
                        [ 3, 3 ],
                        [ 3, 3 ]
                    ]
                ], [
                    [
                        [ 0, 4, 4 ],
                        [ 4, 4, 0 ],
                        [ 0, 0, 0 ]
                    ], [
                        [ 0, 4, 0 ],
                        [ 0, 4, 4 ],
                        [ 0, 0, 4 ]
                    ]
                ], [
                    [
                        [ 0, 0, 0 ],
                        [ 5, 5, 5 ],
                        [ 0, 5, 0 ]
                    ], [
                        [ 0, 5, 0 ],
                        [ 0, 5, 5 ],
                        [ 0, 5, 0 ]
                    ], [
                        [ 0, 5, 0 ],
                        [ 5, 5, 5 ],
                        [ 0, 0, 0 ]
                    ], [
                        [ 0, 5, 0 ],
                        [ 5, 5, 0 ],
                        [ 0, 5, 0 ]
                    ]
                ], [
                    [
                        [ 6, 6, 0 ],
                        [ 0, 6, 6 ],
                        [ 0, 0, 0 ]
                    ], [
                        [ 0, 0, 6 ],
                        [ 0, 6, 6 ],
                        [ 0, 6, 0 ]
                    ]
                ], [
                    [
                        [ 0, 0, 0, 0 ],
                        [ 0, 0, 0, 0 ],
                        [ 7, 7, 7, 7 ],
                        [ 0, 0, 0, 0 ]
                    ], [
                        [ 0, 7, 0, 0 ],
                        [ 0, 7, 0, 0 ],
                        [ 0, 7, 0, 0 ],
                        [ 0, 7, 0, 0 ]
                    ]
                ]
            ];
        }

        // Constructor
        constructor(block) {
            if (block instanceof StBlock) {
                // Type
                this.type = block.type;
                // X Position
                this.xPos = block.xPos;
                // Y Position
                this.yPos = block.yPos;
                // Rotation
                this.rotation = block.rotation;
                // Block
                this.block = block.block.slice();
            }
            else {
                // Type
                this.type = Math.floor(Math.random() * StBlock.blocks.length) + 1;
                // X Position
                this.xPos = 0;
                // Y Position
                this.yPos = 0;
                // Rotation
                this.rotation = 0;
                // Block
                this.block = StBlock.blocks[this.type-1];
            }
        }

        // Get type
        getType() {
            return this.type;
        }

        // Get X size
        getXSize() {
            return this.block[this.rotation][0].length;
        }

        // Get Y size
        getYSize() {
            return this.block[this.rotation].length;
        }

        // Get X position
        getXPos() {
            return this.xPos;
        }

        // Get Y position
        getYPos() {
            return this.yPos;
        }

        // Get rotation
        getRotation() {
            return this.rotation;
        }

        // Get block
        getBlock(x, y) {
            if (x < 0 || x >= this.getXSize())
                return 0;

            if (y < 0 || y >= this.getYSize())
                return 0;

            return this.block[this.rotation][y][x];
        }

        // Set X position
        setXPos(xPos) {
            this.xPos = xPos;
        }

        // Set Y position
        setYPos(yPos) {
            this.yPos = yPos;
        }
        
        // Set rotation
        setRotation(rotation) {
            this.rotation = rotation % this.block.length;
        }
    }
});