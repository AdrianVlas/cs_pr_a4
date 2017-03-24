
#include "LUAlt.hpp"

CPulseAlternator::CPulseAlternator(void) :CLUBase() {
m_chLinkedTimers = 0; //Field bit
m_chStateT       = 0;
m_PulseAltCfgSuit.shTAlternator = 0;
m_NodeTicAlt.lTmrVal = 0;
m_NodeTicAlt.next    = 0;
}

CPulseAlternator::~CPulseAlternator(void) {
}


CPulseAlternator::CPulseAlternator(char chM,char chI)  {
	chMaxIteratoin = chM;
	chIteration = chI;
	
chNumInput  = static_cast<char>(shCLUPulseAlternator_x_y_AmtIn);//
chNumOutput = static_cast<char>(shCLUPulseAlternator_x_y_AmtOut);
	
}
void CPulseAlternator::UpdateCPulseAlt(void){
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}
long CPulseAlternator::LinkPulseAltTimer(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTicAlt)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }

    
    chGlSem--;
    return i;
}
long CPulseAlternator::TAlt(long lActivKey){
  
    register long *plTmrVal = &m_NodeTicAlt.lTmrVal;
    if (lActivKey) {
	
	} else {
        ;
        m_chStateT = 0;
        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}
void PulseAlt_Op(void *pObj){

    register long i, j;

	CPulseAlternator& rPulseAlt = *(static_cast<CPulseAlternator*>(pObj));
	j = 0;
	i = rPulseAlt.TAlt(j);
	
rPulseAlt.arrOut[0] = static_cast<char>(i);

}
