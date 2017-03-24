#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "LUBase.h"
#include "BaseInPoint.h"
#include "InPoint.h"
#include "ExtPoint.h"
#include "Shematic.h"

CLUBase::CLUBase(void)
{
	chMaxIteratoin = 10;
	chIteration = 0;
	chNumInput  = static_cast<char>(0);
	chNumOutput = 0;
	chTypeLogicFunction = LU_OP_NULL;
	shShemasIdLUStng   = 0;
	shShemasOrdNumStng = 0;
	shLUBieldOrdNum    = 0;
	chLinkSetOn = 0;
	LogicFunc  = Null_OP;
	//shOrderNumberCLUBase
	pOut = static_cast<void*>(0);//(void*)0;
	pIn  = static_cast<void*>(0);//(void*)0;
} 
extern LUAreaAuxVar gblLUAreaAuxVar;
void CLUBase::SetOrderNumber(void){
	shLUBieldOrdNum = static_cast<short>(++gblLUAreaAuxVar.shAmountPlacedLogicUnit);
	
}

CLUBase::~CLUBase(void)
{

}

void AND_Op(void *pObj)
{

}
void OR__Op(void *pObj)
{

}
void XOR_Op(void *pObj)
{

}

void Meandr_Op(void *pObj)
{

}

void Null_OP(void *pObj)
{

}
void NOT_Op(void *pObj)
{

}
