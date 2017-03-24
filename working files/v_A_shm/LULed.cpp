#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LULed.h"
//#include "libraries.h"

#include "stm32f2xx.h"
#include "stm32f2xx_it.h"
#include "Ereg.h"



void PUT_Op_1_0_    (void *pObj)
{
//CLUNot_1_1& refCLUNot_1_1 = pObj;
//CLULed *pCLULed = (CLULed*)pObj;

}

CLULed::CLULed(void)
{
}
CLULed::CLULed(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLULed_1_0_AmtIn);
	chNumOutput = static_cast<char>(shCLULed_1_0_AmtOut);
	
	

	//Set Input parameters
	//pIn = (void*)arrPchIn;
	//pOut = (void*)arrOut;
	//Set OutPut parameters

}

CLULed::~CLULed(void)
{
}
char chGLBIn1_5 = 0;
char chGLBIn6_12 = 0;
long lGLBInChek_6_12 = 0;
long lGLBInChek_8_72 = 0;
void SET_LED_Op(void *pObj)
{
	//CLUNot_1_1& refCLUNot_1_1 = pObj;
//	CLULed *pCLULed = (CLULed*)pObj;
CLULed& rCLULed = *(static_cast<CLULed*>(pObj));
struct {
char *pLAdr1;
char *pLAdr2;
char *pLAdr3;
char *pLAdr4;
short*pLASh;
long L_Vl;
char chVal;
short shVal;
} sLV;
 /* asm(
       "bkpt 1"
       );/*
rCLULed.CalcLedSchematic();*/
return;
sLV.pLAdr1 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
sLV.pLAdr1 += ADR_WRITE_RI_COLUMNS01__06;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
sLV.pLAdr2 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
sLV.pLAdr2 += ADR_WRITE_RDO__REL_1_6__ROWS_A__D;
sLV.chVal = 0xff;
*(sLV.pLAdr1) = sLV.chVal;
*(sLV.pLAdr2) = sLV.chVal;

sLV.pLAdr1 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
sLV.pLAdr1 += ADR_WRITE_RI_COLUMNS01__06<<1;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
sLV.pLAdr2 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
sLV.pLAdr2 += ADR_WRITE_RDO__REL_1_6__ROWS_A__D<<1;
sLV.chVal = 0xff;
*(sLV.pLAdr1) = sLV.chVal;
*(sLV.pLAdr2) = sLV.chVal;

sLV.pLAdr3 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
sLV.pLAdr3 +=ADR_WRITE_RDO_REL7_REL14;//reinterpret_cast<char*>(NOR_PSRAM_BANK2+ADR_WRITE_RI_COLUMNS01__06 );
sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
sLV.pLAdr4 += ADR_WRITE_RDO_REL7_REL14;
sLV.chVal = 0xff;
*(sLV.pLAdr3) = sLV.chVal;
*(sLV.pLAdr4) = sLV.chVal;

sLV.pLAdr3 = reinterpret_cast<char*>(NOR_PSRAM_BANK2);
sLV.pLAdr3 += ADR_READ_DIN01__05<<1;//
sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
sLV.pLAdr4 += ADR_READ_DIN06__12<<1;
sLV.chVal = *(sLV.pLAdr3);
chGLBIn1_5  |= sLV.chVal;
sLV.chVal = *(sLV.pLAdr4);
chGLBIn6_12 |= sLV.chVal;

sLV.chVal = 0;
sLV.L_Vl = NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO__REL_1_6<<1);
sLV.pLASh = reinterpret_cast<short*>(sLV.L_Vl);
//sLV.pLASh += ADR_READ_CHECK_RDO__REL_1_6<<1;//
sLV.shVal = *(sLV.pLASh);
lGLBInChek_6_12  |= sLV.shVal;

sLV.chVal = 0;
sLV.L_Vl = NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1);
sLV.pLASh = reinterpret_cast<short*>(sLV.L_Vl);
//sLV.pLASh += ADR_READ_CHECK_RDO__REL_1_6<<1;//
sLV.shVal = *(sLV.pLASh);
lGLBInChek_8_72  |= sLV.shVal;



//sLV.pLAdr3 = reinterpret_cast<long*>( );
//sLV.pLAdr4 = reinterpret_cast<long*>( );
//Set PD3 In O-state
//GPIO_ResetBits(CON_L, CON_L_PIN);
//GPIO_SetBits  (CON_L, CON_L_PIN);

//GPIO_SetBits(CON_L, CON_L_PIN);GPIO_ResetBits(CON_L, CON_L_PIN);


}

#include "LULedp1.cpp"
static char chGLB_QTrg = 0;
void CLULed::CalcLedSchematic(void){
register long rl_Val,i;

#pragma data_alignment=4
char arChIntermediaResult[(TOTAL_LU_CALC_POINT)];
const LedShcemasDscRecord* pLUShcemasDscRec;// = &arPLedShcemasDscRecords;


arChIntermediaResult[OFFSET_OUT_IN_00_LEDIN                   ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_01_RESET                   ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_02_BL_IMP                  ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_03_C1_C2_SELECTOR          ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_04_C1                      ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_05_C2                      ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_NORMAL_SELECTOR        ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_TRIGGER_SELECTOR       ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_STABLE_SELECTOR        ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SELECTOR         ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_SIMPLE_SELECTOR  ] = 0;//Now Default
arChIntermediaResult[OFFSET_OUT_IN_MNU_PULSE_EXTANDED_SELECTOR] = 0;//Now Default
    rl_Val = 0;
	long k, j, l;
    short shCounterProcessedRec = Not06__1_1;
    do {
pLUShcemasDscRec = arPLedShcemasDscRecords[shCounterProcessedRec - Not06__1_1];
        i = pLUShcemasDscRec->chTypeOperation;
        switch (i) {
            case LU_GEN_OP_AND:
                rl_Val = 1;
                for (i = 0; (i < pLUShcemasDscRec->chAmtOut)&&(rl_Val == 1); i++) {
                    k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                    l = arShOffsets[k];
                    j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                    rl_Val &= arChIntermediaResult[j];
                }
                arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
                break;
            case LU_GEN_OP_OR:
                rl_Val = 0;
                for (i = 0; (i < pLUShcemasDscRec->chAmtOut)&&( rl_Val == 0); i++) {
                    k = pLUShcemasDscRec->pInputDscData[i].shOrderNumLU;
                    l = arShOffsets[k];
                    j = l + pLUShcemasDscRec->pInputDscData[i].shIndexOut;
                    rl_Val |= arChIntermediaResult[j];
                }
                arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
                break;
            case LU_GEN_OP_XOR:
                i = pLUShcemasDscRec->pInputDscData[0].shOrderNumLU;
                rl_Val = arShOffsets[i];
                i = rl_Val + pLUShcemasDscRec->pInputDscData[0].shIndexOut;
                j = arChIntermediaResult[i];
                i = pLUShcemasDscRec->pInputDscData[1].shOrderNumLU;
                rl_Val = arShOffsets[i];
                i = rl_Val + pLUShcemasDscRec->pInputDscData[1].shIndexOut;
                rl_Val = j^arChIntermediaResult[i];
                arChIntermediaResult[shCounterProcessedRec++] = rl_Val;
                break;
            case LU_GEN_OP_NOT:
                LUShcemasInDataDsc const *pLUShcemasInDataDsc;
                rl_Val = 0;
                pLUShcemasInDataDsc = pLUShcemasDscRec->pInputDscData;
                i = pLUShcemasInDataDsc[0].shOrderNumLU;
                rl_Val = arShOffsets[i];
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
  
    } while (shCounterProcessedRec < IN_MNU_NORMAL_SELECTOR);

}

