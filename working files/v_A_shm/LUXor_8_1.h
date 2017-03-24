#pragma once
const short shCLUXor_2_1_AmtIn  = 2;
const short shCLUXor_2_1_AmtOut = 1;
#include "lubase.h"

class CLUXor_8_1 :
	public CLUBase
{
public:
	CLUXor_8_1(void);
	~CLUXor_8_1(void);
	CLUXor_8_1(CLUXor_8_1&);
	CLUXor_8_1(char chM,char chI);
	char* arrPchIn[shCLUXor_2_1_AmtIn ];//
	char arrOut   [shCLUXor_2_1_AmtOut];//
	friend void XOR_Op_8_1    (void *pObj);
};


