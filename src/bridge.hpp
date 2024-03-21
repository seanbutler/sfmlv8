#pragma once

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "libplatform/libplatform.h"
#include "v8.h"

#include <SFML/Window.hpp>


using namespace v8;


void doit(const FunctionCallbackInfo<Value>& args);
void age_getter(Local<String> property, const PropertyCallbackInfo<Value>& info);
void age_setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
void property_listener(Local<String> name, const PropertyCallbackInfo<Value>& info);

void print(const v8::FunctionCallbackInfo<v8::Value>& args);

// ------------------------------------------------------------
extern sf::Window window;     // int var;  ->  declaration and definition 

void sfml_create_window(const FunctionCallbackInfo<Value>& args);
void sfml_is_window_open(const FunctionCallbackInfo<Value>& args);
void sfml_poll_event(const FunctionCallbackInfo<Value>& args);
void sflm_handle_window_close_event(const FunctionCallbackInfo<Value>& args);


// void sfml_window_set_position(int x, int y);
// void sfml_window_set_size(int w, int h);
// void sfml_window_set_title(const char *title);

// ------------------------------------------------------------
