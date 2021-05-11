
#include "./scriptsystem.hpp"
#include "./script.hpp"
#include "../../deps/v8/include/libplatform/libplatform.h"


void ScriptSystem::NewScript(std::string S) {
    std::cout << "ScriptSystem::NewScript"   << std::endl; 
    mScript = new Script(GetIsolate(), S);
}

void ScriptSystem::Update() {
    std::cout << "ScriptSystem::Update()"   << std::endl; 
    mScript->Execute();
}


