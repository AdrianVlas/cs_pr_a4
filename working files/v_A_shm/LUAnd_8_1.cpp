#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUAnd_8_1.h"

void AND_Op_8_1    (void *pObj)
{
	register long i,j;
	register char* pCh;
	
//CLUNot_1_1& refCLUNot_1_1 ;
//CLUAnd_8_1 *pCLUAnd_8_1 = (CLUAnd_8_1*)pObj;
	for(i = 0,pCh = (static_cast<CLUAnd_8_1*>(pObj))->arrPchIn[0],j = 1;i < 8; i++){
		if(pCh[i] == 0){
			j = 0;
			break;
		}
	}
	//((CLUAnd_8_1*)pObj)->arrOut[0] = static_cast<char>(j);//(char)j;
	(reinterpret_cast<CLUAnd_8_1 *>(pObj))->arrOut[0] = static_cast<char>(j);
	//((CLUAnd_8_1*)pObj)->arrOut[0] = static_cast<char>(j);
}
CLUAnd_8_1::CLUAnd_8_1(void):CLUBase()
{
}
CLUAnd_8_1::CLUAnd_8_1(char chM,char chI)//,LUOutDsc* pLUOutDsc)
{
	chMaxIteratoin = chM;
	chIteration = chI;
	chNumInput  = static_cast<char>(shCLUAnd_8_1_AmtIn);//(char)8;
	chNumOutput = static_cast<char>(shCLUAnd_8_1_AmtOut);
	
	
	//Set Input parameters
	 //pIn =arrPchIn;

	//Set OutPut parameters
	 //pOut =arrOut;
}

CLUAnd_8_1::~CLUAnd_8_1(void)
{
}
