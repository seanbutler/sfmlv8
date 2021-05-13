var g = 1;

function Start() {
    return 1;
}

function Continue(deltaTimeInSeconds) {
    g = g + 1;
    return g;
}

function Render() {
    return 2;
}

function Finish() {
    return 3;
}
