#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include <stdlib.h>
#include "Shematic.h"
//#include "StructElem.h"
#include "BaseInPoint.h"
#include "InPoint.h"
#include "ExtPoint.h"
#include "LUBase.h"
#include "LUNot_1_1.h"
#include "LUDInput_0_1.h"
#include "LUDout_1_0.h"
#include "LUDInput_0_1.h"
#include "LULed.h"
#include "LUAnd_8_1.h"
#include "LUOr_8_1.h"
#include "LUXor_8_1.h"
#include "Mft.h"

//#include <conio.h>
#include <string.h>
#include <ctime>
#include "stng.h"
__CONFIG_CPP preSetUP = {
    0, //uint32_t device_id;
    10, 10, 10,
    1, //uint32_t n_and;
    1, //uint32_t n_or;
    1, //uint32_t n_xor;
    1, //uint32_t n_not;
    1, //uint32_t n_timers;
    1, //uint32_t n_triggers;
    1, //uint32_t n_alarms;
    1, //uint32_t n_meanders;
    2, 2, 2, 2, 2, 2, 2, 2//uint8_t time_config[7+1];

};

long long LL_CryaCrya @ "NonZeroIniVars_RAM1" = 15;

UNN_LogicUnitArea gLUAreaMem @ "NonZeroIniVars_RAM1" = {

};

LUAreaAuxVar gblLUAreaAuxVar  = {
    0, //.short shAmountPlacedLogicUnit;//counter placed
    0, //.short shIdxLUAreaListElem;    //Index LU Area List Elem
    (SIZE_MEM_BLK - sizeof (LUAreaListElem)), sizeof (LUAreaListElem), //.long  lAmountFreeMem, lAmountUsedMem;
     static_cast<void*>( &(gLUAreaMem.chArRamPrgEvt[((SIZE_MEM_BLK) - 1)])),
	static_cast<void*>(0)

};



/*
//Declare 5 Points & 1 struct element
InPoint ar5Points[TOTAL_POINTS];
StructElem s3And = StructElem(3);
 */

UNN_LogicUnitArea lcUArea;
short shAmountTotalElem = 0;
long lAmountOccupyMem = 0;
//long lIdxHead
//long lIdxTail
short shIdxLUnit = 0;
//Next List Header
//Prev List Header
//Insert function
//Delete function
/*
*	Main Object
*
*/
Shematic sh;
char chGblGround = 0;
char chGblVcc    = 1;

Shematic::Shematic(void) {
    //Debug Code
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut
            = ar_n__Output_Dsc[0].bfInfo_OrdNumOut;
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng
            = ar_n__Output_Dsc[0].bfInfo_OrdNumStng;
    ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng
            = ar_n__Output_Dsc[0].bfInfo_IdLUStng;
    //Debug Code 
	LL_CryaCrya++;
    chInitTerminated = 0;
    
}

void Shematic::Init(void) {
Init2();
chInitTerminated = 1;
}

void Shematic::DoCalc(void) {

    register long i, j;
    register void* pv;

    struct {
        //long lId,lsizeobj;
        short shAmountCalcLU, shRes;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase* pCLUBase;
    } sLV;
    sLV.shAmountCalcLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    i = 0;
    if(chInitTerminated == 0)
        return;
    //j = ar_n_Output_Dsc[0].UN_BitFld_LUInInfo.lArUrgData[0];
    //j+= ar_n__Output_Dsc[0].bfInfo_OrdNumOut;
    //j+= ghj.UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
    while (sLV.shAmountCalcLU--) {
        pv = reinterpret_cast<void*>( &sLV.arrLUAreaListElem[i]);
        sLV.pCLUBase = reinterpret_cast<CLUBase*>( (reinterpret_cast<LUAreaListElem*> (pv))->pvLU);//(CLUBase*)
        pv = reinterpret_cast<void*>( sLV.pCLUBase); //->LogicFunc;
        if ((reinterpret_cast<CLUBase*>( pv))->shShemasOrdNumStng != 0 //&&
                ) {
            j = (reinterpret_cast<CLUBase*>( pv))->shShemasIdLUStng;
            switch (j) {
                case STNG_EXTENDED:
                    break;
                default:
                {
                    if (j > STNG_EXTENDED && j < STNG_LU_UPPER_BOUND) {
                        if ((reinterpret_cast<CLUBase*>( pv))->LogicFunc != Null_OP) {
                            (reinterpret_cast<CLUBase*>( pv))->LogicFunc( reinterpret_cast<void*>(sLV.pCLUBase));
                        }

                    }
                }
            }

        }
        i++;
    }
}

Shematic::~Shematic(void) {
}

void Shematic::printResult(void) {
    /*    int c = 0;
        long lIdxPoint = NUM_IN_POINTS;
        char chAmtInitPoints = NUM_OUT_POINTS-1;
        InPoint*pInPont = &ar5Points[lIdxPoint];
        printf("Result schematic:\n");
        do{
            printf("State ar5Points[");printf("%hhX %s",lIdxPoint,"]=");
            putchar((int)pInPont ->chState+0x30);printf(" \n");
            lIdxPoint++;
            pInPont = &ar5Points[lIdxPoint];//Next Pointer

        }while(chAmtInitPoints--);
        pInPont = &ar5Points[lIdxPoint];

        c = getch();*/

}

void Shematic::PrintPointsState(void) {
    //Print state All Points which Shematic Use
    //Name Logic Unit
}

void Shematic::PrintShematicElemPointsState(void) {
    //Print Only Points Using?
}

//void Shematic::SetupCircutLinks(void *pv) {
//    //register long ik;
//    Init2LcVarArea& rsLV  = *((Init2LcVarArea*)pv);
//    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
//}
//#ifdef RAND_MAX
// #define RAND_MAX 256
//#endif
//static long first_value,last_value;
//random_number = first_value + rand() % last_value;
static long arNum[300] @ "ZeroInivars_RAM1";
static short shCounterCalls_GLB;
long Shematic::GetTrueOrderNum(void) {
    register long i, j;

    struct {
        char chNeedAnotherNumber, chCtrCalls;
    } sLV;
    volatile long random_number;
    sLV.chNeedAnotherNumber = 0;
    srand(time(0));
    //i = (long) rand() % 255; //255 Max diapason
    i = static_cast<long>(rand() % 255); //255 Max diapason

    random_number = i + 1; //1 - min diapason
    sLV.chCtrCalls = 0;
    do {

        for (j = 0; j < 300 && arNum[j] != 0; j++) {

            if (random_number == arNum[j]) {
                j = 300;
                sLV.chNeedAnotherNumber = 1;
                break;
            }
            if(arNum[j+1] == 0){
                sLV.chNeedAnotherNumber = 0;
                break;
            }
        }
        //Another Number
        if (sLV.chNeedAnotherNumber) {
            sLV.chCtrCalls++;
            i = static_cast<long>( rand() % 255); //255 Max diapason
            random_number = i + 1;
        }
    } while (sLV.chNeedAnotherNumber && sLV.chCtrCalls < 250);
    if (sLV.chCtrCalls >= 250) {
        //Clr Mem
        for (j = 0; j < 300; j++)
            arNum[j] = 0;
        shCounterCalls_GLB = 0;
    }
    i = shCounterCalls_GLB;
    arNum[i] = random_number;
    shCounterCalls_GLB = i+1;

    return random_number;
}

void Shematic::CreateTestSchema(void) {
    /*
    register long i,j;
    void* pv;
    struct
        {
            //short shAmtLU,shIdxLUOut;//
                    long lOrderNumber;
            short shAmtLUDsc,shIdx;
                    short shIdxLUOutDsc, shIdxLU;
                    //SBitFld_LUInInfo locSBitFld;
		 
        } sLV;

		
            //sLV.locSBitFldCRefInfo = 
            //SetUP DOUT
            //Form Additional Info
            sLV.shAmtLUDsc = preSetUP.n_and;
            sLV.shIdxLUOutDsc = sLV.shIdxLU = sLV.shIdx = 0;// 
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED;
            //SetUP Led
            //SetUP And
            while(sLV.shIdx < sLV.shAmtLUDsc){
		
                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut 
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng  
            }

	
            //SetUP OR
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8);
            sLV.shAmtLUDsc = preSetUP.n_or;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){
		
                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut 
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng  
            }
            //SetUP XOR
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8)+(MAX_AMOUNT_LU_OR*8 );
            sLV.shAmtLUDsc = preSetUP.n_xor;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){
		
                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut 
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng  
            }
            //SetUP NOT
            sLV.shIdxLUOutDsc = MAX_AMOUNT_LU_OUTPUT+MAX_AMOUNT_LU_LED
            +(MAX_AMOUNT_LU_AND*8)+(MAX_AMOUNT_LU_OR*8 )+(MAX_AMOUNT_LU_XOR*2);
            sLV.shAmtLUDsc = preSetUP.n_not;sLV.shIdx = 0;
            while(sLV.shIdx < sLV.shAmtLUDsc){
		
                    sLV.lOrderNumber = GetTrueOrderNum();//Take OrdNum F-Block From Taras Area
                    locSBitFldCRefInfo.bfInfo_OrdNumOut  = 1;//Now use All ones
                    locSBitFldCRefInfo.bfInfo_IdLUStng   = STNG_LU_INPUT;
                    locSBitFldCRefInfo.bfInfo_BaseID     = sLV.lOrderNumber;
                    for (long j = 0; j < 8 ; j++){//Create data for each Input
                            locSBitFldCRefInfo.bfInfo_OrdNumStng = ORD_INPUT_01+j;
                            arrSBitFldCRefInfo[sLV.shIdxLUOutDsc+j] = locSBitFldCRefInfo;
                    }
                    //locSBitFld.bfInfo_OrdNumOut 
                    //locSBitFld.bfInfo_OrdNumStng
                    //locSBitFld.bfInfo_IdLUStng  
            }
     */
}

struct GlobalObjectMap_tag {

    CLUDInput_0_1 *arPCLUDInput_0_1[MAX_AMOUNT_LU_INPUT]; //NUM_STNG_IN
    CLUDout_1_0   *arPCLUDout_1_0  [MAX_AMOUNT_LU_OUTPUT]; //NUM_STNG_OUT
    CLULed        *arPCLULed       [MAX_AMOUNT_LU_LED]; //NUM_STNG_LED
    CLUNot_1_1    *arPCLUNot_1_1   [MAX_AMOUNT_LU_NOT];
    CLUOr_8_1     *arPCLUOr_8_1    [MAX_AMOUNT_LU_OR];
    CLUAnd_8_1    *arPCLUAnd_8_1   [MAX_AMOUNT_LU_AND];
    CLUXor_8_1    *arPCLUXor_8_1   [MAX_AMOUNT_LU_XOR];
	CMft          *arCMft          [MAX_AMOUNT_LU_TIMERS];
} GlobalObjectMap @ "variables_RAM1";
//Place 3 Unit

void Shematic::Init1(void) {
    long i, j;
    void* pv;
    //char **pCh;

    struct {
        char* pCh;
        char** arrPchIn;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase *pCLUBase, *pCLURef;
        void *pV;
        long lId, lsizeobj;
        short shAmtLU, shIdxLUOut; //
        short shAmtLUDsc, shIdx;
        short shIdxLUOutDsc, shIdxLU; //shCountCmd;
        char chVal, chErrCount, chBrk1, chBrk2;
        //unsigned char uchVal;
    } sLV;
    sLV.shIdx = sLV.shIdxLU = 0;
    sLV.chVal = static_cast<char> (preSetUP.n_input);
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    sLV.chErrCount = sLV.chBrk1 = sLV.chBrk2 = 0;
    sLV.shIdxLUOutDsc = 1;
    DetectCircutLinks();
    if (sLV.chVal) {

        CLUDInput_0_1 locCLUDInput_0_1(10, 0); // = CLUDInput_0_1(0,10);
        j = i = 0;
        do {
            j = InsertLU(LU_INPUT, static_cast<void*> (&locCLUDInput_0_1));

            if (j) {//Success Bield
                //Additional Obj SetUP

                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_INPUT;
                //sLV.uchVal = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                sLV.pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID);
                    sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUDInput_0_1* locPCLUDInput_0_1 = static_cast<CLUDInput_0_1*>(sLV.pCLUBase);
                locPCLUDInput_0_1->pOut = static_cast<void*>( locPCLUDInput_0_1->arrOut);
                CLUDInput_0_1& locRef_CLUDInput_0_1 = *(static_cast<CLUDInput_0_1*>(sLV.pCLUBase));
                locRef_CLUDInput_0_1.chTypeLogicFunction = LU_OP_READ_DI;
                locRef_CLUDInput_0_1.LogicFunc = READ_DI_Op; //???

                GlobalObjectMap.arPCLUDInput_0_1[sLV.shIdx++] = static_cast<CLUDInput_0_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }//Else Error

        } while (sLV.shIdxLU < preSetUP.n_input && j);
        //Check State j
    }
    sLV.shIdx = 0;
    if (preSetUP.n_output != 0) {
        sLV.shIdxLU = 0;
        j = 0;
        CLUDout_1_0 locCLUDout_1_0(10, 0); // = CLUDout_1_0(0,10);
        do {
            j = InsertLU(LU_OUTPUT, static_cast<void*> (&locCLUDout_1_0));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                pv = static_cast<void*>(&sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_OUTPUT;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUDout_1_0* locPCLUDout_1_0 = static_cast<CLUDout_1_0*>(sLV.pCLUBase);
                locPCLUDout_1_0->pIn = static_cast<void*> (locPCLUDout_1_0->arrPchIn);
                locPCLUDout_1_0->chTypeLogicFunction = LU_OP_SET_OUT;
                locPCLUDout_1_0->LogicFunc = SET_OUT_Op; //???

                GlobalObjectMap.arPCLUDout_1_0[sLV.shIdx++] = static_cast<CLUDout_1_0*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_output && j);
    }
    sLV.shIdx = 0;
    if (preSetUP.n_led != 0) {
        volatile short shIdxLU = 0;
        j = 0; //sLV.shIdxLU = 0;
        CLULed locCLULed(10, 0); // = CLULed(0,10);
        do {
            j = InsertLU(LU_LED, static_cast<void*>(&locCLULed));
            //sLV.shIdxLU++;
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_LED;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLULed* locPCLULed = static_cast<CLULed*>(sLV.pCLUBase);
                locPCLULed->pIn = static_cast<void*>(locPCLULed->arrPchIn);
                CLULed& locRef_CLULed = *(static_cast<CLULed*>(sLV.pCLUBase));
                locRef_CLULed.chTypeLogicFunction = LU_OP_SET_LED;
                locRef_CLULed.LogicFunc = SET_LED_Op; //???
                GlobalObjectMap.arPCLULed[sLV.shIdx++] = static_cast<CLULed*>(sLV.pCLUBase);
                shIdxLU++; //
            }

        } while (shIdxLU < preSetUP.n_led && j);
    }
    sLV.shIdx = 0;
    if (preSetUP.n_and != 0) {
        sLV.shIdxLU = 0;
        j = 0;
        CLUAnd_8_1 locCLUAnd_8_1(10, 0); // = CLUAnd_8_1(0,10);
        do {
            j = InsertLU(LU_AND, static_cast<void*>(&locCLUAnd_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_AND;
                sLV.pCLUBase->shShemasOrdNumStng = arrSBitFldCRefInfo[sLV.shIdxLUOutDsc-1].bfInfo_BaseID;
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUAnd_8_1* locPCLUAnd_8_1 = static_cast<CLUAnd_8_1*>(sLV.pCLUBase);
                locPCLUAnd_8_1->pOut = static_cast<void*>(locPCLUAnd_8_1->arrOut  );
                locPCLUAnd_8_1->pIn  = static_cast<void*>(locPCLUAnd_8_1->arrPchIn);
                CLUAnd_8_1& locRef_CLUAnd_8_1 = *(static_cast<CLUAnd_8_1*>(sLV.pCLUBase));
                locRef_CLUAnd_8_1.chTypeLogicFunction = LU_OP_AND; //
                locRef_CLUAnd_8_1.LogicFunc = AND_Op_8_1; //???

                GlobalObjectMap.arPCLUAnd_8_1[sLV.shIdx++] = static_cast<CLUAnd_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_and && j);
    }

    if (preSetUP.n_or != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUOr_8_1 locCLUOr_8_1(10, 0); // = CLUOr_8_1(0,10);
        do {
            j = InsertLU(LU_OR, static_cast<void*>(&locCLUOr_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_OR;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUOr_8_1* locPCLUOr_8_1 = static_cast<CLUOr_8_1*>(sLV.pCLUBase);
                locPCLUOr_8_1->pOut = static_cast<void*>(locPCLUOr_8_1->arrOut  );
                locPCLUOr_8_1->pIn  = static_cast<void*>(locPCLUOr_8_1->arrPchIn);
                CLUOr_8_1& locRef_CLUOr_8_1 = *(static_cast<CLUOr_8_1*>(sLV.pCLUBase));
                locRef_CLUOr_8_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUOr_8_1[sLV.shIdx++] = static_cast<CLUOr_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_or && j);
    }
    if (preSetUP.n_xor != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUXor_8_1 locCLUXor_8_1(10, 0); // = CLUXor_8_1(0,10);
        do {
            j = InsertLU(LU_XOR, static_cast<void*>(&locCLUXor_8_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_XOR;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUXor_8_1* locPCLUXor_8_1 = static_cast<CLUXor_8_1*>(sLV.pCLUBase);
                locPCLUXor_8_1->pOut =  static_cast<void*>(locPCLUXor_8_1->arrOut  );
                locPCLUXor_8_1->pIn  =  static_cast<void*>(locPCLUXor_8_1->arrPchIn);
                CLUXor_8_1& locRef_CLUXor_8_1 = *(static_cast<CLUXor_8_1*>(sLV.pCLUBase));
                locRef_CLUXor_8_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUXor_8_1[sLV.shIdx++] = static_cast<CLUXor_8_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_xor && j);
    }
    if (preSetUP.n_not != 0) {
        sLV.shIdx = sLV.shIdxLU = 0;
        j = 0;
        CLUNot_1_1 locCLUNot_1_1(10, 0); // = CLUNot_1_1(0,10);
        do {
            j = InsertLU(LU_NOT, static_cast<void*>(&locCLUNot_1_1));
            if (j) {//Success Bield
                //Additional Obj SetUP
                i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
                //pv = (void*) &sLV.arrLUAreaListElem[i - 1];
                //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
				pv = static_cast<void*>( &sLV.arrLUAreaListElem[i - 1]);
                sLV.pCLUBase = static_cast<CLUBase*>( ( static_cast<LUAreaListElem*>(pv) )->pvLU);
                sLV.pCLUBase->shShemasIdLUStng = STNG_LU_NOT;
                sLV.pCLUBase->shShemasOrdNumStng =
                        sLV.shIdxLUOutDsc++; //Temporary Numeration Discass It!!!!;
                CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(sLV.pCLUBase);
                locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut  );
                locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
                CLUNot_1_1& locRef_CLUNot_1_1 = *(static_cast<CLUNot_1_1*>(sLV.pCLUBase));
                locRef_CLUNot_1_1.LogicFunc(sLV.pCLUBase);
                GlobalObjectMap.arPCLUNot_1_1[sLV.shIdx++] = static_cast<CLUNot_1_1*>(sLV.pCLUBase);
                sLV.shIdxLU++;
            }

        } while (sLV.shIdxLU < preSetUP.n_not && j);
    }

    //1 Place points In MemArea
    //Place Unit
    //If I try delete operation It shold move all data for efficiently
    //memory Use

    //SetUP Links
    sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    //Find 1st DO
    i = j = sLV.shIdxLUOutDsc = sLV.shIdxLU = 0;
    sLV.lId = 0;
    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]); //Last Elem
    sLV.shAmtLU = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    sLV.shAmtLUDsc = 10 + 10 + 8 * 1; //Demo Variant
    while (sLV.shAmtLUDsc && sLV.chBrk2 == 0) {
        while (sLV.shIdxLU < sLV.shAmtLU && sLV.chBrk1 == 0) {
            i = sLV.shIdxLU;
            pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]);
            sLV.pCLUBase = static_cast<CLUBase*>( (static_cast<LUAreaListElem*>(pv))->pvLU);
            j = sLV.shIdxLUOutDsc;
            if (sLV.pCLUBase->shShemasIdLUStng == ar_n_output_CRDsc[j].shBaseIdLUStng &&
                    sLV.pCLUBase->shShemasOrdNumStng == ar_n_output_CRDsc[j].shBaseOrdNumStng) {
                sLV.pV = pv; //save pv
                sLV.chVal = sLV.pCLUBase->chNumOutput;
                for (sLV.shIdx = 0; sLV.shIdx < sLV.pCLUBase->chNumInput; sLV.shIdx++) {//sLV.pCLUBase->chNumOutput
                    //Find
                    //,,pv = (void*)&sLV.arrLUAreaListElem[0];//Last Elem
                    sLV.chVal = 0;
                    i = 0;
                    sLV.pCh = static_cast<char*>(0);
                    j = sLV.shIdxLUOutDsc + sLV.shIdx;
                    while (i < sLV.shAmtLU) {
                        pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]);
                        sLV.pCLURef = static_cast<CLUBase*>( (static_cast<LUAreaListElem*>(pv))->pvLU);
                        if ((sLV.pCLURef->shShemasIdLUStng == ar_n_output_CRDsc[j].shRefIdLUStng) &&
                                (sLV.pCLURef->shShemasOrdNumStng == ar_n_output_CRDsc[j].shRefOrdNumStng)
                                && (sLV.shIdx == (ar_n_output_CRDsc[j].chRefOrdNumOut - 1))) {
                            sLV.pCh = static_cast<char*>(sLV.pCLURef->pOut);
                            sLV.pCh += ar_n_output_CRDsc[j].chRefOrdNumOut - 1;
                            sLV.chVal++; //Counter success
                            break;
                        }
                        i++;
                    }
                    if (sLV.pCh) {
                        sLV.arrPchIn = static_cast<char**>(sLV.pCLUBase->pIn);
                        sLV.arrPchIn[sLV.shIdx] = sLV.pCh;
                        j++;
                        //Check Next Statment
                        if (sLV.pCLUBase->shShemasIdLUStng != ar_n_output_CRDsc[j].shBaseIdLUStng
                                || sLV.pCLUBase->shShemasOrdNumStng != ar_n_output_CRDsc[j].shBaseOrdNumStng
                                ) {
                            sLV.shIdx = sLV.pCLUBase->chNumInput;
                            break; //goto ;//Break For
                        }
                    }
                }
                if (sLV.chVal) {//Succes SetUP
                    if (sLV.shAmtLUDsc >= sLV.chVal) {
                        sLV.shAmtLUDsc -= sLV.chVal;
                        sLV.shIdxLUOutDsc += sLV.chVal;
                        //goto;
                    } else {
                        //Fix Error
                        sLV.chErrCount++; //Wrong Setup Val
                        sLV.chBrk2 |= 1; //goto;Stop Execution
                    }

                } else {
                    sLV.chErrCount++; //Fix Error
                    //Not Found Out Elem Situation
                    //sLV.chBrk2 |= ;//goto;
                    sLV.lId |= 2;
                }
                sLV.chBrk1 |= 1;
            }
            //.if(sLV.chBrk1==0){
            //.
            //.}Next Iteration while(sLV.shIdxLU<sLV.shAmtLU)
            sLV.shIdxLU++;
        }
        sLV.shIdxLU = 0;
        sLV.chBrk1 = 0;
        //Check Error
        if (sLV.lId & 2) {
            //Not Found Out Elem Situation
            sLV.shAmtLUDsc -= 1;
            sLV.shIdxLUOutDsc += 1;
            sLV.lId &= ~2;
        }
    }
    //Scan Info on Leds


}

long Shematic::EvalSizeObj(long lId) {
    long lsizeObj;
    switch (lId) {
        case BASE_POINT:
            lsizeObj = SIZE_BASE_IN_POINT;
            break;
        case POINT:
            lsizeObj = SIZE_IN_POINT;
            break;
        case EXTENDED:
            lsizeObj = sizeof (ExtPoint);
            break;
        case LU_AND:
            lsizeObj = sizeof (CLUAnd_8_1);
            break;
        case LU_OR:
            lsizeObj = sizeof (CLUOr_8_1);
            break;
        case LU_XOR:
            lsizeObj = sizeof (CLUXor_8_1);
            break;
        case LU_NOT:
            lsizeObj = sizeof (CLUNot_1_1);
            break;
        case LU_MFT:
            lsizeObj = sizeof (CMft);
            break;
        //case LU_TIMERS:
            //case LU_TRIGGERS:
            //case LU_ALARMS:
            //case LU_MEANDERS:

        case LU_INPUT:
            lsizeObj = sizeof (CLUDInput_0_1);
            break;
        case LU_OUTPUT:
            lsizeObj = sizeof (CLUDout_1_0);
            break;
        case LU_LED:
            lsizeObj = sizeof (CLULed);
            break;

        default:
            lsizeObj = 0;
    }
    //ExitEval
    return lsizeObj;
}

long Shematic::InsertLU(long lId, void*pvObjImage) {
    register long i;
    register void* pv;

    struct {
        long lId, lsizeobj;
        void *pV;
        LUAreaListElem* arrLUAreaListElem;
        CLUBase* pCLUBase;
    } sLV;
    //check Id
    sLV.lsizeobj = 0;
    i = EvalSizeObj(lId);
    if (i) {

        //Check pvObjImage
        if (pvObjImage != 0) {
            //check Free Memory
            pv = static_cast<void*>(&gblLUAreaAuxVar);
            if ((static_cast<LUAreaAuxVar*>(pv))->lAmountFreeMem >=
                    static_cast<long>(i + SIZE_LU_AREA_LIST_ITEM)) {
                sLV.lId = lId; //Save Id
                sLV.lsizeobj = i;
                sLV.pV = pv;
                sLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
                i = (static_cast<LUAreaAuxVar*>(pv))->shAmountPlacedLogicUnit; //Now Index in LUAreaListElem

                if (i) {
                    i--; //Detect Head
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i]); //Last Elem
                    //Mem Area
                    lId = reinterpret_cast<long>(( static_cast<LUAreaListElem*>(pv))->pvLU);
                    //Add size
                    lId -= sLV.lsizeobj; //((LUAreaListElem*)pv)->shSizeLU;
                    //gblLUAreaAuxVar.pvHead -= ((LUAreaListElem*)pv)->shSizeLU
                    memcpy(reinterpret_cast<void*>(lId), pvObjImage, sLV.lsizeobj);
                    pv = static_cast<void*>(&sLV.arrLUAreaListElem[i + 1]); //Next
                    (static_cast<LUAreaListElem*>(pv))->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->shIdLU   = static_cast<short>(sLV.lId);
                    (static_cast<LUAreaListElem*>(pv))->pvLU     = reinterpret_cast<void*>(lId);
                    gblLUAreaAuxVar.pvHead = reinterpret_cast<void*>(lId); // (lId - sLV.lId);//For check Only
                    //sLV.pCLUBase = ((LUAreaListElem*) pv)->pvLU;
                    sLV.pCLUBase = static_cast<CLUBase*> (
                            (static_cast<LUAreaListElem*> (pv))->pvLU);
                } else {
                    pv = static_cast<void*>(&gLUAreaMem.headLUAreaList);

                    //First Init
                    lId = reinterpret_cast<long>(&gLUAreaMem.chArRamPrgEvt[SIZE_MEM_BLK]);
                    lId -= (sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv))->pvLU = reinterpret_cast<void*>(lId);
                    memcpy(reinterpret_cast<void*>(lId), pvObjImage, sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv) )->shSizeLU = static_cast<short>(sLV.lsizeobj);
                    (static_cast<LUAreaListElem*>(pv) )->shIdLU =   static_cast<short>(sLV.lId);
                    gblLUAreaAuxVar.pvHead = gblLUAreaAuxVar.pvTail =
                            (static_cast<LUAreaListElem*> (pv))->pvLU;
                    //sLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                    sLV.pCLUBase = static_cast<CLUBase*> (
                            (static_cast<LUAreaListElem*> (pv))->pvLU);
                }
                //Bield Obj in Mem


                //((LUAreaAuxVar*)pv)-> pvHead
                sLV.pCLUBase->SetOrderNumber(); //((LUAreaAuxVar*)pv)->shAmountPlacedLogicUnit += 1;
                pv = static_cast<void*>(&gblLUAreaAuxVar);
                //?!!!((LUAreaAuxVar*) pv)->lAmountFreeMem -= ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                //?!!!((LUAreaAuxVar*) pv)->lAmountUsedMem += ((short) sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*> (pv))->lAmountFreeMem -= (sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
                (static_cast<LUAreaAuxVar*>(pv))->lAmountUsedMem += ( sLV.lsizeobj + SIZE_LU_AREA_LIST_ITEM);
				
            } else sLV.lsizeobj = 0;
        }
        return static_cast<long>(sLV.lsizeobj);
    }



    return 0; //AmountObj
}

void Shematic::DetectCircutLinks(void) {
    //Register Data In CrossRef Array
    long i, j;
    //    char **pCh;

    struct {
        short shAmtLU, shIdx;
        short shCounterScanedObj;
        long lBaseOrdNumStng;
        SBitFld_LUInInfo locSBitFld;
    } sLV;

    sLV.shIdx = sLV.shAmtLU = 0;
    if (preSetUP.n_input != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_input;
        sLV.lBaseOrdNumStng = 0;
        j = i = 0;
        ResetarNum();
        do {
            //Get Obj by Index
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                // i = sLV.shCounterScanedObj; 
                arrSBitFldCRefInfo[i+ j].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i+ j].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i+ j].sBitLUInputInfo = ar_n__Output_Dsc[j];
                j++;
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_output != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_output;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_input;
        i = sLV.shIdx;//Offset Output
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                i = sLV.shCounterScanedObj+sLV.shIdx;
                arrSBitFldCRefInfo[i].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i].sBitLUInputInfo = ar_n__Output_Dsc[j];//Take data from Taras
                j++;
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_led != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_led;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_output*shCLUDout_1_0_AmtIn;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj+sLV.shIdx;
                arrSBitFldCRefInfo[i].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                arrSBitFldCRefInfo[i].bfInfo_OrdNumIn = 1;
                arrSBitFldCRefInfo[i].sBitLUInputInfo = ar_n__Output_Dsc[j];
                j++;
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_and != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_and;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_led*shCLULed_1_0_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj); //HashIdLU
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUAnd_8_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc; 
                for (long ik = 0; ik < shCLUAnd_8_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;
                    
                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_And_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;
                            //ar_n_And_Dsc[j+i+ik].UN_BitFld_LUInInfo.sBitFld_LUInInfo;
                    j++;//Can take change in any aviable way
                    
                }

                
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_or != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_or;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_and*shCLUAnd_8_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUOr_8_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc; 
                for (long ik = 0; ik < shCLUOr_8_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;
                    
                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Or_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;
                         
                    j++;//Can take change in any aviable way
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_xor != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_xor;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_or*shCLUOr_8_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUXor_2_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc; 
                for (long ik = 0; ik < shCLUXor_2_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;
                    
                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Xor_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;
                         
                    j++;//Can take change in any aviable way
                }
            }

        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_not != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_not;
         j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_xor*shCLUXor_2_1_AmtIn;
        i = sLV.shIdx;
        ResetarNum();
        do {
            //Get Obj
            GetHIDLU(&sLV.lBaseOrdNumStng, sLV.shCounterScanedObj);
            //In test read data from External Storage
            if (sLV.lBaseOrdNumStng) {//Element present
                 i = sLV.shCounterScanedObj*shCLUNot_1_1_AmtIn+sLV.shIdx;
                SBitFld_LUInInfo locSBitFld_LUInInfo;//LUInInfoDsc locLUInInfoDsc; 
                for (long ik = 0; ik < shCLUNot_1_1_AmtIn; ik++) {
                    arrSBitFldCRefInfo[i+ik].bfInfo_BaseID = sLV.lBaseOrdNumStng;
                    arrSBitFldCRefInfo[i+ik].bfInfo_OrdNumIn = 1+ik;
                    
                    locSBitFld_LUInInfo.bfInfo_OrdNumOut  = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumOut;
                    locSBitFld_LUInInfo.bfInfo_IdLUStng   = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_IdLUStng;
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = ar_n_Not_Dsc[j].UN_BitFld_LUInInfo.sBitFld_LUInInfo.bfInfo_OrdNumStng;
                    arrSBitFldCRefInfo[i+ik].sBitLUInputInfo = locSBitFld_LUInInfo;
                         
                    j++;//Can take change in any aviable way
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    sLV.shIdx = 0;
//Set Actual Links
    if (preSetUP.n_input != 0) {
        //Detect Number Input
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_input;
        sLV.lBaseOrdNumStng = 0;
        j = i = 0;
        SBitFld_LUInInfo locSBitFld_LUInInfo;
        short shRelativeNumber = 0;
        short shIdLUStng       = 0;
        short shIdx_arrSBitFldCRefInfo = 0;
        do {
            //Change offset on real Number 
            i = sLV.shCounterScanedObj; //
            locSBitFld_LUInInfo = arrSBitFldCRefInfo[i].sBitLUInputInfo;
            shIdLUStng          = locSBitFld_LUInInfo.bfInfo_IdLUStng;
            //Get Index in LU sequence
            switch (shIdLUStng) {
                case STNG_LU_AND:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led;
                    break;
                    
                case STNG_LU_OR:
                     shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and;
                    break;
                    
                case STNG_LU_XOR:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and
                     + shCLUOr_8_1_AmtIn*preSetUP.n_or ;
                    break;
                    
                case STNG_LU_INPUT:
                    shIdx_arrSBitFldCRefInfo = 0;
                    break;
                    
                case STNG_LU_OUTPUT:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input;
                    break;
                    
                case STNG_LU_LED:
                    shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                        +preSetUP.n_output;
                    break;
                    
                case STNG_LU_NOT:
                       shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                     + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and
                     + shCLUOr_8_1_AmtIn*preSetUP.n_or + shCLUXor_2_1_AmtIn*preSetUP.n_xor ;
                    break;
                    
                    
                default:
                    shIdx_arrSBitFldCRefInfo = -1;
            }
             
            shRelativeNumber = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
            if(shIdx_arrSBitFldCRefInfo!= (-1)){
            //Find Element
                    j = shIdx_arrSBitFldCRefInfo + shRelativeNumber-1;//Only Now
                    locSBitFld_LUInInfo.bfInfo_OrdNumStng = arrSBitFldCRefInfo[j].bfInfo_BaseID; //sLV.lBaseOrdNumStng
                    arrSBitFldCRefInfo[i].sBitLUInputInfo.bfInfo_OrdNumStng
                            = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
            }
            
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += preSetUP.n_input;
    }
    
    if (preSetUP.n_output != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_output;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + sLV.shCounterScanedObj;
            ChangeStngOrdnumRelOnBase(i);
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += sLV.shCounterScanedObj;
    }
    if (preSetUP.n_led != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_led;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + sLV.shCounterScanedObj;
            ChangeStngOrdnumRelOnBase(i);
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += sLV.shCounterScanedObj;
    }
    if (preSetUP.n_and != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_and;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUAnd_8_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUAnd_8_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUAnd_8_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_or != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_or;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUOr_8_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUOr_8_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUOr_8_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_xor != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_xor;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUXor_2_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUXor_2_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUXor_2_1_AmtIn*sLV.shCounterScanedObj;
    }
    if (preSetUP.n_not != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_not;
        sLV.lBaseOrdNumStng = 0;
        do {
            i = sLV.shIdx + shCLUNot_1_1_AmtIn*sLV.shCounterScanedObj;
            for(long ik = 0; ik < shCLUNot_1_1_AmtIn; ik++){
                ChangeStngOrdnumRelOnBase(i+ik);
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
        sLV.shIdx += shCLUNot_1_1_AmtIn*sLV.shCounterScanedObj;
    }
    
}
void Shematic::ChangeRelativeOnEvalLinks(void){

//Scan OutPut

   


}

void Shematic::ChangeStngOrdnumRelOnBase(long lIdxScanedObj) {
    register long i,j;
    SBitFld_LUInInfo locSBitFld_LUInInfo;
    short shRelativeNumber = 0;
    short shIdLUStng       = 0;
    short shIdx_arrSBitFldCRefInfo = 0;
    i = j = 0;
 //   do {
            //Change offset on real Number 
            i = lIdxScanedObj; //i = sLV.shCounterScanedObj; //
    locSBitFld_LUInInfo = arrSBitFldCRefInfo[i].sBitLUInputInfo;
    shIdLUStng = locSBitFld_LUInInfo.bfInfo_IdLUStng;
    //Get Index in LU sequence
    switch (shIdLUStng) {
        case STNG_LU_AND:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led;
            break;

        case STNG_LU_OR:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and;
            break;

        case STNG_LU_XOR:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn * preSetUP.n_or;
            break;

        case STNG_LU_INPUT:
            shIdx_arrSBitFldCRefInfo = 0;
            break;

        case STNG_LU_OUTPUT:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input;
            break;

        case STNG_LU_LED:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output;
            break;

        case STNG_LU_NOT:
            shIdx_arrSBitFldCRefInfo = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn * preSetUP.n_or + shCLUXor_2_1_AmtIn * preSetUP.n_xor;
            break;


        default:
            shIdx_arrSBitFldCRefInfo = -1;
    }

    shRelativeNumber = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
    if (shIdx_arrSBitFldCRefInfo != (-1)) {
        //Find Element
        j = shIdx_arrSBitFldCRefInfo + shRelativeNumber - 1; //Only Now
        locSBitFld_LUInInfo.bfInfo_OrdNumStng = arrSBitFldCRefInfo[j].bfInfo_BaseID; //sLV.lBaseOrdNumStng
        arrSBitFldCRefInfo[i].sBitLUInputInfo.bfInfo_OrdNumStng
                = locSBitFld_LUInInfo.bfInfo_OrdNumStng;
    }
    
//        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    
}

void Shematic::Init2(void) {
    register long  j;
//    register void* pv;  
    Init2LcVarArea lsLcVarArea;//lsLc -local struct Local Area
    lsLcVarArea.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
    DetectCircutLinks();
    lsLcVarArea.shCounterInitCLUObj = 1;
    if( preSetUP.n_input ){
        CLUDInput_0_1 locCLUDInput_0_1(10, 0); // = CLUDInput_0_1(0,10);
        short shLC__n_input = preSetUP.n_input;
        short shCounterInitCLUDIn = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_INPUT, static_cast<void*>(&locCLUDInput_0_1));
            
            if (j) {//Success Bield
                SetupCLUDInput_0_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUDIn++;
            }//Else Error
            
        } while (shCounterInitCLUDIn < shLC__n_input && j);
    }
    if (preSetUP.n_output != 0) {
        CLUDout_1_0 locCLUDout_1_0(10, 0);
        short shLC__n_output = preSetUP.n_output;
        short shCounterInitCLUDout = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_OUTPUT, static_cast<void*>(&locCLUDout_1_0));
            
            if (j) {//Success Bield
                SetupCLUDout_1_0StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUDout++;
            }//Else Error
        } while (shCounterInitCLUDout < shLC__n_output && j);
    }
    if (preSetUP.n_led != 0) {
        CLULed locCLULed(10, 0);
        short shLC__n_led = preSetUP.n_led;
        short shCounterInitCLULed = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_LED, static_cast<void*>(&locCLULed));
        if (j) {//Success Bield
                SetupCLULedStngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLULed++;
            }//Else Error
        } while (shCounterInitCLULed < shLC__n_led && j);
    }
    if (preSetUP.n_and != 0) {
        CLUAnd_8_1 locCLUAnd_8_1(10, 0);
        short shLC__n_and = preSetUP.n_and;
        short shCounterInitCLUAnd = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_AND, static_cast<void*>(&locCLUAnd_8_1));
        if (j) {//Success Bield
                SetupCLUAnd_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUAnd++;
            }//Else Error
        } while (shCounterInitCLUAnd < shLC__n_and && j);
    }
    if (preSetUP.n_or != 0) {
        CLUOr_8_1 locCLUOr_8_1(10, 0);
        short shLC__n_or = preSetUP.n_or;
        short shCounterInitCLUOr = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_OR, static_cast<void*>(&locCLUOr_8_1));
        if (j) {//Success Bield
                SetupCLUOr_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUOr++;
            }//Else Error
        } while (shCounterInitCLUOr < shLC__n_or && j);
    }
    if (preSetUP.n_xor != 0) {
        CLUXor_8_1 locCLUXor_8_1(10, 0);
        short shLC__n_xor = preSetUP.n_xor;
        short shCounterInitCLUXor = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_XOR, static_cast<void*>(&locCLUXor_8_1));
        if (j) {//Success Bield
                SetupCLUXor_8_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUXor++;
            }//Else Error
        } while (shCounterInitCLUXor < shLC__n_xor && j);
    }
    if (preSetUP.n_not != 0) {
        CLUNot_1_1 locCLUNot_1_1(10, 0);
        short shLC__n_not = preSetUP.n_not;
        short shCounterInitCLUNot = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_NOT, static_cast<void*>(&locCLUNot_1_1));
        if (j) {//Success Bield
                SetupCLUNot_1_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCLUNot++;
            }//Else Error
        } while (shCounterInitCLUNot < shLC__n_not && j);
    }
    if (preSetUP.n_timers != 0) {
        CMft locCMft(10, 0);
        short shLC__n_timers = preSetUP.n_timers;
        short shCounterInitCMft = 0;
        lsLcVarArea.shIdxGlobalObjectMapPointers = 0;
        j = 0;
        do {
            j = InsertLU(LU_MFT, static_cast<void*>(&locCMft));
        if (j) {//Success Bield
                SetupCLUMft_2_1StngParam(static_cast<void*>(&lsLcVarArea));
                shCounterInitCMft++;
            }//Else Error
        } while (shCounterInitCMft < shLC__n_timers && j);
    }
    
SetupCircutLinks(static_cast<void*>(&lsLcVarArea));

}

void Shematic::SetupCLUDInput_0_1StngParam(void *pv){
    register long i;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
	
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng = STNG_LU_INPUT;
    i = pInit2LcVarArea->shCounterInitCLUObj-1; //sLV.shIdxLUOutDsc-1
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUDInput_0_1* locPCLUDInput_0_1 = static_cast<CLUDInput_0_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUDInput_0_1->pOut = static_cast<void*>(locPCLUDInput_0_1->arrOut);
    CLUDInput_0_1& locRef_CLUDInput_0_1 =
            *(static_cast<CLUDInput_0_1*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUDInput_0_1.chTypeLogicFunction = LU_OP_READ_DI;
    locRef_CLUDInput_0_1.LogicFunc = READ_DI_Op; //???
    i = pInit2LcVarArea->shIdxGlobalObjectMapPointers;//
            
    GlobalObjectMap.arPCLUDInput_0_1[i] = static_cast<CLUDInput_0_1*>(
            pInit2LcVarArea->pCLUBase); //sLV.pCLUBase;
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++           
}
void Shematic::SetupCLUDout_1_0StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
	(static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_OUTPUT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUDout_1_0* locPCLUDout_1_0 = static_cast<CLUDout_1_0*>(pInit2LcVarArea->pCLUBase);
    locPCLUDout_1_0->pIn = static_cast<void*>(locPCLUDout_1_0->arrPchIn);
    locPCLUDout_1_0->arrPchIn[0] = &chGblGround;
    locPCLUDout_1_0->chTypeLogicFunction = LU_OP_SET_OUT;
    locPCLUDout_1_0->LogicFunc = SET_OUT_Op; //???
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    GlobalObjectMap.arPCLUDout_1_0[j] = static_cast<CLUDout_1_0*>(
       pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++           
}
void Shematic::SetupCLULedStngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_LED;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLULed* locPCLULed = static_cast<CLULed*>(pInit2LcVarArea->pCLUBase);
    locPCLULed->pIn = static_cast<void*>(locPCLULed->arrPchIn);
    CLULed& locRef_CLULed = *(static_cast<CLULed*>(pInit2LcVarArea->pCLUBase));
    locRef_CLULed.arrPchIn[0] = &chGblGround;
    locRef_CLULed.chTypeLogicFunction = LU_OP_SET_LED;
    locRef_CLULed.LogicFunc = SET_LED_Op; //???
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arPCLULed[j] = static_cast<CLULed*>(
      pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}
void Shematic::SetupCLUAnd_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_AND;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUAnd_8_1* locPCLUAnd_8_1 = static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUAnd_8_1->pOut = static_cast<void*>(locPCLUAnd_8_1->arrOut);
    locPCLUAnd_8_1->pIn  = static_cast<void*>(locPCLUAnd_8_1->arrPchIn);
    CLUAnd_8_1& locRef_CLUAnd_8_1 = *(static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUAnd_8_1.chTypeLogicFunction = LU_OP_AND; //
     for(i = 0; i < locRef_CLUAnd_8_1.chNumInput;i++)
    locRef_CLUAnd_8_1.arrPchIn[i] = &chGblVcc;
    locRef_CLUAnd_8_1.LogicFunc = AND_Op_8_1; //???

    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arPCLUAnd_8_1[j] = static_cast<CLUAnd_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}
void Shematic::SetupCLUOr_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_OR;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUOr_8_1* locPCLUOr_8_1 = static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUOr_8_1->pOut = static_cast<void*>(locPCLUOr_8_1->arrOut);
    locPCLUOr_8_1->pIn  = static_cast<void*>(locPCLUOr_8_1->arrPchIn);
    CLUOr_8_1& locRef_CLUOr_8_1 = *(static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUOr_8_1.chNumInput;i++)
    locRef_CLUOr_8_1.arrPchIn[i] = &chGblGround;
    locRef_CLUOr_8_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arPCLUOr_8_1[j] = 
      static_cast<CLUOr_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}
void Shematic::SetupCLUXor_8_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_XOR;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUXor_8_1* locPCLUXor_8_1 = static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUXor_8_1->pOut = static_cast<void*>(locPCLUXor_8_1->arrOut);
    locPCLUXor_8_1->pIn  = static_cast<void*>(locPCLUXor_8_1->arrPchIn);
    CLUXor_8_1& locRef_CLUXor_8_1 = *(static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < locRef_CLUXor_8_1.chNumInput;i++)
    locRef_CLUXor_8_1.arrPchIn[i] = &chGblGround;
    locRef_CLUXor_8_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arPCLUXor_8_1[j] = 
      static_cast<CLUXor_8_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}
void Shematic::SetupCLUNot_1_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
	pInit2LcVarArea->pCLUBase = static_cast<CLUBase*>( 
                        (static_cast<LUAreaListElem*>(pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_NOT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut);
    locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CLUNot_1_1& locRef_CLUNot_1_1 = *(static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase));
    locRef_CLUNot_1_1.LogicFunc(pInit2LcVarArea->pCLUBase);
    for(i = 0; i < locRef_CLUNot_1_1.chNumInput;i++)
    locRef_CLUNot_1_1.arrPchIn[i] = &chGblGround;
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arPCLUNot_1_1[j] = 
      static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}
void Shematic::SetupCLUMft_2_1StngParam(void *pv){
    register long i,j;
    register Init2LcVarArea *pInit2LcVarArea = static_cast<Init2LcVarArea*>(pv);
    i = gblLUAreaAuxVar.shAmountPlacedLogicUnit;
    pv = static_cast<void*>(&(pInit2LcVarArea->arrLUAreaListElem[i-1]));
    //pInit2LcVarArea->pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
    pInit2LcVarArea->pCLUBase = static_cast<CLUBase*> (
            (static_cast<LUAreaListElem*> (pv))->pvLU);
    pInit2LcVarArea->pCLUBase->shShemasIdLUStng =  STNG_LU_MFT;
    i = pInit2LcVarArea->shCounterInitCLUObj - 1;
    pInit2LcVarArea->pCLUBase->shShemasOrdNumStng = static_cast<unsigned char>(
    arrSBitFldCRefInfo[i].bfInfo_BaseID);
    pInit2LcVarArea->shCounterInitCLUObj++;// sLV.shIdxLUOutDsc++;
    //CLUNot_1_1* locPCLUNot_1_1 = static_cast<CLUNot_1_1*>(pInit2LcVarArea->pCLUBase);
    //locPCLUNot_1_1->pOut = static_cast<void*>(locPCLUNot_1_1->arrOut);
    //locPCLUNot_1_1->pIn  = static_cast<void*>(locPCLUNot_1_1->arrPchIn);
    CMft& rCMft = *(static_cast<CMft*>(pInit2LcVarArea->pCLUBase));
    for(i = 0; i < rCMft.chNumInput;i++)
    rCMft.arrPchIn[i] = &chGblGround;
    
    rCMft.UpdateCMft();
    i = rCMft.LinkMftTimers();
    if(i==3 ){
       rCMft.chTypeLogicFunction = LU_OP_MFT; //
       rCMft.LogicFunc = Mft_Op;  
    }
    rCMft.LogicFunc(pInit2LcVarArea->pCLUBase);
    //???
    j = pInit2LcVarArea->shIdxGlobalObjectMapPointers;
    
    GlobalObjectMap.arCMft[j] = 
      static_cast<CMft*>(pInit2LcVarArea->pCLUBase);
    pInit2LcVarArea->shIdxGlobalObjectMapPointers++;//sLV.shIdx++          
}


void GetHIDLU(void*pv, long lIdxLUinStng) {
    register long i;
    i = Shematic::GetTrueOrderNum();
    *(static_cast<long*>(pv)) = i;
	//Aux OP
	LL_CryaCrya += lIdxLUinStng>>16;
}

void ResetarNum(void) {
    for (long j = 0; j < 300; j++)
        arNum[j] = 0;
	shCounterCalls_GLB = 0;	
}

long  Shematic::EvalIdxibnarrSBitFldCRefInfo(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case STNG_LU_AND:
            j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led;
            break;

        case STNG_LU_OR:
             j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and;
            break;

        case STNG_LU_XOR:
            j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + shCLUAnd_8_1_AmtIn*preSetUP.n_and
             + shCLUOr_8_1_AmtIn*preSetUP.n_or ;
            break;

        case STNG_LU_INPUT:
            j = 0;
            break;

        case STNG_LU_OUTPUT:
            j = preSetUP.n_input;
            break;

        case STNG_LU_LED:
            j = preSetUP.n_input
                +preSetUP.n_output;
            break;

        case STNG_LU_NOT:
            j = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led 
                    + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn  * preSetUP.n_or 
                    + shCLUXor_2_1_AmtIn * preSetUP.n_xor;
            break;
        case STNG_LU_MFT:
            j = preSetUP.n_input
                    + preSetUP.n_output + preSetUP.n_led
                    + shCLUAnd_8_1_AmtIn * preSetUP.n_and
                    + shCLUOr_8_1_AmtIn  * preSetUP.n_or 
                    + shCLUXor_2_1_AmtIn * preSetUP.n_xor
                    + shCLUNot_1_1_AmtIn * preSetUP.n_not;
            break;

        default:
            j = -1;
    }
      return j;       
            
}
long  Shematic::EvalIdxinarrLUAreaListElem(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case STNG_LU_AND:
            j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led;
            break;

        case STNG_LU_OR:
             j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + preSetUP.n_and;
            break;

        case STNG_LU_XOR:
            j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + preSetUP.n_and
             + preSetUP.n_or ;
            break;

        case STNG_LU_INPUT:
            j = 0;
            break;

        case STNG_LU_OUTPUT:
            j = preSetUP.n_input;
            break;

        case STNG_LU_LED:
            j = preSetUP.n_input
                +preSetUP.n_output;
            break;

        case STNG_LU_NOT:
               j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + preSetUP.n_and
             + preSetUP.n_or + preSetUP.n_xor ;
            break;
        case STNG_LU_MFT:
               j = preSetUP.n_input
             + preSetUP.n_output + preSetUP.n_led + preSetUP.n_and
             + preSetUP.n_or + preSetUP.n_xor + preSetUP.n_not;
            break;

        default:
            j = -1;
    }
      return j;       
            
}
long  Shematic::EvalAmtIn_arrLUAreaListElem(long lLUStng) {
    register long j;
    switch (lLUStng) {
        case STNG_LU_AND:
            j = preSetUP.n_and;
            break;

        case STNG_LU_OR:
             j = preSetUP.n_or;
            break;

        case STNG_LU_XOR:
            j = preSetUP.n_xor;
            break;

        case STNG_LU_INPUT:
            j = preSetUP.n_input;
            break;

        case STNG_LU_OUTPUT:
            j = preSetUP.n_output;
            break;

        case STNG_LU_LED:
            j = preSetUP.n_led;
            break;

        case STNG_LU_NOT:
               j = preSetUP.n_not;
            break;
        case STNG_LU_MFT:
               j = preSetUP.n_timers;
            break;

        default:
            j = -1;
    }
      return j;       
            
}


long  Shematic::FillSBitFld_LUInInfo(void *pvIn,void *pvOut){
    //Now use Index in ordered CrCRefInfo
register long i,j;
volatile CLUBase* plcCLUBase;
//i =  

plcCLUBase = (static_cast<LUCRefExchParam*>( pvIn))->pCLUBase;
        
j = plcCLUBase->shShemasIdLUStng;
i = EvalIdxibnarrSBitFldCRefInfo(j);
j = (static_cast<LUCRefExchParam*>( pvIn))->shLU_ObjScanIndex;
j *= plcCLUBase->chNumInput;
i += j;
i += (static_cast<LUCRefExchParam*>( pvIn))->chLU_OrdNumIn;
*(static_cast<SBitFld_LUInInfo*>(pvOut) ) = arrSBitFldCRefInfo[i].sBitLUInputInfo;  
    return 0;
//Alternative Variant?
    //Use ((CLUBase*)plcCLUBase)->shShemasIdLUStng && shShemasIdLUStng
    //to Find Record
    //then Use ((LUCRefExchParam*) pvIn)->chLU_OrdNumIn to fix Input
}
void Shematic::SetupCircutLinks(void *pv) {
    register long i,j;
    
//	short shAmtPlacedLU;
//	short shAmtLUDscElem;//SBitFldCRefInfo Elem
	
struct {
	short shAmtLU, shIdx;
        short shCounterScanedObj,shCounterFindObj;
        short shAmtLookObj;
        long lBaseOrdNumStng;
        SBitFldCRefInfo *pSBitFldCRefInfo;
        LUCrossRefDsc lcLUCrossRefData;
        CLUBase  *pCLURef;//*pCLUBase,
} sLV;
SBitFld_LUInInfo locSBitFld;
LUCRefExchParam lcLUCRefExchParam;
Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    i = j = 0;

    sLV.shIdx = sLV.shAmtLU = 0;
//    rsLV = *((Init2LcVarArea*) pv);
    sLV.pSBitFldCRefInfo = &arrSBitFldCRefInfo[0]; //Table Links
    rsLV.arrLUAreaListElem = &gLUAreaMem.headLUAreaList;
	

    if (preSetUP.n_output != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_output;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_input;
        i = sLV.shIdx; //Offset Output
        do {
            //Type Obj == STNG_LU_OUTPUT order num == sLV.shCounterScanedObj+sLV.shIdx
            i = sLV.shCounterScanedObj + sLV.shIdx;
            pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
            //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
            rsLV.pCLUBase = static_cast<CLUBase*> (
                    (static_cast<LUAreaListElem*> (pv))->pvLU);
            
            //Take info 2 Possible Variants
            //1-st STNG_LU_OUTPUT And shShemasOrdNumStng
            //2-nd use Index in ordered CrCRefInfo
            for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
                lcLUCRefExchParam.shLU_ObjScanIndex = sLV.shCounterScanedObj;
                lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
                lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
                FillSBitFld_LUInInfo( static_cast<void*>(&lcLUCRefExchParam), 
				static_cast<void*>(&locSBitFld) );
                //Have OutPut Param               
                sLV.lcLUCrossRefData.shRefIdLUStng   = locSBitFld.bfInfo_IdLUStng;
                sLV.lcLUCrossRefData.shRefOrdNumStng = locSBitFld.bfInfo_OrdNumStng;
                sLV.lcLUCrossRefData.chRefOrdNumOut  = locSBitFld.bfInfo_OrdNumOut;
                 //Find Obj
                j = EvalIdxinarrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                if(j!=(-1)){
                    sLV.shCounterFindObj = 0;
                    sLV.shAmtLookObj = EvalAmtIn_arrLUAreaListElem(sLV.lcLUCrossRefData.shRefIdLUStng);
                    if(sLV.shAmtLookObj == (-1))
                        sLV.shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;//Test Only
                    //i = j+sLV.shCounterFindObj;
                    rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
                    while ((sLV.shCounterFindObj)<sLV.shAmtLookObj && rsLV.chVal!=1) {
                        i = j+sLV.shCounterFindObj;
                        pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                        //sLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                        sLV.pCLURef = static_cast<CLUBase*> (
                                (static_cast<LUAreaListElem*> (pv))->pvLU);
                        if ((sLV.pCLURef->shShemasIdLUStng == sLV.lcLUCrossRefData.shRefIdLUStng) &&
                                (sLV.pCLURef->shShemasOrdNumStng == sLV.lcLUCrossRefData.shRefOrdNumStng)
                            ){//Set UP Logic
                            rsLV.pCh = static_cast<char*>(sLV.pCLURef->pOut);
                            rsLV.pCh += sLV.lcLUCrossRefData.chRefOrdNumOut -1;//As Idx
                            rsLV.chVal = 1;
                            break;
                        }
                    sLV.shCounterFindObj++;
                    }
                    if (rsLV.pCh) {
                        rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                        rsLV.arrPchIn[ik] = rsLV.pCh;
                       
                    }
                    if(rsLV.chVal != 1)
                        rsLV.chErrCount++;//Is need?
                }
            }
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_led != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_led;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_output;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do{
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        
        }while (++sLV.shCounterScanedObj < sLV.shAmtLU); 
    }
    if (preSetUP.n_and != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_and;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_led;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_or != 0) {
        sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_or;
        j = 0;
        sLV.shIdx += preSetUP.n_and;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_xor != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_xor;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_or;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
    if (preSetUP.n_not != 0) {
	sLV.shCounterScanedObj = 0;
        sLV.shAmtLU = preSetUP.n_not;
        j = 0; //Idx in OutPut for Test
        sLV.shIdx += preSetUP.n_xor;
        rsLV.shIdx = sLV.shIdx; rsLV.pV = static_cast<void*>(&sLV.shCounterScanedObj);
        do {
            SetupCLUInternalRef(static_cast<void*>(&rsLV));
        } while (++sLV.shCounterScanedObj < sLV.shAmtLU);
    }
	
}
	
//	while (shAmtLUDscElem 
//	&& sLV.chBreakScanLUDscLoop == 0) {
//		//Get Reference on Link Data
//		//sLV.shIdxFldCRefInfo =0;?
//		//
//		while(sLV.shIdxLU < shAmtPlacedLU
//		&& sLV.chBreakScanPlacedLULoop == 0){
//			i = sLV.shIdxLU;
//			pv = (void*) &rsLV.arrLUAreaListElem[i];
//			rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
//			
//			j = sLV.shIdxFldCRefInfo;
//			if (rsLV.pCLUBase->shShemasIdLUStng == ar_n_output_CRDsc[j].shBaseIdLUStng &&
//                    rsLV.pCLUBase->shShemasOrdNumStng == ar_n_output_CRDsc[j].shBaseOrdNumStng) {
//						
//						
//			}
//		}
//	
//	}
	
void Shematic::SetupLULinks(void *pv) {
//	register long i,j;
	//First Param Index in CrrefArray
	//Second Param Id & Type LU
	pv = static_cast<void*>(&LL_CryaCrya);
	*(static_cast<short*>(pv)) = 1000;
}


void Shematic::SetupCLUInternalRef(void *pv){
    register long i,j;
//   register Init2LcVarArea *pInit2LcVarArea = (Init2LcVarArea *)pv;
	SBitFld_LUInInfo locSBitFld;
    LUCRefExchParam lcLUCRefExchParam;
    register Init2LcVarArea& rsLV = *(static_cast<Init2LcVarArea*>(pv));
    volatile short& shCounterScanedObj = *(static_cast<short*>(rsLV.pV));
    

    i = shCounterScanedObj + rsLV.shIdx;
    pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
    //rsLV.pCLUBase = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;static_cast<CLUBase*>( 
    rsLV.pCLUBase = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
    for (long ik = 0; ik < rsLV.pCLUBase->chNumInput; ik++) {
        lcLUCRefExchParam.shLU_ObjScanIndex = shCounterScanedObj;
        lcLUCRefExchParam.chLU_OrdNumIn = ik;// + 1; in function use as Idx
        lcLUCRefExchParam.pCLUBase = rsLV.pCLUBase;
        FillSBitFld_LUInInfo(static_cast<void*>(&lcLUCRefExchParam), static_cast<void*>(&locSBitFld));
        //Have OutPut Param               
        //-lcLUCRefExchParam.shRefIdLUStng   = locSBitFld.bfInfo_IdLUStng;
        //-lcLUCRefExchParam.shRefOrdNumStng = locSBitFld.bfInfo_OrdNumStng;
        //-lcLUCRefExchParam.chRefOrdNumOut  = locSBitFld.bfInfo_OrdNumOut;
         //Find Obj
        j = EvalIdxinarrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng));
        if(j!=(-1)){
             short shCounterFindObj = 0;
             short shAmtLookObj = 0;
            
            shAmtLookObj = static_cast<short>(EvalAmtIn_arrLUAreaListElem(static_cast<long>(locSBitFld.bfInfo_IdLUStng)));
            if(shAmtLookObj == (-1))
                shAmtLookObj = gblLUAreaAuxVar.shAmountPlacedLogicUnit-j;
            
            rsLV.chVal = 0;rsLV.pCh = static_cast<char*>(0);
            while ((shCounterFindObj) < shAmtLookObj && rsLV.chVal != 1) {
                i = j + shCounterFindObj;
                pv = static_cast<void*>(&rsLV.arrLUAreaListElem[i]);
                //rsLV.pCLURef = (CLUBase*) ((LUAreaListElem*) pv)->pvLU;
                rsLV.pCLURef = static_cast<CLUBase*>((static_cast<LUAreaListElem*>(pv))->pvLU);
                if ((rsLV.pCLURef->shShemasIdLUStng == static_cast<short>(locSBitFld.bfInfo_IdLUStng)) &&
                        (rsLV.pCLURef->shShemasOrdNumStng == static_cast<short>(locSBitFld.bfInfo_OrdNumStng))
                        ) {//Set UP Logic
                    rsLV.pCh = static_cast<char*>(rsLV.pCLURef->pOut);
                    rsLV.pCh += static_cast<unsigned char>(locSBitFld.bfInfo_OrdNumOut - 1); //As Idx
                    rsLV.chVal = 1;
                    break;
                }
                shCounterFindObj++;
            }
            if (rsLV.pCh) {
                rsLV.arrPchIn = static_cast<char**>(rsLV.pCLUBase->pIn);
                rsLV.arrPchIn[ik] = rsLV.pCh;
            }
            if(rsLV.chVal != 1)
                rsLV.chErrCount++;//Is need?
        }
    }
}
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//``````````````````````````````````````````````````````````````````````````````````
//==================================================================================
//--- 			 Interface function for CPP Schematic     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
long InitSchematic(void){
sh.Init();
return 1;
}

void DoCalcWrp(void){
sh.DoCalc();
}





