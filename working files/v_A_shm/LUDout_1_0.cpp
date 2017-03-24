#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUDout_1_0.h"


void PUT_Op_1_0    (void *pObj)
{
CLUDout_1_0& refCLUDout_1_0 = *(static_cast<CLUDout_1_0*>(pObj));
//CLUDout_1_0 *pCLUDout_1_0 = (CLUDout_1_0*)pObj;
refCLUDout_1_0.CalcReleySchematic();
}



CLUDout_1_0::CLUDout_1_0(void)
{
}
CLUDout_1_0::CLUDout_1_0(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
    chMaxIteratoin = chM;
    chIteration = chI;
    chNumInput  = static_cast<char>(shCLUDout_1_0_AmtIn );
    chNumOutput = static_cast<char>(shCLUDout_1_0_AmtOut);
    //chTypeLogicFunction = LU_OP_SET_OUT;
    //LogicFunc  = SET_OUT_Op;//???

    //Set Input parameters
    //pIn = (void*)arrPchIn;
    //pOut = (void*)arrOut;
    //Set OutPut parameters

}


CLUDout_1_0::~CLUDout_1_0(void)
{
}

void SET_OUT_Op(void *pObj)
{
    //CLUDout_1_0 *pCLUDout_1_0 = reinterpret_cast<CLUDout_1_0 *>(pObj);
    CLUDout_1_0& rCLUDout_1_0 = *(static_cast<CLUDout_1_0*> (pObj));
/*    asm(
                "bkpt 1"
                );
    rCLUDout_1_0.CalcReleySchematic();   */
}
#include "Rele_p1.cpp"
static char chGLB_QTrg = 0;
void CLUDout_1_0::CalcReleySchematic(void){
register long rl_Val,i;

#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_RELE_LU_CALC_POINT)];
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;
arChIntermediaResult[OFFSET_OUT_IN_RELE_TRIGGER_SELECTOR         ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_STABLE_SELECTOR          ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SELECTOR           ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_SIMPLE_SELECTOR    ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_PULSE_EXTANDED_SELECTOR  ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE__RIN                     ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE__RESET                   ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE__BL_IMP                  ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE__C1_C2                   ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_C1                       ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_RELE_C2                       ] = 0;//Now Default

rl_Val = 0;
long k, j, l;
short shCounterProcessedRec = RELE_Not01__1_1;
  do {
    pLUShcemasDscRec = arPReleShcemasDscRecords[shCounterProcessedRec - RELE_Not01__1_1];
    i = pLUShcemasDscRec->chTypeOperation;
    switch (i) {
        case LU_GEN_OP_AND:
            rl_Val = 1;
            for (i = 0; (i < pLUShcemasDscRec->chAmtOut) &&(rl_Val == 1); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arReleShOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val &= arChIntermediaResult[j];
            }
            arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            break;
        case LU_GEN_OP_OR:
            rl_Val = 0;
            for (i = 0; (i < pLUShcemasDscRec->chAmtOut) &&(rl_Val == 0); i++) {
                k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                l = arReleShOffsets[k];
                j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                rl_Val |= arChIntermediaResult[j];
            }
            arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            break;
        case LU_GEN_OP_XOR:
            i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
            j = arChIntermediaResult[i];
            i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
            rl_Val = j^arChIntermediaResult[i];
            arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            break;
        case LU_GEN_OP_NOT:
            LUShcemasInDataDsc const *pLUShcemasInDataDsc;
            rl_Val = 0;
            pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
            i = pLUShcemasInDataDsc[0].shOrderNumLU;
            rl_Val = arReleShOffsets[i];
            i = rl_Val + pLUShcemasInDataDsc[0].shIndexOut;
            rl_Val = arChIntermediaResult[i];

            arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            break;
        case LU_GEN_OP_RS_TRIGGER:
            rl_Val = 0;
            rl_Val = chGLB_QTrg;
            arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
            arChIntermediaResult[shCounterProcessedRec++] = !rl_Val;
            break;
            //Read Input Data

            //Eval Function
            //Put Result

        default:
            ;
    }

  } while (shCounterProcessedRec < IN_RELE_NORMAL_SELECTOR);

}
