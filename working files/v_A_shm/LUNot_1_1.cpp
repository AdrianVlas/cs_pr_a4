#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUNot_1_1.h"

void NOT_Op_1_1    (void *pObj)
{
//CLUNot_1_1& refCLUNot_1_1 = pObj;
//CLUNot_1_1 *pCLUNot_1_1 = (CLUNot_1_1*)pObj;

}
CLUNot_1_1::CLUNot_1_1(void):CLUBase()
{
}
CLUNot_1_1::CLUNot_1_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUNot_1_1_AmtIn); 
	chNumOutput = static_cast<char>(shCLUNot_1_1_AmtOut);
	chTypeLogicFunction = LU_OP_NOT;
	LogicFunc  = NOT_Op;//???

	//Set Input parameters
	pIn = reinterpret_cast<void*>(arrPchIn);

	//Set OutPut parameters
	pOut = reinterpret_cast<void*>(arrOut);

}
CLUNot_1_1::~CLUNot_1_1(void)
{
}
