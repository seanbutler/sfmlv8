
// function initialise() {
//     print ("initialise\n");
// }

// function update() {
//     print ("update ");
// }

// function draw() {
//     print ("draw ");
// }

// function dispose() {
//     print ("dispose\n");
// }

// age=40;
// doit(age);


print("Hello ");
sfml_create_window();
print("There");

while(sfml_is_window_open()) {
    while(sfml_poll_event()){
        sflm_handle_window_close_event();
        
    }
}