
#include <iostream>


#include "../../deps/v8/include/libplatform/libplatform.h"
#include "../../deps/v8/include/v8.h"

#include <SFML/System.hpp>

#include "./time.hpp"

static sf::Clock global_clock;

void LogCallback(const v8::FunctionCallbackInfo<v8::Value>& args) {
  if (args.Length() < 1) return;
  std::cout << "LOG arg count " << args.Length() << std::endl;
}

