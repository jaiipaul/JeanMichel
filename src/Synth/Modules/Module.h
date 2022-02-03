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

    struct Phase{
        int idx;
        float phase;

        void init(){
            idx = 0;
            phase = 0.0f;
        };

        void advance(float sampleRate, float freq){
            if(idx < sampleRate/freq){
                idx++;
            }else{
                idx = 0;
            }
            phase = fmod(freq*(float)idx/sampleRate, 1.0f);
        };
    };

}


#endif // _Module_H_