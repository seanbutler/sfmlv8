/**
 
 based on: 
    https://www.reddit.com/r/gamedev/comments/52tlqu/integrating_v8_into_your_game_engine/

 and also:
    v8/samples/hello-world.cc 
    v8/samples/process.cc 
 
 */

#pragma once


#include <iostream>

#include "v8.h"

#include "../wrapper/graphics.hpp"
#include "../wrapper/time.hpp"


class Script {
public:
    Script(std::string S)
    :   _source_string(S)
    ,   context_()
    {
        std::cout << "Script()" << std::endl;
    }

	virtual ~Script() {
        std::cout << "~Script()" << std::endl;
    }

    bool Initialize();      // setup the script, compile and run it once 

    //
    // user methods 
    //
    bool Start();           
    bool Continue(double deltaTime=1.0/60.0);
    bool Render();

    v8::Isolate* GetIsolate()               { return v8::Isolate::GetCurrent(); }

protected:
    std::string           _source_string;
    v8::Local<v8::Context> context_;
    
    v8::Global<v8::Function> mStartFunc;
    v8::Global<v8::Function> mContinueFunc;
    v8::Global<v8::Function> mRenderFunc;
};

