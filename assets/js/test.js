
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


sfml_create_window();

while(sfml_is_window_open()) {
    while(sfml_poll_event()){
        sflm_handle_window_close_event();



        sfml_window_clear();


        
        sfml_window_display();

    }
}