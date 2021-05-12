
#include "./scriptsystem.hpp"
#include "./script.hpp"
#include "../../deps/v8/include/libplatform/libplatform.h"

// ----------------------------------------------------------------------

void ScriptSystem::NewScript(std::string S) {
    // std::cout << "ScriptSystem::NewScript"   << std::endl; 
    mScripts.push_back(new Script(GetIsolate(), S));
    
}

// ----------------------------------------------------------------------


void ScriptSystem::Start() {
    for(auto S : mScripts){
        S->Initialize();
    }

    for(auto S : mScripts){
        S->Start();
    }
}

void ScriptSystem::Continue() {
    for(auto S : mScripts){
        S->Continue();
    }
}

void ScriptSystem::Render() {
    for(auto S : mScripts){
        S->Render();
    }
}

// ----------------------------------------------------------------------

