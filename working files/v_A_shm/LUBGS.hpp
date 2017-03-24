#pragma once
#include "lubase.h"
const short shCLUBGSig_x_y_AmtOut = 1;
const short shCLUBGSig_x_y_AmtIn  = 0;
const long lU_NOM = 220000;
#include "prtTmr.hpp"
#include "BgsAux.h"

typedef struct MftSuit_tag{
char chStateGS;
char chCheckBgs;
long lTWait;
long lTReset;
long lIust;
}BGSigSuit;



class CBGSig :
public CLUBase {
public:
    CBGSig(void);
    ~CBGSig(void);
    //CBGSig(CBGSig&);
    CBGSig(char chM, char chI);
    void CalcBusGrSigSchematic(void);
    long lTWait(long lActivKey);
    long lTReset(long lActivKey);
    char* arrPchIn[shCLUBGSig_x_y_AmtIn]; //
    char arrOut [shCLUBGSig_x_y_AmtOut]; //Tra
    char m_chLinkedTimers; //Field bit
    char m_chStateTWait;
    char m_chStateTReset;
    char m_chNumberAnalogChanell;
    BGSigSuit m_BGSigSuit;
    TmrNode m_NodeTWait;
    TmrNode m_NodeTReset;
    long m_lMeasIti_mn_1;
    long m_lIfix;
    long LinkBGSigTimers(void);
    void UpdateCBGSig(void);
    //long Ibus, long lTinterval
    long EvalDeltaIbus(void); //Ibus- Current for check lTinterval - IntervalTime
    //long StoreIfixTimeFix(long lTime, long lIbus, long lActive);
    long EvalDeltaIbusFix(long Ibus, long Ifix, long lActive);
    long EvalIptp(long lI, long lT, long lActive);
    long EvalIctc(long lI, long lT, long lActive);
    long EvalNNC_NCH(long lActivate);
    long EvalNNP_NCH(long lActivate);
    long EvalNNC_CH(long lActivate);
    long EvalNNP_CH(long lActivate);
    long EvalCE(long lActivate);
    long EvalOC(void);
    long EvalNNP(long lNNC, long lNNP);
    long EvalNNM(long lNNC, long lNNP);
    long EvalNCC(long lNCC);
    
    friend long SetBGSigSuit(void* pv);
    friend void BGSig_Op(void *pObj);
};

