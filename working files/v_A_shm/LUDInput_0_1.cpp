#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUDInput_0_1.h"
void READ_Op_0_1(void *pObj)
{
	//CLUNot_1_1& refCLUNot_1_1 = pObj;
//	CLUDInput_0_1 *pCLUDInput_0_1 = (CLUDInput_0_1*)pObj;

}
void READ_DI_Op(void *pObj)
{
	//CLUNot_1_1& refCLUNot_1_1 = pObj;
	CLUDInput_0_1 *pCLUDInput_0_1 = reinterpret_cast<CLUDInput_0_1 *>(pObj);
	pCLUDInput_0_1->arrOut[0] = 
	static_cast<char>(pCLUDInput_0_1->shLUBieldOrdNum);//Any value from Input

}

CLUDInput_0_1::CLUDInput_0_1(void)
{
}

CLUDInput_0_1::CLUDInput_0_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUDInput_0_1_AmtIn );
	chNumOutput = static_cast<char>(shCLUDInput_0_1_AmtOut);
	//chTypeLogicFunction = LU_OP_READ_DI;
	//LogicFunc  = READ_DI_Op;//???

	//Set Input parameters



	//Set OutPut parameters
	//pOut = (void*)arrOut;
}

CLUDInput_0_1::~CLUDInput_0_1(void)
{
}
