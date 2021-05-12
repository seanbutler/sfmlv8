/*

https://stackoverflow.com/questions/11387015/calling-a-v8-javascript-function-from-c-with-an-argument

*/

// --------------------------------------------------------------------------------


#include "./script.hpp"
#include "../../deps/v8/include/v8.h"

// --------------------------------------------------------------------------------

bool Script::Initialize() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context
    v8::Local<v8::Context> context = v8::Context::New(GetIsolate());
    mContext.Reset(GetIsolate(), context);  // lets keep a context for later use when repeat executing the same script
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


    // {
    //     v8::Local<v8::Value> func_val;
    //     v8::Local<v8::String> func_name = v8::String::NewFromUtf8Literal(GetIsolate(), "Finish");

    //     if (!context->Global()->Get(context, func_name).ToLocal(&func_val) ||
    //         !func_val->IsFunction()) {
    //         return false;
    //     }

    //     v8::Local<v8::Function> func_fun = func_val.As<v8::Function>();
    //     mFinishFunc.Reset(GetIsolate(), func_fun);
    // }

    return true;
}




// --------------------------------------------------------------------------------

bool Script::Start() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context
    v8::Local<v8::Context> context = v8::Local<v8::Context>::New(GetIsolate(), mContext);
    v8::Context::Scope context_scope(context);

    v8::TryCatch try_catch(GetIsolate());


    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mStartFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), 17.0);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR %s\n", *error);
        return false;
    }

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("start res %s\n", *utf8);

    return true;
}

// --------------------------------------------------------------------------------

bool Script::Continue() {

    // Create a stack-allocated handle scope
    v8::HandleScope handle_scope(GetIsolate());

    // Create a new context
    v8::Local<v8::Context> context = v8::Local<v8::Context>::New(GetIsolate(), mContext);
    v8::Context::Scope context_scope(context);

    v8::TryCatch try_catch(GetIsolate());


    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mContinueFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), 17.0);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR %s\n", *error);
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

    // Create a new context
    v8::Local<v8::Context> context = v8::Local<v8::Context>::New(GetIsolate(), mContext);
    v8::Context::Scope context_scope(context);

    v8::TryCatch try_catch(GetIsolate());


    // Invoke the Process Function
    v8::Local<v8::Function> process = v8::Local<v8::Function>::New(GetIsolate(), mRenderFunc);

    const int argc=1;
    v8::Handle<v8::Value> argv[argc];
    argv[0] = v8::Number::New(GetIsolate(), 17.0);

    v8::Local<v8::Value> result;

    if (!process->Call(context, context->Global(), argc, argv).ToLocal(&result)) {
        v8::String::Utf8Value error(GetIsolate(), try_catch.Exception());
        printf("ERROR %s\n", *error);
        return false;
    }

    // Convert the result to an UTF8 string and print it.
    v8::String::Utf8Value utf8(GetIsolate(), result);
    printf("render res %s\n", *utf8);

    return true;
}


// --------------------------------------------------------------------------------
