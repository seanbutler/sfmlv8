#include "./script.hpp"
#include "../../deps/v8/include/v8.h"

// --------------------------------------------------------------------------------

bool Script::Initialize() {


    return true;
}

bool Script::Execute() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());
    v8::Context::Scope context_scope(context);

    v8::TryCatch try_catch(GetIsolate());

    // Compile the source code
    v8::Local<v8::Script> compiledScript = v8::Script::Compile(context, mSourceCode).ToLocalChecked();

    // Run the script to get the result.
    v8::Local<v8::Value> result;
    if (!compiledScript->Run(context).ToLocal(&result)) {
        v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR %s\n", *error);
        return false;
    }


    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("yowzers %s\n", *utf8);

    return true;
}

