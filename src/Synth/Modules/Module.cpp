#include "Module.h"

using namespace SynthModules;

Module::Module(){
    ModuleID = "NULL";
}
Module::Module(std::string _ModuleID){
    ModuleID = _ModuleID;
}

void Module::setID(std::string _ModuleID){
    ModuleID = _ModuleID;
}

std::string Module::getID(){
    return ModuleID;
}