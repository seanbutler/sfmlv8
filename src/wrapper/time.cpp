
#include <iostream>


#include "libplatform.h"
#include "v8.h"

#include <SFML/System.hpp>

#include "time.hpp"

static sf::Clock global_clock;

void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) return;

  for (int n=0;n<args.Length(); n++){
    v8::Isolate* isolate = args.GetIsolate();
    v8::HandleScope scope(isolate);
    v8::Local<v8::Value> arg = args[0];
    v8::String::Utf8Value value(isolate, arg);

    std::string cppStr(*value);

    std::cout << cppStr;
  }

  // std::cout << "LOG arg count " << args.Length() << std::endl;
}

