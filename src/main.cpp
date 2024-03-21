// Parts Copyright 2015 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

//
// with help from here https://github.com/danbev/learning-v8
//

// ----------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <iostream>

#include <SFML/Graphics.hpp>

#include "libplatform.h"
#include "v8.h"

#include "bridge.hpp"

// ----------------------------------------------------------------------

void Initialise(const v8::FunctionCallbackInfo<v8::Value>& info)
{
  std::cout << "MY INITIALISE" << std::endl;
}



// ----------------------------------------------------------------------

// Read a file into a char array, copy it into a v8 String Type, then delete the char array and return the v8 string

v8::MaybeLocal<v8::String> ReadFile(v8::Isolate *isolate, const std::string &name)
{
  FILE *file = fopen(name.c_str(), "rb");
  if (file == NULL)
    return v8::MaybeLocal<v8::String>();

  fseek(file, 0, SEEK_END);
  size_t size = ftell(file);
  rewind(file);

  std::unique_ptr<char[]> chars(new char[size + 1]);
  chars.get()[size] = '\0';
  for (size_t i = 0; i < size;)
  {
    i += fread(&chars.get()[i], 1, size - i, file);
    if (ferror(file))
    {
      fclose(file);
      return v8::MaybeLocal<v8::String>();
    }
  }
  fclose(file);
  v8::MaybeLocal<v8::String> result = v8::String::NewFromUtf8(
      isolate, chars.get(), v8::NewStringType::kNormal, static_cast<int>(size));
  return result;
}

// ----------------------------------------------------------------------
int main(int argc, char *argv[])
{
  // Initialize V8
  v8::V8::InitializeICUDefaultLocation(argv[0]);
  v8::V8::InitializeExternalStartupData(argv[0]);

  std::unique_ptr<v8::Platform> platform = v8::platform::NewDefaultPlatform();
  v8::V8::InitializePlatform(platform.get());
  v8::V8::Initialize();

  // Create a new Isolate and make it the current one.
  v8::Isolate::CreateParams create_params;
  create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
  v8::Isolate *isolate = v8::Isolate::New(create_params);

  v8::Isolate::Scope isolate_scope(isolate);
  // Create a stack-allocated handle scope.
  v8::HandleScope handle_scope(isolate);

  // v8::Global<v8::Context> context = CreateShellContext(isolate);

  // Create a JavaScript template object allowing the object (in this case a function which is
  // also an object in JavaScript remember).
  v8::Local<v8::ObjectTemplate> global = v8::ObjectTemplate::New(isolate);

  // associate 'doit' with the doit function, allowing JavaScript to call it.
  global->Set(v8::String::NewFromUtf8(isolate,
                                      "doit",
                                      v8::NewStringType::kNormal).ToLocalChecked(),
                                      v8::FunctionTemplate::New(isolate, doit));

  // associate 'print' with the print function, allowing JavaScript to call it.
  global->Set(v8::String::NewFromUtf8(isolate,
                                      "print",
                                      v8::NewStringType::kNormal).ToLocalChecked(),
                                      v8::FunctionTemplate::New(isolate, print));

  // make 'age' available to JavaScript
  global->SetAccessor(String::NewFromUtf8(isolate,
                                          "age",
                                          v8::NewStringType::kNormal).ToLocalChecked(),
                                          age_getter,
                                          age_setter);

  // set a named property interceptor
  // global->SetNamedPropertyHandler(property_listener);

  // Create a new context.
  v8::Local<v8::Context> context = v8::Context::New(isolate, nullptr, global);


  global->Set(isolate, "initialise", v8::FunctionTemplate::New(isolate, Initialise));




  // Enter the context for compiling and running the hello world script.
  v8::Context::Scope context_scope(context);

  std::string filename = "./assets/js/test.js";
  v8::Local<v8::String> source;

  if (!ReadFile(isolate, filename).ToLocal(&source))
  {
    fprintf(stderr, "Error reading '%s'.\n", filename.c_str());
    return 1;
  }

  {
    // Compile the source code.
    v8::Local<v8::Script> script = v8::Script::Compile(context, source).ToLocalChecked();

    // Run the script to get the result.
    v8::Local<v8::Value> result = script->Run(context).ToLocalChecked();

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(isolate, result);
    printf("%s\n", *utf8);
  }

  sf::Window window(sf::VideoMode(800, 600), "My window");

  // run the program as long as the window is open
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
  }

  // Dispose the isolate and tear down V8.
  isolate->Dispose();
  v8::V8::Dispose();
  v8::V8::DisposePlatform();
  delete create_params.array_buffer_allocator;
  return 0;
}
