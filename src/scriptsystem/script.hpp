/**
 
 based on: 
    https://www.reddit.com/r/gamedev/comments/52tlqu/integrating_v8_into_your_game_engine/

 and also:
    v8/samples/hello-world.cc 
    v8/samples/process.cc 
 
 */

#pragma once


#include <iostream>

#include "../../deps/v8/include/v8.h"

class Script {
public:
    Script(v8::Isolate* I, std::string S) 
    :   mIsolate(I)
    ,   isolate_scope(I)
    ,   handle_scope(I)
    ,   mSourceString(S)
    {
        std::cout << "Script()" << std::endl;

        std::cout << "source = \"" << mSourceString << "\"" << std::endl;

        // TODO i like this here but might be better elsewhere
        mSourceCode = v8::String::NewFromUtf8(I, 
                                        mSourceString.c_str(), 
                                        v8::NewStringType::kNormal
                                    ).ToLocalChecked();
                                    
        std::cout << "exit Script()" << std::endl;

    }

	virtual ~Script() {
        std::cout << "~Script()" << std::endl;

    }

    bool Initialize();
    bool Execute();

public:
    v8::Isolate* GetIsolate()               { return mIsolate; }

private:
    v8::Isolate* mIsolate;
    v8::Isolate::Scope isolate_scope;
    v8::HandleScope handle_scope;

    std::string mSourceString;
    v8::Local<v8::String> mSourceCode;
    
};

