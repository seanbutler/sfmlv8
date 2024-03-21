#include "bridge.hpp"

using namespace v8;

int age = 41;

// --------------------------------------------------

void print(void) {
    std::cout << "print" << std::endl;
}


void doit(const FunctionCallbackInfo<Value>& args) {
    String::Utf8Value str(args.GetIsolate(), args[0]);
    printf("doit argument = %s...\n", *str);
    args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), "doit...done", NewStringType::kNormal).ToLocalChecked());
}

void age_getter(Local<String> property, const PropertyCallbackInfo<Value>& info) {
    printf("age_getter...\n");
    info.GetReturnValue().Set(age);
}

void age_setter(Local<String> property, Local<Value> value, const PropertyCallbackInfo<void>& info) {
    printf("age_setter...\n");
    age = value->Int32Value(info.GetIsolate()->GetCurrentContext()).FromJust();
}

void property_listener(Local<String> name, const PropertyCallbackInfo<Value>& info) {
    String::Utf8Value utf8_value(info.GetIsolate(), name);
    std::string key = std::string(*utf8_value);
    printf("ageListener called for nam %s.\n", key.c_str());
}

// --------------------------------------------------

void print(const v8::FunctionCallbackInfo<v8::Value>& args) {
    String::Utf8Value str(args.GetIsolate(), args[0]);
    printf("%s", *str);
    // args.GetReturnValue().Set(String::NewFromUtf8(args.GetIsolate(), "doit...done", NewStringType::kNormal).ToLocalChecked());
}

// --------------------------------------------------

void test() {
    std::cout << "test" << std::endl;
}
