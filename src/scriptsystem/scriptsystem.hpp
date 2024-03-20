/**
 
    Our scripting system which executes JavaScript scripts
    based on: https://www.reddit.com/r/gamedev/comments/52tlqu/integrating_v8_into_your_game_engine/
 
 */

#pragma once

#include <iostream>

#include "v8.h"
#include "v8-platform.h"
#include "libplatform/libplatform.h"

#include "../wrapper/time.hpp"

class Script;

class ScriptSystem {
public:
	ScriptSystem(char* argv0)
    :   _isolate_ptr(nullptr)
    {
        v8::V8::InitializeICUDefaultLocation(argv0);
        v8::V8::InitializeExternalStartupData(argv0);
        _current_platform_ptr = v8::platform::NewDefaultPlatform();
        v8::V8::InitializePlatform(_current_platform_ptr.get());
        v8::V8::Initialize();

        v8::Isolate::CreateParams create_params;
        create_params.array_buffer_allocator = v8::ArrayBuffer::Allocator::NewDefaultAllocator();
        _isolate_ptr = v8::Isolate::New(create_params);

        if (_isolate_ptr == nullptr) {
            std::cout << "ERROR " << std::endl;
        }
        _isolate_ptr->Enter();
    }


    virtual ~ScriptSystem() {
        if (_isolate_ptr) {
            _isolate_ptr->Exit();
            _isolate_ptr = 0;
        }

        v8::V8::Dispose();
        // v8::V8::ShutdownPlatform();
        // TODO
    }

    void NewScript(std::string source);
    
    void Start();
    void Continue();
    void Render();

    v8::Isolate* GetIsolate()                       {   return _isolate_ptr;   }

protected:
    v8::Isolate * _isolate_ptr;
	std::unique_ptr<v8::Platform> _current_platform_ptr;    
    std::vector<Script*> _script_vector;
};
