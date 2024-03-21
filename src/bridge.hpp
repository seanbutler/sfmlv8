#pragma once

#include <iostream>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include "libplatform/libplatform.h"
#include "v8.h"

using namespace v8;


void doit(const FunctionCallbackInfo<Value>& args);
void age_getter(Local<String> property, const PropertyCallbackInfo<Value>& info);
void age_setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info);
void property_listener(Local<String> name, const PropertyCallbackInfo<Value>& info);


void print(const v8::FunctionCallbackInfo<v8::Value>& args);



