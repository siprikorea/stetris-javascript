requirejs(['StTetris'], (StTetris)=> {
    var canvases = [ document.getElementById("tetris_player1") ];
    canvases.forEach((canvas) => {
        var tetris = new StTetris(canvas);
        tetris.start();
    });
});