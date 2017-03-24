
#include "LUBGS.hpp"
#include "../inc/constants.h"

#include <stdbool.h>
#include <math.h>
//#include <arm_math.h>
#include <stdlib.h>
#include "stm32f2xx.h"
#include "hw_config.h"
#include "../inc/macroses.h"
#include "../inc/type_definition.h"
#include "../inc/variables_external.h"//


CBGSig::CBGSig(void):CLUBase()  {
m_NodeTWait.lTmrVal  = 0;
m_NodeTWait.next     = 0;
m_NodeTReset.lTmrVal = 0;
m_NodeTReset.next    = 0;

m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;
m_BGSigSuit.lTReset    = 0;
m_chLinkedTimers = 0; //Field bit
m_chStateTWait   = 0;
m_chStateTReset  = 0;
m_lIfix = m_lMeasIti_mn_1 = 0;
m_chNumberAnalogChanell = 0;
}

CBGSig::~CBGSig(void) {
}

CBGSig::CBGSig(char chM,char chI){
	chMaxIteratoin = chM;
	chIteration = chI;
	
chNumInput  = static_cast<char>(shCLUBGSig_x_y_AmtIn);//
chNumOutput = static_cast<char>(shCLUBGSig_x_y_AmtOut);
m_NodeTWait.lTmrVal  = 0;
m_NodeTWait.next     = 0;
m_NodeTReset.lTmrVal = 0;
m_NodeTReset.next    = 0;

m_BGSigSuit.chStateGS  = 0;
m_BGSigSuit.chCheckBgs = 0;
m_BGSigSuit.lTWait     = 0;
m_BGSigSuit.lTReset    = 0;
m_chLinkedTimers = 0; //Field bit
m_chStateTWait   = 0;
m_chStateTReset  = 0;


}

long CBGSig::LinkBGSigTimers(void) {
    register long i = 0;
    //Insert TpauseMft
    chGlSem++;
    
    if (PushTmrNode(&m_NodeTWait)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 2;
    }
    //Insert TdelayMft
    if (PushTmrNode(&m_NodeTReset)) {//static_cast<void*>(
        i++;
        m_chLinkedTimers |= 4;
    }

    chGlSem--;
    return i;
}

long CBGSig::lTWait(long lActivKey) {

    register long *plTmrVal = &m_NodeTWait.lTmrVal;
    if (lActivKey) {





    } else {
        ;

        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}

long CBGSig::lTReset(long lActivKey) {
    register long *plTmrVal = &m_NodeTReset.lTmrVal;
    if (lActivKey) {




    } else {
        ;

        *plTmrVal = 0; //m_NodeTpause.lTmrVal = 0;
    }
    return 0;
}
void CBGSig::UpdateCBGSig(void) {
//Set Input parameters
pIn = static_cast<void*>(arrPchIn);
//Set OutPut parameters
pOut = static_cast<void*>(arrOut);
//LinkMftTimers();
//pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;

//Set Operation
//Set Type Operation
}
void BGSig_Op(void *pObj) {
    CBGSig& rCBGSig = *(static_cast<CBGSig*> (pObj));
    asm(
                "bkpt 1"
                );
    rCBGSig.CalcBusGrSigSchematic();
}

#include "LUBgsp1.cpp"
static char chGLB_DTrg = 0;
void CBGSig::CalcBusGrSigSchematic(void){
register long rl_Val,i;

#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_BGS_LU)];
i = EvalDeltaIbus();
//if( i == 1 && (arChIntermediaResult[StoreIfixTimeFix_1]) == 0)
//m_lIfix = 
}
//long Ibus, long lTinterval
long CBGSig::EvalDeltaIbus(void) {
    register long i, j,Iti;
    //Kc = Ucurr_power/Unom_power
    //Num Analog Chanel
    Iti = measurement[m_chNumberAnalogChanell];
    if (Iti > m_lMeasIti_mn_1) {
        j = Iti - m_lMeasIti_mn_1;
    } else {
        j = m_lMeasIti_mn_1 - Iti;
    }
    i = (m_BGSigSuit.lIust * measurement[4]) / lU_NOM;
	
    if (j > i){
        m_lIfix = m_lMeasIti_mn_1;
        i = 1;
        }
	else i = 0;
	m_lMeasIti_mn_1 = Iti;
	

    return i;
}
// long CBGSig::StoreIfixTimeFix(long lTime, long lIbus, long lActive) {
// register long i;

//     return 0;
// }
long CBGSig::EvalDeltaIbusFix(long Ibus, long Ifix, long lActive){
register long i;

    return 0;
}
long CBGSig::EvalIptp (long lI, long lT, long lActive){
register long i;

    return 0;
}
long CBGSig::EvalIctc (long lI, long lT, long lActive){
register long i;

    return 0;
}
long CBGSig::EvalNNC_NCH(long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNP_NCH(long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNC_CH (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalNNP_CH (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalCE (long lActivate){
register long i;

    return 0;
}
long CBGSig::EvalOC(void){
register long i;

    return 0;
}

long CBGSig::EvalNNP(long lNNC, long lNNP){
register long i;

    return 0;
}
long CBGSig::EvalNNM(long lNNC, long lNNP){
register long i;

    return 0;
}
long CBGSig::EvalNCC(long lNCC){
register long i;

    return 0;
}




