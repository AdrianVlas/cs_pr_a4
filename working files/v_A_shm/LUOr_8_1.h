#pragma once
const short shCLUOr_8_1_AmtIn  = 8;
const short shCLUOr_8_1_AmtOut = 1;
#include "lubase.h"
class CLUOr_8_1 :
	public CLUBase
{
public:
	CLUOr_8_1(void);
	~CLUOr_8_1(void);
	CLUOr_8_1(CLUOr_8_1&);
	CLUOr_8_1(char chM,char chI);
	char* arrPchIn[shCLUOr_8_1_AmtIn ];// 
	char  arrOut  [shCLUOr_8_1_AmtOut];// 
	friend void OR_Op_8_1    (void *pObj);
};


