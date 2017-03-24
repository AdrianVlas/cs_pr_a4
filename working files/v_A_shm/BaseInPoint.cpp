#ifdef VISUAL_STUDIO
#include "StdAfx.h"
#endif
#include "BaseInPoint.h"

 short shOrdNumBaseInPoint = 0;
BaseInPoint::BaseInPoint(void)
{
	chMaxIteratoin = 0;
	chIteration    = 0;
	chState        = 0;
	chReqCalc      = 0;
	shOrderNumber  = 0;
	
}
//Copy constructor
BaseInPoint::BaseInPoint(BaseInPoint&cl)
{
	chMaxIteratoin = cl.chMaxIteratoin;
	chIteration    = cl.chIteration   ;
	chState        = cl.chState       ;
	chReqCalc      = cl.chReqCalc     ;
	shOrderNumber  = ++shOrdNumBaseInPoint;
}
BaseInPoint::BaseInPoint(char chM = 0,char chI = 0,char chS = 0,char chR =0)
{
	chMaxIteratoin = chM;
	chIteration    = chI;
	chState        = chS;
	chReqCalc      = chR;
	shOrderNumber  = ++shOrdNumBaseInPoint;
}
//Copy assignment
BaseInPoint& BaseInPoint::operator= (const BaseInPoint&cl)
{
	chMaxIteratoin = cl.chMaxIteratoin;
	chIteration    = cl.chIteration   ;
	chState        = cl.chState       ;
	chReqCalc      = cl.chReqCalc     ;
	shOrderNumber  = ++shOrdNumBaseInPoint;
	return *this;
}

//Move constructor

//Move assignment

BaseInPoint::~BaseInPoint(void)
{
}
