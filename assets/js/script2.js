
var g = 1;

function Start() {
    return 11;
}

function Continue(deltaTime) {
    g++;
    log("hi");
    return g;
}

function Render() {
    return 21;
}

function Finish() {
    return 31;
}
