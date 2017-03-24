#pragma once
const short shCLUAnd_8_1_AmtIn  = 8;
const short shCLUAnd_8_1_AmtOut = 1;

#include "lubase.h"
void AND_Op_8_1    (void *pObj);
class CLUAnd_8_1 :
	public CLUBase
{
public:
	CLUAnd_8_1(void);
	~CLUAnd_8_1(void);
	CLUAnd_8_1(CLUAnd_8_1&);
	//CLUBase(char chM,char chI,char chNumIn,char chNumOut);
	//CLUBase& operator= (const CLUBase&);
	CLUAnd_8_1(char chM,char chI);//,LUOutDsc* pLUOutDsc);
	char* arrPchIn[shCLUAnd_8_1_AmtIn ];//
	char  arrOut  [shCLUAnd_8_1_AmtOut];//
	friend void AND_Op_8_1    (void *pObj);
};
