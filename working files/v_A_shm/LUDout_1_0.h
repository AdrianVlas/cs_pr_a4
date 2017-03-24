#pragma once
#include "lubase.h"
const short shCLUDout_1_0_AmtIn  = 1;
const short shCLUDout_1_0_AmtOut = 0;
#include "DOAuxDsc.h"
typedef struct ReleySuit_tag{
char chSel1;
char chSel2;
char chSel3;
short shAlternatorC1;//Number
short shAlternatorC2;//Number
}ReleyCfgSuit;

class CLUDout_1_0 :
public CLUBase {
public:
    CLUDout_1_0(void);
    ~CLUDout_1_0(void);
    CLUDout_1_0(CLUDout_1_0&);
    CLUDout_1_0(char chM, char chI);
	void CalcReleySchematic(void);
    char* arrPchIn[shCLUDout_1_0_AmtIn]; //
    char* arrPchSchIn[TOTAL_RELE_VISIO_IN];//
	char* arrPchAlternator[2];//
	char  arrOut  [TOTAL_RELE_VISIO_OUTPUT];//Trash field
	ReleyCfgSuit m_ReleyCfgSuit;
    friend void PUT_Op_1_0(void *pObj);
    friend void SET_OUT_Op(void *pObj);
};
