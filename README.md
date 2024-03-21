# sfmlv8

## description

quick and dirty skeleton for projects which combine sfml and v8. 

useful for someone making a game engine who wants to use javascript as the embedded scripting language instead of the usual lua (say).

 - use the speed of C++ for the graphics, sound and windowing.
 - the ease of access and flexability google's v8, which is also super fast.  

## instructions

V8 is part of chromium which uses google's [depot_tools](https://www.chromium.org/developers/how-tos/install-depot-tools/
) for talking to git and makeing builds and changelist wrangling etc. 

1. Follow [these instructions](https://commondatastorage.googleapis.com/chrome-infra-docs/flat/depot_tools/docs/html/depot_tools_tutorial.html#_setting_up) to install [depot_tools](https://www.chromium.org/developers/how-tos/install-depot-tools/
) for your system. 

1. Update depot tools by running "gclient" in a terminal. The first time this may take some minutes. Dont be alarmed if it appears to hang its updating. Successive runs will be near instantaneous.

1. Download V8 itself not using git clone, but using depot_tools and install v8 on your system. You do this using the 'fetch v8' command. Take a look at these [instructions](https://v8.dev/docs/source-code#using-git). 

1. Some IDEs will need a little [setting up](https://v8.dev/docs/ide-setup) for V8. Using Visual Studio Code works for me. YMMV.

1. The platform independant windowing and other multimedia interfacing including 2d sprites is handled by SFML. 
    - On Ubuntu that means issueing the following commands.
~~~
    sudo apt-get install build-essential
    sudo apt-get install libsfml-dev
~~~

1. clone this repo  
1. in the makefile you will have to edit the V8DIR variable so it points to where youve installed the src for v8. Look at Line 7.

~~~ Makefile
    V8DIR = PATH_TO_INSTALL/Projects/v8/
~~~

1. use Make to build this project


~~~

> make

~~~
