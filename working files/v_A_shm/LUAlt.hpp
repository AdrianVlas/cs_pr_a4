#pragma once
#include "lubase.h"
const short shCLUPulseAlternator_x_y_AmtOut = 1;
const short shCLUPulseAlternator_x_y_AmtIn  = 0;
#include "prtTmr.hpp"
typedef struct PulseAltSuit_tag{

short shTAlternator;//Number

}PulseAltCfgSuit;



class CPulseAlternator :
public CLUBase {
public:
    CPulseAlternator(void);
	CPulseAlternator(char chM,char chI); 
    ~CPulseAlternator(void);
    char* arrPchIn[shCLUPulseAlternator_x_y_AmtIn ]; //
    char arrOut [shCLUPulseAlternator_x_y_AmtOut]; //
    long TAlt(long lActivKey);
    char m_chLinkedTimers; //Field bit
    char m_chStateT;
    PulseAltCfgSuit m_PulseAltCfgSuit;
    TmrNode m_NodeTicAlt;
    
    long LinkPulseAltTimer(void);
    void UpdateCPulseAlt(void);
    friend long SetPulseAltSuit(void* pv);
    friend void PulseAlt_Op(void *pObj);
};

