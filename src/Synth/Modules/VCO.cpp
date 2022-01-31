#include "VCO.h"
#include "WaveFunctions.h"

using namespace SynthModules;

VCO::VCO(std::string _ModuleID){
    ModuleID = _ModuleID;
    initialise(&genSAW);
}

VCO::~VCO(){

}

void VCO::switchWaveForm(const int type){
    switch(type){
        case 0 :
            initialise(&genSAW);
            break;
        
        case 1 :
            initialise(&genTRI);
            break;

        case 2 :
            initialise(&genSQR);
            break;
            
        case 3 :
            initialise(&genSINE);
            break;

        default :
            jassertfalse;
            break;
    }
}
