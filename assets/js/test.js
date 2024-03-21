

function initialise() {
    print ("initialise\n");
}

function update() {
    print ("update ");
}

function draw() {
    print ("draw ");
}

function dispose() {
    print ("dispose\n");
}


age=40;
doit(age);

initialise();

update(age);
draw();

dispose();
