#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUOr_8_1.h"

void OR_Op_8_1    (void *pObj)
{
//CLUNot_1_1& refCLUNot_1_1 = pObj;
//CLUOr_8_1 *pCLUOr_8_1 = (CLUOr_8_1*)pObj;

}

CLUOr_8_1::CLUOr_8_1(void)
{
}

CLUOr_8_1::CLUOr_8_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUOr_8_1_AmtIn );
	chNumOutput = static_cast<char>(shCLUOr_8_1_AmtOut);
	chTypeLogicFunction = LU_OP_NOT;
	LogicFunc  = NOT_Op;//???

	//Set Input parameters
	pIn = reinterpret_cast<void*>(arrPchIn);

	//Set OutPut parameters
	pOut = reinterpret_cast<void*>(arrOut);
}
CLUOr_8_1::~CLUOr_8_1(void)
{
}

