// Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "../deps/v8/include/libplatform/libplatform.h"
#include "../deps/v8/include/v8.h"

#include "./scriptsystem/scriptsystem.hpp"
#include "./scriptsystem/script.hpp"

// --------------------------------------------------

// Reads a file into a std::string.
std::string ReadFile(const std::string& name) 
{
  FILE* file = fopen(name.c_str(), "rb");
  if (file == NULL) return std::string();

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  std::unique_ptr<char> chars(new char[size + 1]);
  chars.get()[size] = '\0';
  for (size_t i = 0; i < size;) {
    i += fread(&chars.get()[i], 1, size - i, file);
    if (ferror(file)) {
      fclose(file);
      return std::string();
    }
  }
  fclose(file);

  return chars.get();
}

// --------------------------------------------------

int main(int argc, char* argv[]) {

  sf::RenderWindow window;
  window.create(sf::VideoMode(800, 600), "My window");

  ScriptSystem scriptSystem(argv[0]);

  scriptSystem.NewScript(ReadFile("./assets/js/script.js"));
  scriptSystem.NewScript(ReadFile("./assets/js/script2.js"));

  scriptSystem.Start();

  while (window.isOpen())
  {
    // check all the window's events that were triggered since the last iteration of the loop
    sf::Event event;
    while (window.pollEvent(event))
    {
        // "close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            window.close();
    }

    scriptSystem.Continue();
    
    window.clear(sf::Color::Black);

    scriptSystem.Render();

    // end the current frame
    window.display();
  }

  return 0;
}
