#pragma once
const short shCLULed_1_0_AmtIn  = 1;
const short shCLULed_1_0_AmtOut = 0;
#include "lubase.h"
#include "LedAuxDsc.h"
typedef struct LedSuit_tag{
char chSel1;
char chSel2;
char chSel3;
short shAlternatorC1;//Number
short shAlternatorC2;//Number
}LedCfgSuit;

class CLULed :
	public CLUBase
{
public:
	CLULed(void);
	~CLULed(void);
	CLULed(CLULed&);
	CLULed(char chM,char chI);
	void CalcLedSchematic(void);
	char* arrPchIn[shCLULed_1_0_AmtIn];//
	char* arrPchSchIn[TOTAL_LED_VISIO_IN];//
	char* arrPchAlternator[2];//
	char  arrOut  [TOTAL_LED_VISIO_OUTPUT];//Trash field
	LedCfgSuit m_LedCfgSuit;
	friend void PUT_Op_1_0_    (void *pObj);
	friend void SET_LED_Op(void *pObj);
};



//enum G{
//
//}






