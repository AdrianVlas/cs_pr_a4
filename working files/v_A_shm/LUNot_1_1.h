#pragma once
const short shCLUNot_1_1_AmtIn  = 1;
const short shCLUNot_1_1_AmtOut = 1;
#include "lubase.h"
class CLUNot_1_1 :
	public CLUBase
{
public:
	CLUNot_1_1(void);
	~CLUNot_1_1(void);
	CLUNot_1_1(CLUNot_1_1&);
	//CLUBase(char chM,char chI,char chNumIn,char chNumOut);
	//CLUBase& operator= (const CLUBase&);
	CLUNot_1_1(char chM,char chI);//,LUOutDsc* pLUOutDsc);
	char* arrPchIn[shCLUNot_1_1_AmtIn ];// 
	char  arrOut  [shCLUNot_1_1_AmtOut];// 
	friend void NOT_Op_1_1    (void *pObj);
	//friend void (void *pObj);

};


