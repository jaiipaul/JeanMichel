#ifndef _Module_H_
#define _Module_H_

#include <JuceHeader.h>

namespace SynthModules{
    class Module{
    public:
        Module();
        Module(std::string _ModuleID);
        ~Module(){ };

        void setID(std::string _ModuleID);
        std::string getID();
    
    protected:
        std::string ModuleID;
    };
}


#endif // _Module_H_