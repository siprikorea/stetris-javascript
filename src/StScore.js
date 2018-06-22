define(() => {
    return class StScore {
        // Constructor
        constructor() {
            // Score
            this.score = 0;
        }

        // Clear
        Clear() {
            this.score = 0;
        }

        // Add score
        addScore(score) {
            this.score += score;
        }

        // Set score
        setScore(score) {
            this.score = score;
        }

        // Get score
        getScore() {
            return this.score;
        }
    }
});