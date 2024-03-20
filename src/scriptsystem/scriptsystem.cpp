

#include "libplatform.h"

#include "./scriptsystem.hpp"
#include "./script.hpp"

// ----------------------------------------------------------------------

void ScriptSystem::NewScript(std::string S) {
    std::cout << "ScriptSystem::NewScript"   << std::endl; 
    _script_vector.push_back(new Script(S));
}

// ----------------------------------------------------------------------

void ScriptSystem::Start() {

    // TODO move the compilation phase to here?
    
    for(auto S : _script_vector){
        S->Initialize();
    }

    for(auto S : _script_vector){
        S->Start();
    }
}

void ScriptSystem::Continue() {

    for(auto S : _script_vector){
        S->Continue();
    }
}

void ScriptSystem::Render() {

    for(auto S : _script_vector){
        S->Render();
    }
}

// ----------------------------------------------------------------------
