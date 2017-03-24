
#include "prtTmr.h"
const unsigned char uCh_MAX_Amt_1_MS_TMR  = 200;



char chGlSem;
//==================================================================================
//---            Main file for service prt Timers     -----------
//==================================================================================
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//~~~  
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
short  sh1MsRegisteredTimers;
TmrNode *pHeadTmrNode = (TmrNode*)0; //Pointer on Firsst
TmrNode *pTailTmrNode = (TmrNode*)0;
TmrNode *PCurrNode    = (TmrNode*)0;

void  TmrCalls(void){
   
    register TmrNode *pNode;
    register long i;
    register long lRegTmr = sh1MsRegisteredTimers;

    //Check Semafor Here
    if (chGlSem == 0 && lRegTmr > 0){//Skip change Value
        pNode = pHeadTmrNode;
        do{
            //Look In Program
            i = pNode->lTmrVal;
            if (i)
                pNode->lTmrVal = --i;
            i = (long) pNode->next;
            if (i == 0)
                lRegTmr = 1; //Break
            else {
                pNode = (void*) i;
            }

        }while (--lRegTmr);
    }
//counter for 1ms Timers
//Pointer on Firsst

//counter for 2ms Timers
//Pointer on Firsst

//counter for 5ms Timers
//Pointer on Firsst

//counter for 10 ms Timers
//Pointer on Firsst
}

//counter for 50 ms Timers
//Pointer on Firsst

//counter for 100 ms Timers
//Pointer on Firsst

//Adding an item to the end of the list
long TallingList(TmrNode *pNode) {
    register TmrNode *pCurrent;
    //long i;
    //volatile long lRegListNumber;
    if ((sh1MsRegisteredTimers+1)> uCh_MAX_Amt_1_MS_TMR)
        return 0;
    if (sh1MsRegisteredTimers++) {//
        pCurrent = pTailTmrNode;
        pCurrent-> next = (void*)pNode;
        pNode-> next = (void*) 0;
        pTailTmrNode = pNode;
    } else {//First Insert
        //?if (pHeadTmrNode == pTailTmrNode == ((void *)0))
        pHeadTmrNode = pTailTmrNode = pNode;
        pNode->next  = (void *)0;
        sh1MsRegisteredTimers++;
    }
    return sh1MsRegisteredTimers;
}
//Adding an item to the beginning of the list (pushing to the list)
long PushTmrNode(TmrNode *pNode){

    if ((sh1MsRegisteredTimers+1)> uCh_MAX_Amt_1_MS_TMR)
        return 0;
    if (sh1MsRegisteredTimers) {//
        pNode-> next = (void*)pHeadTmrNode;
        pHeadTmrNode = pNode;
        sh1MsRegisteredTimers++;
    } else {//First Insert
        //?if (pHeadTmrNode == pTailTmrNode == ((void *)0))
        pHeadTmrNode = pTailTmrNode = pNode;
        pNode->next  = (void *)0;
        sh1MsRegisteredTimers++;
    }
    return sh1MsRegisteredTimers;
}
//Adding an item to the special position of the list (cutting to the list)
long IncreaseTmrList(TmrNode *pNode,long lPos){
    register TmrNode *pCurrent;
    void *pv;

    if ((sh1MsRegisteredTimers+1)< uCh_MAX_Amt_1_MS_TMR && lPos< sh1MsRegisteredTimers) {
        pCurrent = pHeadTmrNode;
        while (pCurrent->next != ((void *) 0) && lPos--) {
            pCurrent = (TmrNode*) pCurrent->next;
        }
        if ((lPos == 0) && pCurrent) {
            pv = (void*) pCurrent->next;
            pCurrent->next = (void*) pNode;
            pNode->next = pv;
            return ++sh1MsRegisteredTimers;
        }
    }
    return 0;
}
//Removing the first item (popping from the list)
long PopTmrNode(TmrNode *pNode) {
    register TmrNode *pCurrent;
    register long i;
    if (sh1MsRegisteredTimers) {
        i = 0;
        pCurrent = pHeadTmrNode;
        if (pCurrent == pNode) {
            //Delete 1-st Element
            pHeadTmrNode = pCurrent->next;
            sh1MsRegisteredTimers--;
            return 1; //Registered Number
        }
        while (i < sh1MsRegisteredTimers) {
            if (pCurrent->next == (void*)pNode) {
                pCurrent->next = pNode->next;
                sh1MsRegisteredTimers--;
                return i; //Registered Number
            }
            i++;
        }
    }
    return 0;
}
/*
//Removing the last item of the list
long CuttingList(TmrNode *pNode){
 
    return 0;
}
//Removing a specific item
long DecreaseTmrList(TmrNode *pNode,long lPos){

    return 0;
}
*/
#include "Ereg.h"
char chGbl__DIN1_DIN5__RD_VAL;
char chGbl__DIN6_DIN12__RD_VAL;
char chGbl__LedColumns__RW_VAL;
char chGbl_REL_1_6__ROWS_A_D__RW_VAL;
char chGbl__REL_1_6__RD_VAL;
char chGbl__REL7_REL14__RW_VAL;
char chGbl__REL7_REL14__RD_VAL;




UI32Bit DiHrdStateUI32Bit;//, DiHrdStateUI32Bit
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//---
extern void RdHrdIn(void*pv);
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~     функция считывания состояния дискретных входов                       ~~~~~
//~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//~~~                                                                         ~~~~~
//~~~     Положение бит                                                       ~~~~~
//~~~     MSB ...LSB                                                          ~~~~~
//~~~     ДВ16  ДВ0                                                           ~~~~~
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
////////////////////////////////////////////////////////////////////////////////////
void RdHrdIn(void *pv){
    register long i,j;
    register void *pvRlc;
    //reinterpret_cast<void*>(NOR_PSRAM_BANK2);
    pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_READ_DIN01__05<<1));
    //((char*)pvRlc) += ;//
    i = *((char*)pvRlc);//0-5 bits
    i&= 0x1f;
    ((UI32Bit*) pv)->ar_uch[0] = (char)i;
    pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO__REL_1_6<<1));
    i = *((short*)pvRlc);//9-15 bits
    j = i & 600;
    j >>= 3; 
    ((UI32Bit*) pv)->ar_uch[0] |= (char)j;//6,7 - 9-10
    ((UI32Bit*) pv)->ar_uch[1] = (i >> 3);//8-12
    pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_READ_DIN06__12<<1));
    i = *((char*)pvRlc);//13-17 5bit
    j = i & 0x7;
    ((UI32Bit*) pv)->ar_uch[1] |= (j<<5);
    ((UI32Bit*) pv)->ar_uch[2] = i>>3;
    pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1));
    i = *((short*)pvRlc);
    j = i>>14;
    ((UI32Bit*) pv)->ar_uch[2] |= (j<<2);
/*
sLV.pLAdr4 = reinterpret_cast<char*>( NOR_PSRAM_BANK2);
sLV.pLAdr4 += ADR_READ_DIN06__12<<1;
sLV.chVal = *(sLV.pLAdr3);
*/


   
}
UI32Bit DoStateUI32Bit;
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//---
extern void SetHrdOut(void*pv);
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~     функция записи состояния дискретных входов                       ~~~~~
//~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//~~~                                                                         ~~~~~
//~~~     Положение бит                                                       ~~~~~
//~~~     MSB ...LSB                                                          ~~~~~
//~~~     ДВ16  ДВ0                                                           ~~~~~
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//////////////////////////////////////////////////////////////////////////////////////////
void SetHrdOut(void*pv){
    register long i,j;
    register void *pvRlc;
    i = ((UI32Bit*) pv)->ar_uch[0]; 
    j = i&1;
    
    pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_WRITE_RDO__REL_1_6__ROWS_A__D<<1<<1));
    *((char*)pvRlc) = j;//???
    pvRlc = (void*)((long)NOR_PSRAM_BANK2+(ADR_READ_CHECK_RDO_REL7_REL14<<1));
    i = ((UI32Bit*) pv)->ar_uch[0]; 
    j = i>>1;
    j &= 0x3f;
    *((char*)pvRlc) = j;

    
}
#include "HlDefs.h"
enum LED_AUX_PARTS_OP { 

LED_AUX_OP_INIT  = 0,  
LED_AUX_OP_SET   ,  
LED_AUX_OP_CLR   ,
LED_AUX_OP_EXIT  ,
TOTAL_LED_AUX_OP = LED_AUX_OP_EXIT + 1
};
const char chNumIndependentParts = TOTAL_LED_AUX_OP;
fnPLpvrL arrFnPtr[TOTAL_LED_AUX_OP] = {
LedAuxOp1,
LedAuxOp2,
LedAuxOp3,
LedAuxOp4
};
static long lGlbOperationReflector = 0;
char chCounterLedService = TOTAL_LED_AUX_OP;
UI32Bit LedStateUI32Bit;
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//---
extern void SetHrdLed(void*pv);
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~     функция записи состояния дискретных входов                       ~~~~~
//~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//~~~                                                                         ~~~~~
//~~~     Положение бит                                                       ~~~~~
//~~~     MSB ...LSB                                                          ~~~~~
//~~~     ДВ16  ДВ0                                                           ~~~~~
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//////////////////////////////////////////////////////////////////////////////////////////
void SetHrdLed(void*pv){
register long i,j;
	register void *pvRlc;
    fnPLpvrL CurrAuxfunc; // 
    volatile long lAuxVar = 0;
	//volatile LedRegCode lcsLedRegCode;
    i = chCounterLedService + 1;
    if (i >= chNumIndependentParts){
        i = chCounterLedService = 0;
        lGlbOperationReflector = 0;
    } else{
        chCounterLedService = i;
    }
    //Select Led
    for (i = 0; i < TOTAL_LEDS; i++) {
        
        if (((UI32Bit*) pv)->ul_val & (1 << i)) {//Set bit

        } else {//Clear bit

        }
        j = HLSelectorTable[i].row;
        
        chGbl_REL_1_6__ROWS_A_D__RW_VAL = 1<< j;
        j = HLSelectorTable[i].column;
        chGbl__LedColumns__RW_VAL = ~(1 << j);
        pvRlc = (void *)(((long)NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
        *((char *)pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL;
        pvRlc = (void *)(((long)NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
        *((char *)pvRlc) = chGbl__LedColumns__RW_VAL;
		lAuxVar = chCounterLedService;
    }

//    pvRlc = (void *)(((long)NOR_PSRAM_BANK2) + (ADR_WRITE_RDO__REL_1_6__ROWS_A__D << 1));
//    *((char *)pvRlc) = chGbl_REL_1_6__ROWS_A_D__RW_VAL;
//    pvRlc = (void *)(((long)NOR_PSRAM_BANK2) + (ADR_WRITE_RI_COLUMNS01__06 << 1));
//    *((char *)pvRlc) = chGbl__LedColumns__RW_VAL;

        i = chCounterLedService;
        CurrAuxfunc = arrFnPtr[i];
    j = CurrAuxfunc(i, (void*) &lAuxVar);
}









const char CH_AMOUNT_DI = 19;
char arTimerDi[19] = {
0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0
};
DICfgSuit sDiCfg;



static long lCtr = 0; //char chTestStateIn = 1;char chOut;
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//---
extern void UpdateStateDI (void);
//..................................................................................
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//~~~     функция анализа состояния дискретных входов                       ~~~~~
//~~~     p_out_param должен указывать на область памяти 4 байта              ~~~~~
//~~~     возврат 3 - команда выполнена успешно                               ~~~~~
//~~~                                                                         ~~~~~
//~~~     Положение бит                                                       ~~~~~
//~~~     MSB ...LSB                                                          ~~~~~
//~~~     ДВ16  ДВ0                                                           ~~~~~
//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,
//""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""""
//////////////////////////////////////////////////////////////////////////////////////////
void UpdateStateDI (void){
    register long i, j;
    register unsigned long ulrVal;
    //register char *pCh;
    register DICfgSuit *pDICfgSuit;
    volatile char arChReferenceIdx[] = {
    0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18    };//7, 15, 0, 0};
    volatile long arU32Tst[] = {0, 0, 0, 0};
	pDICfgSuit = &sDiCfg;
	sDiCfg.pDITmr = arTimerDi;
    pDICfgSuit->DiHrdStateUI32Bit.ul_val = DiHrdStateUI32Bit.ul_val;
    for (i = 0; i < CH_AMOUNT_DI; i++){
        //Check Type Signal
        if (pDICfgSuit->DiTypeSignal.ul_val & (1 << i)){
            //Alternate Current
            j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
            if (j == 0)
              pDICfgSuit->DiAND.ul_val &= ~(1 << i);//pCh[OFF_BYTE_AND] &= ~(1 << i);

            //pCh[OFF_BYTE_OR] |= pCh[OFF_BYTE_PIN] & (1 << i);
            pDICfgSuit->DiOR.ul_val |= pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
            j = lCtr;
            j++;
            if (j > 12)
            {
                lCtr = 0; //pCh[OFF_BYTE_DI_timer0+i];
                //Check 1
                //j = (pCh[OFF_BYTE_AND] & (1 << i));
                j = (pDICfgSuit->DiAND.ul_val & (1 << i));
                if ((j == 0) && (pDICfgSuit->DiOR.ul_val & (1 << i))){//Stable 1
                    pDICfgSuit->DiStartUP.ul_val |= (1 << i);//pCh[OFF_BYTE_DI_StartUP] |= (1 << i);
                }else{
                    pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
                    arU32Tst[0] = pDICfgSuit->DiAND.ul_val;//pCh[OFF_BYTE_AND];
                    arU32Tst[1] = pDICfgSuit->DiOR.ul_val;//pCh[OFF_BYTE_OR];
                }
                ulrVal = (pDICfgSuit->DiStartUP.ul_val & (1 << i));
                j = (pDICfgSuit->DiState.ul_val & (1 << i));
                ulrVal ^= j;
                if (ulrVal){
                    ulrVal = pDICfgSuit->pDITmr[i];
                    ulrVal++;
                    j = arChReferenceIdx[i];
                    //j = pprotect_cfg_tbl->ushDurationDI[j] + 1;
                    j = pDICfgSuit->arChDurationDI[j] + 1;
                    if (ulrVal > (unsigned)j){
                        pDICfgSuit->pDITmr[i] = 0;//pCh[OFF_BYTE_DI_timer0 + i] = 0;
                        //pCh[OFF_BYTE_DI_State] &= ~(1 << i);
                        //pCh[OFF_BYTE_DI_State] |= pCh[OFF_BYTE_DI_StartUP] & (1 << i);
                        pDICfgSuit->DiState.ul_val &= ~(1 << i);
                        pDICfgSuit->DiState.ul_val |= pDICfgSuit->DiStartUP.ul_val & (1 << i);
                    }else
                        pDICfgSuit->pDITmr[i] =  ulrVal;//pCh[OFF_BYTE_DI_timer0 + i] = ulrVal;
                }else
                    pDICfgSuit->pDITmr[i] = 0;//pCh[OFF_BYTE_DI_timer0 + i] = 0;
                pDICfgSuit->DiAND.ul_val |= (1 << i);//pCh[OFF_BYTE_AND] |= (1 << i);
                pDICfgSuit->DiOR.ul_val &= ~(1 << i);//pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
            }
            else
                lCtr = j;
        }
        else
        {
            //Direct Current
            //ulrVal = (pCh[OFF_BYTE_DI_StartUP] & (1 << i)) ^ (pCh[OFF_BYTE_PIN] & (1 << i));
            ulrVal = (pDICfgSuit->DiStartUP.ul_val & (1 << i)) 
            ^ (pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i));
            if (ulrVal){
                //Set Di
                //j = pCh[OFF_BYTE_PIN] & (1 << i);
                //pCh[OFF_BYTE_DI_StartUP] &= ~(1 << i);
                //pCh[OFF_BYTE_DI_StartUP] |= j;
                //pCh[OFF_BYTE_AND] |= (1 << i);
                //pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
                //pCh[OFF_BYTE_DI_timer0 + i] = 0;
                j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
                pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
                pDICfgSuit->DiStartUP.ul_val |= j;
                pDICfgSuit->DiAND.ul_val |= (1 << i);
                pDICfgSuit->DiOR.ul_val &= ~(1 << i);
                pDICfgSuit->pDITmr[i] = 0;
            }
            //if ((pCh[OFF_BYTE_DI_StartUP] & (1 << i)) == (pCh[OFF_BYTE_PIN] & (1 << i)))
            if ((pDICfgSuit->DiStartUP.ul_val & (1 << i)) 
            == (pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i))){
                //j = pCh[OFF_BYTE_PIN] & (1 << i);
                j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
                if (j == 0)
                    //pCh[OFF_BYTE_AND] &= ~(1 << i); //Clr Bit
                    pDICfgSuit->DiAND.ul_val &= ~(1 << i); //Clr Bit
                else
                    //pCh[OFF_BYTE_OR] |= pCh[OFF_BYTE_PIN] & (1 << i);
                    pDICfgSuit->DiOR.ul_val |= pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
                //j = pCh[OFF_BYTE_DI_timer0 + i];
                j = pDICfgSuit->pDITmr[i];
                j++;
                ulrVal = arChReferenceIdx[i];
                //if (j < pprotect_cfg_tbl->ushDurationDI[ulrVal]){
                if (j < pDICfgSuit->arChDurationDI[ulrVal]){
                    //pCh[OFF_BYTE_DI_timer0 + i] = j;
                    pDICfgSuit->pDITmr[i] = j;
                }
                else
                {
                    //if ((pCh[OFF_BYTE_AND] & (1 << i)) == (pCh[OFF_BYTE_OR] & (1 << i))) //Stable 1
                    if ((pDICfgSuit->DiAND.ul_val & (1 << i)) == (pDICfgSuit->DiOR.ul_val & (1 << i))) //Stable 1
                    {
                        //Check Time
                        //pCh[OFF_BYTE_DI_State] &= ~(1 << i);
                        //pCh[OFF_BYTE_DI_State] |= pCh[OFF_BYTE_DI_StartUP] & (1 << i);
                        pDICfgSuit->DiState.ul_val &= ~(1 << i);
                        pDICfgSuit->DiState.ul_val |= pDICfgSuit->DiStartUP.ul_val & (1 << i);
                        //Check Inversion
                        //Put Result
                    }
                    else
                    {
                        //reset
                        //pCh[OFF_BYTE_DI_StartUP] &= ~(1 << i);
                        //pCh[OFF_BYTE_DI_StartUP] |= pCh[OFF_BYTE_DI_State] & (1 << i);
                        //pCh[OFF_BYTE_AND] |= (1 << i);
                        //pCh[OFF_BYTE_OR] &= ~(1 << i); //Now 2 Bits
                        //pCh[OFF_BYTE_DI_timer0 + i] = 0;
                        j = pDICfgSuit->DiHrdStateUI32Bit.ul_val & (1 << i);
                        pDICfgSuit->DiStartUP.ul_val &= ~(1 << i);
                        pDICfgSuit->DiStartUP.ul_val |= j;
                        pDICfgSuit->DiAND.ul_val |= (1 << i);
                        pDICfgSuit->DiOR.ul_val &= ~(1 << i);
                        pDICfgSuit->pDITmr[i] = 0;
                    }
                }
            }
        }
    }
}

long LedAuxOp1(long l,void *pv){
    register long i;
	register void *pvRlc;
	i = lGlbOperationReflector;
	i |= 1<<l;
	lGlbOperationReflector = i;
	*((char*)pv) = i;
//	 pvRlc = (void*)(((long)NOR_PSRAM_BANK2)+(ADR_WRITE_RDO__REL_1_6__ROWS_A__D<<1<<1));
//    *((char*)pvRlc) = i;//???
return i;
}
long LedAuxOp2(long l,void *pv){
    register long i;
		i = lGlbOperationReflector;
	i |= 1<<l;
	lGlbOperationReflector = i;
	*((char*)pv) = i;
return i;
}
long LedAuxOp3(long l,void *pv){
    register long i;
		i = lGlbOperationReflector;
	i |= 1<<l;
	lGlbOperationReflector = i;
	*((char*)pv) = i;
return i;
}
long LedAuxOp4(long l,void *pv){
    register long i;
		i = lGlbOperationReflector;
	i |= 1<<l;
	lGlbOperationReflector = i;
	*((char*)pv) = i;
return i;
}
long LedAuxOp5(long l,void *pv){
    register long i;
		i = lGlbOperationReflector;
	i |= 1<<l;
	lGlbOperationReflector = i;
	*((char*)pv) = i;
return i;
}

