
#include "./scriptsystem.hpp"
#include "./script.hpp"
#include "../../deps/v8/include/libplatform/libplatform.h"


void ScriptSystem::NewScript(std::string S) {
    // std::cout << "ScriptSystem::NewScript"   << std::endl; 
    mScripts.push_back(new Script(GetIsolate(), S));
}

void ScriptSystem::Initialize() {
    // std::cout << "ScriptSystem::Initialize()"   << std::endl; 
    for(auto S : mScripts){
        S->Initialize();
    }
}

void ScriptSystem::Update() {
    // std::cout << "ScriptSystem::Update()"   << std::endl; 
    for(auto S : mScripts){
        S->Execute();
    }
}


