/**
 * Our scripting system which executes JavaScript scripts
 
 based on: https://www.reddit.com/r/gamedev/comments/52tlqu/integrating_v8_into_your_game_engine/
 
 */

#pragma once

#include <iostream>

#include "../../deps/v8/include/v8.h"
#include "../../deps/v8/include/v8-platform.h"
#include "../../deps/v8/include/libplatform/libplatform.h"

class Script;

class ScriptSystem {
public:
	ScriptSystem(char* argv0)
    {
        v8::V8::InitializeICUDefaultLocation(argv0);
        v8::V8::InitializeExternalStartupData(argv0);
        mPlatformPtr = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(mPlatformPtr.get());
        v8::V8::Initialize();

        v8::Isolate::CreateParams create_params;
        create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        mIsolate = v8::Isolate::New(create_params);
        mIsolate->Enter();
    }

    virtual ~ScriptSystem() {
        if (mIsolate) {
            mIsolate->Exit();
            mIsolate = 0;
        }

        v8::V8::Dispose();
        v8::V8::ShutdownPlatform();
    }

    void NewScript(std::string source);
    void Update();
    void Initialize();

    v8::Isolate* GetIsolate()                       {   return mIsolate;   }

protected:
	std::unique_ptr<v8::Platform> mPlatformPtr;     
	v8::Isolate* mIsolate;
    std::vector<Script*> mScripts;
};


