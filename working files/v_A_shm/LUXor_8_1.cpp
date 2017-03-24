#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUXor_8_1.h"


void XOR_Op_8_1    (void *pObj)
{
//CLUNot_1_1& refCLUNot_1_1 = pObj;
//CLUXor_8_1 *pCLUXor_8_1 = (CLUXor_8_1*)pObj;

}

CLUXor_8_1::CLUXor_8_1(void)
{
}
CLUXor_8_1::CLUXor_8_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUXor_2_1_AmtIn );
	chNumOutput = static_cast<char>(shCLUXor_2_1_AmtOut);
	chTypeLogicFunction = LU_OP_NOT;
	LogicFunc  = NOT_Op;//???

	//Set Input parameters
	pIn  = reinterpret_cast<void*>(arrPchIn);
	pOut = reinterpret_cast<void*>( arrOut );
	//Set OutPut parameters

}

CLUXor_8_1::~CLUXor_8_1(void)
{
}

