/*

https://stackoverflow.com/questions/11387015/calling-a-v8-javascript-function-from-c-with-an-argument

*/

// --------------------------------------------------------------------------------

#include "./script.hpp"
#include "v8.h"

// --------------------------------------------------------------------------------

bool Script::Initialize() {
    
    std::cout << "Script::Initialize()" <<std::endl;

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context as we are initialising this script
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());

    // Create a new scope and global template to hold global functions
    v8::Context::Scope context_scope();
	v8::Local<v8::ObjectTemplate> global_template = v8::ObjectTemplate::New(GetIsolate());
    global_template->Set(GetIsolate(), "log", v8::FunctionTemplate::New(GetIsolate(), LogCallback));
    context = v8::Context::New(GetIsolate(), nullptr, global_template);

    // lets keep the context for later use when repeat executing the same script
    context_ = context;  

    v8::TryCatch try_catch(GetIsolate());

    v8::Local<v8::String> source_code;

    source_code = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), 
                                    _source_string.c_str(), 
                                    v8::NewStringType::kNormal
                                ).ToLocalChecked();

    // Compile the source code
    v8::Local<v8::Script> compiledScript = v8::Script::Compile(context, source_code).ToLocalChecked();

    // Run the script to get the result.
    v8::Local<v8::Value> result;

    if (!compiledScript->Run(context).ToLocal(&result)) {
        v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR %s\n", *error);
        return false;
    }

    {
        v8::Local<v8::Value> func_val;
        v8::Local<v8::String> func_name = v8::String::NewFromUtf8Literal(GetIsolate(), "Start");

        if (!context->Global()->Get(context, func_name).ToLocal(&func_val) ||
            !func_val->IsFunction()) {
            return false;
        }

        v8::Local<v8::Function> func_fun = func_val.As<v8::Function>();
        mStartFunc.Reset(GetIsolate(), func_fun);
    }

    {
        v8::Local<v8::Value> func_val;
        v8::Local<v8::String> func_name = v8::String::NewFromUtf8Literal(GetIsolate(), "Continue");

        if (!context->Global()->Get(context, func_name).ToLocal(&func_val) ||
            !func_val->IsFunction()) {
            return false;
        }

        v8::Local<v8::Function> func_fun = func_val.As<v8::Function>();
        mContinueFunc.Reset(GetIsolate(), func_fun);
    }

    {
        v8::Local<v8::Value> func_val;
        v8::Local<v8::String> func_name = v8::String::NewFromUtf8Literal(GetIsolate(), "Render");

        if (!context->Global()->Get(context, func_name).ToLocal(&func_val) ||
            !func_val->IsFunction()) {
            return false;
        }

        v8::Local<v8::Function> func_fun = func_val.As<v8::Function>();
        mRenderFunc.Reset(GetIsolate(), func_fun);
    }

    return true;
}

// --------------------------------------------------------------------------------

bool Script::Start() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context as we are initialising this script
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());
    v8::Context::Scope context_scope(context);

    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mStartFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), 17.0);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        // v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR \n");
        return false;
    }

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("start res %s\n", *utf8);

    return true;
}

// --------------------------------------------------------------------------------

bool Script::Continue(double deltaTime) {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context as we are initialising this script
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());
    v8::Context::Scope context_scope(context);

    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mContinueFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), deltaTime);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        // v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR \n");
        return false;
    }

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("continue res %s\n", *utf8);

    return true;
}


bool Script::Render() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context as we are initialising this script
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());
    v8::Context::Scope context_scope(context);

    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mRenderFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), 17.0);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        // v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR \n");
        return false;
    }

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("render res %s\n", *utf8);

    return true;
}


// --------------------------------------------------------------------------------
