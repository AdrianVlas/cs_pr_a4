#pragma once
const short shCLUDInput_0_1_AmtIn  = 0;
const short shCLUDInput_0_1_AmtOut = 1;
#include "lubase.h"
class CLUDInput_0_1 :
	public CLUBase
{
public:
	CLUDInput_0_1(void);
	~CLUDInput_0_1(void);
	CLUDInput_0_1(CLUDInput_0_1&);
	CLUDInput_0_1(char chM,char chI);
	//char* arrPchIn[8];//Trash field
	char arrOut [shCLUDInput_0_1_AmtOut];//
	friend void READ_Op_0_1    (void *pObj);
	friend void READ_DI_Op(void *pObj);
};

